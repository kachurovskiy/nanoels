// HMI (Nextion) <-> host bridge for ESP32-C3.
// - Forwards Nextion serial traffic to the main controller and back.
// - Emits synthetic Nextion touch events from physical buttons.
// Adjust pins and button mapping for your wiring.

#include <Arduino.h>

// UART settings (115200 8N1 to match h5 firmware).
const uint32_t UART_BAUD = 115200;

// Host (main controller) UART pins.
const int HOST_RX_PIN = 4;
const int HOST_TX_PIN = 5;

// Nextion screen UART pins.
const int SCREEN_RX_PIN = 6;
const int SCREEN_TX_PIN = 7;

// Debounce time for physical buttons.
const uint32_t BUTTON_DEBOUNCE_MS = 30;

// Optional matrix keypad (e.g. 4x4). Set to false to disable.
const bool MATRIX_ENABLED = true;
const uint32_t MATRIX_DEBOUNCE_MS = 30;
const uint32_t MATRIX_SCAN_INTERVAL_MS = 5;
const bool MATRIX_ACTIVE_LOW = true;
const uint8_t MATRIX_PAGE_ID = 0x00;

const uint8_t MATRIX_ROWS = 4;
const uint8_t MATRIX_COLS = 4;
const uint8_t MATRIX_ROW_PINS[MATRIX_ROWS] = {12, 13, 18, 19};
const uint8_t MATRIX_COL_PINS[MATRIX_COLS] = {20, 21, 22, 23};

// Component IDs are from h5/h5.ino HEX_TO_KEYCODE table (page 0).
const uint8_t MATRIX_COMPONENT_IDS[MATRIX_ROWS][MATRIX_COLS] = {
  {27, 28, 29, 25}, // 1 2 3 On/Enter
  {30, 31, 32, 42}, // 4 5 6 Plus
  {33, 34, 35, 43}, // 7 8 9 Minus
  {24, 26, 3, 4},   // Backspace 0 Off/Esc Mode
};

struct ButtonConfig {
  uint8_t pin;
  uint8_t pageId;
  uint8_t componentId;
  bool activeLow;
};

// Map physical buttons to Nextion component IDs.
// Component IDs are from h5/h5.ino HEX_TO_KEYCODE table (page 0).
const ButtonConfig BUTTONS[] = {
  {2, 0x00, 48, true}, // Left
  {3, 0x00, 49, true}, // Right
  {8, 0x00, 44, true}, // Up
  {9, 0x00, 45, true}, // Down
  {10, 0x00, 25, true}, // On/Enter
  {11, 0x00, 3, true}, // Off/Esc
};

struct ButtonState {
  bool lastStable;
  bool lastRead;
  uint32_t lastChangeMs;
};

constexpr size_t BUTTON_COUNT = sizeof(BUTTONS) / sizeof(BUTTONS[0]);
ButtonState buttonStates[BUTTON_COUNT];

HardwareSerial hostSerial(0);
HardwareSerial screenSerial(1);

struct KeyState {
  bool lastStable;
  bool lastRead;
  uint32_t lastChangeMs;
};

KeyState matrixStates[MATRIX_ROWS][MATRIX_COLS];
uint32_t lastMatrixScanMs = 0;

void sendTouchEvent(uint8_t pageId, uint8_t componentId, bool pressed) {
  uint8_t msg[7] = {0x65, pageId, componentId, static_cast<uint8_t>(pressed ? 1 : 0), 0xFF, 0xFF, 0xFF};
  hostSerial.write(msg, sizeof(msg));
}

void pollButtons() {
  const uint32_t now = millis();
  for (size_t i = 0; i < BUTTON_COUNT; i++) {
    const ButtonConfig& cfg = BUTTONS[i];
    bool raw = digitalRead(cfg.pin);
    if (cfg.activeLow) raw = !raw;

    ButtonState& st = buttonStates[i];
    if (raw != st.lastRead) {
      st.lastRead = raw;
      st.lastChangeMs = now;
    }

    if ((now - st.lastChangeMs) >= BUTTON_DEBOUNCE_MS && raw != st.lastStable) {
      st.lastStable = raw;
      sendTouchEvent(cfg.pageId, cfg.componentId, raw);
    }
  }
}

void bridgeStream(HardwareSerial& from, HardwareSerial& to) {
  while (from.available() > 0) {
    to.write(from.read());
  }
}

void setAllRows(bool level) {
  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    digitalWrite(MATRIX_ROW_PINS[r], level ? HIGH : LOW);
  }
}

void initMatrix() {
  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    pinMode(MATRIX_ROW_PINS[r], OUTPUT);
  }
  for (uint8_t c = 0; c < MATRIX_COLS; c++) {
    pinMode(MATRIX_COL_PINS[c], MATRIX_ACTIVE_LOW ? INPUT_PULLUP : INPUT);
  }

  setAllRows(true);
  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    digitalWrite(MATRIX_ROW_PINS[r], LOW);
    delayMicroseconds(5);
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
      bool raw = digitalRead(MATRIX_COL_PINS[c]);
      if (MATRIX_ACTIVE_LOW) raw = !raw;
      matrixStates[r][c] = {raw, raw, millis()};
    }
    digitalWrite(MATRIX_ROW_PINS[r], HIGH);
  }
}

void pollMatrix() {
  if (!MATRIX_ENABLED) return;
  const uint32_t now = millis();
  if (now - lastMatrixScanMs < MATRIX_SCAN_INTERVAL_MS) return;
  lastMatrixScanMs = now;

  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    setAllRows(true);
    digitalWrite(MATRIX_ROW_PINS[r], LOW);
    delayMicroseconds(5);
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
      bool raw = digitalRead(MATRIX_COL_PINS[c]);
      if (MATRIX_ACTIVE_LOW) raw = !raw;

      KeyState& st = matrixStates[r][c];
      if (raw != st.lastRead) {
        st.lastRead = raw;
        st.lastChangeMs = now;
      }

      if ((now - st.lastChangeMs) >= MATRIX_DEBOUNCE_MS && raw != st.lastStable) {
        st.lastStable = raw;
        uint8_t componentId = MATRIX_COMPONENT_IDS[r][c];
        if (componentId != 0) {
          sendTouchEvent(MATRIX_PAGE_ID, componentId, raw);
        }
      }
    }
    digitalWrite(MATRIX_ROW_PINS[r], HIGH);
  }
}

void setup() {
#if ARDUINO_USB_CDC_ON_BOOT
  Serial.begin(115200);
  Serial.println("ESP32-C3 HMI bridge starting");
#endif

  hostSerial.begin(UART_BAUD, SERIAL_8N1, HOST_RX_PIN, HOST_TX_PIN);
  screenSerial.begin(UART_BAUD, SERIAL_8N1, SCREEN_RX_PIN, SCREEN_TX_PIN);

  for (size_t i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BUTTONS[i].pin, BUTTONS[i].activeLow ? INPUT_PULLUP : INPUT);
    bool raw = digitalRead(BUTTONS[i].pin);
    if (BUTTONS[i].activeLow) raw = !raw;
    buttonStates[i] = {raw, raw, millis()};
  }

  if (MATRIX_ENABLED) initMatrix();
}

void loop() {
  bridgeStream(screenSerial, hostSerial);
  bridgeStream(hostSerial, screenSerial);
  pollButtons();
  pollMatrix();
}

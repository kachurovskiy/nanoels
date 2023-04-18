// https://github.com/kachurovskiy/nanoels

/* Change values in this section to suit your hardware. */

// Define your hardware parameters here. Don't remove the ".0" at the end.
#define ENCODER_STEPS 600.0 // 600 step spindle optical rotary encoder
#define MOTOR_STEPS 200.0
#define LEAD_SCREW_DU 20000.0 // 2mm lead screw in deci-microns (10^-7) of a meter

// Spindle rotary encoder pins. Swap values if the rotation direction is wrong.
#define ENC_A 15
#define ENC_B 7

// Stepper pulse and acceleration constants.
#define PULSE_MIN_US round(500.0 * 200.0 / MOTOR_STEPS) // Microseconds to wait after high pulse, min.
#define PULSE_MAX_US round(2000.0 * 200.0 / MOTOR_STEPS) // Microseconds to wait after high pulse, max. Slow start.
#define ACCELERATION 20
#define INVERT_STEPPER false // change (true/false) if the carriage moves e.g. "left" when you press "right".
#define DISABLE_STEPPER_WHEN_RESTING false

/* Changing anything below shouldn't be needed for basic use. */

#define LONG_MIN long(-2147483648)
#define LONG_MAX long(2147483647)

#define LOOP_COUNTER_MAX 1500 // 1500 loops without stepper move to start reading buttons
#define DUPR_MAX long(100000) // 10mm
#define STARTS_MAX 124 // No more than 124-start thread

// Ratios between spindle and stepper.
#define ENCODER_TO_STEPPER_STEP_RATIO MOTOR_STEPS / (LEAD_SCREW_DU * ENCODER_STEPS)
#define STEPPER_TO_ENCODER_STEP_RATIO LEAD_SCREW_DU * ENCODER_STEPS / MOTOR_STEPS

// If time between encoder ticks is less than this, direction change is not allowed.
// Effectively this limits direction change to the time when spindle is <20rpm.
#define DIR_CHANGE_DIFF_MICROS (int) (5000 * ENCODER_STEPS / 600)

// Version of the EEPROM storage format, should be changed when non-backward-compatible
// changes are made to the storage logic, resulting in EEPROM wipe on first start.
#define EEPROM_VERSION 1

// To be incremented whenever a measurable improvement is made.
#define SOFTWARE_VERSION 1

// To be changed whenever a different PCB / encoder / stepper / ... design is used.
#define HARDWARE_VERSION 4

#define Z_ENA 16
#define Z_DIR 17
#define Z_STEP 18

#define X_ENA 8
#define X_DIR 19
#define X_STEP 20

#define OVERALL_ENABLE 3

#define INT 4
#define SCL 5
#define SDA 6

#define B_LEFT 57
#define B_RIGHT 37
#define B_UP 47
#define B_DOWN 67
#define B_MINUS 5
#define B_PLUS 64
#define B_ON 17
#define B_OFF 27
#define B_STOPL 7
#define B_STOPR 15
#define B_STOPU 6
#define B_STOPD 16
#define B_DISPL 43
#define B_STEP 24
#define B_SETTINGS 34
#define B_MEASURE 54
#define B_REVERSE 44
#define B_0 51
#define B_1 41
#define B_2 61
#define B_3 31
#define B_4 2
#define B_5 21
#define B_6 12
#define B_7 11
#define B_8 22
#define B_9 1
#define B_BACKSPACE 32
#define B_MODE_GEARS 42
#define B_MODE_TURN 52
#define B_MODE_FACE 62
#define B_MODE_CONE 3
#define B_MODE_CUT 13
#define B_MODE_THREAD 23
#define B_MODE_OTHER 33
#define B_X_0 53
#define B_X_ENA 4
#define B_Z_0 63
#define B_Z_ENA 14

#define ADDR_EEPROM_VERSION 0 // takes 1 byte
#define ADDR_DUPR 2 // takes 4 bytes
#define ADDR_POS 6 // takes 4 bytes
#define ADDR_LEFT_STOP 10 // takes 4 bytes
#define ADDR_RIGHT_STOP 14 // takes 4 bytes
#define ADDR_SPINDLE_POS 18 // takes 4 bytes
#define ADDR_OUT_OF_SYNC 22 // takes 2 bytes
#define ADDR_SHOW_ANGLE 24 // takes 1 byte
#define ADDR_SHOW_TACHO 25 // takes 1 byte
#define ADDR_MOVE_STEP 26 // takes 2 bytes
#define ADDR_STARTS 28 // takes 2 bytes
#define ADDR_MODE 30 // takes 2 bytes
#define ADDR_MEASURE 32 // takes 2 bytes

#define MOVE_STEP_1 10000 // 1mm
#define MOVE_STEP_2 1000 // 0.1mm
#define MOVE_STEP_3 100 // 0.01mm
#define MOVE_STEP_4 10 // 1 micron
#define MOVE_STEP_IMP_1 25400 // 1/10"
#define MOVE_STEP_IMP_2 2540 // 1/100"
#define MOVE_STEP_IMP_3 254 // 1/1000" also known as 1 thou

#define MODE_NORMAL 0
#define MODE_MULTISTART 1
#define MODE_ASYNC 2

#define MEASURE_METRIC 0
#define MEASURE_INCH 1
#define MEASURE_TPI 2

// For MEASURE_TPI, round TPI to the nearest integer if it's within this range of it.
// E.g. 80.02tpi would be shown as 80tpi but 80.04tpi would be shown as-is.
#define TPI_ROUND_EPSILON 0.03

#define RPM_BULK ENCODER_STEPS // Measure RPM averaged over this number of encoder pulses
#define RPM_UPDATE_INTERVAL_MICROS 1000000 // Don't redraw RPM more often than once per second

// Uncomment to print out debug info in Serial.
// #define DEBUG

#define DREAD(x) digitalRead(x)
#define DHIGH(x) digitalWrite(x, HIGH)
#define DLOW(x) digitalWrite(x, LOW)

#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(45, 48, 47, 38, 39, 40, 41, 42, 2, 1);
long lcdHash = 0;

#include <EEPROM.h>

#include <Adafruit_TCA8418.h>
Adafruit_TCA8418 keypad;

// Most buttons we only have "down" handling, holding them has no effect.
// Buttons with special "holding" logic have flags below.
bool buttonLeftPressed = false;
bool buttonRightPressed = false;
bool buttonUpPressed = false;
bool buttonDownPressed = false;
bool buttonOffPressed = false;
bool inNumpad = false;
int numpadDigits[6];
int numpadIndex = 0;

unsigned long buttonDownTime = 0;
unsigned long buttonUpTime = 0;
int buttonId = 0;
volatile long loopCounter = 0;
int buttonLoopCounter = 0;
bool isOn = false;
unsigned long resetMillis = 0;
bool resetOnStartup = false;
bool emergencyStop = false;

volatile long dupr = 0; // pitch, tenth of a micron per rotation
long savedDupr = 0; // dupr saved in EEPROM

int starts = 1; // number of starts in a multi-start thread
int savedStarts = 0; // starts saved in EEPROM

volatile long pos = 0; // relative position of the stepper motor, in steps
long savedPos = 0; // value saved in EEPROM
float fractionalPos = 0.0; // fractional distance in steps that we meant to travel but couldn't

volatile long leftStop = 0; // left stop value of pos
long savedLeftStop = 0; // value saved in EEPROM
bool leftStopFlag = true; // prevent toggling the stop while button is pressed.

volatile long rightStop = 0; // right stop value of pos
long savedRightStop = 0; // value saved in EEPROM
bool rightStopFlag = true; // prevent toggling the stop while button is pressed.

volatile unsigned long spindleEncTime = 0; // micros() of the previous spindle update
volatile unsigned long spindleEncTimeDiff = 0; // micros() since the previous spindle update
volatile unsigned long spindleEncTimeDiffBulk = 0; // micros() between RPM_BULK spindle updates
volatile unsigned long spindleEncTimeAtIndex0 = 0; // micros() when spindleEncTimeIndex was 0
volatile int spindleEncTimeIndex = 0; // counter going between 0 and RPM_BULK - 1
volatile int spindleDeltaPrev = 0; // Previously detected spindle direction
volatile long spindlePos = 0; // Spindle position
long savedSpindlePos = 0; // spindlePos value saved in EEPROM
long spindleLeftStop = 0;
long spindleRightStop = 0;

volatile int spindlePosSync = 0;
int savedSpindlePosSync = 0;

volatile int stepDelayUs = PULSE_MAX_US;
volatile bool stepDelayDirection = true; // To reset stepDelayUs when direction changes.
volatile bool stepDirectionInitialized = false;
volatile unsigned long stepStartMicros = 0;
int stepperEnableCounter = 0;
bool manualEnableFlag = !DISABLE_STEPPER_WHEN_RESTING;

bool showAngle = false; // Whether to show 0-359 spindle angle on screen
bool showTacho = false; // Whether to show spindle RPM on screen
bool savedShowAngle = false; // showAngle value saved in EEPROM
bool savedShowTacho = false; // showTacho value saved in EEPROM
int shownRpm = 0;
unsigned long shownRpmTime = 0; // micros() when shownRpm was set

int moveStep = 0; // thousandth of a mm
int savedMoveStep = 0; // moveStep saved in EEPROM
volatile bool movingManually = false; // whether stepper is being moved by left/right buttons

volatile int mode = -1; // mode of operation (ELS, multi-start ELS, asynchronous)
int savedMode = -1; // mode saved in EEPROM

int measure = MEASURE_METRIC; // Whether to show distances in inches
int savedMeasure = MEASURE_METRIC; // measure value saved in EEPROM

hw_timer_t *async_timer = timerBegin(0, 80, true);

int getApproxRpm() {
  if (!showTacho) {
    return 0;
  }
  unsigned long t = micros();
  if (t > spindleEncTime + 100000) {
    // RPM less than 10.
    return 0;
  }
  if (t < shownRpmTime + RPM_UPDATE_INTERVAL_MICROS) {
    // Don't update RPM too often to avoid flickering.
    return shownRpm;
  }
  int rpm = 0;
  if (spindleEncTimeDiffBulk > 0) {
    rpm = 60000000 / spindleEncTimeDiffBulk;
    if (abs(rpm - shownRpm) < (rpm < 1000 ? 2 : 5)) {
      // Don't update RPM with insignificant differences.
      rpm = shownRpm;
    }
  }
  return rpm;
}

bool stepperIsRunning() {
  return micros() - stepStartMicros < 10000;
}

void printMicrons(long deciMicrons) {
  if (deciMicrons == 0) {
    lcd.print("0");
    return;
  }
  bool imperial = measure != MEASURE_METRIC;
  long v = imperial ? round(deciMicrons / 25.4) : deciMicrons;
  int points = 0;
  if (v == 0) {
    points = 5;
  } else if ((v % 10) != 0) {
    points = 4;
  } else if ((v % 100) != 0) {
    points = 3;
  } else if ((v % 1000) != 0) {
    points = 2;
  } else if ((v % 10000) != 0) {
    points = 1;
  }
  lcd.print(deciMicrons / (imperial ? 254000.0 : 10000.0), points);
  lcd.print(imperial ? "\"" : "mm");
}

void printDupr(long value) {
  if (measure != MEASURE_TPI) {
    printMicrons(value);
  } else {
    float tpi = 254000.0 / value;
    if (abs(tpi - round(tpi)) < TPI_ROUND_EPSILON) {
      lcd.print(int(round(tpi)));
    } else {
      int tpi100 = round(tpi * 100);
      int points = 0;
      if ((tpi100 % 10) != 0) {
        points = 2;
      } else if ((tpi100 % 100) != 0) {
        points = 1;
      }
      lcd.print(tpi, points);
    }
    lcd.print("tpi");
  }
}

void updateDisplay(bool beforeRunning) {
  if (emergencyStop) {
    return;
  }
  int rpm = getApproxRpm();
  // Hide rows 3 and 4 if ON and about to or is already moving.
  // Not hiding when off since it results in flickering of rows 3 and 4 during short manual moves.
  bool running = isOn && (beforeRunning || stepperIsRunning());
  long numpadDupr = numpadToDupr();
  // Sum of values affecting rows 1 and 2 of the LCD.
  long hashRows12 = dupr + isOn * 2 + leftStop / 3
                    + rightStop / 4 + spindlePosSync * 5 + resetOnStartup * 6
                    + moveStep * 7 + running * 8 + starts * 12 + mode * 13 + measure * 14;
  // Sum of values affecting rows 3 and 4 of the LCD.
  long hashRows34 = pos * 9 + showAngle * 10 + (showTacho ? rpm : -1) * 11 + measure * 14 + numpadDupr;
  // Ignore changes in hashRows34 when stepper is running since they aren't shown.
  long newLcdHash = hashRows12 + (running ? 0 : hashRows34);
  // Don't show angle if stepper is running or spindle is turning.
  bool spindleStopped = micros() > spindleEncTime + 100000;
  if (!running && showAngle && spindleStopped) {
    newLcdHash += spindlePos;
  }

  // Don't spend 40ms and flicker the screen if nothing changed.
  if (newLcdHash == lcdHash) {
    return;
  }

  lcdHash = newLcdHash;
  lcd.clear();

  // First row.
  lcd.setCursor(0, 0);
  if (mode == MODE_MULTISTART) {
    lcd.print("MUL ");
  } else if (mode == MODE_ASYNC) {
    lcd.print("ASY ");
  }
  lcd.print(isOn ? "ON" : "off");
  if (leftStop != LONG_MAX && rightStop != LONG_MIN) {
    lcd.print(" LR");
  } else if (leftStop != LONG_MAX) {
    lcd.print(" L");
  } else if (rightStop != LONG_MIN) {
    lcd.print("  R");
  }

  if (spindlePosSync) {
    lcd.print(" SYN");
  }
  if (resetOnStartup) {
    lcd.print(" LTW");
  }
  if (mode == MODE_NORMAL && !resetOnStartup && !spindlePosSync) {
    lcd.print(" step ");
  } else {
    lcd.print(" ");
  }
  printMicrons(moveStep);

  // Second row.
  lcd.setCursor(0, 1);
  lcd.print("Pitch ");
  printDupr(dupr);
  if (starts != 1) {
    lcd.print(" x");
    lcd.print(starts);
  }

  if (running) {
    // Stepper is running, updateDisplay() will no longer be called soon,
    // don't draw position, RPM and angle that won't be accurate shortly.
    return;
  }

  // Third row.
  lcd.setCursor(0, 2);
  lcd.print("Position ");
  printMicrons(round(pos * LEAD_SCREW_DU / MOTOR_STEPS));

  // Fourth row.
  lcd.setCursor(0, 3);
  if (numpadDupr != 0) {
    lcd.print("Use ");
    printDupr(numpadDupr);
    lcd.print("?");
  } else if (showAngle) {
    lcd.print("Angle ");
    if (spindleStopped) {
      lcd.print(((spindlePos % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS) * 360 / ENCODER_STEPS, 2);
      lcd.print(char(223));
    }
  } else if (showTacho) {
    lcd.print("Tacho ");
    lcd.print(rpm);
    if (shownRpm != rpm) {
      shownRpm = rpm;
      shownRpmTime = micros();
    }
    lcd.print("rpm");
  }
}

void saveInt(int i, int v) {
  // Can't concatenate all in one line due to compiler problems, same throughout the code.
#ifdef DEBUG
  Serial.print("Saving int at ");
  Serial.print(i);
  Serial.print(" = ");
  Serial.println(v);
#endif
  EEPROM.write(i, v >> 8 & 0xFF);
  EEPROM.write(i + 1, v & 0xFF);
}
int loadInt(int i) {
  // 255 is the default value when nothing was written before.
  if (EEPROM.read(i) == 255 && EEPROM.read(i + 1) == 255) {
    return 0;
  }
  return (EEPROM.read(i) << 8) + EEPROM.read(i + 1);
}
void saveLong(int i, long v) {
#ifdef DEBUG
  Serial.print("Saving long at ");
  Serial.print(i);
  Serial.print(" = ");
  Serial.println(v);
#endif
  EEPROM.write(i, v >> 24 & 0xFF);
  EEPROM.write(i + 1, v >> 16 & 0xFF);
  EEPROM.write(i + 2, v >> 8 & 0xFF);
  EEPROM.write(i + 3, v & 0xFF);
}
long loadLong(int i) {
  long p0 = EEPROM.read(i);
  long p1 = EEPROM.read(i + 1);
  long p2 = EEPROM.read(i + 2);
  long p3 = EEPROM.read(i + 3);
  // 255 is the default value when nothing was written before.
  if (p0 == 255 && p1 == 255 && p2 == 255 && p3 == 255) {
    return 0;
  }
  return (p0 << 24) + (p1 << 16) + (p2 << 8) + p3;
}

// Called on a FALLING interrupt for the spindle rotary encoder pin.
// Keeps track of the spindle position.
void spinEnc() {
  unsigned long microsNow = micros();
  if (spindleEncTimeIndex == 0) {
    spindleEncTimeDiffBulk = microsNow - spindleEncTimeAtIndex0;
    spindleEncTimeAtIndex0 = microsNow;
  }
  spindleEncTimeIndex = (spindleEncTimeIndex + 1) % int(RPM_BULK);

  int delta;
  spindleEncTimeDiff = microsNow - spindleEncTime;
  if (spindleEncTimeDiff > DIR_CHANGE_DIFF_MICROS || !stepDirectionInitialized) {
    delta = DREAD(ENC_B) ? -1 : 1;
    spindleDeltaPrev = delta;
  } else {
    // Spindle is going fast, unlikely to change direction momentarily.
    delta = spindleDeltaPrev;
  }
  spindlePos += delta;
  spindleEncTime = microsNow;

  if (spindlePosSync != 0) {
    spindlePosSync += delta;
    if (spindlePosSync == 0 || spindlePosSync == ENCODER_STEPS) {
      spindlePosSync = 0;
      spindlePos = spindleFromPos(pos);
    }
  }
}

void setAsyncTimerEnable(bool value) {
  if (value) {
    timerAlarmEnable(async_timer);
  } else {
    timerAlarmDisable(async_timer);
  }
}

void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  pinMode(Z_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT);
  pinMode(Z_ENA, OUTPUT);
  DHIGH(Z_STEP);

  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(X_ENA, OUTPUT);
  DHIGH(X_STEP);

  EEPROM.begin(256);
  // Wipe EEPROM if this is the first start after uploading a new build.
  if (EEPROM.read(ADDR_EEPROM_VERSION) != EEPROM_VERSION) {
    for (int i = 0; i < 256; i++) {
      EEPROM.write(i, 255); // 255 is the default value.
    }
    EEPROM.write(ADDR_EEPROM_VERSION, EEPROM_VERSION);
    saveLong(ADDR_LEFT_STOP, savedLeftStop = leftStop = LONG_MAX);
    saveLong(ADDR_RIGHT_STOP, savedRightStop = rightStop = LONG_MIN);
    saveInt(ADDR_MOVE_STEP, MOVE_STEP_1);
  }

  isOn = false;
  savedDupr = dupr = loadLong(ADDR_DUPR);
  savedStarts = starts = min(STARTS_MAX, max(1, loadInt(ADDR_STARTS)));
  savedPos = pos = loadLong(ADDR_POS);
  savedLeftStop = leftStop = loadLong(ADDR_LEFT_STOP);
  savedRightStop = rightStop = loadLong(ADDR_RIGHT_STOP);
  savedSpindlePos = spindlePos = loadLong(ADDR_SPINDLE_POS);
  savedSpindlePosSync = spindlePosSync = loadInt(ADDR_OUT_OF_SYNC);
  savedShowAngle = showAngle = EEPROM.read(ADDR_SHOW_ANGLE) == 1;
  savedShowTacho = showTacho = EEPROM.read(ADDR_SHOW_TACHO) == 1;
  savedMoveStep = loadInt(ADDR_MOVE_STEP);
  moveStep = savedMoveStep > 0 ? savedMoveStep : MOVE_STEP_1;
  savedMode = loadInt(ADDR_MODE);
  savedMeasure = measure = loadInt(ADDR_MEASURE);
  setMode(savedMode);

  if (DISABLE_STEPPER_WHEN_RESTING) {
    stepperEnable(isOn);
  } else {
    DHIGH(Z_ENA);
  }

  lcd.begin(20, 4);
  updateDisplay(false /*beforeRunning*/);

  Serial.begin(115200);
  // During first second prints don't show up in Serial Monitor.
  delay(1000);
  Serial.print("NanoEls H");
  Serial.print(HARDWARE_VERSION);
  Serial.print(" V");
  Serial.println(SOFTWARE_VERSION);

  if (!Wire.begin(SDA, SCL)) {
    Serial.println("I2C initialization failed");
  } else if (!keypad.begin(TCA8418_DEFAULT_ADDR, &Wire)) {
    Serial.println("TCA8418 key controller not found");
  } else {
    keypad.matrix(7, 7);
    keypad.enableDebounce();
    keypad.flush();
  }

  delay(100);
  if (keypad.available()) {
    emergencyStop = true;
    setAsyncTimerEnable(false);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Key down at power-up");
    lcd.setCursor(0, 1);
    lcd.print("Hardware failure?");
    return;
  }

  attachInterrupt(digitalPinToInterrupt(ENC_A), spinEnc, FALLING);

  pinMode(OVERALL_ENABLE, OUTPUT);
  DHIGH(OVERALL_ENABLE);
}

// Saves all positions in EEPROM, should be called infrequently to reduce EEPROM wear.
void saveIfChanged() {
  bool changed = false;
  if (dupr != savedDupr) {
    saveLong(ADDR_DUPR, savedDupr = dupr);
    changed = true;
  }
  if (starts != savedStarts) {
    saveInt(ADDR_STARTS, savedStarts = starts);
    changed = true;
  }
  if (pos != savedPos) {
    saveLong(ADDR_POS, savedPos = pos);
    changed = true;
  }
  if (leftStop != savedLeftStop) {
    saveLong(ADDR_LEFT_STOP, savedLeftStop = leftStop);
    changed = true;
  }
  if (rightStop != savedRightStop) {
    saveLong(ADDR_RIGHT_STOP, savedRightStop = rightStop);
    changed = true;
  }
  if (spindlePos != savedSpindlePos) {
    saveLong(ADDR_SPINDLE_POS, savedSpindlePos = spindlePos);
    changed = true;
  }
  if (spindlePosSync != savedSpindlePosSync) {
    saveInt(ADDR_OUT_OF_SYNC, savedSpindlePosSync = spindlePosSync);
    changed = true;
  }
  if (showAngle != savedShowAngle) {
    EEPROM.write(ADDR_SHOW_ANGLE, savedShowAngle = showAngle);
    changed = true;
  }
  if (showTacho != savedShowTacho) {
    EEPROM.write(ADDR_SHOW_TACHO, savedShowTacho = showTacho);
    changed = true;
  }
  if (moveStep != savedMoveStep) {
    saveInt(ADDR_MOVE_STEP, savedMoveStep = moveStep);
    changed = true;
  }
  if (mode != savedMode) {
    saveInt(ADDR_MODE, savedMode = mode);
    changed = true;
  }
  if (measure != savedMeasure) {
    saveInt(ADDR_MEASURE, savedMeasure = measure);
    changed = true;
  }
  if (changed) {
    EEPROM.commit();
  }
}

// Loose the thread and mark current physical positions of
// encoder and stepper as a new 0. To be called when dupr changes
// or ELS is turned on/off. Without this, changing dupr will
// result in stepper rushing across the lathe to the new position.
void markAsZero() {
  noInterrupts();
  if (leftStop != LONG_MAX) {
    leftStop -= pos;
  }
  if (rightStop != LONG_MIN) {
    rightStop -= pos;
  }
  pos = 0;
  fractionalPos = 0;
  spindlePos = 0;
  spindlePosSync = 0;
  interrupts();
}

void updateAsyncTimerSettings() {
  // dupr and therefore direction can change while we're in async mode.
  setDir(dupr > 0);

  // dupr can change while we're in async mode, keep updating timer frequency.
  timerAlarmWrite(async_timer, getTimerLimit(), true);
}

void setDupr(long value) {
  dupr = value;
  markAsZero();
  // Printing new pitch can stall the motor due to time spent on it. Don't have time to even clear the LCD.
  if (!stepperIsRunning()) {
    updateDisplay(false /*beforeRunning*/);
  }
  if (mode == MODE_ASYNC) {
    updateAsyncTimerSettings();
  }
}

void setStarts(int value) {
  if (starts == value) {
    return;
  }
  starts = value;
  markAsZero();
  // Printing new pitch can stall the motor due to time spent on it. Don't have time to even clear the LCD.
  if (!stepperIsRunning()) {
    updateDisplay(false /*beforeRunning*/);
  }
}

void setMeasure(int value) {
  if (measure == value) {
    return;
  }
  measure = value;
  moveStep = measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1;
}

void splashScreen() {
#ifndef TEST
  lcd.clear();
  lcd.setCursor(6, 1);
  lcd.print("NanoEls");
  lcd.setCursor(6, 2);
  lcd.print("H" + String(HARDWARE_VERSION) + " V" + String(SOFTWARE_VERSION));
  lcdHash = 0;
  delay(2000);
#endif
}

unsigned int getTimerLimit() {
  if (dupr == 0) {
    return 65535;
  }
  return min(long(65535), long(1000000 / (MOTOR_STEPS * abs(dupr) / LEAD_SCREW_DU)) - 1); // 1000000/Hz - 1
}

// Only used for async movement.
// Keep code in this method to absolute minimum to achieve high stepper speeds.
void IRAM_ATTR onAsyncTimer() {
  if (!isOn || movingManually) {
    return;
  } else if (dupr > 0 && (leftStop == LONG_MAX || pos < leftStop)) {
    pos++;
  } else if (dupr < 0 && (rightStop == LONG_MIN || pos > rightStop)) {
    pos--;
  } else {
    return;
  }

  DLOW(Z_STEP);
  stepStartMicros = micros();
  loopCounter = 0;
  delayMicroseconds(10);
  DHIGH(Z_STEP);
}

void setMode(int value) {
  if (mode == value) {
    return;
  }
  if (mode == MODE_MULTISTART) {
    setStarts(1);
  } else if (mode == MODE_ASYNC) {
    setAsyncTimerEnable(false);
  }
  mode = value;
  markAsZero();
  if (mode == MODE_ASYNC) {
    if (isOn) {
      updateDisplay(true /*beforeRunning*/);
    }

    timerAttachInterrupt(async_timer, &onAsyncTimer, true);
    updateAsyncTimerSettings();
    setAsyncTimerEnable(true);
  } else if (mode == MODE_MULTISTART) {
    if (starts < 2) {
      setStarts(2);
    }
  }
}

void reset() {
  resetOnStartup = false;
  leftStop = LONG_MAX;
  rightStop = LONG_MIN;
  setDupr(0);
  setStarts(1);
  moveStep = MOVE_STEP_1;
  setMode(MODE_NORMAL);
  measure = MEASURE_METRIC;
  splashScreen();
}

// Called when left/right stop restriction is removed while we're on it.
// Prevents stepper from rushing to a position far away by waiting for the right
// spindle position and starting smoothly.
void setOutOfSync() {
  if (!isOn || mode == MODE_ASYNC) {
    return;
  }
  spindlePosSync = ((spindlePos - spindleFromPos(pos)) % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS;
#ifdef DEBUG
  Serial.print("spindlePosSync ");
  Serial.println(spindlePosSync);
#endif
}

long normalizePitch(long pitch) {
  int scale = 1;
  if (measure == MEASURE_METRIC) {
    // Keep the 3rd precision point only if we're in the micron mode.
    // Always drop the 4th precision point if any.
    scale = moveStep == MOVE_STEP_4 ? 10 : 100;
  } else if (measure == MEASURE_INCH) {
    // Always drop the 4th precision point in inch representation if any.
    scale = 254;
  }
  return round(pitch / scale) * scale;
}

void buttonPlusMinusPress(bool plus) {
  bool minus = !plus;
  if (mode == MODE_MULTISTART) {
    if (minus && starts > 2) {
      setStarts(starts - 1);
    } else if (plus && starts < STARTS_MAX) {
      setStarts(starts + 1);
    }
  } else if (measure != MEASURE_TPI) {
    bool isMetric = measure == MEASURE_METRIC;
    int delta = isMetric ? MOVE_STEP_3 : MOVE_STEP_IMP_3;
    if (moveStep == MOVE_STEP_4) {
      // Don't speed up scrolling when on smallest step.
      delta = MOVE_STEP_4;
    }
    // Switching between mm/inch/tpi often results in getting non-0 3rd and 4th
    // precision points that can't be easily controlled. Remove them.
    long normalizedDupr = normalizePitch(dupr);
    if (minus) {
      if (dupr > -DUPR_MAX) {
        setDupr(max(-DUPR_MAX, normalizedDupr - delta));
      }
    } else if (plus) {
      if (dupr < DUPR_MAX) {
        setDupr(min(DUPR_MAX, normalizedDupr + delta));
      }
    }
  } else { // TPI
    if (dupr == 0) {
      setDupr(plus ? 1 : -1);
    } else {
      long currentTpi = round(254000.0 / dupr);
      long tpi = currentTpi + (plus ? 1 : -1);
      long newDupr = newDupr = round(254000.0 / tpi);
      // Happens for small pitches like 0.01mm.
      if (newDupr == dupr) {
        newDupr += plus ? -1 : 1;
      }
      if (newDupr != dupr && newDupr < DUPR_MAX && newDupr > -DUPR_MAX) {
        setDupr(newDupr);
      }
    }
  }
}

void buttonOnOffPress(bool on) {
  resetMillis = millis();
  isOn = on;
  stepperEnable(on);
  updateDisplay(false /*beforeRunning*/);
}

void buttonOffRelease() {
  if (millis() - resetMillis > 4000) {
    reset();
  }
}

void buttonLeftStopPress() {
  if (leftStop == LONG_MAX) {
    leftStop = pos;
  } else {
    if (pos == leftStop) {
      // Spindle is most likely out of sync with the stepper because
      // it was spinning while the lead screw was on the stop.
      setOutOfSync();
    }
    leftStop = LONG_MAX;
  }
}

void buttonRightStopPress() {
  if (rightStop == LONG_MIN) {
    rightStop = pos;
  } else {
    if (pos == rightStop) {
      // Spindle is most likely out of sync with the stepper because
      // it was spinning while the lead screw was on the stop.
      setOutOfSync();
    }
    rightStop = LONG_MIN;
  }
}

bool allowMultiStartAdvance = false;

void nextStart() {
  noInterrupts();
  spindlePos += round(1.0 * ENCODER_STEPS / starts) * (dupr > 0 ? -1 : 1);
  interrupts();
}

void checkIfNextStart() {
  if (starts <= 1 || dupr == 0 || rightStop == LONG_MIN || leftStop == LONG_MAX) {
    return;
  }
  if (allowMultiStartAdvance && pos == (dupr > 0 ? rightStop : leftStop)) {
    nextStart();
    allowMultiStartAdvance = false;
  } else if (pos == (dupr > 0 ? leftStop : rightStop)) {
    allowMultiStartAdvance = true;
  }
}

long getAsyncMovePos(int sign) {
  long posDiff = sign * MOTOR_STEPS * abs(dupr) / LEAD_SCREW_DU / 5;
  if (posDiff > 0 && leftStop != LONG_MAX && (pos + posDiff) > leftStop) {
    return leftStop;
  } else if (posDiff < 0 && rightStop != LONG_MIN && (pos + posDiff) < rightStop) {
    return rightStop;
  }
  return pos + posDiff;
}

void buttonLeftRightUpDownPress() {
  bool left = buttonLeftPressed;
  bool right = buttonRightPressed;
  if (!left && !right) {
    return;
  }
  if (spindlePosSync) {
    // Edge case.
    return;
  }
  int sign = left ? 1 : -1;
  bool stepperOn = true;
  stepperEnable(true);
  if (isOn && dupr != 0) {
    // Move by moveStep in the desired direction but stay in the thread by possibly traveling a little more.
    int diff = ceil(moveStep * 1.0 / abs(dupr * starts)) * ENCODER_STEPS * sign * (dupr > 0 ? 1 : -1);
    long prevSpindlePos = spindlePos;
    bool resting = false;
    movingManually = true;
    do {
      if (mode != MODE_ASYNC) {
        noInterrupts();
        if (!resting) {
          spindlePos += diff;
        }
        // If spindle is moving, it will be changing spindlePos at the same time. Account for it.
        while (diff > 0 ? (spindlePos < prevSpindlePos) : (spindlePos > prevSpindlePos)) {
          spindlePos += diff;
        };
        prevSpindlePos = spindlePos;
        interrupts();
      }

      long newPos = mode == MODE_ASYNC ? getAsyncMovePos(sign) : posFromSpindle(prevSpindlePos, true);
      int posDiff = abs(newPos - pos);
      if (posDiff > 0) {
        step(newPos > pos, posDiff);
      } else if (pos == (left ? leftStop : rightStop)) {
        // We're standing on a stop with the L/R move button pressed.
        resting = true;
        checkIfNextStart();
        if (stepperOn) {
          stepperEnable(false);
          stepperOn = false;
        }
        updateDisplay(false /*beforeRunning*/);
        delay(200);
      }
      processKeypadEvents();
    } while (left ? buttonLeftPressed : buttonRightPressed);
    movingManually = false;
  } else {
    int delta = 0;
    do {
      float fractionalDelta = moveStep * sign / LEAD_SCREW_DU * MOTOR_STEPS + fractionalPos;
      delta = round(fractionalDelta);
      // Don't lose fractional steps when moving by 0.01" or 0.001".
      fractionalPos = fractionalDelta - delta;
      if (delta == 0) {
        // When moveStep is e.g. 1 micron and MOTOR_STEPS is 200, make delta non-zero.
        delta = 1;
      }

      // Don't left-right move out of stops.
      if (leftStop != LONG_MAX && pos + delta > leftStop) {
        delta = leftStop - pos;
      } else if (rightStop != LONG_MIN && pos + delta < rightStop) {
        delta = rightStop - pos;
      }

      step(delta > 0, abs(delta));

      if (moveStep != (measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1)) {
        // Allow some time for the button to be released to
        // make it possible to do single steps at 0.1, 0.01mm and 0.001mm.
        updateDisplay(false /*beforeRunning*/);
        delay(500);
      }
      processKeypadEvents();
    } while (delta != 0 && (left ? buttonLeftPressed : buttonRightPressed));
    if (isOn) {
      // Prevent stepper from jumping back to position calculated from the spindle.
      markAsZero();
    }
  }
  if (stepperOn) {
    stepperEnable(false);
  }
}

void buttonDisplayPress() {
  if (!showAngle && !showTacho) {
    showAngle = true;
  } else if (showAngle) {
    showAngle = false;
    showTacho = true;
  } else {
    showTacho = false;
  }
}

void buttonMoveStepPress() {
  if (measure == MEASURE_METRIC) {
    if (moveStep == MOVE_STEP_1) {
      moveStep = MOVE_STEP_2;
    } else if (moveStep == MOVE_STEP_2) {
      moveStep = MOVE_STEP_3;
    } else if (moveStep == MOVE_STEP_3) {
      moveStep = MOVE_STEP_4;
    } else {
      moveStep = MOVE_STEP_1;
    }
  } else {
    if (moveStep == MOVE_STEP_IMP_1) {
      moveStep = MOVE_STEP_IMP_2;
    } else if (moveStep == MOVE_STEP_IMP_2) {
      moveStep = MOVE_STEP_IMP_3;
    } else {
      moveStep = MOVE_STEP_IMP_1;
    }
  }
}

void setDir(bool dir) {
  // Start slow if direction changed.
  if (stepDelayDirection != dir || !stepDirectionInitialized) {
    stepDelayUs = PULSE_MAX_US;
    stepDelayDirection = dir;
    stepDirectionInitialized = true;
    if (dir ^ INVERT_STEPPER) {
      DHIGH(Z_DIR);
    } else {
      DLOW(Z_DIR);
    }
  }
}

void buttonModePress() {
  if (mode == MODE_NORMAL) {
    setMode(MODE_MULTISTART);
  } else if (mode == MODE_MULTISTART) {
    setMode(MODE_ASYNC);
  } else {
    setMode(MODE_NORMAL);
  }
}

void buttonMeasurePress() {
  if (measure == MEASURE_METRIC) {
    setMeasure(MEASURE_INCH);
  } else if (measure == MEASURE_INCH) {
    setMeasure(MEASURE_TPI);
  } else {
    setMeasure(MEASURE_METRIC);
  }
}

void buttonReversePress() {
  setDupr(-dupr);
}

void numpadPress(int digit) {
  if (!inNumpad) {
    numpadIndex = 0;
  }
  numpadDigits[numpadIndex] = digit;
  if (numpadIndex < sizeof(numpadDigits) - 1) {
    numpadIndex++;
  } else {
    numpadIndex = 0;
  }
}

void numpadBackspace() {
  if (inNumpad && numpadIndex > 0) {
    numpadIndex--;
  }
}

void resetNumpad() {
  numpadIndex = 0;
}

long getNumpadResult() {
  long result = 0;
  for (int i = 0; i < numpadIndex; i++) {
    result += numpadDigits[i] * pow(10, numpadIndex - 1 - i);
  }
  return result;
}

long numpadToDupr() {
  long result = getNumpadResult();
  if (result == 0) {
    return 0;
  }
  if (measure == MEASURE_INCH) {
    result = result * 254;
  } else if (measure == MEASURE_TPI) {
    result = round(254000.0 / result);
  } else { // Metric
    result = result * 10;
  }
  return result;
}

void processKeypadEvents() {
  while (keypad.available() > 0) {
    int event = keypad.getEvent();
    int keyCode = event;
    bitWrite(keyCode, 7, 0);
    bool isPress = bitRead(event, 7) == 1; // 1 - press, 0 - release
    if (keyCode == B_OFF) {
      buttonOffPressed = isPress;
      isPress ? buttonOnOffPress(false) : buttonOffRelease();
    } else if (keyCode == B_LEFT) {
      buttonLeftPressed = isPress;
      if (isPress) buttonLeftRightUpDownPress();
    } else if (keyCode == B_RIGHT) {
      buttonRightPressed = isPress;
      if (isPress) buttonLeftRightUpDownPress();
    } else if (keyCode == B_UP) {
      buttonUpPressed = isPress;
      if (isPress) buttonLeftRightUpDownPress();
    } else if (keyCode == B_DOWN) {
      buttonDownPressed = isPress;
      if (isPress) buttonLeftRightUpDownPress();
    }

    // For all other keys we have no "release" logic.
    if (!isPress) {
      continue;
    }

    // Numpad separately to lower inNumpad when non-numeric key is pressed.
    if (keyCode == B_0) {
      numpadPress(0);
      inNumpad = true;
    } else if (keyCode == B_1) {
      numpadPress(1);
      inNumpad = true;
    } else if (keyCode == B_2) {
      numpadPress(2);
      inNumpad = true;
    } else if (keyCode == B_3) {
      numpadPress(3);
      inNumpad = true;
    } else if (keyCode == B_4) {
      numpadPress(4);
      inNumpad = true;
    } else if (keyCode == B_5) {
      numpadPress(5);
      inNumpad = true;
    } else if (keyCode == B_6) {
      numpadPress(6);
      inNumpad = true;
    } else if (keyCode == B_7) {
      numpadPress(7);
      inNumpad = true;
    } else if (keyCode == B_8) {
      numpadPress(8);
      inNumpad = true;
    } else if (keyCode == B_9) {
      numpadPress(9);
      inNumpad = true;
    } else if (keyCode == B_BACKSPACE) {
      numpadBackspace();
      inNumpad = true;
    } else if (inNumpad) {
      inNumpad = false;
      long newDupr = numpadToDupr();
      resetNumpad();
      // Ignore numpad input unless confirmed with ON.
      if (keyCode == B_ON) {
        if (abs(newDupr) <= DUPR_MAX) {
          setDupr(newDupr);
        }
        // Don't use this ON press for starting the motion.
        continue;
      }
    }

    if (keyCode == B_PLUS) {
      buttonPlusMinusPress(true);
    } else if (keyCode == B_MINUS) {
      buttonPlusMinusPress(false);
    } else if (keyCode == B_ON) {
      buttonOnOffPress(true);
    } else if (keyCode == B_STOPL) {
      buttonLeftStopPress();
    } else if (keyCode == B_STOPR) {
      buttonRightStopPress();
    } else if (keyCode == B_STOPU) {
      // TODO.
    } else if (keyCode == B_STOPD) {
      // TODO.
    } else if (keyCode == B_MODE_OTHER) {
      buttonModePress();
    } else if (keyCode == B_DISPL) {
      buttonDisplayPress();
    } else if (keyCode == B_X_0) {
      // TODO.
    } else if (keyCode == B_X_ENA) {
      // TODO.
    } else if (keyCode == B_Z_0) {
      markAsZero();
    } else if (keyCode == B_Z_ENA) {
      manualEnableFlag = !manualEnableFlag;
      stepperEnable(manualEnableFlag);
    } else if (keyCode == B_STEP) {
      buttonMoveStepPress();
    } else if (keyCode == B_SETTINGS) {
      // TODO.
    } else if (keyCode == B_REVERSE) {
      buttonReversePress();
    } else if (keyCode == B_MEASURE) {
      buttonMeasurePress();
    }
  }
}

unsigned long stepStart = 0;
unsigned long stepToStep = PULSE_MIN_US;

// Moves the stepper.
void step(bool dir, long steps) {
  setDir(dir);

  // Stepper basically has no speed if it was standing for 10ms.
  if (!stepperIsRunning()) {
    stepDelayUs = PULSE_MAX_US;
  }

  if (stepDelayUs == PULSE_MAX_US) {
    // Hide 2 bottom rows in anticipation of stepper move as that info
    // will go stale and display won't be updated anymore.
    updateDisplay(true /*beforeRunning*/);
  }

  long minDelay = steps == 1 ? 1 : PULSE_MIN_US;
  for (int i = 0; i < steps; i++) {
    DLOW(Z_STEP);
    long constAccelDelay = 1000000 / (1000000 / stepDelayUs + ACCELERATION * stepDelayUs / 1000);
    stepDelayUs = min(long(PULSE_MAX_US), max(minDelay, constAccelDelay));
    unsigned long t = micros();
    stepToStep = min(stepToStep, t - stepStartMicros);
    stepStartMicros = t;
    delayMicroseconds(5);
    DHIGH(Z_STEP);
    // Don't wait during the last step, it will pass by itself before we get back to stepping again.
    // This condition is the reason moving left-right is limited to 600rpm but with ELS On and spindle
    // gradually speeding up, stepper can go to ~1200rpm.
    if (i < steps - 1) {
      delayMicroseconds(stepDelayUs);
    } else if (stepDelayUs > stepToStep) {
      delayMicroseconds(stepDelayUs - stepToStep);
    }
  }
  pos += (dir ? 1 : -1) * steps;
}

// Calculates stepper position from spindle position.
long posFromSpindle(long s, bool respectStops) {
  long newPos = s * ENCODER_TO_STEPPER_STEP_RATIO * dupr * starts;

  // Respect left/right stops.
  if (respectStops) {
    if (rightStop != LONG_MIN && newPos < rightStop) {
      newPos = rightStop;
    } else if (leftStop != LONG_MAX && newPos > leftStop) {
      newPos = leftStop;
    }
  }

  return newPos;
}

// Calculates spindle position from stepper position.
long spindleFromPos(long p) {
  return p * STEPPER_TO_ENCODER_STEP_RATIO / (dupr * starts);
}

void stepperEnable(bool value) {
  if (!DISABLE_STEPPER_WHEN_RESTING) {
    return;
  }

  if (value) {
    stepperEnableCounter++;
    if (value == 1) {
      DHIGH(Z_ENA);
      // Stepper driver needs some time before it will react to pulses.
      delay(100);
    }
  } else if (stepperEnableCounter > 0) {
    stepperEnableCounter--;
    if (stepperEnableCounter == 0) {
      DLOW(Z_ENA);
    }
  }
}

void loop() {
  processKeypadEvents();

  noInterrupts();
  long spindlePosCopy = spindlePos;
  long spindlePosSyncCopy = spindlePosSync;
  interrupts();

  // Move the stepper if needed.
  if (isOn && mode != MODE_ASYNC && spindlePosSyncCopy == 0) {
    long newPos = posFromSpindle(spindlePosCopy, true);
    if (newPos != pos) {
      // Move the stepper to the right position.
      step(newPos > pos, 1);
      if (loopCounter > 0) {
        loopCounter = 0;
      }

      // No long calls on this path or stepper will move unevenly.
      return;
    }
  }

  // Perform auxiliary logic but don't take more than a few milliseconds since
  // stepper just be moving slowly and will need signalling soon.

  // When standing at the stop, ignore full spindle turns.
  // This allows to avoid waiting when spindle direction reverses
  // and reduces the chance of the skipped stepper steps since
  // after a reverse the spindle starts slow.
  if (dupr != 0) {
    noInterrupts();
    if (rightStop != LONG_MIN && pos == rightStop) {
      long stopSpindlePos = spindleFromPos(rightStop);
      if (dupr > 0) {
        if (spindlePos < stopSpindlePos - ENCODER_STEPS) {
          spindlePos += ENCODER_STEPS;
        }
      } else {
        if (spindlePos > stopSpindlePos + ENCODER_STEPS) {
          spindlePos -= ENCODER_STEPS;
        }
      }
    } else if (leftStop != LONG_MAX && pos == leftStop) {
      long stopSpindlePos = spindleFromPos(leftStop);
      if (dupr > 0) {
        if (spindlePos > stopSpindlePos + ENCODER_STEPS) {
          spindlePos -= ENCODER_STEPS;
        }
      } else {
        if (spindlePos < stopSpindlePos - ENCODER_STEPS) {
          spindlePos += ENCODER_STEPS;
        }
      }
    }
    interrupts();
    checkIfNextStart();
  }

  loopCounter++;
  if (loopCounter > LOOP_COUNTER_MAX) {
    // Only check buttons when stepper is surely not running.
    // It might have to run any millisecond though e.g. when leaving the stop
    // so it still should complete within milliseconds.
    if (loopCounter % 8 == 0) {
      // This takes a really long time.
      updateDisplay(false /*beforeRunning*/);
    }
    if (loopCounter % 137 == 0) {
      saveIfChanged();
    }

    // Drop the lost thread warning after some time.
    if (resetOnStartup && loopCounter > 2 * LOOP_COUNTER_MAX) {
      resetOnStartup = false;
    }
  }
}

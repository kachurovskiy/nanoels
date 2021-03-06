// https://github.com/kachurovskiy/nanoels

/* Change values in this section to suit your hardware. */

// Define your hardware parameters here. Don't remove the ".0" at the end.
#define ENCODER_STEPS 600.0 // 600 step spindle optical rotary encoder
#define MOTOR_STEPS 200.0 // 200 step stepper motor, no microstepping
#define LEAD_SCREW_HMM 200.0 // 2mm lead screw

// Tweak these values to move display picture around to center it in the window.
// Acceptable values 0 to ~10 pixels, anything higher and text will be cropped.
#define DISPLAY_LEFT 4
#define DISPLAY_TOP 4

// Spindle rotary encoder pins. Nano only supports interrupts on D2 and D3.
// Swap values if the rotation direction is wrong.
#define ENC_A 3 // D3
#define ENC_B 2 // D2

// Stepper pulse and acceleration constants.
#define PULSE_MIN_US round(500 * (200.0 / MOTOR_STEPS)) // Microseconds to wait after high pulse, min.
#define PULSE_MAX_US round(2000 * (200.0 / MOTOR_STEPS)) // Microseconds to wait after high pulse, max. Slow start.
#define PULSE_DELTA_US 7 // Microseconds remove from waiting time on every step. Acceleration.
#define INVERT_STEPPER true // false for 1:1 geared connection, true for 1:1 belt connection

// Pitch shortcut buttons, set to your most used values that should be available within 1 click.
#define F3_PITCH 10 // 0.1mm
#define F4_PITCH 100 // 1mm
#define F5_PITCH 200 // 2mm

// Uncomment if you're using a big LCD2004 display.
// #define LCD

/* Changing anything below shouldn't be needed for basic use. */

#define LONG_MIN long(-2147483648)
#define LONG_MAX long(2147483647)

#define LOOP_COUNTER_MAX 1500 // 1500 loops without stepper move to start reading buttons
#define HMMPR_MAX 1000 // 10mm

// Ratios between spindle and stepper.
#define ENCODER_TO_STEPPER_STEP_RATIO MOTOR_STEPS / (LEAD_SCREW_HMM * ENCODER_STEPS)
#define STEPPER_TO_ENCODER_STEP_RATIO LEAD_SCREW_HMM * ENCODER_STEPS / MOTOR_STEPS

// If time between encoder ticks is less than this, direction change is not allowed.
// Effectively this limits direction change to the time when spindle is <20rpm.
#define DIR_CHANGE_DIFF_MS (int) (5 * ENCODER_STEPS / 600)

// Version of the EEPROM storage format, should be changed when non-backward-compatible
// changes are made to the storage logic, resulting in EEPROM wipe on first start.
#define EEPROM_VERSION 2

// To be incremented whenever a measurable improvement is made.
#define SOFTWARE_VERSION 9

// To be changed whenever a different PCB / encoder / stepper / ... design is used.
#define HARDWARE_VERSION 1

#define DIR A0
#define STEP A1

#define LEFT 11
#define ONOFF 10
#define RIGHT A3

#define LEFT_STOP 7
#define RIGHT_STOP 9

#define F1 6
#define F2 5
#define F3 4
#define F4 12
#define F5 8

#define ADDR_EEPROM_VERSION 0 // takes 1 byte
#define ADDR_ONOFF 1 // takes 1 byte
#define ADDR_HMMPR 2 // takes 2 bytes
#define ADDR_POS 4 // takes 4 bytes
#define ADDR_LEFT_STOP 8 // takes 4 bytes
#define ADDR_RIGHT_STOP 12 // takes 4 bytes
#define ADDR_SPINDLE_POS 16 // takes 4 bytes
#define ADDR_OUT_OF_SYNC 20 // takes 2 bytes
#define ADDR_SHOW_ANGLE 22 // takes 1 byte

// Uncomment to print out debug info in Serial.
// #define DEBUG

// Uncomment to run the self-test of the code instead of the actual program.
// #define TEST
#ifdef TEST
  bool mockDigitalPins[20] = {0};
  int mockDigitalPinToggleOnRead = -1;
  int mockDigitalRead(int x) {
    int value = mockDigitalPins[x];
    if (x == mockDigitalPinToggleOnRead) {
      mockDigitalPins[x] ^= 1;
    }
    return value;
  }
  #define DREAD(x) mockDigitalRead(x)
#else
  #include <FastGPIO.h>
  #define DREAD(x) FastGPIO::Pin<x>::isInputHigh()
#endif

#ifndef TEST
  #include <SPI.h>
  #include <Wire.h>
  #ifdef LCD
    #include <LiquidCrystal_I2C.h>
    LiquidCrystal_I2C lcd(0x27, 20, 4);
    long lcdHash = 0;
  #else
    #include <Adafruit_SSD1306.h>
    Adafruit_SSD1306 display(128, 64, &Wire, -1);
  #endif
#endif

#include <EEPROM.h>

unsigned long buttonTime = 0;
long loopCounter = 0;
bool isOn = false;
unsigned long resetMillis = 0;
bool resetOnStartup = false;

int hmmpr = 0; // hundredth of a mm per rotation
int savedHmmpr = 0; // hmmpr saved in EEPROM
int hmmprPrevious = 0;

long pos = 0; // relative position of the stepper motor, in steps
long savedPos = 0; // value saved in EEPROM

long leftStop = 0; // left stop value of pos
long savedLeftStop = 0; // value saved in EEPROM
bool leftStopFlag = true; // prevent toggling the stop while button is pressed.

long rightStop = 0; // right stop value of pos
long savedRightStop = 0; // value saved in EEPROM
bool rightStopFlag = true; // prevent toggling the stop while button is pressed.

volatile unsigned long spindleDeltaTime = 0; // millis() of the previous spindle update
volatile int spindleDeltaPrev = 0; // Previously detected spindle direction
volatile long spindlePos = 0; // Spindle position
long savedSpindlePos = 0; // spindlePos value saved in EEPROM
long spindleLeftStop = 0;
long spindleRightStop = 0;

volatile int spindlePosSync = 0;
int savedSpindlePosSync = 0;

int stepDelayUs = PULSE_MAX_US;
bool stepDelayDirection = true; // To reset stepDelayUs when direction changes.
unsigned long stepStartMs = 0;

bool showAngle = false; // Whether to show 0-359 spindle angle on screen
bool savedShowAngle = false; // showAngle value saved in EEPROM
bool showAngleFlag = true;

void updateDisplay() {
  #ifndef TEST
  float posMm = pos * LEAD_SCREW_HMM / MOTOR_STEPS / 100;
  #ifdef LCD
    // Avoid updating the LCD when nothing has changed, it flickers.
    long newLcdHash = spindlePos + pos * 2 + hmmpr * 3 + isOn * 4 + leftStop / 5
      + rightStop / 6 + spindlePosSync * 7 + resetOnStartup * 8 + showAngle * 9;
    if (newLcdHash == lcdHash) {
      return;
    }

    lcdHash = newLcdHash;
    lcd.clear();

    // First row.
    lcd.setCursor(0,0);
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

    // Second row.
    lcd.setCursor(0,1);
    lcd.print("Pitch: ");
    lcd.print(hmmpr * 1.0 / 100, 2);
    lcd.print("mm");

    // Third row.
    lcd.setCursor(0,2);
    lcd.print("Position: ");
    lcd.print(posMm, 2);
    lcd.print("mm");

    // Fourth row.
    lcd.setCursor(0,3);
    if (showAngle) {
      lcd.print("Angle: ");
      lcd.print(round(((spindlePos % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS) * 360 / ENCODER_STEPS));
      lcd.print("deg");
    }
  #else
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(DISPLAY_LEFT, DISPLAY_TOP);
    display.setTextSize(2);
    display.print(isOn ? "ON" : "off");
    if (leftStop != LONG_MAX && rightStop != LONG_MIN) {
      display.print(" LR");
    } else if (leftStop != LONG_MAX) {
      display.print(" L");
    } else if (rightStop != LONG_MIN) {
      display.print(" R");
    }
    if (spindlePosSync) {
      display.print(" SYN");
    }
    if (!spindlePosSync && resetOnStartup) {
      display.print(" LTW");
    }

    display.setCursor(DISPLAY_LEFT, 20 + DISPLAY_TOP);
    display.print(hmmpr * 1.0 / 100, 2);
    display.print("mm");

    display.setCursor(DISPLAY_LEFT, 40 + DISPLAY_TOP);
    display.print(posMm, 2);

    if (showAngle && abs(posMm) < 100) {
      display.print(" ");
      display.print(round(((spindlePos % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS) * 360 / ENCODER_STEPS));
    } else {
      display.print("mm");
    }

    display.display();
  #endif
  #endif
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
  int delta;
  unsigned long timeDiff = millis() - spindleDeltaTime;
  if (timeDiff > DIR_CHANGE_DIFF_MS) {
    delta = DREAD(ENC_B) ? -1 : 1;
    spindleDeltaPrev = delta;
  } else {
    // Spindle is going fast, unlikely to change direction momentarily.
    delta = spindleDeltaPrev;
  }
  spindlePos += delta;
  spindleDeltaTime += timeDiff;

  if (spindlePosSync != 0) {
    spindlePosSync += delta;
    if (spindlePosSync == 0 || spindlePosSync == ENCODER_STEPS) {
      spindlePosSync = 0;
      spindlePos = spindleFromPos(pos);
    }
  }
}

#ifdef TEST
void setup() {
  Serial.begin(9600);
}
#else
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(ONOFF, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  pinMode(LEFT_STOP, INPUT_PULLUP);
  pinMode(RIGHT_STOP, INPUT_PULLUP);

  pinMode(F1, INPUT_PULLUP);
  pinMode(F2, INPUT_PULLUP);
  pinMode(F3, INPUT_PULLUP);
  pinMode(F4, INPUT_PULLUP);
  pinMode(F5, INPUT_PULLUP);

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);

  // Wipe EEPROM if this is the first start after uploading a new build.
  if (EEPROM.read(ADDR_EEPROM_VERSION) != EEPROM_VERSION) {
    for (int i = 0; i < 256; i++) {
      EEPROM.write(i, 255); // 255 is the default value.
    }
    EEPROM.write(ADDR_EEPROM_VERSION, EEPROM_VERSION);
    saveLong(ADDR_LEFT_STOP, savedLeftStop = leftStop = LONG_MAX);
    saveLong(ADDR_RIGHT_STOP, savedRightStop = rightStop = LONG_MIN);
  }

  isOn = EEPROM.read(ADDR_ONOFF) == 1;
  savedHmmpr = hmmpr = loadInt(ADDR_HMMPR);
  savedPos = pos = loadLong(ADDR_POS);
  savedLeftStop = leftStop = loadLong(ADDR_LEFT_STOP);
  savedRightStop = rightStop = loadLong(ADDR_RIGHT_STOP);
  savedSpindlePos = spindlePos = loadLong(ADDR_SPINDLE_POS);
  savedSpindlePosSync = spindlePosSync = loadInt(ADDR_OUT_OF_SYNC);
  savedShowAngle = showAngle = EEPROM.read(ADDR_SHOW_ANGLE) == 1;

  attachInterrupt(digitalPinToInterrupt(ENC_A), spinEnc, FALLING);

  #ifdef LCD
    lcd.init();
    lcd.backlight();
  #else
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  #endif
  updateDisplay();

  Serial.begin(9600);
  Serial.print("NanoEls H");
  Serial.print(HARDWARE_VERSION);
  Serial.print(" V");
  Serial.println(SOFTWARE_VERSION);

  preventMoveOnStart();
}
#endif

void preventMoveOnStart() {
  // Sometimes, especially if ELS was run outside above max RPM before, pos and spindlePos
  // will be out of sync causing immediate stepper movement if isOn. This could be dangerous
  // and surely won't be expected by the operator.
  long newPos = posFromSpindle(spindlePos, true);
  if (isOn && newPos != pos) {
    #ifdef DEBUG
    Serial.println("Losing the thread");
    #endif
    resetOnStartup = true;
    markAsZero();
  }
}

// Saves all positions in EEPROM, should be called infrequently to reduce EEPROM wear.
void saveIfChanged() {
  if (hmmpr != savedHmmpr) {
    saveInt(ADDR_HMMPR, savedHmmpr = hmmpr);
  }
  if (pos != savedPos) {
    saveLong(ADDR_POS, savedPos = pos);
  }
  if (leftStop != savedLeftStop) {
    saveLong(ADDR_LEFT_STOP, savedLeftStop = leftStop);
  }
  if (rightStop != savedRightStop) {
    saveLong(ADDR_RIGHT_STOP, savedRightStop = rightStop);
  }
  if (spindlePos != savedSpindlePos) {
    saveLong(ADDR_SPINDLE_POS, savedSpindlePos = spindlePos);
  }
  if (spindlePosSync != savedSpindlePosSync) {
    saveInt(ADDR_OUT_OF_SYNC, savedSpindlePosSync = spindlePosSync);
  }
  if (showAngle != savedShowAngle) {
    EEPROM.write(ADDR_SHOW_ANGLE, savedShowAngle = showAngle);
  }
}

// Checks if some button was recently pressed. Returns true if not.
bool checkAndMarkButtonTime() {
  if (millis() > buttonTime + 300) {
    buttonTime = millis();
    return true;
  }
  return false;
}

// Loose the thread and mark current physical positions of
// encoder and stepper as a new 0. To be called when hmmpr changes
// or ELS is turned on/off. Without this, changing hmmpr will
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
  spindlePos = 0;
  spindlePosSync = 0;
  interrupts();
}

void setHmmpr(int value) {
  hmmpr = value;
  markAsZero();
  updateDisplay();
}

void splashScreen() {
  #ifndef TEST
  #ifdef LCD
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("NanoEls");
    lcd.setCursor(6, 2);
    lcd.print("H" + String(HARDWARE_VERSION) + " V" + String(SOFTWARE_VERSION));
    lcdHash = 0;
  #else
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(DISPLAY_LEFT, 10 + DISPLAY_TOP);
    display.println("NanoEls");
    display.setCursor(DISPLAY_LEFT, 30 + DISPLAY_TOP);
    display.println("H" + String(HARDWARE_VERSION) + " V" + String(SOFTWARE_VERSION));
    display.display();
  #endif
  delay(2000);
  #endif
}

void reset() {
  resetOnStartup = false;
  leftStop = LONG_MAX;
  rightStop = LONG_MIN;
  setHmmpr(0);
  splashScreen();
}

// Called when left/right stop restriction is removed while we're on it.
// Prevents stepper from rushing to a position far away by waiting for the right
// spindle position and starting smoothly.
void setOutOfSync() {
  if (!isOn) {
    return;
  }
  spindlePosSync = ((spindlePos - spindleFromPos(pos)) % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS;
  #ifdef DEBUG
  Serial.print("spindlePosSync ");
  Serial.println(spindlePosSync);
  #endif
}

// Check if the - or + buttons are pressed.
void checkPlusMinusButtons() {
  // Speed up scrolling when needed.
  int delta = abs(hmmprPrevious - hmmpr) >= 10 ? 10 : 1;
  bool left = DREAD(LEFT) == LOW;
  bool right = DREAD(RIGHT) == LOW;
  if (left && right && showAngleFlag) {
    showAngle = !showAngle;
    showAngleFlag = false;
  } else if (left && checkAndMarkButtonTime()) {
    if (hmmpr > -HMMPR_MAX) {
      setHmmpr(max(-HMMPR_MAX, hmmpr - delta));
    }
  } else if (right && checkAndMarkButtonTime()) {
    if (hmmpr < HMMPR_MAX) {
      setHmmpr(min(HMMPR_MAX, hmmpr + delta));
    }
  } else if (!left && !right) {
    hmmprPrevious = hmmpr;
    showAngleFlag = true;
  }
}

// Check if the ON/OFF button is pressed.
void checkOnOffButton() {
  if (DREAD(ONOFF) == LOW) {
    if (resetMillis == 0) {
      resetMillis = millis();
      isOn = !isOn;
      EEPROM.write(ADDR_ONOFF, isOn ? 1 : 0);
      #ifdef DEBUG
      Serial.print("isOn ");
      Serial.println(isOn);
      #endif
      markAsZero();
      updateDisplay();
    } else if (resetMillis > 0 && millis() - resetMillis > 6000) {
      resetMillis = 0;
      reset();
    }
  } else {
    resetMillis = 0;
  }
}

// Check if the left stop button is pressed.
void checkLeftStopButton() {
  if (DREAD(LEFT_STOP) == LOW) {
    if (leftStopFlag) {
      leftStopFlag = false;
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
  } else {
    leftStopFlag = true;
  }
}

// Check if the right stop button is pressed.
void checkRightStopButton() {
  if (DREAD(RIGHT_STOP) == LOW) {
    if (rightStopFlag) {
      rightStopFlag = false;
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
  } else {
    rightStopFlag = true;
  }
}

void checkMoveButtons() {
  bool left = DREAD(F1) == LOW;
  bool right = DREAD(F2) == LOW;
  if (!left && !right) {
    return;
  }
  if (isOn && millis() - spindleDeltaTime < 100) {
    // Spindle is still moving.
    return;
  }
  if (spindlePosSync) {
    // Edge case.
    return;
  }

  int sign = left ? 1 : -1;
  // There was some weird bug when hmmpr == 1 and isOn == true in the first branch.
  // Carriage moved back-and-forth.
  if (isOn && hmmpr != 0 && abs(hmmpr) != 1) {
    int posDiff = 0;
    do {
      noInterrupts();
      // Move 1mm in the desired direction but stay in the thread by possibly traveling a little more.
      spindlePos += ceil(MOTOR_STEPS * 100.0 / LEAD_SCREW_HMM * STEPPER_TO_ENCODER_STEP_RATIO / ENCODER_STEPS / abs(hmmpr))
        * ENCODER_STEPS
        * sign
        * (hmmpr > 0 ? 1 : -1);
      long newPos = posFromSpindle(spindlePos, true);
      interrupts();
      posDiff = abs(newPos - pos);
      step(newPos > pos, posDiff);
    } while (posDiff != 0 && (left ? DREAD(F1) : DREAD(F2)) == LOW);
  } else {
    int delta = 0;
    do {
      if (hmmpr == 0 || abs(hmmpr) == 1) {
        delta = 100.0 / LEAD_SCREW_HMM * MOTOR_STEPS;
      } else {
        int increments = MOTOR_STEPS * abs(hmmpr) / LEAD_SCREW_HMM;
        delta = ceil(MOTOR_STEPS * 100.0 / LEAD_SCREW_HMM / increments) * increments;
      }

      // Don't left-right move out of stops.
      if (leftStop != LONG_MAX && pos + delta * sign > leftStop) {
        delta = leftStop - pos;
      } else if (rightStop != LONG_MIN && pos + delta * sign < rightStop) {
        delta = rightStop - pos;
      }

      step(left, abs(delta));
    } while (delta != 0 && (left ? DREAD(F1) : DREAD(F2)) == LOW);
    if (isOn) {
      // Prevent stepper from jumping back to position calculated from the spindle.
      markAsZero();
    }
  }
}

// Checks if one of the pitch shortcut buttons were pressed.
void checkPitchShortcutButton(int pinValue, int pitch) {
  if (pinValue == LOW && checkAndMarkButtonTime()) {
    hmmpr = pitch;
    markAsZero();
  }
}

// Called when loop() is not busy running the stepper.
// Should take as little time as possible since it's possible that
// lead screw is ON and stepper has to run in a few milliseconds.
void secondaryWork() {
  checkLeftStopButton();
  checkRightStopButton();
  checkMoveButtons();
  checkPitchShortcutButton(DREAD(F3), F3_PITCH);
  checkPitchShortcutButton(DREAD(F4), F4_PITCH);
  checkPitchShortcutButton(DREAD(F5), F5_PITCH);

  if (loopCounter % 8 == 0) {
    // This takes a really long time.
    updateDisplay();
  }
  if (loopCounter % 137 == 0) {
    saveIfChanged();
  }
}

// Moves the stepper.
long step(bool dir, long steps) {
  // Start slow if direction changed.
  if (stepDelayDirection != dir) {
    stepDelayUs = PULSE_MAX_US;
    stepDelayDirection = dir;
    digitalWrite(DIR, dir ^ INVERT_STEPPER ? HIGH : LOW);
    #ifdef DEBUG
    Serial.print("Direction change");
    #endif
  }

  // Stepper basically has no speed if it was standing for 10ms.
  if (millis() - stepStartMs > 10) {
    stepDelayUs = PULSE_MAX_US;
  }

  for (int i = 0; i < steps; i++) {
    unsigned long t = millis();
    int tDiffMs = stepStartMs == 0 ? 0 : t - stepStartMs;
    // long to int can overflow
    if (tDiffMs < 0 || tDiffMs > PULSE_MAX_US) {
      stepDelayUs = PULSE_MAX_US;
    } else {
      stepDelayUs = min(PULSE_MAX_US, max(PULSE_MIN_US, stepDelayUs - PULSE_DELTA_US + tDiffMs));
    }
    stepStartMs = t;

    digitalWrite(STEP, HIGH);
    // digitalWrite() is slow enough that we don't need to wait in the HIGH position.
    digitalWrite(STEP, LOW);
    // Don't wait during the last step, it will pass by itself before we get back to stepping again.
    // This condition is the reason moving left-right is limited to 600rpm but with ELS On and spindle
    // gradually speeding up, stepper can go to ~1200rpm.
    if (i < steps - 1) {
      delayMicroseconds(stepDelayUs);
    }
  }
  pos += (dir ? 1 : -1) * steps;
}

// Calculates stepper position from spindle position.
long posFromSpindle(long s, bool respectStops) {
  long newPos = s * ENCODER_TO_STEPPER_STEP_RATIO * hmmpr;

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
  return p * STEPPER_TO_ENCODER_STEP_RATIO / hmmpr;
}

// What is called in the loop() function in when not in test mode.
void nonTestLoop() {
  // Has to be called before reading the spindle value because it can zero it.
  checkOnOffButton();
  checkPlusMinusButtons();

  noInterrupts();
  long spindlePosCopy = spindlePos;
  long spindlePosSyncCopy = spindlePosSync;
  interrupts();

  // Move the stepper if needed.
  long newPos = posFromSpindle(spindlePosCopy, true);
  if (isOn && !spindlePosSyncCopy && newPos != pos) {
    // Move the stepper to the right position.
    step(newPos > pos, abs(newPos - pos));
    if (loopCounter > 0) {
      loopCounter = 0;
    }

    // No long calls on this path or stepper will move unevenly.
    return;
  }

  // Perform auxiliary logic but don't take more than a few milliseconds since
  // stepper just be moving slowly and will need signalling soon.

  // When standing at the stop, ignore full spindle turns.
  // This allows to avoid waiting when spindle direction reverses
  // and reduces the chance of the skipped stepper steps since
  // after a reverse the spindle starts slow.
  if (hmmpr != 0) {
    noInterrupts();
    if (rightStop != LONG_MIN && pos == rightStop) {
      long stopSpindlePos = spindleFromPos(rightStop);
      if (hmmpr > 0) {
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
      if (hmmpr > 0) {
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
  }

  loopCounter++;
  if (loopCounter > LOOP_COUNTER_MAX) {
    #ifdef DEBUG
    if (loopCounter % LOOP_COUNTER_MAX == 0) {
      Serial.print("pos ");
      Serial.print(pos);
      Serial.print(" hmmpr ");
      Serial.print(hmmpr);
      Serial.print(" leftStop ");
      Serial.print(leftStop == LONG_MAX ? "-" : String(leftStop));
      Serial.print(" rightStop ");
      Serial.print(rightStop == LONG_MIN ? "-" : String(rightStop));
      Serial.print(" spindlePos ");
      Serial.println(spindlePos);
    }
    #endif

    // Only check buttons when stepper is surely not running.
    // It might have to run any millisecond though e.g. when leaving the stop
    // so it still should complete within milliseconds.
    secondaryWork();

    // Drop the lost thread warning after some time.
    if (resetOnStartup && loopCounter > 2 * LOOP_COUNTER_MAX) {
      resetOnStartup = false;
    }
  }
}

// In unit testing mode, include test library.
#ifdef TEST
#include <AUnit.h>
#endif

void loop() {
  // In unit testing mode, only run tests.
  #ifdef TEST
  setupEach();
  aunit::TestRunner::run();
  #else
  nonTestLoop();
  #endif
}

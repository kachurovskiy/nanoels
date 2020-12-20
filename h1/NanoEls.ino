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
#define PULSE_MIN_US 500 // Microseconds to wait after high pulse, min.
#define PULSE_MAX_US 2000 // Microseconds to wait after high pulse, max. Slow start.
#define PULSE_DELTA_US 7 // Microseconds remove from waiting time on every step. Acceleration.
#define STEPPER_MAX_RPM 600 // Stepper loses most of it's torque at speeds higher than that.
#define INVERT_STEPPER true // false for 1:1 geared connection, true for 1:1 belt connection

/* Changing anything below shouldn't be needed for basic use. */

#define LOOP_COUNTER_MAX 1500 // 1500 loops without stepper move to start reading buttons
#define HMMPR_MAX 1000 // 10mm

// Uncomment to run the self-test of the code instead of the actual program.
// #define TEST

// Ratios between spindle and stepper.
#define ENCODER_TO_STEPPER_STEP_RATIO MOTOR_STEPS / (LEAD_SCREW_HMM * ENCODER_STEPS)
#define STEPPER_TO_ENCODER_STEP_RATIO LEAD_SCREW_HMM * ENCODER_STEPS / MOTOR_STEPS

// Version of the EEPROM storage format, should be changed when non-backward-compatible
// changes are made to the storage logic, resulting in EEPROM wipe on first start.
#define EEPROM_VERSION 1

// To be incremented whenever a measurable improvement is made.
#define SOFTWARE_VERSION 3

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

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

unsigned long buttonTime = 0;
long loopCounter = 0;
bool onOffFlag = false;
bool isOn = false;
int resetCounter = 0;
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

volatile long spindlePos = 0; // spindle position
long savedSpindlePos = 0; // value saved in EEPROM
long spindleLeftStop = 0;
long spindleRightStop = 0;

volatile int outOfSync = 0;
int savedOutOfSync = 0;

int stepDelayUs = PULSE_MAX_US;
bool stepDelayDirection = true; // To reset stepDelayUs when direction changes.
unsigned long stepStartMs = 0;

void updateDisplay() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(DISPLAY_LEFT, DISPLAY_TOP);
  display.setTextSize(2);
  display.print(isOn ? "   ON" : "off  ");
  display.print(outOfSync ? " SYN" : "");
  if (!outOfSync && resetOnStartup) {
    display.print(" LTW");
  }
  display.setCursor(DISPLAY_LEFT, 20 + DISPLAY_TOP);
  display.print(String(hmmpr * 1.0 / 100, 2));
  display.print("mm");

  long maxSpindleRpm = hmmpr == 0 ? 1250 : STEPPER_MAX_RPM * LEAD_SCREW_HMM / abs(hmmpr);
  display.setCursor(DISPLAY_LEFT, 40 + DISPLAY_TOP);
  if (leftStop != 0 || rightStop != 0) {
    display.print(leftStop != 0 ? "L " : "  ");
    display.print("STOP");
    display.print(rightStop != 0 ? " R" : "  ");
  } else if (maxSpindleRpm < 1250) {
    display.print("<");
    display.print(maxSpindleRpm);
    display.print("rpm");
  }
  display.display();
}

void saveInt(int i, int v) {
  // Can't concatenate all in one line due to compiler problems, same throughout the code.
  Serial.print("Saving int at ");
  Serial.print(i);
  Serial.print(" = ");
  Serial.println(v);
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
  Serial.print("Saving long at ");
  Serial.print(i);
  Serial.print(" = ");
  Serial.println(v);
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
  int delta = digitalRead(ENC_B) ? -1 : 1;
  spindlePos += delta;

  if (outOfSync != 0) {
    outOfSync += delta;
    if (outOfSync == 0 || outOfSync == ENCODER_STEPS) {
      outOfSync = 0;
      spindlePos = pos * STEPPER_TO_ENCODER_STEP_RATIO / hmmpr;
    }
  }
}

void setup() {
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
  }

  isOn = EEPROM.read(ADDR_ONOFF) == 1;
  savedHmmpr = hmmpr = loadInt(ADDR_HMMPR);
  savedPos = pos = loadLong(ADDR_POS);
  savedLeftStop = leftStop = loadLong(ADDR_LEFT_STOP);
  savedRightStop = rightStop = loadLong(ADDR_RIGHT_STOP);
  savedSpindlePos = spindlePos = loadLong(ADDR_SPINDLE_POS);
  savedOutOfSync = outOfSync = loadInt(ADDR_OUT_OF_SYNC);

  attachInterrupt(digitalPinToInterrupt(ENC_A), spinEnc, FALLING);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  updateDisplay();

  Serial.begin(9600);
  Serial.print("NanoEls H");
  Serial.print(HARDWARE_VERSION);
  Serial.print(" V");
  Serial.print(SOFTWARE_VERSION);

  // Sometimes, especially if ELS was run outside above max RPM before, pos and spindlePos
  // will be out of sync causing immediate stepper movement if isOn. This could be dangerous
  // and surely won't be expected by the operator.
  long newPos = posFromSpindle(spindlePos, true);
  if (newPos != pos) {
    Serial.println("Losing the thread");
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
  if (outOfSync != savedOutOfSync) {
    saveInt(ADDR_OUT_OF_SYNC, savedOutOfSync = outOfSync);
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
  if (leftStop != 0) {
    leftStop -= pos;
    if (leftStop == 0) {
      leftStop = 1;
    }
  }
  if (rightStop != 0) {
    rightStop -= pos;
    if (rightStop == 0) {
      rightStop = -1;
    }
  }
  pos = 0;
  spindlePos = 0;
  outOfSync = 0;
}

void splashScreen() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(DISPLAY_LEFT, 10 + DISPLAY_TOP);
  display.println("NanoEls");
  display.setCursor(DISPLAY_LEFT, 30 + DISPLAY_TOP);
  display.println("H" + String(HARDWARE_VERSION) + " V" + String(SOFTWARE_VERSION));
  display.display();
  delay(2000);
}

void reset() {
  hmmpr = 0;
  leftStop = 0;
  rightStop = 0;
  markAsZero();
  splashScreen();
}

// Called when left/right stop restriction is removed while we're on it.
// Prevents stepper from rushing to a position far away by waiting for the right
// spindle position and starting smoothly.
void setOutOfSync() {
  outOfSync = (int) ((pos - posFromSpindle(spindlePos, false)) % (int) MOTOR_STEPS + MOTOR_STEPS) % (int) MOTOR_STEPS;
  Serial.print("outOfSync ");
  Serial.println(outOfSync);
}

// Called when loop() is not busy running the stepper.
// Should take as little time as possible since it's possible that
// lead screw is ON and stepper has to run in a few milliseconds.
// Don't do more than 2 digitalRead()-s in one run, spread them out using loopCounter
// or the stepper won't run smooth.
void secondaryWork() {
  // Left-right buttons.
  if (loopCounter % 41 == 0) {
    // Speed up scrolling when needed.
    int delta = abs(hmmprPrevious - hmmpr) >= 10 ? 10 : 1;
    if (digitalRead(LEFT) == LOW) {
      if (hmmpr > -HMMPR_MAX) {
        hmmpr -= delta;
        markAsZero();
      }
    } else if (digitalRead(RIGHT) == LOW) {
      if (hmmpr < HMMPR_MAX) {
        hmmpr += delta;
        markAsZero();
      }
    } else {
      hmmprPrevious = hmmpr;
    }
  }

  // On-off button.
  if (loopCounter % 7 == 0) {
    if (digitalRead(ONOFF) == LOW) {
      resetCounter++;
      if (onOffFlag) {
        onOffFlag = false;
        isOn = !isOn;
        EEPROM.write(ADDR_ONOFF, isOn ? 1 : 0);
        Serial.print("isOn ");
        Serial.println(isOn);
        markAsZero();
      } else if (resetCounter > 100) {
        resetCounter = 0;
        reset();
      }
    } else {
      resetCounter = 0;
      onOffFlag = true;
    }
  }

  // Left-right stop buttons.
  if (loopCounter % 9 == 0) {
    if (digitalRead(LEFT_STOP) == LOW) {
      if (leftStopFlag) {
        leftStopFlag = false;
        if (leftStop == 0) {
          leftStop = pos == 0 ? 1 : pos;
        } else {
          if (pos == leftStop) {
            // Spindle is most likely out of sync with the stepper because
            // it was spinning while the lead screw was on the stop.
            setOutOfSync();
          }
          leftStop = 0;
        }
      }
    } else {
      leftStopFlag = true;
    }
  }
  if (loopCounter % 11 == 0) {
    if (digitalRead(RIGHT_STOP) == LOW) {
      if (rightStopFlag) {
        rightStopFlag = false;
        if (rightStop == 0) {
          rightStop = pos == 0 ? -1 : pos;
        } else {
          if (pos == rightStop) {
            // Spindle is most likely out of sync with the stepper because
            // it was spinning while the lead screw was on the stop.
            setOutOfSync();
          }
          rightStop = 0;
        }
      }
    } else {
      rightStopFlag = true;
    }
  }

  // Carriage left-right buttons.
  if (loopCounter % 33 == 0 && !outOfSync && loopCounter > LOOP_COUNTER_MAX) {
    bool left = digitalRead(F1) == LOW;
    bool right = digitalRead(F2) == LOW;
    if (left || right) {
      int sign = left ? 1 : -1;
      // There was some weir bug when hmmpr == 1 and isOn == true in the first branch.
      // Carriage moved back-and-forth.
      if (isOn && hmmpr != 0 && abs(hmmpr) != 1) {
        int delta = 0;
        do {
          // Move 1mm in the desired direction but stay in the thread by possibly traveling a little more.
          delta = ceil(MOTOR_STEPS * 100.0 / LEAD_SCREW_HMM * STEPPER_TO_ENCODER_STEP_RATIO / ENCODER_STEPS / hmmpr) * ENCODER_STEPS * sign;

          // Don't left-right move out of stops.
          long deltaPos = posFromSpindle(spindlePos + delta, false);
          if (leftStop != 0 && deltaPos > leftStop) {
            // TODO: support moving exactly to leftPos and setting outOfSync to the right value.
            break;
          }
          if (rightStop != 0 && deltaPos < rightStop) {
            // TODO: support moving exactly to rightPos and setting outOfSync to the right value.
            break;
          }

          noInterrupts();
          spindlePos += delta;
          interrupts();

          long newPos = posFromSpindle(spindlePos, true);
          step(newPos > pos, abs(newPos - pos));
        } while (delta != 0 && (pos == 0 || pos != leftStop && pos != rightStop) && digitalRead(left ? F1 : F2) == LOW);
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
          int signedDelta = delta * (left ? 1 : -1);
          if (leftStop != 0 && pos + signedDelta > leftStop) {
            delta = leftStop - pos;
          } else if (rightStop != 0 && pos + signedDelta < rightStop) {
            delta = pos - rightStop;
          }

          // markAsZero() can move leftStop and rightStop by 1, don't allow to creep to them.
          if (delta == 1) {
            break;
          }

          step(left, delta);
        } while (delta != 0 && digitalRead(left ? F1 : F2) == LOW);
        markAsZero();
      }
    }
  }

  // 0.05mm pitch shortcut button.
  if (loopCounter % 15 == 0) {
    if (digitalRead(F3) == LOW) {
      if (checkAndMarkButtonTime()) {
        hmmpr = 5;
        markAsZero();
      }
    }
  }

  // 1mm pitch shortcut button.
  if (loopCounter % 17 == 0) {
    if (digitalRead(F4) == LOW) {
      if (checkAndMarkButtonTime()) {
        hmmpr = 100;
        markAsZero();
      }
    }
  }

  // 2mm pitch shortcut button.
  if (loopCounter % 19 == 0) {
    if (digitalRead(F5) == LOW) {
      if (checkAndMarkButtonTime()) {
        hmmpr = 200;
        markAsZero();
      }
    }
  }

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
    if (rightStop != 0 && newPos < rightStop) {
      newPos = rightStop;
    } else if (leftStop != 0 && newPos > leftStop) {
      newPos = leftStop;
    }
  }

  return newPos;
}

// Calculates spindle position from stepper position.
long spindleFromPos(long s) {
  return s * STEPPER_TO_ENCODER_STEP_RATIO / hmmpr;
}

// In unit testing mode, include test library.
#ifdef TEST
#include <AUnitVerbose.h>
using namespace aunit;
#endif

void loop() {
  // In unit testing mode, only run tests.
  #ifdef TEST
    TestRunner::run();
    return;
  #endif

  long newPos = posFromSpindle(spindlePos, true);
  if (isOn && !outOfSync && newPos != pos) {
    // Move the stepper to the right position.
    step(newPos > pos, abs(newPos - pos));
    loopCounter = 0;
    // No long calls such as digitalRead() allowed on this path or stepper will move unevenly.
  } else {
    // Perform auxiliary logic but don't take more than a few milliseconds since
    // stepper just be moving slowly and will need signalling soon.

    // When standing at the stop, ignore full spindle turns.
    // This allows to avoid waiting when spindle direction reverses
    // and reduces the chance of the skipped stepper steps since
    // after a reverse the spindle starts slow.
    if (rightStop != 0 && pos == rightStop) {
      long minSpindlePos = rightStop * STEPPER_TO_ENCODER_STEP_RATIO / hmmpr - ENCODER_STEPS;
      if (spindlePos < minSpindlePos) {
        noInterrupts();
        spindlePos += ENCODER_STEPS;
        interrupts();
      }
    } else if (leftStop != 0 && pos == leftStop) {
      long maxSpindlePos = leftStop * STEPPER_TO_ENCODER_STEP_RATIO / hmmpr + ENCODER_STEPS;
      if (spindlePos > maxSpindlePos) {
        noInterrupts();
        spindlePos -= ENCODER_STEPS;
        interrupts();
      }
    }

    loopCounter++;
    if (loopCounter > LOOP_COUNTER_MAX) {
      if (loopCounter % LOOP_COUNTER_MAX == 0) {
        Serial.print("pos ");
        Serial.print(pos);
        Serial.print(" hmmpr ");
        Serial.print(hmmpr);
        Serial.print(" leftStop ");
        Serial.print(leftStop);
        Serial.print(" rightStop ");
        Serial.print(rightStop);
        Serial.print(" spindlePos ");
        Serial.println(spindlePos);
      }

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
}

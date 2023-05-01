// https://github.com/kachurovskiy/nanoels

/* Change values in this section to suit your hardware. */

// Define your hardware parameters here. Don't remove the ".0" at the end.
#define ENCODER_STEPS 600.0 // 600 step spindle optical rotary encoder

// Spindle rotary encoder pins. Swap values if the rotation direction is wrong.
#define ENC_A 7
#define ENC_B 15

// Main lead screw (Z) parameters.
#define MOTOR_STEPS_Z 1600.0
#define SCREW_Z_DU 20000.0 // 2mm lead screw in deci-microns (10^-7) of a meter
#define SPEED_START_Z (2 * MOTOR_STEPS_Z) // Initial speed of a motor, steps / second.
#define ACCELERATION_Z (30 * MOTOR_STEPS_Z) // Acceleration of a motor, steps / second ^ 2.
#define SPEED_MANUAL_MOVE_Z (8 * MOTOR_STEPS_Z) // Maximum speed of a motor during manual move, steps / second.
#define INVERT_Z false // change (true/false) if the carriage moves e.g. "left" when you press "right".
#define NEEDS_REST_Z false // Set to false for closed-loop drivers, true for open-loop.

// Cross-slide lead screw (X) parameters.
#define MOTOR_STEPS_X 400.0
#define SCREW_X_DU 4166.6 // 1.25mm lead screw with 3x reduction in deci-microns (10^-7) of a meter
#define SPEED_START_X (2 * MOTOR_STEPS_X) // Initial speed of a motor, steps / second.
#define ACCELERATION_X (30 * MOTOR_STEPS_X) // Acceleration of a motor, steps / second ^ 2.
#define SPEED_MANUAL_MOVE_X (8 * MOTOR_STEPS_X) // Maximum speed of a motor during manual move, steps / second.
#define INVERT_X true // change (true/false) if the carriage moves e.g. "left" when you press "right".
#define NEEDS_REST_X false // Set to false for all kinds of drivers or X will be unlocked when not moving.

/* Changing anything below shouldn't be needed for basic use. */

#define LONG_MIN long(-2147483648)
#define LONG_MAX long(2147483647)

#define DUPR_MAX long(254000) // 25.4mm
#define STARTS_MAX 124 // No more than 124-start thread

// Version of the EEPROM storage format, should be changed when non-backward-compatible
// changes are made to the storage logic, resulting in EEPROM wipe on first start.
#define EEPROM_VERSION 2

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

#define BUZZ 4
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
#define B_DISPL 14
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
#define B_X 53
#define B_Z 43
#define B_A 4
#define B_B 63

#define ADDR_EEPROM_VERSION 0 // takes 1 byte
#define ADDR_DUPR 2 // takes 4 bytes
#define ADDR_POS_Z 6 // takes 4 bytes
#define ADDR_LEFT_STOP_Z 10 // takes 4 bytes
#define ADDR_RIGHT_STOP_Z 14 // takes 4 bytes
#define ADDR_SPINDLE_POS 18 // takes 4 bytes
#define ADDR_OUT_OF_SYNC 22 // takes 2 bytes
#define ADDR_SHOW_ANGLE 24 // takes 1 byte
#define ADDR_SHOW_TACHO 25 // takes 1 byte
#define ADDR_MOVE_STEP 26 // takes 2 bytes
#define ADDR_STARTS 28 // takes 2 bytes
#define ADDR_MODE 30 // takes 2 bytes
#define ADDR_MEASURE 32 // takes 2 bytes
#define ADDR_ORIGIN_POS_Z 34 // takes 4 bytes
#define ADDR_POS_X 38 // takes 4 bytes
#define ADDR_LEFT_STOP_X 42 // takes 4 bytes
#define ADDR_RIGHT_STOP_X 46 // takes 4 bytes
#define ADDR_ORIGIN_POS_X 50 // takes 4 bytes

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
#define MODE_CONE 3

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
#define DWRITE(x, y) digitalWrite(x, y)

#define DELAY(x) vTaskDelay(x / portTICK_PERIOD_MS);

#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(21, 48, 47, 38, 39, 40, 41, 42, 2, 1);
#define LCD_HASH_INITIAL -3845709 // Random number that's unlikely to naturally occur as an actual hash
long lcdHashLine0 = LCD_HASH_INITIAL;
long lcdHashLine1 = LCD_HASH_INITIAL;
long lcdHashLine2 = LCD_HASH_INITIAL;
long lcdHashLine3 = LCD_HASH_INITIAL;

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
int numpadDigits[20];
int numpadIndex = 0;

bool isOn = false;
unsigned long resetMillis = 0;
bool emergencyStop = false;

volatile long dupr = 0; // pitch, tenth of a micron per rotation
long savedDupr = 0; // dupr saved in EEPROM

int starts = 1; // number of starts in a multi-start thread
int savedStarts = 0; // starts saved in EEPROM

struct Axis {
  SemaphoreHandle_t mutex;

  float motorSteps; // motor steps per revolution of the axis
  float screwPitch; // lead screw pitch in deci-microns (10^-7 of a meter)

  long pos; // relative position of the stepper motor, in steps
  long savedPos; // value saved in EEPROM
  float fractionalPos; // fractional distance in steps that we meant to travel but couldn't
  long originPos; // relative position of the stepper motor to origin, in steps
  long savedOriginPos; // originPos saved in EEPROM
  int pendingPos; // steps of the stepper motor that we should make as soon as possible

  long leftStop; // left stop value of pos
  long savedLeftStop; // value saved in EEPROM
  bool leftStopFlag; // prevent toggling the stop while button is pressed.

  long rightStop; // right stop value of pos
  long savedRightStop; // value saved in EEPROM
  bool rightStopFlag; // prevent toggling the stop while button is pressed.

  unsigned long speed; // motor speed in steps / second
  unsigned long speedStart; // Initial speed of a motor, steps / second.
  unsigned long speedMax; // To limit max speed e.g. for manual moves
  unsigned long speedManualMove; // Maximum speed of a motor during manual move, steps / second.
  unsigned long acceleration; // Acceleration of a motor, steps / second ^ 2.

  bool direction; // To reset speed when direction changes.
  bool directionInitialized;
  unsigned long stepStartUs;
  int stepperEnableCounter;
  bool isEnabled;

  bool invertStepper; // change (true/false) if the carriage moves e.g. "left" when you press "right".
  bool needsRest; // set to false for closed-loop drivers, true for open-loop.
  bool movingManually; // whether stepper is being moved by left/right buttons

  int ena; // Enable pin of this motor
  int dir; // Direction pin of this motor
  int step; // Step pin of this motor
};

void initAxis(volatile Axis*  a, float motorSteps, float screwPitch, long speedStart, long speedManualMove, long acceleration, bool invertStepper, bool needsRest, int ena, int dir, int step) {
  a->mutex = xSemaphoreCreateMutex();

  a->motorSteps = motorSteps;
  a->screwPitch = screwPitch;

  a->pos = 0;
  a->savedPos = 0;
  a->fractionalPos = 0.0;
  a->originPos = 0;
  a->savedOriginPos = 0;
  a->pendingPos = 0;

  a->leftStop = 0;
  a->savedLeftStop = 0;
  a->leftStopFlag = true;

  a->rightStop = 0;
  a->savedRightStop = 0;
  a->rightStopFlag = true;

  a->speed = speedStart;
  a->speedStart = speedStart;
  a->speedMax = LONG_MAX;
  a->speedManualMove = speedManualMove;
  a->acceleration = acceleration;

  a->direction = true;
  a->directionInitialized = false;
  a->stepStartUs = 0;
  a->stepperEnableCounter = 0;
  a->isEnabled = !needsRest;
  
  a->invertStepper = invertStepper;
  a->needsRest = needsRest;
  a->movingManually = false;

  a->ena = ena;
  a->dir = dir;
  a->step = step;
}

volatile Axis z;
volatile Axis x;

volatile unsigned long spindleEncTime = 0; // micros() of the previous spindle update
volatile unsigned long spindleEncTimeDiffBulk = 0; // micros() between RPM_BULK spindle updates
volatile unsigned long spindleEncTimeAtIndex0 = 0; // micros() when spindleEncTimeIndex was 0
volatile int spindleEncTimeIndex = 0; // counter going between 0 and RPM_BULK - 1
volatile int spindleDeltaPrev = 0; // Previously detected spindle direction
volatile long spindlePos = 0; // Spindle position
long savedSpindlePos = 0; // spindlePos value saved in EEPROM

volatile int spindlePosSync = 0;
int savedSpindlePosSync = 0;

bool showAngle = false; // Whether to show 0-359 spindle angle on screen
bool showTacho = false; // Whether to show spindle RPM on screen
bool savedShowAngle = false; // showAngle value saved in EEPROM
bool savedShowTacho = false; // showTacho value saved in EEPROM
int shownRpm = 0;
unsigned long shownRpmTime = 0; // micros() when shownRpm was set

int moveStep = 0; // thousandth of a mm
int savedMoveStep = 0; // moveStep saved in EEPROM

volatile int mode = -1; // mode of operation (ELS, multi-start ELS, asynchronous)
int savedMode = -1; // mode saved in EEPROM

int measure = MEASURE_METRIC; // Whether to show distances in inches
int savedMeasure = MEASURE_METRIC; // measure value saved in EEPROM

float coneRatio = 1; // In cone mode, how much X moves for 1 step of Z

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

bool stepperIsRunning(volatile Axis* a) {
  return micros() - a->stepStartUs < 10000;
}

// Returns number of letters printed.
int printMicrons(long deciMicrons, int precisionPointsMax) {
  if (deciMicrons == 0) {
    return lcd.print("0");
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
  int count = lcd.print(deciMicrons / (imperial ? 254000.0 : 10000.0), min(precisionPointsMax, points));
  count += lcd.print(imperial ? "\"" : "mm");
  return count;
}

int printDupr(long value) {
  int count = 0;
  if (measure != MEASURE_TPI) {
    count += printMicrons(value, 5);
  } else {
    float tpi = 254000.0 / value;
    if (abs(tpi - round(tpi)) < TPI_ROUND_EPSILON) {
      count += lcd.print(int(round(tpi)));
    } else {
      int tpi100 = round(tpi * 100);
      int points = 0;
      if ((tpi100 % 10) != 0) {
        points = 2;
      } else if ((tpi100 % 100) != 0) {
        points = 1;
      }
      count += lcd.print(tpi, points);
    }
    count += lcd.print("tpi");
  }
  return count;
}

void printLcdSpaces(int charIndex) {
  // Our screen has width 20.
  for (; charIndex < 20; charIndex++) {
    lcd.print(" ");
  }
}

int printAxisPos(volatile Axis* a) {
  return printMicrons(round((a->pos + a->originPos) * a->screwPitch / a->motorSteps), 3);
}

void updateDisplay() {
  if (emergencyStop) {
    return;
  }
  int rpm = getApproxRpm();
  int charIndex = 0;

  if (lcdHashLine0 == LCD_HASH_INITIAL) {
    // First run after reset.
    lcd.clear();
  }

  long newHashLine0 = isOn + (z.leftStop - z.rightStop) + (x.leftStop - x.rightStop) + spindlePosSync + moveStep + mode + measure;
  if (lcdHashLine0 != newHashLine0) {
    lcdHashLine0 = newHashLine0;
    charIndex = 0;
    lcd.setCursor(0, 0);
    if (mode == MODE_MULTISTART) {
      charIndex += lcd.print("MUL ");
    } else if (mode == MODE_ASYNC) {
      charIndex += lcd.print("ASY ");
    } else if (mode == MODE_CONE) {
      charIndex += lcd.print("CONE ");
    }
    charIndex += lcd.print(isOn ? "ON " : "off ");
    int beforeStops = charIndex;
    if (z.leftStop != LONG_MAX) {
      charIndex += lcd.print("L");
    }
    if (z.rightStop != LONG_MIN) {
      charIndex += lcd.print("R");
    }
    if (x.leftStop != LONG_MAX) {
      charIndex += lcd.print("U");
    }
    if (x.rightStop != LONG_MIN) {
      charIndex += lcd.print("D");
    }
    if (beforeStops != charIndex) {
      charIndex += lcd.print(" ");
    }

    if (spindlePosSync) {
      charIndex += lcd.print("SYN ");
    }
    if (mode == MODE_NORMAL && !spindlePosSync) {
      charIndex += lcd.print("step ");
    }
    charIndex += printMicrons(moveStep, 5);
    printLcdSpaces(charIndex);
  }

  long newHashLine1 = dupr + starts + mode + measure;
  if (lcdHashLine1 != newHashLine1) {
    lcdHashLine1 = newHashLine1;
    charIndex = 0;
    lcd.setCursor(0, 1);
    charIndex += lcd.print("Pitch ");
    charIndex += printDupr(dupr);
    if (starts != 1) {
      charIndex += lcd.print(" x");
      charIndex += lcd.print(starts);
    }
    printLcdSpaces(charIndex);
  }

  long zDisplayPos = z.pos + z.originPos;
  long xDisplayPos = x.pos + x.originPos;
  long newHashLine2 = zDisplayPos + xDisplayPos + measure;
  if (lcdHashLine2 != newHashLine2) {
    lcdHashLine2 = newHashLine2;
    charIndex = 0;
    lcd.setCursor(0, 2);
    if (xDisplayPos == 0) {
      charIndex += lcd.print("Position ");
    }
    charIndex += printAxisPos(&z);
    if (xDisplayPos != 0) {
      while (charIndex < 10) {
        charIndex += lcd.print(" ");
      }
      charIndex += printAxisPos(&x);
    }
    printLcdSpaces(charIndex);
  }

  long numpadResult = getNumpadResult();
  long newHashLine3 = z.pos + (showAngle ? spindlePos : -1) + (showTacho ? rpm : -2) + measure + numpadResult + mode + round(coneRatio * 10000);
  if (lcdHashLine3 != newHashLine3) {
    lcdHashLine3 = newHashLine3;
    charIndex = 0;
    lcd.setCursor(0, 3);
    if (numpadResult != 0) {
      charIndex += lcd.print("Use ");
      if (mode == MODE_CONE) {
        charIndex += lcd.print(numpadToConeRatio(), 5);
      } else {
        charIndex += printDupr(numpadToDupr());
      }
      charIndex += lcd.print("?");
    } else if (mode == MODE_CONE) {
      charIndex += lcd.print("Cone ratio ");
      charIndex += lcd.print(coneRatio, 5);
    } else if (showAngle) {
      charIndex += lcd.print("Angle ");
      charIndex += lcd.print(((spindlePos % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS) * 360 / ENCODER_STEPS, 2);
      charIndex += lcd.print(char(223));
    } else if (showTacho) {
      charIndex += lcd.print("Tacho ");
      charIndex += lcd.print(rpm);
      if (shownRpm != rpm) {
        shownRpm = rpm;
        shownRpmTime = micros();
      }
      charIndex += lcd.print("rpm");
    }
    printLcdSpaces(charIndex);
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

  int delta = DREAD(ENC_B) ? -1 : 1;
  spindleDeltaPrev = delta;
  spindlePos += delta;
  spindleEncTime = microsNow;

  if (spindlePosSync != 0) {
    spindlePosSync += delta;
    if (spindlePosSync == 0 || spindlePosSync == ENCODER_STEPS) {
      spindlePosSync = 0;
      spindlePos = spindleFromPos(z.pos);
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

void taskDisplay(void *param) {
  while (true) {
    updateDisplay();
    if (!stepperIsRunning(&z) && !stepperIsRunning(&x)) {
      saveIfChanged();
    }
    taskYIELD();
  }
}

void taskKeypad(void *param) {
  while (true) {
    processKeypadEvents();
    taskYIELD();
  }
}

void taskSpindleOnStop(void *param) {
  while (true) {
    // When standing at the stop, ignore full spindle turns.
    // This allows to avoid waiting when spindle direction reverses
    // and reduces the chance of the skipped stepper steps since
    // after a reverse the spindle starts slow.
    if (dupr != 0 && !stepperIsRunning(&z)) {
      int spindlePosDiff = 0;
      if (z.rightStop != LONG_MIN && z.pos == z.rightStop) {
        long stopSpindlePos = spindleFromPos(z.rightStop);
        if (dupr > 0) {
          if (spindlePos < stopSpindlePos - ENCODER_STEPS) {
            spindlePosDiff = ENCODER_STEPS;
          }
        } else {
          if (spindlePos > stopSpindlePos + ENCODER_STEPS) {
            spindlePosDiff = -ENCODER_STEPS;
          }
        }
      } else if (z.leftStop != LONG_MAX && z.pos == z.leftStop) {
        long stopSpindlePos = spindleFromPos(z.leftStop);
        if (dupr > 0) {
          if (spindlePos > stopSpindlePos + ENCODER_STEPS) {
            spindlePosDiff = -ENCODER_STEPS;
          }
        } else {
          if (spindlePos < stopSpindlePos - ENCODER_STEPS) {
            spindlePosDiff = ENCODER_STEPS;
          }
        }
      }
      if (spindlePosDiff != 0) {
        noInterrupts();
        spindlePos += spindlePosDiff;
        interrupts();
      }
      checkIfNextStart();
    }
    taskYIELD();
  }
}

void waitForPendingPosNear0(volatile Axis* a) {
  while (abs(a->pendingPos) > a->motorSteps / 10) {
    taskYIELD();
  }
}

void waitForPendingPos0(volatile Axis* a) {
  while (a->pendingPos != 0) {
    taskYIELD();
  }
}

void taskMoveZ(void *param) {
  while (true) {
    bool left = buttonLeftPressed;
    bool right = buttonRightPressed;
    if (!left && !right) {
      taskYIELD();
      continue;
    }
    if (spindlePosSync != 0) {
      // Edge case.
      taskYIELD();
      continue;
    }
    int sign = left ? 1 : -1;
    bool stepperOn = true;
    stepperEnable(&z, true);
    z.speedMax = z.speedManualMove;
    z.movingManually = true;
    if (isOn && dupr != 0 && mode != MODE_CONE) {
      // Move by moveStep in the desired direction but stay in the thread by possibly traveling a little more.
      int diff = ceil(moveStep * 1.0 / abs(dupr * starts)) * ENCODER_STEPS * sign * (dupr > 0 ? 1 : -1);
      long prevSpindlePos = spindlePos;
      bool resting = false;
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
        if (newPos != z.pos) {
          stepTo(&z, newPos);
          waitForPendingPosNear0(&z);
        } else if (z.pos == (left ? z.leftStop : z.rightStop)) {
          // We're standing on a stop with the L/R move button pressed.
          resting = true;
          checkIfNextStart();
          if (stepperOn) {
            stepperEnable(&z, false);
            stepperOn = false;
          }
          DELAY(200);
        }
      } while (left ? buttonLeftPressed : buttonRightPressed);
    } else {
      int delta = 0;
      do {
        float fractionalDelta = moveStep * sign / SCREW_Z_DU * MOTOR_STEPS_Z + z.fractionalPos;
        delta = round(fractionalDelta);
        // Don't lose fractional steps when moving by 0.01" or 0.001".
        z.fractionalPos = fractionalDelta - delta;
        if (delta == 0) {
          // When moveStep is e.g. 1 micron and MOTOR_STEPS_Z is 200, make delta non-zero.
          delta = sign;
        }

        long posCopy = z.pos + z.pendingPos;
        // Don't left-right move out of stops.
        if (z.leftStop != LONG_MAX && posCopy + delta > z.leftStop) {
          delta = z.leftStop - posCopy;
        } else if (z.rightStop != LONG_MIN && posCopy + delta < z.rightStop) {
          delta = z.rightStop - posCopy;
        }
        stepTo(&z, posCopy + delta);
        waitForPendingPosNear0(&z);

        if (moveStep != (measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1)) {
          DELAY(500);
        }
      } while (delta != 0 && (left ? buttonLeftPressed : buttonRightPressed));
      if (isOn) {
        waitForPendingPos0(&z);
        markOrigin();
      }
    }
    z.movingManually = false;
    if (stepperOn) {
      stepperEnable(&z, false);
    }
    z.speedMax = LONG_MAX;
    taskYIELD();
  }
}

void taskMoveX(void *param) {
  while (true) {
    bool up = buttonUpPressed;
    bool down = buttonDownPressed;
    if (!up && !down) {
      taskYIELD();
      continue;
    }
    x.movingManually = true;
    x.speedMax = x.speedManualMove;
    stepperEnable(&x, true);

    int delta = 0;
    int sign = up ? 1 : -1;
    do {
      float fractionalDelta = moveStep * sign / x.screwPitch * x.motorSteps + x.fractionalPos;
      delta = round(fractionalDelta);
      // Don't lose fractional steps when moving by 0.01" or 0.001".
      x.fractionalPos = fractionalDelta - delta;
      if (delta == 0) {
        // When moveStep is e.g. 1 micron and MOTOR_STEPS_Z is 200, make delta non-zero.
        delta = sign;
      }

      long posCopy = x.pos + x.pendingPos;
      // Don't move out of stops.
      if (x.leftStop != LONG_MAX && posCopy + delta > x.leftStop) {
        delta = x.leftStop - posCopy;
      } else if (x.rightStop != LONG_MIN && posCopy + delta < x.rightStop) {
        delta = x.rightStop - posCopy;
      }
      stepTo(&x, posCopy + delta);
      waitForPendingPosNear0(&x);

      if (moveStep != (measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1)) {
        DELAY(500);
      }
    } while (delta != 0 && (up ? buttonUpPressed : buttonDownPressed));
    if (isOn) {
      waitForPendingPos0(&z);
      markOrigin();
    }
    x.movingManually = false;
    x.speedMax = LONG_MAX;
    stepperEnable(&x, false);

    taskYIELD();
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

  pinMode(BUZZ, OUTPUT);

  EEPROM.begin(256);
  // Wipe EEPROM if this is the first start after uploading a new build.
  if (EEPROM.read(ADDR_EEPROM_VERSION) != EEPROM_VERSION) {
    for (int i = 0; i < 256; i++) {
      EEPROM.write(i, 255); // 255 is the default value.
    }
    EEPROM.write(ADDR_EEPROM_VERSION, EEPROM_VERSION);
    saveLong(ADDR_LEFT_STOP_Z, LONG_MAX);
    saveLong(ADDR_RIGHT_STOP_Z, LONG_MIN);
    saveLong(ADDR_LEFT_STOP_X, LONG_MAX);
    saveLong(ADDR_RIGHT_STOP_X, LONG_MIN);
    saveInt(ADDR_MOVE_STEP, MOVE_STEP_1);
  }

  initAxis(&z, MOTOR_STEPS_Z, SCREW_Z_DU, SPEED_START_Z, SPEED_MANUAL_MOVE_Z, ACCELERATION_Z, INVERT_Z, NEEDS_REST_Z, Z_ENA, Z_DIR, Z_STEP);
  initAxis(&x, MOTOR_STEPS_X, SCREW_X_DU, SPEED_START_X, SPEED_MANUAL_MOVE_X, ACCELERATION_X, INVERT_X, NEEDS_REST_X, X_ENA, X_DIR, X_STEP);

  isOn = false;
  savedDupr = dupr = loadLong(ADDR_DUPR);
  savedStarts = starts = min(STARTS_MAX, max(1, loadInt(ADDR_STARTS)));
  z.savedPos = z.pos = loadLong(ADDR_POS_Z);
  z.savedOriginPos = z.originPos = loadLong(ADDR_ORIGIN_POS_Z);
  z.savedLeftStop = z.leftStop = loadLong(ADDR_LEFT_STOP_Z);
  z.savedRightStop = z.rightStop = loadLong(ADDR_RIGHT_STOP_Z);
  x.savedPos = x.pos = loadLong(ADDR_POS_X);
  x.savedOriginPos = x.originPos = loadLong(ADDR_ORIGIN_POS_X);
  x.savedLeftStop = x.leftStop = loadLong(ADDR_LEFT_STOP_X);
  x.savedRightStop = x.rightStop = loadLong(ADDR_RIGHT_STOP_X);
  savedSpindlePos = spindlePos = loadLong(ADDR_SPINDLE_POS);
  savedSpindlePosSync = spindlePosSync = loadInt(ADDR_OUT_OF_SYNC);
  savedShowAngle = showAngle = EEPROM.read(ADDR_SHOW_ANGLE) == 1;
  savedShowTacho = showTacho = EEPROM.read(ADDR_SHOW_TACHO) == 1;
  savedMoveStep = loadInt(ADDR_MOVE_STEP);
  moveStep = savedMoveStep > 0 ? savedMoveStep : MOVE_STEP_1;
  savedMode = loadInt(ADDR_MODE);
  savedMeasure = measure = loadInt(ADDR_MEASURE);
  setMode(savedMode);

  if (!z.needsRest) {
    DHIGH(Z_ENA);
  }
  if (!x.needsRest) {
    DHIGH(X_ENA);
  }

  lcd.begin(20, 4);

  Serial.begin(115200);
  // Serial output during this time doesn't show up in the Serial Monitor.
  delay(2000);
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

  // Non-time-sensitive tasks on core 0.
  xTaskCreatePinnedToCore(taskDisplay, "taskDisplay", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskKeypad, "taskKeypad", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskSpindleOnStop, "taskSpindleOnStop", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskMoveZ, "taskMoveZ", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskMoveX, "taskMoveX", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
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
  if (z.pos != z.savedPos) {
    saveLong(ADDR_POS_Z, z.savedPos = z.pos);
    changed = true;
  }
  if (z.originPos != z.savedOriginPos) {
    saveLong(ADDR_ORIGIN_POS_Z, z.savedOriginPos = z.originPos);
    changed = true;
  }
  if (z.leftStop != z.savedLeftStop) {
    saveLong(ADDR_LEFT_STOP_Z, z.savedLeftStop = z.leftStop);
    changed = true;
  }
  if (z.rightStop != z.savedRightStop) {
    saveLong(ADDR_RIGHT_STOP_Z, z.savedRightStop = z.rightStop);
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
  if (x.pos != x.savedPos) {
    saveLong(ADDR_POS_X, x.savedPos = x.pos);
    changed = true;
  }
  if (x.originPos != x.savedOriginPos) {
    saveLong(ADDR_ORIGIN_POS_X, x.savedOriginPos = x.originPos);
    changed = true;
  }
  if (x.leftStop != x.savedLeftStop) {
    saveLong(ADDR_LEFT_STOP_X, x.savedLeftStop = x.leftStop);
    changed = true;
  }
  if (x.rightStop != x.savedRightStop) {
    saveLong(ADDR_RIGHT_STOP_X, x.savedRightStop = x.rightStop);
    changed = true;
  }
  if (changed) {
    EEPROM.commit();
  }
}

void markAxisOrigin(volatile Axis* a) {
  bool hasSemaphore = xSemaphoreTake(a->mutex, 10) == pdTRUE;
  long finalPos = a->pos + a->pendingPos;
  if (a->leftStop != LONG_MAX) {
    a->leftStop -= finalPos;
  }
  if (a->rightStop != LONG_MIN) {
    a->rightStop -= finalPos;
  }
  a->originPos += finalPos;
  a->pos = -a->pendingPos;
  a->fractionalPos = 0;
  a->pendingPos = 0;
  if (hasSemaphore) {
    xSemaphoreGive(a->mutex);
  }
}

// Loose the thread and mark current physical positions of
// encoder and stepper as a new 0. To be called when dupr changes
// or ELS is turned on/off. Without this, changing dupr will
// result in stepper rushing across the lathe to the new position.
void markOrigin() {
  markAxisOrigin(&z);
  markAxisOrigin(&x);
  noInterrupts();
  spindlePos = 0;
  spindlePosSync = 0;
  interrupts();
}

void markZ0() {
  z.originPos = -z.pos - z.pendingPos;
}

void markX0() {
  x.originPos = -x.pos - x.pendingPos;
}

void updateAsyncTimerSettings() {
  // dupr and therefore direction can change while we're in async mode.
  setDir(&z, dupr > 0);

  // dupr can change while we're in async mode, keep updating timer frequency.
  timerAlarmWrite(async_timer, getTimerLimit(), true);
}

void setDupr(long value) {
  dupr = value;
  markOrigin();
  if (mode == MODE_ASYNC) {
    updateAsyncTimerSettings();
  }
}

void setStarts(int value) {
  if (starts == value) {
    return;
  }
  starts = value;
  markOrigin();
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
  lcdHashLine0 = LCD_HASH_INITIAL;
  lcdHashLine1 = LCD_HASH_INITIAL;
  lcdHashLine2 = LCD_HASH_INITIAL;
  lcdHashLine3 = LCD_HASH_INITIAL;
  delay(2000);
#endif
}

unsigned int getTimerLimit() {
  if (dupr == 0) {
    return 65535;
  }
  return min(long(65535), long(1000000 / (MOTOR_STEPS_Z * abs(dupr) / SCREW_Z_DU)) - 1); // 1000000/Hz - 1
}

// Only used for async movement.
// Keep code in this method to absolute minimum to achieve high stepper speeds.
void IRAM_ATTR onAsyncTimer() {
  if (!isOn || z.movingManually) {
    return;
  } else if (dupr > 0 && (z.leftStop == LONG_MAX || z.pos < z.leftStop)) {
    z.pos++;
  } else if (dupr < 0 && (z.rightStop == LONG_MIN || z.pos > z.rightStop)) {
    z.pos--;
  } else {
    return;
  }

  DLOW(Z_STEP);
  z.stepStartUs = micros();
  delayMicroseconds(10);
  DHIGH(Z_STEP);
}

void setMode(int value) {
  if (mode == value) {
    return;
  }
  if (isOn) {
    setIsOn(false);
  }
  if (mode == MODE_MULTISTART) {
    setStarts(1);
  } else if (mode == MODE_ASYNC) {
    setAsyncTimerEnable(false);
  }
  mode = value;
  if (mode == MODE_ASYNC) {
    timerAttachInterrupt(async_timer, &onAsyncTimer, true);
    updateAsyncTimerSettings();
    setAsyncTimerEnable(true);
  } else if (mode == MODE_MULTISTART) {
    if (starts < 2) {
      setStarts(2);
    }
  }
}

void setConeRatio(float value) {
  coneRatio = value;
  markOrigin();
}

void reset() {
  z.leftStop = LONG_MAX;
  z.rightStop = LONG_MIN;
  z.originPos = 0;
  z.pendingPos = 0;
  x.leftStop = LONG_MAX;
  x.rightStop = LONG_MIN;
  x.originPos = 0;
  x.pendingPos = 0;
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
  spindlePosSync = ((spindlePos - spindleFromPos(z.pos)) % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS;
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
  setIsOn(on);
}

void setIsOn(bool on) {
  isOn = on;
  stepperEnable(&z, on);
  stepperEnable(&x, on);
  markOrigin();
}

void buttonOffRelease() {
  if (millis() - resetMillis > 4000) {
    reset();
  }
}

void buttonLeftStopPress() {
  if (z.leftStop == LONG_MAX) {
    z.leftStop = z.pos;
  } else {
    if (z.pos == z.leftStop) {
      // Spindle is most likely out of sync with the stepper because
      // it was spinning while the lead screw was on the stop.
      setOutOfSync();
    }
    z.leftStop = LONG_MAX;
  }
}

void buttonRightStopPress() {
  if (z.rightStop == LONG_MIN) {
    z.rightStop = z.pos;
  } else {
    if (z.pos == z.rightStop) {
      // Spindle is most likely out of sync with the stepper because
      // it was spinning while the lead screw was on the stop.
      setOutOfSync();
    }
    z.rightStop = LONG_MIN;
  }
}

void buttonUpStopPress() {
  if (x.leftStop == LONG_MAX) {
    x.leftStop = x.pos;
  } else {
    x.leftStop = LONG_MAX;
  }
}

void buttonDownStopPress() {
  if (x.rightStop == LONG_MIN) {
    x.rightStop = x.pos;
  } else {
    x.rightStop = LONG_MIN;
  }
}

bool allowMultiStartAdvance = false;

void nextStart() {
  noInterrupts();
  spindlePos += round(1.0 * ENCODER_STEPS / starts) * (dupr > 0 ? -1 : 1);
  interrupts();
}

void checkIfNextStart() {
  if (starts <= 1 || dupr == 0 || z.rightStop == LONG_MIN || z.leftStop == LONG_MAX) {
    return;
  }
  if (allowMultiStartAdvance && z.pos == (dupr > 0 ? z.rightStop : z.leftStop)) {
    nextStart();
    allowMultiStartAdvance = false;
  } else if (z.pos == (dupr > 0 ? z.leftStop : z.rightStop)) {
    allowMultiStartAdvance = true;
  }
}

long getAsyncMovePos(int sign) {
  long posDiff = sign * MOTOR_STEPS_Z * abs(dupr) / SCREW_Z_DU / 5;
  long posCopy = z.pos;
  if (posDiff > 0 && z.leftStop != LONG_MAX && (posCopy + posDiff) > z.leftStop) {
    return z.leftStop;
  } else if (posDiff < 0 && z.rightStop != LONG_MIN && (posCopy + posDiff) < z.rightStop) {
    return z.rightStop;
  }
  return posCopy + posDiff;
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

void setDir(volatile Axis* a, bool dir) {
  // Start slow if direction changed.
  if (a->direction != dir || !a->directionInitialized) {
    a->speed = SPEED_START_Z;
    a->direction = dir;
    a->directionInitialized = true;
    DWRITE(a->dir, dir ^ a->invertStepper);
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
  if (numpadIndex < 7) {
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

float numpadToConeRatio() {
  return getNumpadResult() / 100000.0;
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
    } else if (keyCode == B_RIGHT) {
      buttonRightPressed = isPress;
    } else if (keyCode == B_UP) {
      buttonUpPressed = isPress;
    } else if (keyCode == B_DOWN) {
      buttonDownPressed = isPress;
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
      float newConeRatio = numpadToConeRatio();
      resetNumpad();
      // Ignore numpad input unless confirmed with ON.
      if (keyCode == B_ON) {
        if (mode == MODE_CONE) {
          setConeRatio(newConeRatio);
        } else {
          if (abs(newDupr) <= DUPR_MAX) {
            setDupr(newDupr);
          }
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
      buttonUpStopPress();
    } else if (keyCode == B_STOPD) {
      buttonDownStopPress();
    } else if (keyCode == B_MODE_OTHER) {
      buttonModePress();
    } else if (keyCode == B_DISPL) {
      buttonDisplayPress();
    } else if (keyCode == B_X) {
      markX0();
    } else if (keyCode == B_Z) {
      markZ0();
    } else if (keyCode == B_A) {
      // TODO.
    } else if (keyCode == B_B) {
      // TODO.
    } else if (keyCode == B_STEP) {
      buttonMoveStepPress();
    } else if (keyCode == B_SETTINGS) {
      // TODO.
    } else if (keyCode == B_REVERSE) {
      buttonReversePress();
    } else if (keyCode == B_MEASURE) {
      buttonMeasurePress();
    } else if (keyCode == B_MODE_GEARS) {
      setMode(MODE_NORMAL);
    } else if (keyCode == B_MODE_CONE) {
      setMode(MODE_CONE);
    }
  }
}

// Moves the stepper.
bool stepTo(volatile Axis* a, long newPos) {
  if (xSemaphoreTake(a->mutex, 10) == pdTRUE) {
    a->pendingPos = newPos - a->pos;
    xSemaphoreGive(a->mutex);
    return true;
  }
  return false;
}

// Calculates stepper position from spindle position.
long posFromSpindle(long s, bool respectStops) {
  long newPos = s * MOTOR_STEPS_Z / SCREW_Z_DU / ENCODER_STEPS * dupr * starts;

  // Respect left/right stops.
  if (respectStops) {
    if (z.rightStop != LONG_MIN && newPos < z.rightStop) {
      newPos = z.rightStop;
    } else if (z.leftStop != LONG_MAX && newPos > z.leftStop) {
      newPos = z.leftStop;
    }
  }

  return newPos;
}

// Calculates spindle position from stepper position.
long spindleFromPos(long p) {
  return p * SCREW_Z_DU * ENCODER_STEPS / MOTOR_STEPS_Z / (dupr * starts);
}

void stepperEnable(volatile Axis* a, bool value) {
  if (!a->needsRest) {
    return;
  }

  if (value) {
    a->stepperEnableCounter++;
    if (value == 1) {
      DHIGH(a->ena);
      // Stepper driver needs some time before it will react to pulses.
      DELAY(100);
    }
  } else if (a->stepperEnableCounter > 0) {
    a->stepperEnableCounter--;
    if (a->stepperEnableCounter == 0) {
      DLOW(a->ena);
    }
  }
}

void moveAxis(volatile Axis* a) {
  // Stepper basically has no speed if it was standing for 10ms.
  if (!stepperIsRunning(a)) {
    a->speed = a->speedStart;
  }

  unsigned long nowUs = micros();
  float delayUs = 1000000.0 / a->speed;
  if (nowUs >= (a->stepStartUs + delayUs) && xSemaphoreTake(a->mutex, 1) == pdTRUE) {
    if (a->pendingPos != 0) {
      DLOW(a->step);

      bool dir = a->pendingPos > 0;
      setDir(a, dir);
      a->pendingPos += dir ? -1 : 1;
      a->pos += dir ? 1 : -1;

      a->speed += ACCELERATION_Z * delayUs / 1000000.0;
      if (a->speed > a->speedMax) {
        a->speed = a->speedMax;
      }
      a->stepStartUs = nowUs;

      DHIGH(a->step);
    }
    xSemaphoreGive(a->mutex);
  }
}

void modeGearbox() {
  if (isOn && spindlePosSync == 0 && !z.movingManually) {
    stepTo(&z, posFromSpindle(spindlePos, true));
  }
}

void modeCone() {
  if (isOn && spindlePosSync == 0 && !z.movingManually && !x.movingManually && coneRatio != 0) {
    // -0.1/1600*400/4166*20000 = -0.12
    float zToXRatio = -coneRatio / z.motorSteps * x.motorSteps / x.screwPitch * z.screwPitch;

    // Respect limits of both axis by translating them into limits on spindlePos value.
    long spindle = spindlePos;
    long spindleMin = LONG_MIN;
    long spindleMax = LONG_MAX;
    if (z.leftStop != LONG_MAX) {
      spindleMax = spindleFromPos(z.leftStop);
    }
    if (z.rightStop != LONG_MIN) {
      spindleMin = spindleFromPos(z.rightStop);
    }
    long lim1 = x.leftStop == LONG_MAX ? LONG_MAX : spindleFromPos(round(x.leftStop / zToXRatio));
    long lim2 = x.rightStop == LONG_MIN ? LONG_MIN : spindleFromPos(round(x.rightStop / zToXRatio));
    spindleMin = max(lim1, lim2);
    spindleMax = min(lim1, lim2);
    if (spindle > spindleMax) {
      spindle = spindleMax;
    } else if (spindle < spindleMin) {
      spindle = spindleMin;
    }

    long zPos = posFromSpindle(spindle, true);
    stepTo(&z, zPos);
    stepTo(&x, round(zPos * zToXRatio));
  }
}

void loop() {
  moveAxis(&z);
  moveAxis(&x);
  if (mode == MODE_NORMAL || mode == MODE_MULTISTART) {
    modeGearbox();
  } else if (mode == MODE_CONE) {
    modeCone();
  }
}

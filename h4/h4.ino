// https://github.com/kachurovskiy/nanoels

/* Change values in this section to suit your hardware. */

// Define your hardware parameters here. Don't remove the ".0" at the end.
#define ENCODER_STEPS 600.0 // 600 step spindle optical rotary encoder

// Spindle rotary encoder pins. Swap values if the rotation direction is wrong.
#define ENC_A 7
#define ENC_B 15

// Main lead screw (Z) parameters.
#define MOTOR_STEPS_Z 1600.0
#define SCREW_Z_DU 20000.0 // 2mm lead screw in deci-microns (10^-7 of a meter)
#define SPEED_START_Z (2 * MOTOR_STEPS_Z) // Initial speed of a motor, steps / second.
#define ACCELERATION_Z (30 * MOTOR_STEPS_Z) // Acceleration of a motor, steps / second ^ 2.
#define SPEED_MANUAL_MOVE_Z (7 * MOTOR_STEPS_Z) // Maximum speed of a motor during manual move, steps / second.
#define INVERT_Z false // change (true/false) if the carriage moves e.g. "left" when you press "right".
#define NEEDS_REST_Z false // Set to false for closed-loop drivers, true for open-loop.
#define MAX_TRAVEL_MM_Z 300 // Lathe bed doesn't allow to travel more than this in one go, 30cm / ~1 foot
#define BACKLASH_DU_Z 6500 // 0.65mm backlash in deci-microns (10^-7 of a meter)

// Cross-slide lead screw (X) parameters.
#define MOTOR_STEPS_X 800.0
#define SCREW_X_DU 4166.6 // 1.25mm lead screw with 3x reduction in deci-microns (10^-7) of a meter
#define SPEED_START_X (2 * MOTOR_STEPS_X) // Initial speed of a motor, steps / second.
#define ACCELERATION_X (20 * MOTOR_STEPS_X) // Acceleration of a motor, steps / second ^ 2.
#define SPEED_MANUAL_MOVE_X (5 * MOTOR_STEPS_X) // Maximum speed of a motor during manual move, steps / second.
#define INVERT_X true // change (true/false) if the carriage moves e.g. "left" when you press "right".
#define NEEDS_REST_X false // Set to false for all kinds of drivers or X will be unlocked when not moving.
#define MAX_TRAVEL_MM_X 100 // Cross slide doesn't allow to travel more than this in one go, 10cm
#define BACKLASH_DU_X 1000 // 0.10mm backlash in deci-microns (10^-7 of a meter)

/* Changing anything below shouldn't be needed for basic use. */

#define LONG_MIN long(-2147483648)
#define LONG_MAX long(2147483647)

#define DUPR_MAX long(254000) // 25.4mm
#define STARTS_MAX 124 // No more than 124-start thread
#define PASSES_MAX 999 // No more turn or face passes than this

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
#define ADDR_STARTS 28 // takes 2 bytes
#define ADDR_MODE 30 // takes 2 bytes
#define ADDR_MEASURE 32 // takes 2 bytes
#define ADDR_ORIGIN_POS_Z 34 // takes 4 bytes
#define ADDR_POS_X 38 // takes 4 bytes
#define ADDR_LEFT_STOP_X 42 // takes 4 bytes
#define ADDR_RIGHT_STOP_X 46 // takes 4 bytes
#define ADDR_ORIGIN_POS_X 50 // takes 4 bytes
#define ADDR_CONE_RATIO 54 // takes 4 bytes
#define ADDR_TURN_PASSES 58 // takes 2 bytes
#define ADDR_MOVE_STEP 62 // takes 4 bytes

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
#define MODE_TURN 4
#define MODE_FACE 5
#define MODE_CUT 6
#define MODE_THREAD 7

#define MEASURE_METRIC 0
#define MEASURE_INCH 1
#define MEASURE_TPI 2

#define ESTOP_NONE 0
#define ESTOP_KEY 1
#define ESTOP_POS 2
#define ESTOP_MARK_ORIGIN 3

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
int emergencyStop = 0;

long dupr = 0; // pitch, tenth of a micron per rotation
long savedDupr = 0; // dupr saved in EEPROM

SemaphoreHandle_t motionMutex; // controls blocks of code where variables affecting the motion loop() are changed

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
  bool isManuallyDisabled;

  bool invertStepper; // change (true/false) if the carriage moves e.g. "left" when you press "right".
  bool needsRest; // set to false for closed-loop drivers, true for open-loop.
  bool movingManually; // whether stepper is being moved by left/right buttons
  long estopSteps; // amount of steps to exceed machine limits
  long backlashSteps; // amount of steps in reverse direction to re-engage the carriage

  int ena; // Enable pin of this motor
  int dir; // Direction pin of this motor
  int step; // Step pin of this motor
};

void initAxis(Axis*  a, float motorSteps, float screwPitch, long speedStart, long speedManualMove, long acceleration, bool invertStepper, bool needsRest, long maxTravelMm, long backlashDu, int ena, int dir, int step) {
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
  a->isManuallyDisabled = false;

  a->invertStepper = invertStepper;
  a->needsRest = needsRest;
  a->movingManually = false;
  a->estopSteps = maxTravelMm * 10000 / a->screwPitch * a->motorSteps;
  a->backlashSteps = backlashDu * a->motorSteps / a->screwPitch;

  a->ena = ena;
  a->dir = dir;
  a->step = step;
}

Axis z;
Axis x;

unsigned long spindleEncTime = 0; // micros() of the previous spindle update
unsigned long spindleEncTimeDiffBulk = 0; // micros() between RPM_BULK spindle updates
unsigned long spindleEncTimeAtIndex0 = 0; // micros() when spindleEncTimeIndex was 0
int spindleEncTimeIndex = 0; // counter going between 0 and RPM_BULK - 1
long spindlePos = 0; // Spindle position
long savedSpindlePos = 0; // spindlePos value saved in EEPROM
volatile long spindlePosDelta = 0; // Unprocessed encoder ticks.

int spindlePosSync = 0;
int savedSpindlePosSync = 0;

bool showAngle = false; // Whether to show 0-359 spindle angle on screen
bool showTacho = false; // Whether to show spindle RPM on screen
bool savedShowAngle = false; // showAngle value saved in EEPROM
bool savedShowTacho = false; // showTacho value saved in EEPROM
int shownRpm = 0;
unsigned long shownRpmTime = 0; // micros() when shownRpm was set

long moveStep = 0; // thousandth of a mm
long savedMoveStep = 0; // moveStep saved in EEPROM

int mode = -1; // mode of operation (ELS, multi-start ELS, asynchronous)
int savedMode = -1; // mode saved in EEPROM

int measure = MEASURE_METRIC; // Whether to show distances in inches
int savedMeasure = MEASURE_METRIC; // measure value saved in EEPROM

float coneRatio = 1; // In cone mode, how much X moves for 1 step of Z
float savedConeRatio = 0; // value of coneRatio saved in EEPROM

int turnPasses = 3; // In turn mode, how many turn passes to make
int savedTurnPasses = 0; // value of turnPasses saved in EEPROM

long setupIndex = 0; // Index of automation setup step

long opIndex = 0; // Index of an automation operation
long opSubIndex = 0; // Sub-index of an automation operation
int opDuprSign = 1; // 1 if dupr was positive when operation started, -1 if negative

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

bool stepperIsRunning(Axis* a) {
  return micros() - a->stepStartUs < 10000;
}

// Returns number of letters printed.
int printDeciMicrons(long deciMicrons, int precisionPointsMax) {
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
    count += printDeciMicrons(value, 5);
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

int printAxisPos(Axis* a) {
  return printDeciMicrons(round((a->pos + a->originPos) * a->screwPitch / a->motorSteps), 3);
}

int printNoTrailing0(float value) {
  long v = round(value * 100000);
  int points = 0;
  if ((v % 10) != 0) {
    points = 5;
  } else if ((v % 100) != 0) {
    points = 4;
  } else if ((v % 1000) != 0) {
    points = 3;
  } else if ((v % 10000) != 0) {
    points = 2;
  } else if ((v % 100000) != 0) {
    points = 1;
  }
  return lcd.print(value, points);
}

bool needZStops() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_THREAD;
}

bool isPassMode() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CUT || mode == MODE_THREAD;
}

bool isSetupAndGoMode() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CONE || mode == MODE_CUT || mode == MODE_THREAD;
}

void updateDisplay() {
  if (emergencyStop != ESTOP_NONE) {
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
    } else if (mode == MODE_TURN) {
      charIndex += lcd.print("TURN ");
    } else if (mode == MODE_FACE) {
      charIndex += lcd.print("FACE ");
    } else if (mode == MODE_CUT) {
      charIndex += lcd.print("CUT ");
    } else if (mode == MODE_THREAD) {
      charIndex += lcd.print("THRD ");
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
    charIndex += printDeciMicrons(moveStep, 5);
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
  long newHashLine2 = zDisplayPos + xDisplayPos + measure + z.isManuallyDisabled + x.isManuallyDisabled;
  if (lcdHashLine2 != newHashLine2) {
    lcdHashLine2 = newHashLine2;
    charIndex = 0;
    lcd.setCursor(0, 2);
    if (z.isManuallyDisabled) {
      charIndex += lcd.print("Z disable");
    } else {
      if (xDisplayPos == 0 && !x.isManuallyDisabled) {
        charIndex += lcd.print("Position ");
      }
      charIndex += printAxisPos(&z);
    }
    while (charIndex < 10) {
      charIndex += lcd.print(" ");
    }
    if (x.isManuallyDisabled) {
      charIndex += lcd.print("X disable");
    } else if (xDisplayPos != 0) {
      charIndex += printAxisPos(&x);
    }
    printLcdSpaces(charIndex);
  }

  long numpadResult = getNumpadResult();
  long newHashLine3 = z.pos + (showAngle ? spindlePos : -1) + (showTacho ? rpm : -2) + measure + (numpadResult > 0 ? numpadResult : -1) + mode * 5 +
      (mode == MODE_CONE ? round(coneRatio * 10000) : 0) + turnPasses + opIndex + setupIndex + isOn * 4 + (inNumpad ? 10 : 0) +
      (z.leftStop == LONG_MAX ? 123 : z.leftStop) + (z.rightStop == LONG_MIN ? 1234 : z.rightStop) +
      (x.leftStop == LONG_MAX ? 1235 : x.leftStop) + (x.rightStop == LONG_MIN ? 123456 : x.rightStop);
  if (lcdHashLine3 != newHashLine3) {
    lcdHashLine3 = newHashLine3;
    charIndex = 0;
    lcd.setCursor(0, 3);
    if (isPassMode()) {
      bool missingStops = needZStops() && (z.leftStop == LONG_MAX || z.rightStop == LONG_MIN) || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN;
      if (!inNumpad && missingStops) {
        charIndex += lcd.print(needZStops() ? "Set all stops" : "Set X stops");
      } else if (numpadResult != 0 && setupIndex == 1) {
        long passes = min(long(PASSES_MAX), numpadResult);
        charIndex += lcd.print(passes);
        charIndex += lcd.print(" passes?");
      } else if (!isOn && setupIndex == 1) {
        charIndex += lcd.print(turnPasses);
        charIndex += lcd.print(" passes?");
      } else if (!isOn && setupIndex == 2) {
        charIndex += lcd.print("Go?");
      } else if (isOn && numpadResult == 0) {
        charIndex += lcd.print("Operation ");
        charIndex += lcd.print(opIndex);
        charIndex += lcd.print(" of ");
        charIndex += lcd.print(turnPasses + 1);
      }
    } else if (mode == MODE_CONE) {
      if (numpadResult != 0 && setupIndex == 1) {
        charIndex += lcd.print("Use ratio ");
        charIndex += lcd.print(numpadToConeRatio(), 5);
        charIndex += lcd.print("?");
      } else if (!isOn && setupIndex == 1) {
        charIndex += lcd.print("Use ratio ");
        charIndex += printNoTrailing0(coneRatio);
        charIndex += lcd.print("?");
      } else if (!isOn && setupIndex == 2) {
        charIndex += lcd.print("Go?");
      } else if (isOn && numpadResult == 0) {
        charIndex += lcd.print("Cone ratio ");
        charIndex += printNoTrailing0(coneRatio);
      }
    }

    if (charIndex == 0 && inNumpad) { // Also show for 0 input to allow setting limits to 0.
      charIndex += lcd.print("Use ");
      charIndex += printDupr(numpadToDeciMicrons());
      charIndex += lcd.print("?");
    }

    if (charIndex > 0) {
      // No space for shared RPM/angle text.
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
void IRAM_ATTR spinEnc() {
  spindlePosDelta += DREAD(ENC_B) ? -1 : 1;
}

void setAsyncTimerEnable(bool value) {
  if (value) {
    timerAlarmEnable(async_timer);
  } else {
    timerAlarmDisable(async_timer);
  }
}

void taskDisplay(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    updateDisplay();
    // Calling EEPROM.commit() blocks all interrupts for 30ms, don't call saveIfChanged() if
    // encoder is likely to move soon.
    if (!stepperIsRunning(&z) && !stepperIsRunning(&x) && (micros() > spindleEncTime + 1000000)) {
      saveIfChanged();
    }
    taskYIELD();
  }
  reset();
  saveIfChanged();
}

void taskKeypad(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    processKeypadEvents();
    taskYIELD();
  }
}

void waitForPendingPosNear0(Axis* a) {
  while (abs(a->pendingPos) > a->motorSteps / 10) {
    taskYIELD();
  }
}

void waitForPendingPos0(Axis* a) {
  while (a->pendingPos != 0) {
    taskYIELD();
  }
}

void taskMoveZ(void *param) {
  while (emergencyStop == ESTOP_NONE) {
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
    if (isOn && dupr != 0) {
      // Move by moveStep in the desired direction but stay in the thread by possibly traveling a little more.
      int diff = ceil(moveStep * 1.0 / abs(dupr * starts)) * ENCODER_STEPS * sign * (dupr > 0 ? 1 : -1);
      long prevSpindlePos = spindlePos;
      bool resting = false;
      do {
        if (mode != MODE_ASYNC && xSemaphoreTake(motionMutex, 100) == pdTRUE) {
          if (!resting) {
            spindlePos += diff;
          }
          // If spindle is moving, it will be changing spindlePos at the same time. Account for it.
          while (diff > 0 ? (spindlePos < prevSpindlePos) : (spindlePos > prevSpindlePos)) {
            spindlePos += diff;
          };
          prevSpindlePos = spindlePos;
          xSemaphoreGive(motionMutex);
        }

        long newPos = mode == MODE_ASYNC ? getAsyncMovePos(sign) : posFromSpindle(&z, prevSpindlePos, true);
        if (newPos != z.pos) {
          stepTo(&z, newPos);
          waitForPendingPosNear0(&z);
        } else if (z.pos == (left ? z.leftStop : z.rightStop)) {
          // We're standing on a stop with the L/R move button pressed.
          resting = true;
          if (xSemaphoreTake(motionMutex, 100) == pdTRUE) {
            checkIfNextStart();
            xSemaphoreGive(motionMutex);
          }
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
    }
    if (isOn) {
      waitForPendingPos0(&z);
      if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
        setEmergencyStop(ESTOP_MARK_ORIGIN);
      } else {
        markOrigin();
        xSemaphoreGive(motionMutex);
      }
      if (isPassMode()) {
        setIsOn(false);
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
  while (emergencyStop == ESTOP_NONE) {
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
      waitForPendingPos0(&x);
      markOrigin();
      if (isPassMode()) {
        setIsOn(false);
      }
    }
    x.movingManually = false;
    x.speedMax = LONG_MAX;
    stepperEnable(&x, false);

    taskYIELD();
  }
}

void taskAttachInterrupts(void *param) {
  // Attaching interrupt on core 0 to have more time on core 1 where axes are moved.
  attachInterrupt(digitalPinToInterrupt(ENC_A), spinEnc, FALLING);
  vTaskDelete(NULL);
}

void setEmergencyStop(int kind) {
  emergencyStop = kind;
  setAsyncTimerEnable(false);
  xSemaphoreTake(z.mutex, 10);
  xSemaphoreTake(x.mutex, 10);
  lcd.clear();
  lcd.setCursor(0, 0);
  if (emergencyStop == ESTOP_KEY) {
    lcd.print("Key down at power-up");
    lcd.setCursor(0, 1);
    lcd.print("Hardware failure?");
  } else if (emergencyStop == ESTOP_POS) {
    lcd.print("Requested position");
    lcd.setCursor(0, 1);
    lcd.print("outside machine");
  } else if (emergencyStop == ESTOP_MARK_ORIGIN) {
    lcd.print("Unable to");
    lcd.setCursor(0, 1);
    lcd.print("mark origin");
  } else {
    lcd.print("Emergency stop");
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
    saveLong(ADDR_MOVE_STEP, MOVE_STEP_1);
    EEPROM.put(ADDR_CONE_RATIO, coneRatio);
    EEPROM.put(ADDR_TURN_PASSES, turnPasses);
  }

  initAxis(&z, MOTOR_STEPS_Z, SCREW_Z_DU, SPEED_START_Z, SPEED_MANUAL_MOVE_Z, ACCELERATION_Z, INVERT_Z, NEEDS_REST_Z, MAX_TRAVEL_MM_Z, BACKLASH_DU_Z, Z_ENA, Z_DIR, Z_STEP);
  initAxis(&x, MOTOR_STEPS_X, SCREW_X_DU, SPEED_START_X, SPEED_MANUAL_MOVE_X, ACCELERATION_X, INVERT_X, NEEDS_REST_X, MAX_TRAVEL_MM_X, BACKLASH_DU_X, X_ENA, X_DIR, X_STEP);

  isOn = false;
  savedDupr = dupr = loadLong(ADDR_DUPR);
  motionMutex = xSemaphoreCreateMutex();
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
  savedMoveStep = loadLong(ADDR_MOVE_STEP);
  moveStep = savedMoveStep > 0 ? savedMoveStep : MOVE_STEP_1;
  savedMode = loadInt(ADDR_MODE);
  savedMeasure = measure = loadInt(ADDR_MEASURE);
  setMode(savedMode);
  EEPROM.get(ADDR_CONE_RATIO, coneRatio);
  savedTurnPasses = turnPasses = loadInt(ADDR_TURN_PASSES);

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
    keypad.flush();
  }

  delay(100);
  if (keypad.available()) {
    setEmergencyStop(ESTOP_KEY);
    return;
  }

  // Non-time-sensitive tasks on core 0.
  xTaskCreatePinnedToCore(taskDisplay, "taskDisplay", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskKeypad, "taskKeypad", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskMoveZ, "taskMoveZ", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskMoveX, "taskMoveX", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskAttachInterrupts, "taskAttachInterrupts", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
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
    saveLong(ADDR_MOVE_STEP, savedMoveStep = moveStep);
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
  if (coneRatio != savedConeRatio) {
    EEPROM.put(ADDR_CONE_RATIO, savedConeRatio = coneRatio);
    changed = true;
  }
  if (turnPasses != savedTurnPasses) {
    saveInt(ADDR_TURN_PASSES, savedTurnPasses = turnPasses);
    changed = true;
  }
  if (changed) {
    EEPROM.commit();
  }
}

void markAxisOrigin(Axis* a) {
  bool hasSemaphore = xSemaphoreTake(a->mutex, 10) == pdTRUE;
  if (a->leftStop != LONG_MAX) {
    a->leftStop -= a->pos;
  }
  if (a->rightStop != LONG_MIN) {
    a->rightStop -= a->pos;
  }
  a->originPos += a->pos;
  a->pos = 0;
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
// Must be called while holding motionMutex.
void markOrigin() {
  markAxisOrigin(&z);
  markAxisOrigin(&x);
  spindlePos = 0;
  spindlePosSync = 0;
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
  if (xSemaphoreTake(motionMutex, 1000) != pdTRUE) {
    return;
  }
  dupr = value;
  markOrigin();
  xSemaphoreGive(motionMutex);
  if (mode == MODE_ASYNC) {
    updateAsyncTimerSettings();
  }
}

void setStarts(int value) {
  if (starts == value) {
    return;
  }
  if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
    return;
  }
  starts = value;
  markOrigin();
  xSemaphoreGive(motionMutex);
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
  setupIndex = 0;
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

void setTurnPasses(int value) {
  if (isOn) {
    beep();
  } else {
    turnPasses = value;
  }
}

void setConeRatio(float value) {
  if (xSemaphoreTake(motionMutex, 1000) != pdTRUE) {
    return;
  }
  coneRatio = value;
  markOrigin();
  xSemaphoreGive(motionMutex);
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
  coneRatio = 1;
}

// Called when left/right stop restriction is removed while we're on it.
// Prevents stepper from rushing to a position far away by waiting for the right
// spindle position and starting smoothly.
void setOutOfSync() {
  if (!isOn || mode == MODE_ASYNC) {
    return;
  }
  spindlePosSync = ((spindlePos - spindleFromPos(&z, z.pos)) % (int) ENCODER_STEPS + (int) ENCODER_STEPS) % (int) ENCODER_STEPS;
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
  // Mutex is aquired in setDupr() and setStarts().
  bool minus = !plus;
  if (mode == MODE_MULTISTART) {
    if (minus && starts > 2) {
      setStarts(starts - 1);
    } else if (plus && starts < STARTS_MAX) {
      setStarts(starts + 1);
    }
  } else if (isPassMode() && setupIndex == 1 && getNumpadResult() == 0) {
    if (minus && turnPasses > 1) {
      setTurnPasses(turnPasses - 1);
    } else if (plus && turnPasses < PASSES_MAX) {
      setTurnPasses(turnPasses + 1);
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

void beep() {
  tone(BUZZ, 1000);
  DELAY(500);
  noTone(BUZZ);
}

void buttonOnOffPress(bool on) {
  resetMillis = millis();
  if (on && isSetupAndGoMode()) {
    if (setupIndex == 0) {
      // Passes / ratio entry step.
      setupIndex = 1;
      return;
    } else if (setupIndex == 1) {
      // "Go?" step.
      setupIndex = 2;
      return;
    } // else start.
  }
  setIsOn(on);
}

void setIsOn(bool on) {
  if (isOn && on) {
    return;
  }

  if (on && isPassMode()) {
    if (needZStops() && (z.leftStop == LONG_MAX || z.rightStop == LONG_MIN) || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN || turnPasses <= 0) {
      beep();
      return;
    }
  }

  bool hasMutex = xSemaphoreTake(motionMutex, 1000) == pdTRUE;
  if (!on) {
    isOn = false;
    setupIndex = 0;
  }
  stepperEnable(&z, on);
  stepperEnable(&x, on);
  markOrigin();
  if (on) {
    isOn = true;
    opDuprSign = dupr >= 0 ? 1 : -1;
    opIndex = 0;
    opSubIndex = 0;
    setupIndex = 0;
  }
  if (hasMutex) {
    xSemaphoreGive(motionMutex);
  }
}

void buttonOffRelease() {
  if (millis() - resetMillis > 4000) {
    reset();
    splashScreen();
  }
}

bool setLeftStop(Axis* a, long value) {
  if (xSemaphoreTake(motionMutex, 1000) != pdTRUE) {
    return false;
  }
  if (a->leftStop == value || a->pos > value) {
    xSemaphoreGive(motionMutex);
    return false;
  }
  bool onFormerStop = a->pos == a->leftStop;
  a->leftStop = value;
  if (onFormerStop) {
    // Spindle is most likely out of sync with the stepper because
    // it was spinning while the lead screw was on the stop.
    if (&z == a) {
      setOutOfSync();
    }
    if (mode == MODE_CONE) {
      // To avoid X rushing to a far away position if standing on limit.
      markOrigin();
    }
  }
  xSemaphoreGive(motionMutex);
  return true;
}

bool setRightStop(Axis* a, long value) {
  if (xSemaphoreTake(motionMutex, 1000) != pdTRUE) {
    return false;
  }
  if (a->rightStop == value || a->pos < value) {
    xSemaphoreGive(motionMutex);
    return false;
  }
  bool onFormerStop = a->pos == a->rightStop;
  a->rightStop = value;
  if (onFormerStop) {
    // Spindle is most likely out of sync with the stepper because
    // it was spinning while the lead screw was on the stop.
    if (&z == a) {
      setOutOfSync();
    }
    if (mode == MODE_CONE) {
      // To avoid X rushing to a far away position if standing on limit.
      markOrigin();
    }
  }
  xSemaphoreGive(motionMutex);
  return true;
}

void buttonLeftStopPress() {
  setLeftStop(&z, z.leftStop == LONG_MAX ? z.pos : LONG_MAX);
}

void buttonRightStopPress() {
  setRightStop(&z, z.rightStop == LONG_MIN ? z.pos : LONG_MIN);
}

void buttonUpStopPress() {
  setLeftStop(&x, x.leftStop == LONG_MAX ? x.pos : LONG_MAX);
}

void buttonDownStopPress() {
  setRightStop(&x, x.rightStop == LONG_MIN ? x.pos : LONG_MIN);
}

bool allowMultiStartAdvance = false;

void checkIfNextStart() {
  if (starts <= 1 || dupr == 0 || z.rightStop == LONG_MIN || z.leftStop == LONG_MAX) {
    return;
  }
  if (allowMultiStartAdvance && z.pos == (dupr > 0 ? z.rightStop : z.leftStop)) {
    spindlePos += round(1.0 * ENCODER_STEPS / starts) * (dupr > 0 ? -1 : 1);
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

void setDir(Axis* a, bool dir) {
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

void numpadPlusMinus(bool plus) {
  if (numpadDigits[numpadIndex - 1] < 9 && plus) {
    numpadDigits[numpadIndex - 1]++;
  } else if (numpadDigits[numpadIndex - 1] > 1 && !plus) {
    numpadDigits[numpadIndex - 1]--;
  }
  // TODO: implement going over 9 and below 1.
}

long numpadToDeciMicrons() {
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
    } else if (!inNumpad || !isPress) {
      if (keyCode == B_LEFT) {
        buttonLeftPressed = isPress;
      } else if (keyCode == B_RIGHT) {
        buttonRightPressed = isPress;
      } else if (keyCode == B_UP) {
        buttonUpPressed = isPress;
      } else if (keyCode == B_DOWN) {
        buttonDownPressed = isPress;
      }
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
    } else if (inNumpad && (keyCode == B_PLUS || keyCode == B_MINUS)) {
      numpadPlusMinus(keyCode == B_PLUS);
      continue;
    } else if (inNumpad) {
      inNumpad = false;
      long newDu = numpadToDeciMicrons();
      float newConeRatio = numpadToConeRatio();
      long numpadResult = getNumpadResult();
      resetNumpad();
      // Ignore numpad input unless confirmed with ON.
      if (keyCode == B_ON) {
        if (isPassMode() && setupIndex == 1) {
          setTurnPasses(int(min(long(PASSES_MAX), numpadResult)));
        } else if (mode == MODE_CONE && setupIndex == 1) {
          setConeRatio(newConeRatio);
        } else {
          if (abs(newDu) <= DUPR_MAX) {
            setDupr(newDu);
          }
        }
        // Don't use this ON press for starting the motion.
        continue;
      }

      // Shared piece for stops and moves.
      Axis* a = (keyCode == B_STOPL || keyCode == B_STOPR || keyCode == B_LEFT || keyCode == B_RIGHT) ? &z : &x;
      long pos = a->pos + newDu / a->screwPitch * a->motorSteps * ((keyCode == B_STOPL || keyCode == B_STOPU || keyCode == B_LEFT || keyCode == B_UP) ? 1 : -1);

      // Potentially assign a new value to a limit. Treat newDu as a relative distance from current position.
      bool isStop = true;
      bool stopSet = false;
      if (keyCode == B_STOPL) {
        stopSet = setLeftStop(&z, pos);
      } else if (keyCode == B_STOPR) {
        stopSet = setRightStop(&z, pos);
      } else if (keyCode == B_STOPU) {
        stopSet = setLeftStop(&x, pos);
      } else if (keyCode == B_STOPD) {
        stopSet = setRightStop(&x, pos);
      } else {
        isStop = false;
      }
      if (isStop) {
        if (!stopSet) {
          beep();
        }
        continue;
      }

      // Potentially move by newDu in the given direction.
      // We don't support precision manual moves when ON yet. Can't stay in the thread for most modes.
      if (!isOn && (keyCode == B_LEFT || keyCode == B_RIGHT || keyCode == B_UP || keyCode == B_DOWN)) {
        if (pos < a->rightStop) {
          pos = a->rightStop;
          beep();
        } else if (pos > a->leftStop) {
          pos = a->leftStop;
          beep();
        } else if (abs(pos - a->pos) > a->estopSteps) {
          beep();
          continue;
        }
        a->speedMax = a->speedManualMove;
        stepTo(a, pos);
        continue;
      }

      if (keyCode == B_STEP) {
        if (newDu > 0) {
          moveStep = newDu;
        } else {
          beep();
        }
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
      x.isManuallyDisabled = !x.isManuallyDisabled;
      updateEnable(&x);
    } else if (keyCode == B_B) {
      z.isManuallyDisabled = !z.isManuallyDisabled;
      updateEnable(&z);
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
    } else if (keyCode == B_MODE_TURN) {
      setMode(MODE_TURN);
    } else if (keyCode == B_MODE_FACE) {
      setMode(MODE_FACE);
    } else if (keyCode == B_MODE_CONE) {
      setMode(MODE_CONE);
    } else if (keyCode == B_MODE_CUT) {
      setMode(MODE_CUT);
    } else if (keyCode == B_MODE_THREAD) {
      setMode(MODE_THREAD);
    }
  }
}

// Moves the stepper.
bool stepTo(Axis* a, long newPos) {
  if (xSemaphoreTake(a->mutex, 10) == pdTRUE) {
    a->pendingPos = newPos - a->pos;
    xSemaphoreGive(a->mutex);
    return true;
  }
  return false;
}

// Calculates stepper position from spindle position.
long posFromSpindle(Axis* a, long s, bool respectStops) {
  long newPos = s * a->motorSteps / a->screwPitch / ENCODER_STEPS * dupr * starts;

  // Respect left/right stops.
  if (respectStops) {
    if (newPos < a->rightStop) {
      newPos = a->rightStop;
    } else if (newPos > a->leftStop) {
      newPos = a->leftStop;
    }
  }

  return newPos;
}

// Calculates spindle position from stepper position.
long spindleFromPos(Axis* a, long p) {
  return p * a->screwPitch * ENCODER_STEPS / a->motorSteps / (dupr * starts);
}

void stepperEnable(Axis* a, bool value) {
  if (!a->needsRest) {
    return;
  }
  if (value) {
    a->stepperEnableCounter++;
    if (value == 1) {
      updateEnable(a);
    }
  } else if (a->stepperEnableCounter > 0) {
    a->stepperEnableCounter--;
    if (a->stepperEnableCounter == 0) {
      updateEnable(a);
    }
  }
}

void updateEnable(Axis* a) {
  if (!a->isManuallyDisabled && (!a->needsRest || a->stepperEnableCounter > 0)) {
    DHIGH(a->ena);
    // Stepper driver needs some time before it will react to pulses.
    DELAY(100);
  } else {
    DLOW(a->ena);
  }
}

bool setPosEmergencyStop() {
  if (abs(z.pendingPos) > z.estopSteps || abs(x.pendingPos) > x.estopSteps) {
    setEmergencyStop(ESTOP_POS);
    return true;
  }
  return false;
}

void moveAxis(Axis* a) {
  // Most of the time a step isn't needed.
  if (a->pendingPos == 0) {
    return;
  }

  // Stepper basically has no speed if it was standing for 10ms.
  if (!stepperIsRunning(a)) {
    a->speed = a->speedStart;
  }

  unsigned long nowUs = micros();
  float delayUs = 1000000.0 / a->speed;
  if (nowUs >= (a->stepStartUs + delayUs) && xSemaphoreTake(a->mutex, 1) == pdTRUE) {
    // Check pendingPos again now that we have the mutex.
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
  if (z.movingManually) {
    return;
  }
  z.speedMax = LONG_MAX;
  stepTo(&z, posFromSpindle(&z, spindlePos, true));
}

void modeTurn(Axis* main, Axis* aux) {
  if (main->movingManually || aux->movingManually || turnPasses <= 0 ||
      main->leftStop == LONG_MAX || main->rightStop == LONG_MIN ||
      aux->leftStop == LONG_MAX || aux->rightStop == LONG_MIN ||
      dupr == 0 || (dupr * opDuprSign < 0)) {
    return;
  }
  aux->speedMax = aux->speedManualMove;

  // Start from left or right depending on the pitch.
  long mainStartStop = opDuprSign > 0 ? main->rightStop : main->leftStop;
  long mainEndStop = opDuprSign > 0 ? main->leftStop : main->rightStop;
  long mainBacklash = -opDuprSign * main->backlashSteps;

  // Will vary for internal/external cuts.
  long auxStartStop = aux->rightStop;
  long auxEndStop = aux->leftStop;
  long auxBacklash = -aux->backlashSteps;

  if (opIndex == 0) {
    // Move to right-bottom limit, take out backlash.
    main->speedMax = main->speedManualMove;
    long auxPos = auxStartStop + (opSubIndex == 0 ? auxBacklash : 0);
    long mainPos = mainStartStop + (opSubIndex == 0 ? mainBacklash : 0);
    stepTo(main, mainPos);
    stepTo(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      if (opSubIndex == 0) {
        opSubIndex = 1;
      } else {
        opIndex = 1;
        opSubIndex = 0;
      }
    }
  } else if (opIndex <= turnPasses) {
    // Bringing X to starting position.
    if (opSubIndex == 0) {
      long auxPos = auxEndStop - (auxEndStop - auxStartStop) / turnPasses * (turnPasses - opIndex);
      stepTo(aux, auxPos);
      if (aux->pos == auxPos) {
        long base = round(spindleFromPos(main, main->pos) / ENCODER_STEPS) * ENCODER_STEPS - ENCODER_STEPS;
        spindlePos = base + spindlePos % int(ENCODER_STEPS);
        opSubIndex = 1;
      }
    }
    // Doing the pass cut.
    if (opSubIndex == 1) {
      main->speedMax = LONG_MAX;
      stepTo(main, posFromSpindle(main, spindlePos, true));
      if (main->pos == mainEndStop) {
        opSubIndex = 2;
      }
    }
    // Retracting the tool
    if (opSubIndex == 2) {
      long auxPos = auxStartStop;
      stepTo(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 3;
      }
    }
    // Returning to start main minus backlash.
    if (opSubIndex == 3) {
      main->speedMax = main->speedManualMove;
      long mainPos = mainStartStop + mainBacklash;
      stepTo(main, mainPos);
      if (main->pos == mainPos) {
        opSubIndex = 4;
      }
    }
    // Returning to start of main.
    if (opSubIndex == 4) {
      long mainPos = mainStartStop;
      stepTo(main, mainPos);
      if (main->pos == mainPos) {
        main->speedMax = LONG_MAX;
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    // Move to right-bottom limit, take out backlash.
    main->speedMax = main->speedManualMove;
    long auxPos = auxStartStop + (opSubIndex == 0 ? auxBacklash : 0);
    long mainPos = mainStartStop + (opSubIndex == 0 ? mainBacklash : 0);
    stepTo(main, mainPos);
    stepTo(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      if (opSubIndex == 0) {
        opSubIndex = 1;
      } else {
        beep();
        setIsOn(false);
      }
    }
  }
}

void modeCone() {
  if (z.movingManually || x.movingManually || coneRatio == 0) {
    return;
  }

  float zToXRatio = -coneRatio / 2 / z.motorSteps * x.motorSteps / x.screwPitch * z.screwPitch;
  if (zToXRatio == 0) {
    return;
  }

  // TODO: calculate maximum speeds and accelerations to avoid potential desync.
  x.speedMax = LONG_MAX;
  z.speedMax = LONG_MAX;

  // Respect limits of both axis by translating them into limits on spindlePos value.
  long spindle = spindlePos;
  long spindleMin = LONG_MIN;
  long spindleMax = LONG_MAX;
  if (z.leftStop != LONG_MAX) {
    (dupr > 0 ? spindleMax : spindleMin) = spindleFromPos(&z, z.leftStop);
  }
  if (z.rightStop != LONG_MIN) {
    (dupr > 0 ? spindleMin: spindleMax) = spindleFromPos(&z, z.rightStop);
  }
  if (x.leftStop != LONG_MAX) {
    long lim = spindleFromPos(&z, round(x.leftStop / zToXRatio));
    if (zToXRatio < 0) {
      (dupr > 0 ? spindleMin: spindleMax) = lim;
    } else {
      (dupr > 0 ? spindleMax : spindleMin) = lim;
    }
  }
  if (x.rightStop != LONG_MIN) {
    long lim = spindleFromPos(&z, round(x.rightStop / zToXRatio));
    if (zToXRatio < 0) {
      (dupr > 0 ? spindleMax : spindleMin) = lim;
    } else {
      (dupr > 0 ? spindleMin: spindleMax) = lim;
    }
  }
  if (spindle > spindleMax) {
    spindle = spindleMax;
  } else if (spindle < spindleMin) {
    spindle = spindleMin;
  }

  stepTo(&z, posFromSpindle(&z, spindle, true));
  stepTo(&x, round(z.pos * zToXRatio));
}

void modeCut() {
  if (x.movingManually || turnPasses <= 0 || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN || dupr <= 0) {
    return;
  }
  if (opIndex == 0) {
    // Move to back limit, take out backlash.
    x.speedMax = x.speedManualMove;
    long xPos = x.rightStop - (opSubIndex == 0 ? x.backlashSteps : 0);
    stepTo(&x, xPos);
    if (x.pos == xPos) {
      if (opSubIndex == 0) {
        opSubIndex = 1;
      } else {
        opIndex = 1;
        opSubIndex = 0;
      }
    }
  } else if (opIndex <= turnPasses) {
    // Set spindlePos and x.pos in sync.
    if (opSubIndex == 0) {
      markAxisOrigin(&x);
      spindlePos = 0;
      spindlePosSync = 0;
      opSubIndex = 1;
    }
    // Doing the pass cut.
    if (opSubIndex == 1) {
      x.speedMax = LONG_MAX;
      long maxPos = x.leftStop - (x.leftStop - x.rightStop) / turnPasses * (turnPasses - opIndex);
      long xPos = min(maxPos, posFromSpindle(&x, spindlePos, true));
      stepTo(&x, xPos);
      if (x.pos == maxPos) {
        opSubIndex = 2;
      }
    }
    // Returning to start minus backlash.
    if (opSubIndex == 2) {
      x.speedMax = x.speedManualMove;
      long xPos = x.rightStop - x.backlashSteps;
      stepTo(&x, xPos);
      if (x.pos == xPos) {
        opSubIndex = 3;
      }
    }
    // Returning to start.
    if (opSubIndex == 3) {
      long xPos = x.rightStop;
      stepTo(&x, xPos);
      if (x.pos == xPos) {
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    beep();
    setIsOn(false);
  }
}

void discountFullSpindleTurns() {
  // When standing at the stop, ignore full spindle turns.
  // This allows to avoid waiting when spindle direction reverses
  // and reduces the chance of the skipped stepper steps since
  // after a reverse the spindle starts slow.
  if (dupr != 0 && !stepperIsRunning(&z)) {
    int spindlePosDiff = 0;
    if (z.pos == z.rightStop) {
      long stopSpindlePos = spindleFromPos(&z, z.rightStop);
      if (dupr > 0) {
        if (spindlePos < stopSpindlePos - ENCODER_STEPS) {
          spindlePosDiff = ENCODER_STEPS;
        }
      } else {
        if (spindlePos > stopSpindlePos + ENCODER_STEPS) {
          spindlePosDiff = -ENCODER_STEPS;
        }
      }
    } else if (z.pos == z.leftStop) {
      long stopSpindlePos = spindleFromPos(&z, z.leftStop);
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
      spindlePos += spindlePosDiff;
    }
    checkIfNextStart();
  }
}

void processSpindlePosDelta() {
  noInterrupts();
  long delta = spindlePosDelta;
  spindlePosDelta = 0;
  interrupts();
  if (delta == 0) {
    return;
  }

  unsigned long microsNow = micros();
  if (showTacho) {
    if (spindleEncTimeIndex >= RPM_BULK) {
      spindleEncTimeDiffBulk = microsNow - spindleEncTimeAtIndex0;
      spindleEncTimeAtIndex0 = microsNow;
      spindleEncTimeIndex = 0;
    }
    spindleEncTimeIndex += abs(delta);
  } else {
    spindleEncTimeDiffBulk = 0;
  }

  spindlePos += delta;
  spindleEncTime = microsNow;

  if (spindlePosSync != 0) {
    spindlePosSync += delta;
    if (spindlePosSync % int(ENCODER_STEPS) == 0) {
      spindlePosSync = 0;
      spindlePos = spindleFromPos(&z, z.pos);
    }
  }
}

void loop() {
  if (emergencyStop != ESTOP_NONE || setPosEmergencyStop()) {
    return;
  }
  if (xSemaphoreTake(motionMutex, 1) != pdTRUE) {
    return;
  }
  processSpindlePosDelta();
  discountFullSpindleTurns();
  if (!isOn || dupr == 0 || spindlePosSync != 0) {
    // None of the modes work.
  } else if (mode == MODE_NORMAL || mode == MODE_MULTISTART) {
    modeGearbox();
  } else if (mode == MODE_TURN) {
    modeTurn(&z, &x);
  } else if (mode == MODE_FACE) {
    modeTurn(&x, &z);
  } else if (mode == MODE_CUT) {
    modeCut();
  } else if (mode == MODE_CONE) {
    modeCone();
  } else if (mode == MODE_THREAD) {
    modeTurn(&z, &x);
  }
  moveAxis(&z);
  moveAxis(&x);
  xSemaphoreGive(motionMutex);
}

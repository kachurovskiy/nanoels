// https://github.com/kachurovskiy/nanoels

/* Change values in this section to suit your hardware. */

// Define your hardware parameters here. Don't remove the ".0" at the end.
#define ENCODER_STEPS 600.0 // 600 step spindle optical rotary encoder
#define ENCODER_BACKLASH 3 // Numer of impulses encoder can issue without movement of the spindle

// Spindle rotary encoder pins. Swap values if the rotation direction is wrong.
#define ENC_A 7
#define ENC_B 15

// Main lead screw (Z) parameters.
#define MOTOR_STEPS_Z 800.0
#define SCREW_Z_DU 20000.0 // 2mm lead screw in deci-microns (10^-7 of a meter)
#define SPEED_START_Z (2 * MOTOR_STEPS_Z) // Initial speed of a motor, steps / second.
#define ACCELERATION_Z (40 * MOTOR_STEPS_Z) // Acceleration of a motor, steps / second ^ 2.
#define SPEED_MANUAL_MOVE_Z (6 * MOTOR_STEPS_Z) // Maximum speed of a motor during manual move, steps / second.
#define INVERT_Z false // change (true/false) if the carriage moves e.g. "left" when you press "right".
#define NEEDS_REST_Z false // Set to false for closed-loop drivers, true for open-loop.
#define MAX_TRAVEL_MM_Z 300 // Lathe bed doesn't allow to travel more than this in one go, 30cm / ~1 foot
#define BACKLASH_DU_Z 6500 // 0.65mm backlash in deci-microns (10^-7 of a meter)

// Cross-slide lead screw (X) parameters.
#define MOTOR_STEPS_X 2400.0 // 800 steps at 3x reduction
#define SCREW_X_DU 12500.0 // 1.25mm lead screw with 3x reduction in deci-microns (10^-7) of a meter
#define SPEED_START_X (MOTOR_STEPS_X) // Initial speed of a motor, steps / second.
#define ACCELERATION_X (10 * MOTOR_STEPS_X) // Acceleration of a motor, steps / second ^ 2.
#define SPEED_MANUAL_MOVE_X (2 * MOTOR_STEPS_X) // Maximum speed of a motor during manual move, steps / second.
#define INVERT_X true // change (true/false) if the carriage moves e.g. "left" when you press "right".
#define NEEDS_REST_X false // Set to false for all kinds of drivers or X will be unlocked when not moving.
#define MAX_TRAVEL_MM_X 100 // Cross slide doesn't allow to travel more than this in one go, 10cm
#define BACKLASH_DU_X 1500 // 0.15mm backlash in deci-microns (10^-7 of a meter)

// Manual stepping with left/right/up/down buttons. Only used when step isn't default continuous (1mm or 0.1").
#define STEP_TIME_MS 500 // Time in milliseconds it should take to make 1 manual step.
#define DELAY_BETWEEN_STEPS_MS 80 // Time in milliseconds to wait between steps.

// Manual handwheels on A1 and A2. Ignore if you don't have them installed.
#define PULSE_1_USE false // Whether there's a pulse generator connected on A11-A13 to be used for movement.
#define PULSE_1_AXIS 'z' // Set to 'x' to make A11-A13 pulse generator control X instead.
#define PULSE_1_INVERT false // Set to true to change the direction in which encoder moves the axis
#define PULSE_2_USE false // Whether there's a pulse generator connected on A21-A23 to be used for movement.
#define PULSE_2_AXIS 'x' // Set to 'z' to make A21-A23 pulse generator control Z instead.
#define PULSE_2_INVERT true // Set to false to change the direction in which encoder moves the axis
#define PULSE_PER_REVOLUTION 100.0 // PPR of handwheels used on A1 and/or A2.
#define PULSE_MIN_WIDTH_US 1000 // Microseconds width of the pulse that is required for it to be registered. Prevents noise.
#define PULSE_HALF_BACKLASH 2 // Prevents spurious reverses when moving using a handwheel. Raise to 3 or 4 if they still happen.

/* Changing anything below shouldn't be needed for basic use. */

#define LONG_MIN long(-2147483648)
#define LONG_MAX long(2147483647)

#define DUPR_MAX long(254000) // 25.4mm
#define STARTS_MAX 124 // No more than 124-start thread
#define PASSES_MAX 999 // No more turn or face passes than this
#define SAFE_DISTANCE_DU 5000 // Step back 0.5mm from the material when moving between cuts in automated modes
#define SAVE_DELAY_US 5000000 // Wait 5s after last save and last change of saveable data before saving again
#define DIRECTION_SETUP_DELAY_US 2 // Stepper driver needs some time to adjust to direction change

// Version of the pref storage format, should be changed when non-backward-compatible
// changes are made to the storage logic, resulting in Preferences wipe on first start.
#define PREFERENCES_VERSION 1
#define PREF_NAMESPACE "h4"

// GCode-related constants.
#define LINEAR_INTERPOLATION_PRECISION 0.1 // 0 < x <= 1, smaller values make for quicker G0 and G1 moves
#define GCODE_WAIT_EPSILON_STEPS 10

// To be incremented whenever a measurable improvement is made.
#define SOFTWARE_VERSION 2

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

#define A11 9
#define A12 10
#define A13 11

#define A21 12
#define A22 13
#define A23 14

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

#define PREF_VERSION "v"
#define PREF_DUPR "d"
#define PREF_POS_Z "zp"
#define PREF_LEFT_STOP_Z "zls"
#define PREF_RIGHT_STOP_Z "zrs"
#define PREF_ORIGIN_POS_Z "zpo"
#define PREF_POS_GLOBAL_Z "zpg"
#define PREF_MOTOR_POS_Z "zpm"
#define PREF_POS_X "xp"
#define PREF_LEFT_STOP_X "xls"
#define PREF_RIGHT_STOP_X "xrs"
#define PREF_ORIGIN_POS_X "xpo"
#define PREF_POS_GLOBAL_X "xpg"
#define PREF_MOTOR_POS_X "xpm"
#define PREF_SPINDLE_POS "sp"
#define PREF_SPINDLE_POS_AVG "spa"
#define PREF_OUT_OF_SYNC "oos"
#define PREF_SPINDLE_POS_GLOBAL "spg"
#define PREF_SHOW_ANGLE "ang"
#define PREF_SHOW_TACHO "rpm"
#define PREF_STARTS "sta"
#define PREF_MODE "mod"
#define PREF_MEASURE "mea"
#define PREF_CONE_RATIO "cr"
#define PREF_TURN_PASSES "tp"
#define PREF_MOVE_STEP "ms"

#define MOVE_STEP_1 10000 // 1mm
#define MOVE_STEP_2 1000 // 0.1mm
#define MOVE_STEP_3 100 // 0.01mm

#define MOVE_STEP_IMP_1 25400 // 1/10"
#define MOVE_STEP_IMP_2 2540 // 1/100"
#define MOVE_STEP_IMP_3 254 // 1/1000" also known as 1 thou

#define MODE_NORMAL 0
#define MODE_ASYNC 2
#define MODE_CONE 3
#define MODE_TURN 4
#define MODE_FACE 5
#define MODE_CUT 6
#define MODE_THREAD 7
#define MODE_ELLIPSE 8
#define MODE_GCODE 9

#define MEASURE_METRIC 0
#define MEASURE_INCH 1
#define MEASURE_TPI 2

#define ESTOP_NONE 0
#define ESTOP_KEY 1
#define ESTOP_POS 2
#define ESTOP_MARK_ORIGIN 3
#define ESTOP_ON_OFF 4

// For MEASURE_TPI, round TPI to the nearest integer if it's within this range of it.
// E.g. 80.02tpi would be shown as 80tpi but 80.04tpi would be shown as-is.
#define TPI_ROUND_EPSILON 0.03

#define RPM_BULK ENCODER_STEPS // Measure RPM averaged over this number of encoder pulses
#define RPM_UPDATE_INTERVAL_MICROS 1000000 // Don't redraw RPM more often than once per second

#define GCODE_FEED_DEFAULT_DU_SEC 20000 // Default feed in du/sec in GCode mode

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

#include <Preferences.h>

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

bool beepFlag = false; // allows time-critical code to ask for a beep on another core

long dupr = 0; // pitch, tenth of a micron per rotation
long savedDupr = 0; // dupr saved in Preferences
long nextDupr = dupr; // dupr value that should be applied asap
bool nextDuprFlag = false; // whether nextDupr requires attention

SemaphoreHandle_t motionMutex; // controls blocks of code where variables affecting the motion loop() are changed

int starts = 1; // number of starts in a multi-start thread
int savedStarts = 0; // starts saved in Preferences
int nextStarts = starts; // number of starts that should be used asap
bool nextStartsFlag = false; // whether nextStarts requires attention

struct Axis {
  SemaphoreHandle_t mutex;

  char name;
  float motorSteps; // motor steps per revolution of the axis
  float screwPitch; // lead screw pitch in deci-microns (10^-7 of a meter)

  long pos; // relative position of the tool in stepper motor steps
  long savedPos; // value saved in Preferences
  float fractionalPos; // fractional distance in steps that we meant to travel but couldn't
  long originPos; // relative position of the stepper motor to origin, in steps
  long savedOriginPos; // originPos saved in Preferences
  long posGlobal; // global position of the motor in steps
  long savedPosGlobal; // posGlobal saved in Preferences
  int pendingPos; // steps of the stepper motor that we should make as soon as possible
  long motorPos; // position of the motor in stepper motor steps, same as pos unless moving back, then differs by backlashSteps
  long savedMotorPos; // motorPos saved in Preferences

  long leftStop; // left stop value of pos
  long savedLeftStop; // value saved in Preferences
  long nextLeftStop; // left stop value that should be applied asap
  bool nextLeftStopFlag; // whether nextLeftStop required attention

  long rightStop; // right stop value of pos
  long savedRightStop; // value saved in Preferences
  long nextRightStop; // right stop value that should be applied asap
  bool nextRightStopFlag; // whether nextRightStop requires attention

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
  long gcodeRelativePos; // absolute position in steps that relative GCode refers to

  int ena; // Enable pin of this motor
  int dir; // Direction pin of this motor
  int step; // Step pin of this motor
};

void initAxis(Axis* a, char name, float motorSteps, float screwPitch, long speedStart, long speedManualMove, long acceleration, bool invertStepper, bool needsRest, long maxTravelMm, long backlashDu, int ena, int dir, int step) {
  a->mutex = xSemaphoreCreateMutex();

  a->name = name;
  a->motorSteps = motorSteps;
  a->screwPitch = screwPitch;

  a->pos = 0;
  a->savedPos = 0;
  a->fractionalPos = 0.0;
  a->originPos = 0;
  a->savedOriginPos = 0;
  a->posGlobal = 0;
  a->savedPosGlobal = 0;
  a->pendingPos = 0;
  a->motorPos = 0;
  a->savedMotorPos = 0;

  a->leftStop = 0;
  a->savedLeftStop = 0;
  a->nextLeftStopFlag = false;

  a->rightStop = 0;
  a->savedRightStop = 0;
  a->nextRightStopFlag = false;

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
  a->gcodeRelativePos = 0;

  a->ena = ena;
  a->dir = dir;
  a->step = step;
}

Axis z;
Axis x;

unsigned long saveTime = 0; // micros() of the previous Prefs write
unsigned long spindleEncTime = 0; // micros() of the previous spindle update
unsigned long spindleEncTimeDiffBulk = 0; // micros() between RPM_BULK spindle updates
unsigned long spindleEncTimeAtIndex0 = 0; // micros() when spindleEncTimeIndex was 0
int spindleEncTimeIndex = 0; // counter going between 0 and RPM_BULK - 1
long spindlePos = 0; // Spindle position
long spindlePosAvg = 0; // Spindle position accounting for encoder backlash
long savedSpindlePosAvg = 0; // spindlePosAvg saved in Preferences
long savedSpindlePos = 0; // spindlePos value saved in Preferences
volatile long spindlePosDelta = 0; // Unprocessed encoder ticks.
int spindlePosSync = 0; // Non-zero if gearbox is on and a soft limit was removed while axis was on it
int savedSpindlePosSync = 0; // spindlePosSync saved in Preferences
long spindlePosGlobal = 0; // global spindle position that is unaffected by e.g. zeroing
long savedSpindlePosGlobal = 0; // spindlePosGlobal saved in Preferences

volatile int pulse1Delta = 0; // Outstanding pulses generated by pulse generator on terminal A1.
volatile int pulse2Delta = 0; // Outstanding pulses generated by pulse generator on terminal A2.

bool showAngle = false; // Whether to show 0-359 spindle angle on screen
bool showTacho = false; // Whether to show spindle RPM on screen
bool savedShowAngle = false; // showAngle value saved in Preferences
bool savedShowTacho = false; // showTacho value saved in Preferences
int shownRpm = 0;
unsigned long shownRpmTime = 0; // micros() when shownRpm was set

long moveStep = 0; // thousandth of a mm
long savedMoveStep = 0; // moveStep saved in Preferences

int mode = -1; // mode of operation (ELS, multi-start ELS, asynchronous)
int savedMode = -1; // mode saved in Preferences

int measure = MEASURE_METRIC; // Whether to show distances in inches
int savedMeasure = MEASURE_METRIC; // measure value saved in Preferences

float coneRatio = 1; // In cone mode, how much X moves for 1 step of Z
float savedConeRatio = 0; // value of coneRatio saved in Preferences
float nextConeRatio = 0; // coneRatio that should be applied asap
bool nextConeRatioFlag = false; // whether nextConeRatio requires attention

int turnPasses = 3; // In turn mode, how many turn passes to make
int savedTurnPasses = 0; // value of turnPasses saved in Preferences

long setupIndex = 0; // Index of automation setup step
bool auxForward = true; // True for external, false for external thread

long opIndex = 0; // Index of an automation operation
long opSubIndex = 0; // Sub-index of an automation operation
int opDuprSign = 1; // 1 if dupr was positive when operation started, -1 if negative

const int customCharMmCode = 0;
byte customCharMm[] = {
  B11010,
  B10101,
  B10101,
  B00000,
  B11010,
  B10101,
  B10101,
  B00000
};
const int customCharLimUpCode = 1;
byte customCharLimUp[] = {
  B11111,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00000,
  B00000
};
const int customCharLimDownCode = 2;
byte customCharLimDown[] = {
  B00000,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B11111,
  B00000
};
const int customCharLimLeftCode = 3;
byte customCharLimLeft[] = {
  B10000,
  B10010,
  B10100,
  B11111,
  B10100,
  B10010,
  B10000,
  B00000
};
const int customCharLimRightCode = 4;
byte customCharLimRight[] = {
  B00001,
  B01001,
  B00101,
  B11111,
  B00101,
  B01001,
  B00001,
  B00000
};
const int customCharLimUpDownCode = 5;
byte customCharLimUpDown[] = {
  B11111,
  B00100,
  B01110,
  B00000,
  B01110,
  B00100,
  B11111,
  B00000
};

String gcodeCommand = "";
long gcodeFeedDuPerSec = GCODE_FEED_DEFAULT_DU_SEC;
bool gcodeInitialized = false;
bool gcodeAbsolutePositioning = true;
bool gcodeInBrace = false;
bool gcodeInSemicolon = false;

hw_timer_t *async_timer = timerBegin(0, 80, true);

int getApproxRpm() {
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
  unsigned long nowUs = micros();
  return nowUs > a->stepStartUs ? nowUs - a->stepStartUs < 50000 : nowUs < 25000;
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
  count += imperial ? lcd.print("\"") : lcd.write(customCharMmCode);
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

long getAxisPosDu(Axis* a) {
  return round((a->pos + a->originPos) * a->screwPitch / a->motorSteps);
}

int printAxisPos(Axis* a) {
  return printDeciMicrons(getAxisPosDu(a), 3);
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
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_THREAD || mode == MODE_ELLIPSE;
}

bool isPassMode() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CUT || mode == MODE_THREAD || mode == MODE_ELLIPSE;
}

int getLastSetupIndex() {
  if (mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CONE || mode == MODE_CUT || mode == MODE_THREAD || mode == MODE_ELLIPSE) {
    return 3;
  }
  return 0;
}

Axis* getPitchAxis() {
  return mode == MODE_FACE ? &x : &z;
}

void updateDisplay() {
  if (emergencyStop != ESTOP_NONE) {
    return;
  }
  int rpm = showTacho ? getApproxRpm() : 0;
  int charIndex = 0;

  if (lcdHashLine0 == LCD_HASH_INITIAL) {
    // First run after reset.
    lcd.clear();
    lcdHashLine1 = LCD_HASH_INITIAL;
    lcdHashLine2 = LCD_HASH_INITIAL;
    lcdHashLine3 = LCD_HASH_INITIAL;
  }

  long newHashLine0 = isOn + (z.leftStop - z.rightStop) + (x.leftStop - x.rightStop) + spindlePosSync + moveStep + mode + measure;
  if (lcdHashLine0 != newHashLine0) {
    lcdHashLine0 = newHashLine0;
    charIndex = 0;
    lcd.setCursor(0, 0);
    if (mode == MODE_ASYNC) {
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
    } else if (mode == MODE_ELLIPSE) {
      charIndex += lcd.print("ELLI ");
    } else if (mode == MODE_GCODE) {
      charIndex += lcd.print("GCODE ");
    }
    charIndex += lcd.print(isOn ? "ON " : "off ");
    int beforeStops = charIndex;
    if (z.leftStop != LONG_MAX) {
      charIndex += lcd.write(customCharLimLeftCode);
    }
    if (x.leftStop != LONG_MAX && x.rightStop != LONG_MIN) {
      charIndex += lcd.write(customCharLimUpDownCode);
    } else if (x.leftStop != LONG_MAX) {
      charIndex += lcd.write(customCharLimUpCode);
    } else if (x.rightStop != LONG_MIN) {
      charIndex += lcd.write(customCharLimDownCode);
    }
    if (z.rightStop != LONG_MIN) {
      charIndex += lcd.write(customCharLimRightCode);
    }
    if (beforeStops != charIndex) {
      charIndex += lcd.print(" ");
    }

    if (spindlePosSync && !isPassMode()) {
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
  long gcodeCommandHash = 0;
  for (int i = 0; i < gcodeCommand.length(); i++) {
    gcodeCommandHash += gcodeCommand.charAt(i);
  }
  long newHashLine3 = z.pos + (showAngle ? spindlePos : -1) + (showTacho ? rpm : -2) + measure + (numpadResult > 0 ? numpadResult : -1) + mode * 5 + dupr +
      (mode == MODE_CONE ? round(coneRatio * 10000) : 0) + turnPasses + opIndex + setupIndex + isOn * 4 + (inNumpad ? 10 : 0) + (auxForward ? 1 : 0) +
      (z.leftStop == LONG_MAX ? 123 : z.leftStop) + (z.rightStop == LONG_MIN ? 1234 : z.rightStop) +
      (x.leftStop == LONG_MAX ? 1235 : x.leftStop) + (x.rightStop == LONG_MIN ? 123456 : x.rightStop) + gcodeCommandHash;
  if (lcdHashLine3 != newHashLine3) {
    lcdHashLine3 = newHashLine3;
    charIndex = 0;
    lcd.setCursor(0, 3);
    if (mode == MODE_GCODE) {
      charIndex += lcd.print(gcodeCommand.substring(0, 20));
    } else if (isPassMode()) {
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
        if (mode == MODE_FACE) {
          charIndex += lcd.print(auxForward ? "Right to left?" : "Left to right?");
        } else if (mode == MODE_CUT) {
          charIndex += lcd.print(dupr >= 0 ? "Pitch > 0, external" : "Pitch < 0, internal");
        } else {
          charIndex += lcd.print(auxForward ? "External?" : "Internal?");
        }
      } else if (!isOn && setupIndex == 3) {
        charIndex += lcd.print("Go?");
      } else if (isOn && numpadResult == 0) {
        charIndex += lcd.print("Operation ");
        charIndex += lcd.print(opIndex);
        charIndex += lcd.print(" of ");
        charIndex += lcd.print(turnPasses * starts);
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
        charIndex += lcd.print(auxForward ? "External?" : "Internal?");
      } else if (!isOn && setupIndex == 3) {
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
      charIndex += lcd.print(spindleModulo(spindlePos) * 360 / ENCODER_STEPS, 2);
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

// Called on a FALLING interrupt for the spindle rotary encoder pin.
void IRAM_ATTR spinEnc() {
  spindlePosDelta += DREAD(ENC_B) ? -1 : 1;
}

unsigned long pulse1HighMicros = 0;
unsigned long pulse2HighMicros = 0;

// Called on a FALLING interrupt for the first axis rotary encoder pin.
void IRAM_ATTR pulse1Enc() {
  unsigned long now = micros();
  if (DREAD(A12)) {
    pulse1HighMicros = now;
  } else if (now > pulse1HighMicros + PULSE_MIN_WIDTH_US) {
    pulse1Delta += (DREAD(A13) ? -1 : 1) * (PULSE_1_INVERT ? -1 : 1);
  }
}

// Called on a FALLING interrupt for the second axis rotary encoder pin.
void IRAM_ATTR pulse2Enc() {
  unsigned long now = micros();
  if (DREAD(A22)) {
    pulse2HighMicros = now;
  } else if (now > pulse2HighMicros + PULSE_MIN_WIDTH_US) {
    pulse2Delta += (DREAD(A23) ? -1 : 1) * (PULSE_2_INVERT ? -1 : 1);
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
  while (emergencyStop == ESTOP_NONE) {
    updateDisplay();
    // Calling Preferences.commit() blocks all interrupts for 30ms, don't call saveIfChanged() if
    // encoder is likely to move soon.
    unsigned long now = micros();
    if (!stepperIsRunning(&z) && !stepperIsRunning(&x) && (now > spindleEncTime + SAVE_DELAY_US) && (now < saveTime || now > saveTime + SAVE_DELAY_US)) {
      if (saveIfChanged()) {
        saveTime = now;
      }
    }
    if (beepFlag) {
      beepFlag = false;
      beep();
    }
    if (abs(z.pendingPos) > z.estopSteps || abs(x.pendingPos) > x.estopSteps) {
      setEmergencyStop(ESTOP_POS);
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

bool isContinuousStep() {
  return moveStep == (measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1);
}

long getStepMaxSpeed(Axis* a) {
  return isContinuousStep() ? a->speedManualMove : min(long(a->speedManualMove), abs(moveStep) * 1000 / STEP_TIME_MS);
}

void waitForStep(Axis* a) {
  if (isContinuousStep()) {
    // Move continuously for default step.
    waitForPendingPosNear0(a);
  } else {
    // Move with tiny pauses allowing to stop precisely.
    waitForPendingPos0(a);
    DELAY(DELAY_BETWEEN_STEPS_MS);
  }
}

int getAndResetPulses(Axis* a) {
  int delta = 0;
  if (PULSE_1_AXIS == a->name) {
    if (pulse1Delta < -PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse1Delta + PULSE_HALF_BACKLASH;
      pulse1Delta = -PULSE_HALF_BACKLASH;
      interrupts();
    } else if (pulse1Delta > PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse1Delta - PULSE_HALF_BACKLASH;
      pulse1Delta = PULSE_HALF_BACKLASH;
      interrupts();
    }
  } else if (PULSE_2_AXIS == a->name) {
    if (pulse2Delta < -PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse2Delta + PULSE_HALF_BACKLASH;
      pulse2Delta = -PULSE_HALF_BACKLASH;
      interrupts();
    } else if (pulse2Delta > PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse2Delta - PULSE_HALF_BACKLASH;
      pulse2Delta = PULSE_HALF_BACKLASH;
      interrupts();
    }
  }
  return delta;
}

void taskMoveZ(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    int pulseDelta = getAndResetPulses(&z);
    bool left = buttonLeftPressed;
    bool right = buttonRightPressed;
    if (!left && !right && pulseDelta == 0) {
      taskYIELD();
      continue;
    }
    if (spindlePosSync != 0) {
      // Edge case.
      taskYIELD();
      continue;
    }
    if (isOn && isPassMode()) {
      setIsOnAfterMutex(false);
    }
    int sign = pulseDelta == 0 ? (left ? 1 : -1) : (pulseDelta > 0 ? 1 : -1);
    bool stepperOn = true;
    stepperEnable(&z, true);
    z.movingManually = true;
    if (isOn && dupr != 0 && mode != MODE_CONE) {
      // Move by moveStep in the desired direction but stay in the thread by possibly traveling a little more.
      int diff = ceil(moveStep * 1.0 / abs(dupr * starts)) * ENCODER_STEPS * sign * (dupr > 0 ? 1 : -1);
      long prevSpindlePos = spindlePos;
      bool resting = false;
      do {
        z.speedMax = z.speedManualMove;
        if (mode != MODE_ASYNC && xSemaphoreTake(motionMutex, 100) == pdTRUE) {
          if (!resting) {
            spindlePos += diff;
            spindlePosAvg += diff;
          }
          // If spindle is moving, it will be changing spindlePos at the same time. Account for it.
          while (diff > 0 ? (spindlePos < prevSpindlePos) : (spindlePos > prevSpindlePos)) {
            spindlePos += diff;
            spindlePosAvg += diff;
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
          if (stepperOn) {
            stepperEnable(&z, false);
            stepperOn = false;
          }
          DELAY(200);
        }
      } while (left ? buttonLeftPressed : buttonRightPressed);
      if (mode == MODE_ASYNC) {
        // Restore async direction.
        waitForPendingPos0(&z);
        updateAsyncTimerSettings();
      }
    } else {
      z.speedMax = getStepMaxSpeed(&z);
      int delta = 0;
      do {
        float fractionalDelta = (pulseDelta == 0 ? moveStep * sign / SCREW_Z_DU : pulseDelta / PULSE_PER_REVOLUTION) * MOTOR_STEPS_Z + z.fractionalPos;
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
        z.speedMax = getStepMaxSpeed(&z);
        stepTo(&z, posCopy + delta);
        waitForStep(&z);
      } while (delta != 0 && (left ? buttonLeftPressed : buttonRightPressed));
      waitForPendingPos0(&z);
      if (isOn && mode == MODE_CONE) {
        if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
          setEmergencyStop(ESTOP_MARK_ORIGIN);
        } else {
          markOrigin();
          xSemaphoreGive(motionMutex);
        }
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
    int pulseDelta = getAndResetPulses(&x);
    bool up = buttonUpPressed || pulseDelta > 0;
    bool down = buttonDownPressed || pulseDelta < 0;
    if (!up && !down) {
      taskYIELD();
      continue;
    }
    if (isOn && isPassMode()) {
      setIsOnAfterMutex(false);
    }
    x.movingManually = true;
    x.speedMax = getStepMaxSpeed(&x);
    stepperEnable(&x, true);

    int delta = 0;
    int sign = up ? 1 : -1;
    do {
      float fractionalDelta = (pulseDelta == 0 ? moveStep * sign / x.screwPitch : pulseDelta / PULSE_PER_REVOLUTION) * x.motorSteps + x.fractionalPos;
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
      waitForStep(&x);
      pulseDelta = getAndResetPulses(&x);
    } while (delta != 0 && (pulseDelta != 0 || (up ? buttonUpPressed : buttonDownPressed)));
    if (isOn && mode == MODE_CONE) {
      if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
        setEmergencyStop(ESTOP_MARK_ORIGIN);
      } else {
        markOrigin();
        xSemaphoreGive(motionMutex);
      }
    }
    x.movingManually = false;
    x.speedMax = LONG_MAX;
    stepperEnable(&x, false);

    taskYIELD();
  }
}

void taskGcode(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    if (mode != MODE_GCODE) {
      gcodeInitialized = false;
      taskYIELD();
      continue;
    }
    if (!gcodeInitialized) {
      gcodeInitialized = true;
      gcodeCommand = "";
      gcodeAbsolutePositioning = true;
      gcodeFeedDuPerSec = GCODE_FEED_DEFAULT_DU_SEC;
      gcodeInBrace = false;
      gcodeInSemicolon = false;
    }
    // Implementing a relevant subset of RS274 (Gcode) and GRBL (state management) covering basic use cases.
    if (Serial.available() > 0) {
      char receivedChar = Serial.read();
      int charCode = int(receivedChar);
      if (gcodeInBrace) {
        if (receivedChar == ')') gcodeInBrace = false;
      } else if (receivedChar == '(') {
        gcodeInBrace = true;
      } else if (receivedChar == ';' /* start of comment till end of line */) {
        gcodeInSemicolon = true;
      } else if (gcodeInSemicolon && charCode >= 32) {
        // Ignoring comment.
      } else if (receivedChar == '!' /* stop */) {
        setIsOnAfterMutex(false);
      } else if (receivedChar == '~' /* resume */) {
        setIsOnAfterMutex(true);
      } else if (receivedChar == '%' /* start/end marker */) {
        // Not using % markers in this implementation.
      } else if (receivedChar == '?' /* status */) {
        Serial.print("<");
        Serial.print(isOn ? "Run" : "Idle");
        Serial.print("|WPos:");
        float divisor = measure == MEASURE_METRIC ? 10000.0 : 254000.0;
        Serial.print(getAxisPosDu(&x) / divisor, 3);
        Serial.print(",0.000,");
        Serial.print(getAxisPosDu(&z) / divisor, 3);
        Serial.print("|FS:");
        Serial.print(round(gcodeFeedDuPerSec * 60 / 10000.0));
        Serial.print(",");
        Serial.print(getApproxRpm());
        Serial.print(">"); // no new line to allow client to easily cut out the status response
      } else if (isOn) {
        if (gcodeInBrace && charCode < 32) {
          Serial.println("error: comment not closed");
          setIsOnAfterMutex(false);
        } else if (charCode < 32 && gcodeCommand.length() > 1) {
          if (handleGcodeCommand(gcodeCommand)) Serial.println("ok");
          gcodeCommand = "";
          gcodeInSemicolon = false;
        } else if (charCode < 32) {
          Serial.println("ok");
          gcodeCommand = "";
        } else if (charCode >= 32 && (charCode == 'G' || charCode == 'M')) {
          // Split consequent G and M commands on one line.
          // No "ok" for commands in the middle of the line.
          handleGcodeCommand(gcodeCommand);
          gcodeCommand = receivedChar;
        } else if (charCode >= 32) {
          gcodeCommand += receivedChar;
        }
      } else {
        // ignoring non-realtime command input when off
        // to flush any commands coming after an error
      }
    }
    taskYIELD();
  }
}

void taskAttachInterrupts(void *param) {
  // Attaching interrupt on core 0 to have more time on core 1 where axes are moved.
  attachInterrupt(digitalPinToInterrupt(ENC_A), spinEnc, FALLING);
  if (PULSE_1_USE) attachInterrupt(digitalPinToInterrupt(A12), pulse1Enc, CHANGE);
  if (PULSE_2_USE) attachInterrupt(digitalPinToInterrupt(A22), pulse2Enc, CHANGE);
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
  } else if (emergencyStop == ESTOP_ON_OFF) {
    lcd.print("Unable to");
    lcd.setCursor(0, 1);
    lcd.print("turn on/off");
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

  if (PULSE_1_USE) {
    pinMode(A11, OUTPUT);
    pinMode(A12, INPUT);
    pinMode(A13, INPUT);
    DLOW(A11);
  }

  if (PULSE_2_USE) {
    pinMode(A21, OUTPUT);
    pinMode(A22, INPUT);
    pinMode(A23, INPUT);
    DLOW(A21);
  }

  Preferences pref;
  pref.begin(PREF_NAMESPACE);
  if (pref.getInt(PREF_VERSION) != PREFERENCES_VERSION) {
    pref.clear();
    pref.putInt(PREF_VERSION, PREFERENCES_VERSION);
  }

  initAxis(&z, 'z', MOTOR_STEPS_Z, SCREW_Z_DU, SPEED_START_Z, SPEED_MANUAL_MOVE_Z, ACCELERATION_Z, INVERT_Z, NEEDS_REST_Z, MAX_TRAVEL_MM_Z, BACKLASH_DU_Z, Z_ENA, Z_DIR, Z_STEP);
  initAxis(&x, 'x', MOTOR_STEPS_X, SCREW_X_DU, SPEED_START_X, SPEED_MANUAL_MOVE_X, ACCELERATION_X, INVERT_X, NEEDS_REST_X, MAX_TRAVEL_MM_X, BACKLASH_DU_X, X_ENA, X_DIR, X_STEP);

  isOn = false;
  savedDupr = dupr = pref.getLong(PREF_DUPR);
  motionMutex = xSemaphoreCreateMutex();
  savedStarts = starts = min(STARTS_MAX, max(1, pref.getInt(PREF_STARTS)));
  z.savedPos = z.pos = pref.getLong(PREF_POS_Z);
  z.savedPosGlobal = z.posGlobal = pref.getLong(PREF_POS_GLOBAL_Z);
  z.savedOriginPos = z.originPos = pref.getLong(PREF_ORIGIN_POS_Z);
  z.savedMotorPos = z.motorPos = pref.getLong(PREF_MOTOR_POS_Z);
  z.savedLeftStop = z.leftStop = pref.getLong(PREF_LEFT_STOP_Z, LONG_MAX);
  z.savedRightStop = z.rightStop = pref.getLong(PREF_RIGHT_STOP_Z, LONG_MIN);
  x.savedPos = x.pos = pref.getLong(PREF_POS_X);
  x.savedPosGlobal = x.posGlobal = pref.getLong(PREF_POS_GLOBAL_X);
  x.savedOriginPos = x.originPos = pref.getLong(PREF_ORIGIN_POS_X);
  x.savedMotorPos = x.motorPos = pref.getLong(PREF_MOTOR_POS_X);
  x.savedLeftStop = x.leftStop = pref.getLong(PREF_LEFT_STOP_X, LONG_MAX);
  x.savedRightStop = x.rightStop = pref.getLong(PREF_RIGHT_STOP_X, LONG_MIN);
  savedSpindlePos = spindlePos = pref.getLong(PREF_SPINDLE_POS);
  savedSpindlePosAvg = spindlePosAvg = pref.getLong(PREF_SPINDLE_POS_AVG);
  savedSpindlePosSync = spindlePosSync = pref.getInt(PREF_OUT_OF_SYNC);
  savedSpindlePosGlobal = spindlePosGlobal = pref.getLong(PREF_SPINDLE_POS_GLOBAL);
  savedShowAngle = showAngle = pref.getBool(PREF_SHOW_ANGLE);
  savedShowTacho = showTacho = pref.getBool(PREF_SHOW_TACHO);
  savedMoveStep = moveStep = pref.getLong(PREF_MOVE_STEP, MOVE_STEP_1);
  setMode(savedMode = pref.getInt(PREF_MODE));
  savedMeasure = measure = pref.getInt(PREF_MEASURE);
  savedConeRatio = coneRatio = pref.getFloat(PREF_CONE_RATIO, coneRatio);
  savedTurnPasses = turnPasses = pref.getInt(PREF_TURN_PASSES, turnPasses);
  pref.end();

  if (!z.needsRest) {
    DHIGH(Z_ENA);
  }
  if (!x.needsRest) {
    DHIGH(X_ENA);
  }

  lcd.begin(20, 4);
  lcd.createChar(customCharMmCode, customCharMm);
  lcd.createChar(customCharLimLeftCode, customCharLimLeft);
  lcd.createChar(customCharLimRightCode, customCharLimRight);
  lcd.createChar(customCharLimUpCode, customCharLimUp);
  lcd.createChar(customCharLimDownCode, customCharLimDown);
  lcd.createChar(customCharLimUpDownCode, customCharLimUpDown);

  Serial.begin(115200);

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
  xTaskCreatePinnedToCore(taskGcode, "taskGcode", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
}

bool saveIfChanged() {
  // Should avoid calling Preferences whenever possible to reduce memory wear and avoid ~20ms write delay that blocks interrupts.
  if (dupr == savedDupr && starts == savedStarts && z.pos == z.savedPos && z.originPos == z.savedOriginPos && z.posGlobal == z.savedPosGlobal && z.motorPos == z.savedMotorPos && z.leftStop == z.savedLeftStop && z.rightStop == z.savedRightStop &&
      spindlePos == savedSpindlePos && spindlePosAvg == savedSpindlePosAvg && spindlePosSync == savedSpindlePosSync && savedSpindlePosGlobal == spindlePosGlobal && showAngle == savedShowAngle && showTacho == savedShowTacho && moveStep == savedMoveStep &&
      mode == savedMode && measure == savedMeasure && x.pos == x.savedPos && x.originPos == x.savedOriginPos && x.posGlobal == x.savedPosGlobal && x.motorPos == x.savedMotorPos && x.leftStop == x.savedLeftStop && x.rightStop == x.savedRightStop &&
      coneRatio == savedConeRatio && turnPasses == savedTurnPasses) return false;

  Preferences pref;
  pref.begin(PREF_NAMESPACE);
  if (dupr != savedDupr) pref.putLong(PREF_DUPR, savedDupr = dupr);
  if (starts != savedStarts) pref.putInt(PREF_STARTS, savedStarts = starts);
  if (z.pos != z.savedPos) pref.putLong(PREF_POS_Z, z.savedPos = z.pos);
  if (z.posGlobal != z.savedPosGlobal) pref.putLong(PREF_POS_GLOBAL_Z, z.savedPosGlobal = z.posGlobal);
  if (z.originPos != z.savedOriginPos) pref.putLong(PREF_ORIGIN_POS_Z, z.savedOriginPos = z.originPos);
  if (z.motorPos != z.savedMotorPos) pref.putLong(PREF_MOTOR_POS_Z, z.savedMotorPos = z.motorPos);
  if (z.leftStop != z.savedLeftStop) pref.putLong(PREF_LEFT_STOP_Z, z.savedLeftStop = z.leftStop);
  if (z.rightStop != z.savedRightStop) pref.putLong(PREF_RIGHT_STOP_Z, z.savedRightStop = z.rightStop);
  if (spindlePos != savedSpindlePos) pref.putLong(PREF_SPINDLE_POS, savedSpindlePos = spindlePos);
  if (spindlePosAvg != savedSpindlePosAvg) pref.putLong(PREF_SPINDLE_POS_AVG, savedSpindlePosAvg = spindlePosAvg);
  if (spindlePosSync != savedSpindlePosSync) pref.putInt(PREF_OUT_OF_SYNC, savedSpindlePosSync = spindlePosSync);
  if (spindlePosGlobal != savedSpindlePosGlobal) pref.putLong(PREF_SPINDLE_POS_GLOBAL, savedSpindlePosGlobal = spindlePosGlobal);
  if (showAngle != savedShowAngle) pref.putBool(PREF_SHOW_ANGLE, savedShowAngle = showAngle);
  if (showTacho != savedShowTacho) pref.putBool(PREF_SHOW_TACHO, savedShowTacho = showTacho);
  if (moveStep != savedMoveStep) pref.putLong(PREF_MOVE_STEP, savedMoveStep = moveStep);
  if (mode != savedMode) pref.putInt(PREF_MODE, savedMode = mode);
  if (measure != savedMeasure) pref.putInt(PREF_MEASURE, savedMeasure = measure);
  if (x.pos != x.savedPos) pref.putLong(PREF_POS_X, x.savedPos = x.pos);
  if (x.posGlobal != x.savedPosGlobal) pref.putLong(PREF_POS_GLOBAL_X, x.savedPosGlobal = x.posGlobal);
  if (x.originPos != x.savedOriginPos) pref.putLong(PREF_ORIGIN_POS_X, x.savedOriginPos = x.originPos);
  if (x.motorPos != x.savedMotorPos) pref.putLong(PREF_MOTOR_POS_X, x.savedMotorPos = x.motorPos);
  if (x.leftStop != x.savedLeftStop) pref.putLong(PREF_LEFT_STOP_X, x.savedLeftStop = x.leftStop);
  if (x.rightStop != x.savedRightStop) pref.putLong(PREF_RIGHT_STOP_X, x.savedRightStop = x.rightStop);
  if (coneRatio != savedConeRatio) pref.putFloat(PREF_CONE_RATIO, savedConeRatio = coneRatio);
  if (turnPasses != savedTurnPasses) pref.putInt(PREF_TURN_PASSES, savedTurnPasses = turnPasses);
  pref.end();
  return true;
}

void markAxisOrigin(Axis* a) {
  bool hasSemaphore = xSemaphoreTake(a->mutex, 10) == pdTRUE;
  if (!hasSemaphore) {
    beepFlag = true;
  }
  if (a->leftStop != LONG_MAX) {
    a->leftStop -= a->pos;
  }
  if (a->rightStop != LONG_MIN) {
    a->rightStop -= a->pos;
  }
  a->motorPos -= a->pos;
  a->originPos += a->pos;
  a->pos = 0;
  a->fractionalPos = 0;
  a->pendingPos = 0;
  if (hasSemaphore) {
    xSemaphoreGive(a->mutex);
  }
}

void zeroSpindlePos() {
  spindlePos = 0;
  spindlePosAvg = 0;
  spindlePosSync = 0;
}

// Loose the thread and mark current physical positions of
// encoder and stepper as a new 0. To be called when dupr changes
// or ELS is turned on/off. Without this, changing dupr will
// result in stepper rushing across the lathe to the new position.
// Must be called while holding motionMutex.
void markOrigin() {
  markAxisOrigin(&z);
  markAxisOrigin(&x);
  zeroSpindlePos();
}

void markZ0() {
  z.originPos = -z.pos;
}

void markX0() {
  x.originPos = -x.pos;
}

void updateAsyncTimerSettings() {
  // dupr and therefore direction can change while we're in async mode.
  setDir(&z, dupr > 0);

  // dupr can change while we're in async mode, keep updating timer frequency.
  timerAlarmWrite(async_timer, getTimerLimit(), true);
}

void setDupr(long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextDupr = value;
  nextDuprFlag = true;
}

// Must be called while holding motionMutex.
void applyDupr() {
  if (nextDupr == dupr) {
    return;
  }
  dupr = nextDupr;
  markOrigin();
  if (mode == MODE_ASYNC) {
    updateAsyncTimerSettings();
  }
}

void setStarts(int value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextStarts = value;
  nextStartsFlag = true;
}

// Must be called while holding motionMutex.
void applyStarts() {
  if (starts == nextStarts) {
    return;
  }
  starts = nextStarts;
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
    if (z.pos >= z.motorPos) {
      z.pos++;
    }
    z.motorPos++;
    z.posGlobal++;
  } else if (dupr < 0 && (z.rightStop == LONG_MIN || z.pos > z.rightStop)) {
    if (z.pos >= z.motorPos + z.backlashSteps) {
      z.pos--;
    }
    z.motorPos--;
    z.posGlobal--;
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
    setIsOnAfterMutex(false);
  }
  if (mode == MODE_THREAD) {
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
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextConeRatio = value;
  nextConeRatioFlag = true;
}

void applyConeRatio() {
  if (nextConeRatio == coneRatio) {
    return;
  }
  coneRatio = nextConeRatio;
  markOrigin();
}

void reset() {
  z.leftStop = LONG_MAX;
  z.nextLeftStopFlag = false;
  z.rightStop = LONG_MIN;
  z.nextRightStopFlag = false;
  z.originPos = 0;
  z.posGlobal = 0;
  z.motorPos = 0;
  z.pendingPos = 0;
  x.leftStop = LONG_MAX;
  x.nextLeftStopFlag = false;
  x.rightStop = LONG_MIN;
  x.nextRightStopFlag = false;
  x.originPos = 0;
  x.posGlobal = 0;
  x.motorPos = 0;
  x.pendingPos = 0;
  setDupr(0);
  setStarts(1);
  moveStep = MOVE_STEP_1;
  setMode(MODE_NORMAL);
  measure = MEASURE_METRIC;
  setConeRatio(1);
}

// Called when left/right stop restriction is removed while we're on it.
// Prevents stepper from rushing to a position far away by waiting for the right
// spindle position and starting smoothly.
void setOutOfSync(Axis* a) {
  if (!isOn || mode == MODE_ASYNC) {
    return;
  }
  spindlePosSync = spindleModulo(spindlePos - spindleFromPos(a, a->pos));
#ifdef DEBUG
  Serial.print("spindlePosSync ");
  Serial.println(spindlePosSync);
#endif
}

long normalizePitch(long pitch) {
  int scale = 1;
  if (measure == MEASURE_METRIC) {
    // Drop the 3rd and 4th precision point if any.
    scale = 100;
  } else if (measure == MEASURE_INCH) {
    // Always drop the 4th precision point in inch representation if any.
    scale = 254;
  }
  return round(pitch / scale) * scale;
}

void buttonPlusMinusPress(bool plus) {
  // Mutex is aquired in setDupr() and setStarts().
  bool minus = !plus;
  if (mode == MODE_THREAD && setupIndex == 2) {
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
    int delta = measure == MEASURE_METRIC ? MOVE_STEP_3 : MOVE_STEP_IMP_3;
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
  tone(BUZZ, 1000, 500);
}

void buttonOnOffPress(bool on) {
  resetMillis = millis();
  if (on && isPassMode() && (needZStops() && (z.leftStop == LONG_MAX || z.rightStop == LONG_MIN) || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN)) {
    beep();
  } else if (on && getLastSetupIndex() != 0 && setupIndex < getLastSetupIndex()) {
    // Move to the next setup step.
    setupIndex++;
  } else {
    setIsOnAfterMutex(on);
  }
}

void setIsOnAfterMutex(bool on) {
  if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
    setEmergencyStop(ESTOP_ON_OFF);
    return;
  }
  setIsOn(on);
  xSemaphoreGive(motionMutex);
}

void setIsOn(bool on) {
  if (isOn && on) {
    return;
  }
  if (!on) {
    isOn = false;
    setupIndex = 0;
    auxForward = true;
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
}

void buttonOffRelease() {
  if (millis() - resetMillis > 4000) {
    reset();
    splashScreen();
  }
}

void setLeftStop(Axis* a, long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  a->nextLeftStop = value;
  a->nextLeftStopFlag = true;
}

void leaveStop(Axis* a, long oldStop) {
  if (mode == MODE_CONE) {
    // To avoid rushing to a far away position if standing on limit.
    markOrigin();
  } else if (mode == MODE_NORMAL && a == getPitchAxis() && a->pos == oldStop) {
    // Spindle is most likely out of sync with the stepper because
    // it was spinning while the lead screw was on the stop.
    setOutOfSync(a);
  }
}

void applyLeftStop(Axis* a) {
  // Accept left stop even if it's lower than pos.
  // Stop button press processing takes time during which motor could have moved.
  long oldStop = a->leftStop;
  a->leftStop = a->nextLeftStop;
  leaveStop(a, oldStop);
}

void setRightStop(Axis* a, long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  a->nextRightStop = value;
  a->nextRightStopFlag = true;
}

void applyRightStop(Axis* a) {
  // Accept right stop even if it's higher than pos.
  // Stop button press processing takes time during which motor could have moved.
  long oldStop = a->rightStop;
  a->rightStop = a->nextRightStop;
  leaveStop(a, oldStop);
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
    a->speed = a->speedStart;
    a->direction = dir;
    a->directionInitialized = true;
    DWRITE(a->dir, dir ^ a->invertStepper);
    delayMicroseconds(DIRECTION_SETUP_DELAY_US);
  }
}

void buttonModePress() {
  if (mode == MODE_NORMAL) {
    setMode(MODE_ELLIPSE);
  } else if (mode == MODE_ELLIPSE) {
    setMode(MODE_GCODE);
  } else if (mode == MODE_GCODE) {
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

bool processNumpad(int keyCode) {
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
    return true;
  } else if (inNumpad) {
    inNumpad = false;
    return processNumpadResult(keyCode);
  }
  return inNumpad;
}

bool processNumpadResult(int keyCode) {
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
    return true;
  }

  // Shared piece for stops and moves.
  Axis* a = (keyCode == B_STOPL || keyCode == B_STOPR || keyCode == B_LEFT || keyCode == B_RIGHT) ? &z : &x;
  long pos = a->pos + newDu / a->screwPitch * a->motorSteps * ((keyCode == B_STOPL || keyCode == B_STOPU || keyCode == B_LEFT || keyCode == B_UP) ? 1 : -1);

  // Potentially assign a new value to a limit. Treat newDu as a relative distance from current position.
  if (keyCode == B_STOPL) {
    setLeftStop(&z, pos);
    return true;
  } else if (keyCode == B_STOPR) {
    setRightStop(&z, pos);
    return true;
  } else if (keyCode == B_STOPU) {
    setLeftStop(&x, pos);
    return true;
  } else if (keyCode == B_STOPD) {
    setRightStop(&x, pos);
    return true;
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
      return true;
    }
    a->speedMax = a->speedManualMove;
    stepTo(a, pos);
    return true;
  }

  if (keyCode == B_STEP) {
    if (newDu > 0) {
      moveStep = newDu;
    } else {
      beep();
    }
    return true;
  }

  return false;
}

void processKeypadEvents() {
  while (keypad.available() > 0) {
    int event = keypad.getEvent();
    int keyCode = event;
    bitWrite(keyCode, 7, 0);
    bool isPress = bitRead(event, 7) == 1; // 1 - press, 0 - release

    // Off button always gets handled.
    if (keyCode == B_OFF) {
      buttonOffPressed = isPress;
      isPress ? buttonOnOffPress(false) : buttonOffRelease();
    }

    if (mode == MODE_GCODE && isOn) {
      // Not allowed to interfere other than turn off.
      if (isPress && keyCode != B_OFF) beep();
      return;
    }

    // Releases don't matter in numpad but it has to run before LRUD since it might handle those keys.
    if (isPress && processNumpad(keyCode)) {
      continue;
    }

    // Setup wizard navigation.
    if ((setupIndex == 2) && (keyCode == B_LEFT || keyCode == B_RIGHT)) {
      if (isPress) {
        auxForward = !auxForward;
      }
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

    // Rest of the buttons.
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

// Moves the stepper so that the tool is located at the newPos.
bool stepTo(Axis* a, long newPos) {
  if (xSemaphoreTake(a->mutex, 10) == pdTRUE) {
    if (newPos == a->pos) {
      a->pendingPos = 0;
    } else {
      a->pendingPos = newPos - a->motorPos - (newPos > a->pos ? 0 : a->backlashSteps);
    }
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

void moveAxis(Axis* a) {
  // Most of the time a step isn't needed.
  if (a->pendingPos == 0) {
    if (a->speed > a->speedStart) {
      a->speed--;
    }
    return;
  }

  unsigned long nowUs = micros();
  float delayUs = 1000000.0 / a->speed;
  if (nowUs < a->stepStartUs) a->stepStartUs = 0; // micros() overflow
  if (a->pendingPos == 1 && a->speedMax == LONG_MAX) {
    // Don't limit ourselves by step timing to improve performance.
  } else if (nowUs < (a->stepStartUs + delayUs - 5)) {
    // Not enough time has passed to issue this step.
    return;
  }

  if (xSemaphoreTake(a->mutex, 1) == pdTRUE) {
    // Check pendingPos again now that we have the mutex.
    if (a->pendingPos != 0) {
      DLOW(a->step);

      bool dir = a->pendingPos > 0;
      setDir(a, dir);
      int delta = dir ? 1 : -1;
      a->pendingPos -= delta;
      if (dir && a->motorPos >= a->pos) {
        a->pos++;
      } else if (!dir && a->motorPos <= (a->pos - a->backlashSteps)) {
        a->pos--;
      }
      a->motorPos += delta;
      a->posGlobal += delta;

      a->speed += a->acceleration * delayUs / 1000000.0;
      if (a->speed > a->speedMax) {
        a->speed = a->speedMax;
      } else if (a->speed < a->speedStart) {
        a->speed = a->speedStart;
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
  stepTo(&z, posFromSpindle(&z, spindlePosAvg, true));
}

long spindleModulo(long value) {
  value = value % int(ENCODER_STEPS);
  if (value < 0) {
    value += int(ENCODER_STEPS);
  }
  return value;
}

long auxSafeDistance, startOffset;
void modeTurn(Axis* main, Axis* aux) {
  if (main->movingManually || aux->movingManually || turnPasses <= 0 ||
      main->leftStop == LONG_MAX || main->rightStop == LONG_MIN ||
      aux->leftStop == LONG_MAX || aux->rightStop == LONG_MIN ||
      dupr == 0 || (dupr * opDuprSign < 0) || starts < 1) {
    setIsOn(false);
    return;
  }

  // Variables below have to be re-calculated every time because origin can change
  // while TURN is running e.g. due to dupr change.
  long mainStartStop = opDuprSign > 0 ? main->rightStop : main->leftStop;
  long mainEndStop = opDuprSign > 0 ? main->leftStop : main->rightStop;
  long auxStartStop = auxForward ? aux->rightStop : aux->leftStop;
  long auxEndStop = auxForward ? aux->leftStop : aux->rightStop;

  // opIndex 0 is only executed once, do setup calculations here.
  if (opIndex == 0) {
    auxSafeDistance = (auxForward ? -1 : 1) * SAFE_DISTANCE_DU / aux->screwPitch * aux->motorSteps;
    startOffset = starts == 1 ? 0 : round(1.0 * ENCODER_STEPS / starts) * -opDuprSign;

    // Move to right-bottom limit.
    main->speedMax = main->speedManualMove;
    aux->speedMax = aux->speedManualMove;
    long auxPos = auxStartStop;
    long mainPos = mainStartStop;
    stepTo(main, mainPos);
    stepTo(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      opIndex = 1;
    }
  } else if (opIndex <= turnPasses * starts) {
    // Bringing X to starting position.
    if (opSubIndex == 0) {
      long auxPos = auxEndStop - (auxEndStop - auxStartStop) / turnPasses * (turnPasses - ceil(opIndex / float(starts)));
      stepTo(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 1;
        spindlePosSync = spindleModulo(spindlePosGlobal - spindleFromPos(main, main->posGlobal) - startOffset * opIndex);
        return; // Instead of jumping to the next step, let spindlePosSync get to 0 first.
      }
    }
    // Doing the pass cut.
    if (opSubIndex == 1) {
      main->speedMax = LONG_MAX;
      stepTo(main, posFromSpindle(main, spindlePosAvg, true));
      if (main->pos == mainEndStop) {
        opSubIndex = 2;
      }
    }
    // Retracting the tool
    if (opSubIndex == 2) {
      long auxPos = auxStartStop + auxSafeDistance;
      stepTo(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 3;
      }
    }
    // Returning to start of main.
    if (opSubIndex == 3) {
      main->speedMax = main->speedManualMove;
      // Overstep by 1 so that "main" backlash is taken out before "opSubIndex == 1".
      long mainPos = mainStartStop + (opDuprSign > 0 ? -1 : 1);
      stepTo(main, mainPos);
      if (main->pos == mainPos) {
        stepTo(main, mainStartStop);
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    // Move to right-bottom limit.
    main->speedMax = main->speedManualMove;
    long auxPos = auxStartStop;
    long mainPos = mainStartStop;
    stepTo(main, mainPos);
    stepTo(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      setIsOn(false);
      beep();
    }
  }
}

void modeCone() {
  if (z.movingManually || x.movingManually || coneRatio == 0) {
    return;
  }

  float zToXRatio = -coneRatio / 2 / z.motorSteps * x.motorSteps / x.screwPitch * z.screwPitch * (auxForward ? 1 : -1);
  if (zToXRatio == 0) {
    return;
  }

  // TODO: calculate maximum speeds and accelerations to avoid potential desync.
  x.speedMax = LONG_MAX;
  z.speedMax = LONG_MAX;

  // Respect limits of both axis by translating them into limits on spindlePos value.
  long spindle = spindlePosAvg;
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
  if (x.movingManually || turnPasses <= 0 || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN || dupr == 0 || dupr * opDuprSign < 0) {
    setIsOn(false);
    return;
  }

  long startStop = opDuprSign > 0 ? x.rightStop : x.leftStop;
  long endStop = opDuprSign > 0 ? x.leftStop : x.rightStop;

  if (opIndex == 0) {
    // Move to back limit.
    x.speedMax = x.speedManualMove;
    long xPos = startStop;
    stepTo(&x, xPos);
    if (x.pos == xPos) {
      opIndex = 1;
    }
  } else if (opIndex <= turnPasses) {
    // Set spindlePos and x.pos in sync.
    if (opSubIndex == 0) {
      markAxisOrigin(&x);
      zeroSpindlePos();
      opSubIndex = 1;
    }
    // Doing the pass cut.
    if (opSubIndex == 1) {
      x.speedMax = LONG_MAX;
      long maxPos = endStop - (endStop - startStop) / turnPasses * (turnPasses - opIndex);
      long xPos = min(maxPos, posFromSpindle(&x, spindlePosAvg, true));
      stepTo(&x, xPos);
      if (x.pos == maxPos) {
        opSubIndex = 2;
      }
    }
    // Returning to start.
    if (opSubIndex == 2) {
      x.speedMax = x.speedManualMove;
      stepTo(&x, startStop);
      if (x.pos == startStop) {
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    setIsOn(false);
    beep();
  }
}

void modeEllipse(Axis* main, Axis* aux) {
  if (main->movingManually || aux->movingManually || turnPasses <= 0 ||
      main->leftStop == LONG_MAX || main->rightStop == LONG_MIN ||
      aux->leftStop == LONG_MAX || aux->rightStop == LONG_MIN ||
      main->leftStop == main->rightStop ||
      aux->leftStop == aux->rightStop ||
      dupr == 0 || (dupr * opDuprSign < 0)) {
    setIsOn(false);
    return;
  }

  // Start from left or right depending on the pitch.
  long mainStartStop = opDuprSign > 0 ? main->rightStop : main->leftStop;
  long mainEndStop = opDuprSign > 0 ? main->leftStop : main->rightStop;

  // Will vary for internal/external cuts.
  long auxStartStop = auxForward ? aux->rightStop : aux->leftStop;
  long auxEndStop = auxForward ? aux->leftStop : aux->rightStop;

  main->speedMax = main->speedManualMove;
  aux->speedMax = aux->speedManualMove;

  if (opIndex == 0) {
    opIndex = 1;
    opSubIndex = 0;
    spindlePos = 0;
    spindlePosAvg = 0;
  } else if (opIndex <= turnPasses) {
    float pass0to1 = opIndex / float(turnPasses);
    long mainDelta = round(pass0to1 * (mainEndStop - mainStartStop));
    long auxDelta = round(pass0to1 * (auxEndStop - auxStartStop));
    long spindleDelta = spindleFromPos(main, mainDelta);

    // Move to starting position.
    if (opSubIndex == 0) {
      long auxPos = auxStartStop;
      stepTo(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 1;
      }
    } else if (opSubIndex == 1) {
      long mainPos = mainEndStop - mainDelta;
      stepTo(main, mainPos);
      if (main->pos == mainPos) {
        opSubIndex = 2;
        spindlePos = 0;
        spindlePosAvg = 0;
      }
    } else if (opSubIndex == 2) {
      float progress0to1 = 0;
      if ((spindleDelta > 0 && spindlePosAvg >= spindleDelta) || (spindleDelta < 0 && spindlePosAvg <= spindleDelta)) {
        progress0to1 = 1;
      } else {
        progress0to1 = spindlePosAvg / float(spindleDelta);
      }
      long mainPos = mainEndStop - mainDelta + round(mainDelta * cos(HALF_PI * (3 + progress0to1)));
      long auxPos = auxStartStop + round(auxDelta * (1 + sin(HALF_PI * (3 + progress0to1))));
      stepTo(main, mainPos);
      stepTo(aux, auxPos);
      if (progress0to1 == 1 && main->pos == mainPos && aux->pos == auxPos) {
        opIndex++;
        opSubIndex = 0;
      }
    }
  } else if (opIndex == turnPasses + 1) {
    stepTo(aux, auxStartStop);
    if (aux->pos == auxStartStop) {
      setIsOn(false);
      beep();
    }
  }
}

long mmOrInchToAbsolutePos(Axis* a, float mmOrInch) {
  long scaleToDu = measure == MEASURE_METRIC ? 10000 : 254000;
  long part1 = a->gcodeRelativePos;
  long part2 = round(mmOrInch * scaleToDu / a->screwPitch * a->motorSteps);
  return part1 + part2;
}

void stepToRelativeMmOrInch(Axis* a, float mmOrInch) {
  stepTo(a, mmOrInchToAbsolutePos(a, mmOrInch));
}

String getValueString(const String& command, char letter) {
  int index = command.indexOf(letter);
  if (index == -1) {
    return "";
  }
  String valueString;
  for (int i = index + 1; i < command.length(); i++) {
    char c = command.charAt(i);
    if (isDigit(c) || c == '.' || c == '-') {
      valueString += c;
    } else {
      break;
    }
  }
  return valueString;
}

float getFloat(const String& command, char letter) {
  return getValueString(command, letter).toFloat();
}

int getInt(const String& command, char letter) {
  return getValueString(command, letter).toInt();
}

void updateAxisSpeeds(long diffX, long diffZ) {
  if (diffX == 0 && diffZ == 0) return;
  long absX = abs(diffX);
  long absZ = abs(diffZ);
  float maxStepsPerSecX = gcodeFeedDuPerSec / x.screwPitch * x.motorSteps;
  if (maxStepsPerSecX > x.speedManualMove || maxStepsPerSecX < 1) maxStepsPerSecX = x.speedManualMove;
  float maxStepsPerSecZ = gcodeFeedDuPerSec / z.screwPitch * z.motorSteps;
  if (maxStepsPerSecZ > z.speedManualMove || maxStepsPerSecZ < 1) maxStepsPerSecZ = z.speedManualMove;
  float secX = absX / maxStepsPerSecX;
  float secZ = absZ / maxStepsPerSecZ;
  float sec = max(secX, secZ);
  x.speedMax = sec > 0 ? absX / sec : x.speedManualMove;
  z.speedMax = sec > 0 ? absZ / sec : z.speedManualMove;
}

void setFeedRate(const String& command) {
  float feed = getFloat(command, 'F');
  if (feed <= 0) return;
  gcodeFeedDuPerSec = round(feed * (measure == MEASURE_METRIC ? 10000 : 254000) / 60.0);
}

void gcodeWaitEpsilon(int epsilon) {
  while (abs(x.pendingPos) > epsilon || abs(z.pendingPos) > epsilon) {
    taskYIELD();
  }
}

void gcodeWaitNear() {
  gcodeWaitEpsilon(GCODE_WAIT_EPSILON_STEPS);
}

void gcodeWaitStop() {
  gcodeWaitEpsilon(0);
}

// Rapid positioning / linear interpolation.
void G00_01(const String& command) {
  long xStart = x.pos;
  long zStart = z.pos;
  long xEnd = command.indexOf('X') >= 0 ? mmOrInchToAbsolutePos(&x, getFloat(command, 'X')) : xStart;
  long zEnd = command.indexOf('Z') >= 0 ? mmOrInchToAbsolutePos(&z, getFloat(command, 'Z')) : zStart;
  long xDiff = xEnd - xStart;
  long zDiff = zEnd - zStart;
  updateAxisSpeeds(xDiff, zDiff);
  long chunks = round(max(abs(xDiff), abs(zDiff)) * LINEAR_INTERPOLATION_PRECISION);
  for (long i = 0; i < chunks; i++) {
    if (!isOn) return;
    float scale = i / float(chunks);
    stepTo(&x, xStart + xDiff * scale);
    stepTo(&z, zStart + zDiff * scale);
    gcodeWaitNear();
  }
  // To avoid any rounding error, move to precise position.
  stepTo(&x, xEnd);
  stepTo(&z, zEnd);
  gcodeWaitStop();
}

bool handleGcode(const String& command) {
  int op = getInt(command, 'G');
  if (op == 0 || op == 1) { // 0 also covers X and Z commands without G.
    G00_01(command);
  } else if (op == 20 || op == 21) {
    setMeasure(op == 20 ? MEASURE_INCH : MEASURE_METRIC);
  } else if (op == 90 || op == 91) {
    gcodeAbsolutePositioning = op == 90;
  } else if (op == 94) {
    /* no-op feed per minute */
  } else if (op == 18) {
    /* no-op ZX plane selection */
  } else {
    Serial.print("error: unsupported command ");
    Serial.println(command);
    return false;
  }
  return true;
}

bool handleMcode(const String& command) {
  int op = getInt(command, 'M');
  if (op == 0 || op == 1 || op == 2 || op == 30) {
    setIsOnAfterMutex(false);
  } else {
    setIsOnAfterMutex(false);
    Serial.print("error: unsupported command ");
    Serial.println(command);
    return false;
  }
  return true;
}

void handleAxisMove(Axis* a, float mmOrInch) {
  stepToRelativeMmOrInch(&x, mmOrInch);
  updateAxisSpeeds(x.pendingPos, z.pendingPos);
  gcodeWaitStop();
}

// Process one command, return ok flag.
bool handleGcodeCommand(String command) {
  // Trim N.. prefix.
  char code = command.charAt(0);
  int spaceIndex = command.indexOf(' ');
  if (code == 'N' && spaceIndex > 0) {
    command = command.substring(spaceIndex + 1);
    code = command.charAt(0);
  }

  // Update position for relative calculations right before performing them.
  z.gcodeRelativePos = (gcodeAbsolutePositioning ? 0 : z.pos) - z.originPos;
  x.gcodeRelativePos = (gcodeAbsolutePositioning ? 0 : x.pos) - x.originPos;

  setFeedRate(command);
  switch (code) {
    case 'G':
    case 'X':
    case 'Z': return handleGcode(command);
    case 'F': return true; /* feed already handled above */
    case 'M': return handleMcode(command);
    case 'T': return true; /* ignoring tool changes */
    default: Serial.print("error: unsupported command "); Serial.println(code); return false;
  }
}

void discountFullSpindleTurns() {
  // When standing at the stop, ignore full spindle turns.
  // This allows to avoid waiting when spindle direction reverses
  // and reduces the chance of the skipped stepper steps since
  // after a reverse the spindle starts slow.
  if (dupr != 0 && !stepperIsRunning(&z) && mode != MODE_FACE && mode != MODE_ELLIPSE) {
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
      spindlePosAvg += spindlePosDiff;
    }
  }
}

void processSpindlePosDelta() {
  if (spindlePosDelta == 0) {
    return;
  }

  noInterrupts();
  long delta = spindlePosDelta;
  spindlePosDelta = 0;
  interrupts();

  unsigned long microsNow = micros();
  if (showTacho || mode == MODE_GCODE) {
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
  spindlePosGlobal += delta;
  if (spindlePosGlobal > int(ENCODER_STEPS)) {
    spindlePosGlobal -= int(ENCODER_STEPS);
  } else if (spindlePosGlobal < 0) {
    spindlePosGlobal += int(ENCODER_STEPS);
  }
  if (spindlePos > spindlePosAvg) {
    spindlePosAvg = spindlePos;
  } else if (spindlePos < spindlePosAvg - ENCODER_BACKLASH) {
    spindlePosAvg = spindlePos + ENCODER_BACKLASH;
  }
  spindleEncTime = microsNow;

  if (spindlePosSync != 0) {
    spindlePosSync += delta;
    if (spindlePosSync % int(ENCODER_STEPS) == 0) {
      spindlePosSync = 0;
      Axis* a = getPitchAxis();
      spindlePosAvg = spindlePos = spindleFromPos(a, a->pos);
    }
  }
}

// Apply changes requested by the keyboard thread.
void applySettings() {
  if (nextDuprFlag) {
    applyDupr();
    nextDuprFlag = false;
  }
  if (nextStartsFlag) {
    applyStarts();
    nextStartsFlag = false;
  }
  if (z.nextLeftStopFlag) {
    applyLeftStop(&z);
    z.nextLeftStopFlag = false;
  }
  if (z.nextRightStopFlag) {
    applyRightStop(&z);
    z.nextRightStopFlag = false;
  }
  if (x.nextLeftStopFlag) {
    applyLeftStop(&x);
    x.nextLeftStopFlag = false;
  }
  if (x.nextRightStopFlag) {
    applyRightStop(&x);
    x.nextRightStopFlag = false;
  }
  if (nextConeRatioFlag) {
    applyConeRatio();
    nextConeRatioFlag = false;
  }
}

void loop() {
  if (emergencyStop != ESTOP_NONE) {
    return;
  }
  if (xSemaphoreTake(motionMutex, 1) != pdTRUE) {
    return;
  }
  applySettings();
  processSpindlePosDelta();
  discountFullSpindleTurns();
  if (!isOn || dupr == 0 || spindlePosSync != 0) {
    // None of the modes work.
  } else if (mode == MODE_NORMAL) {
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
  } else if (mode == MODE_ELLIPSE) {
    modeEllipse(&z, &x);
  }
  moveAxis(&z);
  moveAxis(&x);
  xSemaphoreGive(motionMutex);
}

#ifdef TEST

#define TEST_ADDR 200

void spinEncTimes(int times) {
  for (int i = 0; i < times; i++) {
    spinEnc();
  }
}

void nonTestLoopTimes(int times) {
  for (int i = 0; i < times; i++) {
    nonTestLoop();
  }
}

void prepareButtonPress(int button) {
  mockDigitalPins[button] = LOW;
  checkAndMarkButtonTime(button);
  delay(400);
  // Next checkAndMarkButtonTime(button) will return true.
}

void setupEach() {
  buttonId = 0;
  buttonDownTime = 0;
  buttonUpTime = 0;
  loopCounter = 0;
  resetMillis = false;
  isOn = false;

  dupr = 0;
  savedDupr = 0;
  duprPrevious = 0;

  pos = 0;
  savedPos = 0;

  leftStop = LONG_MAX;
  savedLeftStop = LONG_MAX;
  leftStopFlag = true;

  rightStop = LONG_MIN;
  savedRightStop = LONG_MIN;
  rightStopFlag = true;

  spindlePos = 0;
  savedSpindlePos = 0;
  spindleLeftStop = 0;
  spindleRightStop = 0;

  spindlePosSync = 0;
  savedSpindlePosSync = 0;

  stepDelayUs = PULSE_MAX_US;
  stepDelayDirection = true;
  stepStartMicros = 0;

  showAngle = false;
  savedShowAngle = false;

  setMode(MODE_NORMAL);
  setMeasure(MEASURE_METRIC);

  for (int i = 0; i < sizeof(mockDigitalPins); i++) {
    mockDigitalPins[i] = HIGH;
  }
  mockDigitalPinToggleOnRead = false;

  // Wait a bit so that time-sensitive spindle turning logic resets too.
  delay(10);
  spindleEncTime = 0;
}

test(saveLoadInt) {
  saveInt(TEST_ADDR, 15);
  assertEqual(15, loadInt(TEST_ADDR));
  saveInt(TEST_ADDR, 32000);
  assertEqual(32000, loadInt(TEST_ADDR));
  saveInt(TEST_ADDR, -32000);
  assertEqual(-32000, loadInt(TEST_ADDR));
}

test(saveLoadLong) {
  saveLong(TEST_ADDR, 15L);
  assertEqual(15L, loadLong(TEST_ADDR));
  saveLong(TEST_ADDR, 2111222333L);
  assertEqual(2111222333L, loadLong(TEST_ADDR));
  saveLong(TEST_ADDR, -2111222333L);
  assertEqual(-2111222333L, loadLong(TEST_ADDR));
}

test(spinEnc) {
  spindlePos = 0;
  prepareButtonPress(ENC_B);
  spinEnc();
  spinEnc();
  assertEqual(2L, spindlePos);

  delay(10);
  mockDigitalPins[ENC_B] = HIGH;
  spinEnc();
  spinEnc();
  spinEnc();
  assertEqual(-1L, spindlePos);
}

test(spinEncSyncHigh) {
  dupr = 5000;
  pos = 200;
  spindlePos = 0;
  spindlePosSync = 100;
  mockDigitalPins[ENC_B] = HIGH;

  spinEnc();
  assertEqual(-1L, spindlePos);
  assertEqual(99, spindlePosSync);

  for (int i = 0; i < 98; i++) {
    spinEnc();
  }
  assertEqual(-99L, spindlePos);
  assertEqual(1, spindlePosSync);

  spinEnc();
  // With 0.5mm pitch, to get to pos 200 will take 4 full turns of the spindle.
  // At 600 encoder steps, spindlePos should now be at 2400 now that it synced.
  assertEqual(2400L, spindlePos);
  assertEqual(0, spindlePosSync);
}

test(spinEncSyncLow) {
  dupr = 5000;
  pos = 200;
  spindlePos = 0;
  spindlePosSync = 100;
  prepareButtonPress(ENC_B);

  spinEnc();
  assertEqual(1L, spindlePos);
  assertEqual(101, spindlePosSync);

  spinEncTimes(498);
  assertEqual(499L, spindlePos);
  assertEqual(599, spindlePosSync);

  spinEnc();
  // With 0.5mm pitch, to get to pos 200 will take 4 full turns of the spindle.
  // At 600 encoder steps, spindlePos should now be at 2400 now that it synced.
  assertEqual(2400L, spindlePos);
  assertEqual(0, spindlePosSync);
}

test(saveIfChanged) {
  savedDupr = 0;
  dupr = 100;
  savedPos = 0;
  pos = 2;
  savedLeftStop = 0;
  leftStop = 3;
  savedRightStop = 0;
  rightStop = 4;
  savedSpindlePos = 0;
  spindlePos = 5;
  savedSpindlePosSync = 0;
  spindlePosSync = 6;
  savedShowAngle = false;
  showAngle = true;
  savedShowTacho = false;
  showTacho = true;
  savedMoveStep = 0;
  moveStep = 10;
  savedMode = MODE_NORMAL;
  mode = MODE_MULTISTART;
  saveIfChanged();
  assertEqual(100L, savedDupr);
  assertEqual(2L, savedPos);
  assertEqual(3L, savedLeftStop);
  assertEqual(4L, savedRightStop);
  assertEqual(5L, savedSpindlePos);
  assertEqual(true, savedShowAngle);
  assertEqual(true, savedShowTacho);
  assertEqual(10, savedMoveStep);
  assertEqual(MODE_MULTISTART, savedMode);
}

test(checkAndMarkButtonTime) {
  delay(400);
  assertFalse(checkAndMarkButtonTime(B_LEFT));
  delay(100);
  assertTrue(checkAndMarkButtonTime(B_LEFT));
  delay(100);
  assertFalse(checkAndMarkButtonTime(B_LEFT));
  delay(400);
  assertTrue(checkAndMarkButtonTime(B_LEFT));
}

test(markAsZero) {
  pos = 0;
  spindlePos = 0;
  spindlePosSync = 0;
  markAsZero();
  assertEqual(0L, pos);
  assertEqual(LONG_MAX, leftStop);
  assertEqual(LONG_MIN, rightStop);
  assertEqual(0L, spindlePos);
  assertEqual(0, spindlePosSync);

  pos = 200;
  leftStop = 300;
  rightStop = 100;
  spindlePos = 600;
  spindlePosSync = 0;
  markAsZero();
  assertEqual(0L, pos);
  assertEqual(100L, leftStop);
  assertEqual(-100L, rightStop);
  assertEqual(0L, spindlePos);
  assertEqual(0, spindlePosSync);

  pos = 100;
  leftStop = 300;
  rightStop = 100;
  spindlePos = 600;
  spindlePosSync = 0;
  markAsZero();
  assertEqual(0L, pos);
  assertEqual(200L, leftStop);
  assertEqual(0L, rightStop);
  assertEqual(0L, spindlePos);
  assertEqual(0, spindlePosSync);

  pos = 300;
  leftStop = 300;
  rightStop = 100;
  spindlePos = 600;
  spindlePosSync = 0;
  markAsZero();
  assertEqual(0L, pos);
  assertEqual(0L, leftStop);
  assertEqual(-200L, rightStop);
  assertEqual(0L, spindlePos);
  assertEqual(0, spindlePosSync);
}

test(setOutOfSync) {
  dupr = 10000;
  pos = 0;
  spindlePos = 0;
  setOutOfSync();
  assertEqual(0, spindlePosSync);

  pos = 50;
  spindlePos = 300;
  setOutOfSync();
  assertEqual(0, spindlePosSync);

  pos = 50;
  spindlePos = 400;
  setOutOfSync();
  assertEqual(0, spindlePosSync);

  isOn = true;
  setOutOfSync();
  assertEqual(100, spindlePosSync);

  pos = 50;
  spindlePos = 600400;
  setOutOfSync();
  assertEqual(100, spindlePosSync);

  pos = -50;
  spindlePos = -300;
  setOutOfSync();
  assertEqual(0, spindlePosSync);

  pos = -50;
  spindlePos = -60400;
  setOutOfSync();
  assertEqual(500, spindlePosSync);
}

test(checkPlusMinusButtons) {
  mockDigitalPins[B_MINUS] = HIGH;
  mockDigitalPins[B_PLUS] = HIGH;
  pos = 100;
  dupr = 100;
  duprPrevious = 0;
  checkPlusMinusButtons();
  assertEqual(100L, pos);
  assertEqual(100L, dupr);
  assertEqual(100L, duprPrevious);

  prepareButtonPress(B_MINUS);
  mockDigitalPins[B_PLUS] = HIGH;
  checkPlusMinusButtons();
  assertEqual(0L, pos);
  assertEqual(0L, dupr);
  assertEqual(100L, duprPrevious);

  prepareButtonPress(B_MINUS);
  checkPlusMinusButtons();
  assertEqual(0L, pos);
  assertEqual(-100L, dupr);
  assertEqual(100L, duprPrevious);

  mockDigitalPins[B_MINUS] = HIGH;
  checkPlusMinusButtons();
  assertEqual(0L, pos);
  assertEqual(-100L, dupr);
  assertEqual(-100L, duprPrevious);

  for (int i = 0; i < 110; i++) {
    prepareButtonPress(B_MINUS);
    checkPlusMinusButtons();
  }
  assertEqual(0L, pos);
  assertEqual(-100000L, dupr);
  assertEqual(-100L, duprPrevious);

  mockDigitalPins[B_MINUS] = HIGH;
  buttonDownTime = 0L;
  checkPlusMinusButtons();
  assertEqual(-100000L, duprPrevious);

  for (int i = 0; i < 220; i++) {
    prepareButtonPress(B_PLUS);
    checkPlusMinusButtons();
  }
  assertEqual(0L, pos);
  assertEqual(100000L, dupr);
  assertEqual(-100000L, duprPrevious);
}

test(checkOnOffButton) {
  isOn = false;
  mockDigitalPins[B_ONOFF] = HIGH;
  checkOnOffButton();
  assertFalse(isOn);

  prepareButtonPress(B_ONOFF);
  checkOnOffButton();
  assertTrue(isOn);
  checkOnOffButton();
  assertTrue(isOn);

  mockDigitalPins[B_ONOFF] = HIGH;
  checkOnOffButton();
  assertTrue(isOn);

  prepareButtonPress(B_ONOFF);
  checkOnOffButton();
  assertFalse(isOn);
  checkOnOffButton();
  assertFalse(isOn);

  dupr = 100;
  pos = 2;
  leftStop = 3;
  rightStop = -1;
  resetMillis = millis() - 6001;
  checkOnOffButton();
  assertFalse(isOn);
  assertEqual(0L, dupr);
  assertEqual(0L, pos);
  assertEqual(LONG_MAX, leftStop);
  assertEqual(LONG_MIN, rightStop);
}

test(checkLeftStopButton) {
  isOn = true;
  dupr = 10000;
  pos = 200;
  spindlePos = 1200;
  spindlePosSync = 0;
  mockDigitalPins[B_STOPL] = HIGH;
  checkLeftStopButton();
  assertEqual(LONG_MAX, leftStop);

  prepareButtonPress(B_STOPL);
  checkLeftStopButton();
  assertEqual(200L, leftStop);
  checkLeftStopButton();
  assertEqual(200L, leftStop);

  mockDigitalPins[B_STOPL] = HIGH;
  checkLeftStopButton();
  prepareButtonPress(B_STOPL);
  checkLeftStopButton();
  assertEqual(LONG_MAX, leftStop);
  assertEqual(0, spindlePosSync);

  mockDigitalPins[B_STOPL] = HIGH;
  checkLeftStopButton();
  prepareButtonPress(B_STOPL);
  checkLeftStopButton();
  assertEqual(200L, leftStop);

  // Go left beyound the left stop.
  prepareButtonPress(ENC_B);
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1206L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, leftStop);

  // Full spindle turns should be discarded.
  spinEncTimes(600);
  nonTestLoop();
  assertEqual(1206L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, leftStop);

  // Go back into the allowed interval.
  delay(10);
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(1194L, spindlePos);
  assertEqual(199L, pos);
  assertEqual(200L, leftStop);
  assertEqual(0, spindlePosSync);

  // Go left beyound the left stop.
  delay(10);
  prepareButtonPress(ENC_B);
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(1206L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, leftStop);

  // Remove the stop when spindle is out of sync with the stepper.
  mockDigitalPins[B_STOPL] = HIGH;
  checkLeftStopButton();
  prepareButtonPress(B_STOPL);
  checkLeftStopButton();
  assertEqual(1206L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(LONG_MAX, leftStop);
  assertEqual(6, spindlePosSync);

  // Move spindle back to the sync position.
  delay(10);
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1200L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(LONG_MAX, leftStop);
  assertEqual(0, spindlePosSync);

  // Move spindle some more to test that stepper is now moving too.
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1194L, spindlePos);
  assertEqual(199L, pos);
  assertEqual(LONG_MAX, leftStop);
  assertEqual(0, spindlePosSync);
  spinEncTimes(594);
  nonTestLoopTimes(200);
  assertEqual(600L, spindlePos);
  assertEqual(100L, pos);
  assertEqual(LONG_MAX, leftStop);
  assertEqual(0, spindlePosSync);
}

test(checkRightStopButton) {
  isOn = true;
  dupr = 10000;
  pos = 200;
  spindlePos = 1200;
  spindlePosSync = 0;
  mockDigitalPins[B_STOPR] = HIGH;
  checkRightStopButton();
  assertEqual(LONG_MIN, rightStop);

  prepareButtonPress(B_STOPR);
  checkRightStopButton();
  assertEqual(200L, rightStop);
  checkRightStopButton();
  assertEqual(200L, rightStop);

  mockDigitalPins[B_STOPR] = HIGH;
  checkRightStopButton();
  prepareButtonPress(B_STOPR);
  checkRightStopButton();
  assertEqual(LONG_MIN, rightStop);
  assertEqual(0, spindlePosSync);

  mockDigitalPins[B_STOPR] = HIGH;
  checkRightStopButton();
  prepareButtonPress(B_STOPR);
  checkRightStopButton();
  assertEqual(200L, rightStop);

  // Go right beyound the right stop.
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1194L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, rightStop);

  // Full spindle turns should be discarded.
  spinEncTimes(600);
  nonTestLoop();
  assertEqual(1194L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, rightStop);

  // Go back into the allowed interval.
  delay(10);
  prepareButtonPress(ENC_B);
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(1206L, spindlePos);
  assertEqual(201L, pos);
  assertEqual(200L, rightStop);
  assertEqual(0, spindlePosSync);

  // Go right beyound the right stop.
  delay(10);
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(1194L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, rightStop);

  // Remove the stop when spindle is out of sync with the stepper.
  mockDigitalPins[B_STOPR] = HIGH;
  checkRightStopButton();
  prepareButtonPress(B_STOPR);
  checkRightStopButton();
  assertEqual(1194L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(LONG_MIN, rightStop);
  assertEqual(594, spindlePosSync);

  // Move spindle back to the sync position.
  delay(10);
  prepareButtonPress(ENC_B);
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1200L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(LONG_MIN, rightStop);
  assertEqual(0, spindlePosSync);

  // Move spindle some more to test that stepper is now moving too.
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1206L, spindlePos);
  assertEqual(201L, pos);
  assertEqual(LONG_MIN, rightStop);
  assertEqual(0, spindlePosSync);
  spinEncTimes(594);
  nonTestLoopTimes(100);
  assertEqual(1800L, spindlePos);
  assertEqual(300L, pos);
  assertEqual(LONG_MIN, rightStop);
  assertEqual(0, spindlePosSync);
}

test(leftStopNegativePitch) {
  isOn = true;
  leftStop = 200;
  dupr = -10000;
  pos = 200;
  spindlePos = -1200;
  spindlePosSync = 0;

  // Go left beyound the left stop.
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(-1206L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, leftStop);

  // Go right.
  delay(10);
  prepareButtonPress(ENC_B);
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(-1194L, spindlePos);
  assertEqual(199L, pos);
  assertEqual(200L, leftStop);
}

test(rightStopNegativePitch) {
  isOn = true;
  rightStop = 200;
  dupr = -10000;
  pos = 200;
  spindlePos = -1200;
  spindlePosSync = 0;

  // Go right beyound the right stop.
  prepareButtonPress(ENC_B);
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(-1194L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, rightStop);

  // Go left.
  delay(10);
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(-1206L, spindlePos);
  assertEqual(201L, pos);
  assertEqual(200L, rightStop);
}

test(turnForward) {
  isOn = false;
  dupr = 10000;
  delay(10);
  prepareButtonPress(ENC_B);
  for (long i = 0; i < 300; i++) {
    spinEnc();
    nonTestLoop();
  }

  prepareButtonPress(B_ONOFF);
  checkOnOffButton();
  mockDigitalPins[B_ONOFF] = HIGH;

  dupr = 10000;
  delay(10);
  prepareButtonPress(ENC_B);
  long lastPos = pos;
  for (long i = 0; i < 300; i++) {
    spinEnc();
    nonTestLoop();
    assertLessOrEqual(lastPos, pos);
    lastPos = pos;
  }
  assertEqual(50L, pos);
}

test(turnForwardNegativeDupr) {
  isOn = true;
  dupr = -10000;
  delay(10);
  prepareButtonPress(ENC_B);
  long lastPos = pos;
  for (long i = 0; i < 300; i++) {
    spinEnc();
    nonTestLoop();
    assertMoreOrEqual(lastPos, pos);
    lastPos = pos;
  }
  assertEqual(-50L, pos);
}

test(turnReverse) {
  isOn = true;
  dupr = 10000;
  delay(10);
  mockDigitalPins[ENC_B] = HIGH;
  long lastPos = pos;
  for (long i = 0; i < 300; i++) {
    spinEnc();
    nonTestLoop();
    assertMoreOrEqual(lastPos, pos);
    lastPos = pos;
  }
  assertEqual(-50L, pos);
}

test(turnReverseNegativeDupr) {
  isOn = true;
  dupr = -10000;
  delay(10);
  mockDigitalPins[ENC_B] = HIGH;
  long lastPos = pos;
  for (long i = 0; i < 300; i++) {
    spinEnc();
    nonTestLoop();
    assertLessOrEqual(lastPos, pos);
    lastPos = pos;
  }
  assertEqual(50L, pos);
}

test(moveLeftIsOff) {
  isOn = false;
  pos = 0L;
  spindlePos = 0L;
  leftStop = 150L;
  rightStop = -100L;
  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  mockDigitalPinToggleOnRead = B_LEFT;
  checkMoveButtons();

  assertEqual(100L, pos);
  assertEqual(0L, spindlePos);
  assertEqual(150L, leftStop);
  assertEqual(-100L, rightStop);

  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  checkMoveButtons();
  assertEqual(150L, pos);
  assertEqual(0L, spindlePos);
  assertEqual(150L, leftStop);
  assertEqual(-100L, rightStop);
}

test(moveLeftIsOffNegativeDupr) {
  isOn = false;
  dupr = -5000;
  pos = 0L;
  spindlePos = 0L;
  leftStop = 150L;
  rightStop = -100L;
  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  mockDigitalPinToggleOnRead = B_LEFT;
  checkMoveButtons();

  assertEqual(100L, pos);
  assertEqual(0L, spindlePos);
  assertEqual(150L, leftStop);
  assertEqual(-100L, rightStop);
}

test(moveRightIsOff) {
  isOn = false;
  pos = 0L;
  spindlePos = 0L;
  leftStop = 100L;
  rightStop = -150L;
  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  mockDigitalPinToggleOnRead = B_RIGHT;
  checkMoveButtons();

  assertEqual(-100L, pos);
  assertEqual(0L, spindlePos);
  assertEqual(100L, leftStop);
  assertEqual(-150L, rightStop);

  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  checkMoveButtons();
  assertEqual(-150L, pos);
  assertEqual(0L, spindlePos);
  assertEqual(100L, leftStop);
  assertEqual(-150L, rightStop);
}

test(moveRightIsOffNegativeDupr) {
  isOn = false;
  dupr = -5000;
  pos = 0L;
  spindlePos = 0L;
  leftStop = 100L;
  rightStop = -150L;
  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  mockDigitalPinToggleOnRead = B_RIGHT;
  checkMoveButtons();

  assertEqual(-100L, pos);
  assertEqual(0L, spindlePos);
  assertEqual(100L, leftStop);
  assertEqual(-150L, rightStop);
}

test(moveIsOn) {
  isOn = true;
  pos = 0L;
  dupr = 7500;
  spindlePos = 0L;
  leftStop = 200L;
  rightStop = -200L;
  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  mockDigitalPinToggleOnRead = B_LEFT;
  checkMoveButtons();

  assertEqual(150L, pos);
  assertEqual(1200L, spindlePos);

  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  checkMoveButtons();

  assertEqual(200L, pos);
  assertEqual(2400L, spindlePos);

  nonTestLoop();
  assertEqual(1800L, spindlePos);

  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  mockDigitalPinToggleOnRead = B_RIGHT;
  checkMoveButtons();

  assertEqual(75L, pos);
  assertEqual(600L, spindlePos);

  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  checkMoveButtons();

  assertEqual(-75L, pos);
  assertEqual(-600L, spindlePos);

  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  checkMoveButtons();

  assertEqual(-200L, pos);
  assertEqual(-1800L, spindlePos);

  nonTestLoop();
  assertEqual(-1800L, spindlePos);

  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  mockDigitalPinToggleOnRead = B_LEFT;
  checkMoveButtons();

  assertEqual(-75L, pos);
  assertEqual(-600L, spindlePos);
}

test(moveIsOnZeroDupr) {
  isOn = true;
  pos = 0L;
  dupr = 0;
  spindlePos = 0L;
  leftStop = 200L;
  rightStop = -200L;
  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  mockDigitalPinToggleOnRead = B_LEFT;
  checkMoveButtons();

  assertEqual(0L, pos);
  assertEqual(0L, spindlePos);
  assertEqual(100L, leftStop);
  assertEqual(-300L, rightStop);
}

test(moveIsOnNegativeDupr) {
  isOn = true;
  pos = 0L;
  dupr = -7500;
  spindlePos = 0L;
  leftStop = 200L;
  rightStop = -200L;
  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  mockDigitalPinToggleOnRead = B_LEFT;
  checkMoveButtons();

  assertEqual(150L, pos);
  assertEqual(-1200L, spindlePos);

  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  checkMoveButtons();

  assertEqual(200L, pos);
  assertEqual(-2400L, spindlePos);

  nonTestLoop();
  assertEqual(-1800L, spindlePos);

  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  mockDigitalPinToggleOnRead = B_RIGHT;
  checkMoveButtons();

  assertEqual(75L, pos);
  assertEqual(-600L, spindlePos);

  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  checkMoveButtons();

  assertEqual(-75L, pos);
  assertEqual(600L, spindlePos);

  mockDigitalPins[B_LEFT] = HIGH;
  prepareButtonPress(B_RIGHT);
  checkMoveButtons();

  assertEqual(-200L, pos);
  assertEqual(1800L, spindlePos);

  nonTestLoop();
  assertEqual(1800L, spindlePos);

  prepareButtonPress(B_LEFT);
  mockDigitalPins[B_RIGHT] = HIGH;
  mockDigitalPinToggleOnRead = B_LEFT;
  checkMoveButtons();

  assertEqual(-75L, pos);
  assertEqual(600L, spindlePos);
}

#endif

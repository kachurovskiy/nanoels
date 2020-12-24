#ifdef TEST

#define TEST_ADDR 200

void spinEncTimes(int times) {
  for (int i = 0; i < times; i++) {
    spinEnc();
  }
}

void setupEach() {
  buttonTime = 0;
  loopCounter = 0;
  onOffFlag = false;
  isOn = false;
  resetCounter = 0;
  resetOnStartup = false;

  hmmpr = 0;
  savedHmmpr = 0;
  hmmprPrevious = 0;

  pos = 0;
  savedPos = 0;

  leftStop = 0;
  savedLeftStop = 0;
  leftStopFlag = true;

  rightStop = 0;
  savedRightStop = 0;
  rightStopFlag = true;

  spindlePos = 0;
  savedSpindlePos = 0;
  spindleLeftStop = 0;
  spindleRightStop = 0;

  spindlePosSync = 0;
  savedSpindlePosSync = 0;

  stepDelayUs = PULSE_MAX_US;
  stepDelayDirection = true;
  stepStartMs = 0;

  // Wait a bit so that time-sensitive spindle turning logic resets too.
  delay(100);
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
  mockDigitalPins[ENC_B] = LOW;
  spinEnc();
  spinEnc();
  assertEqual(2L, spindlePos);

  delay(100);
  mockDigitalPins[ENC_B] = HIGH;
  spinEnc();
  spinEnc();
  spinEnc();
  assertEqual(-1L, spindlePos);
}

test(spinEncSyncHigh) {
  hmmpr = 50;
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
  hmmpr = 50;
  pos = 200;
  spindlePos = 0;
  spindlePosSync = 100;
  mockDigitalPins[ENC_B] = LOW;

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

test(preventMoveOnStart) {
  leftStop = 0;
  rightStop = 0;
  hmmpr = 100;
  spindlePos = 300;
  pos = 50;
  preventMoveOnStart();
  assertFalse(resetOnStartup);

  pos = 0;
  preventMoveOnStart();
  assertTrue(resetOnStartup);
  assertEqual(0L, pos);
  assertEqual(0L, spindlePos);
}

test(saveIfChanged) {
  savedHmmpr = 0;
  hmmpr = 1;
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
  saveIfChanged();
  assertEqual(1, savedHmmpr);
  assertEqual(2L, savedPos);
  assertEqual(3L, savedLeftStop);
  assertEqual(4L, savedRightStop);
  assertEqual(5L, savedSpindlePos);
  assertEqual(6, savedSpindlePosSync);
}

test(checkAndMarkButtonTime) {
  delay(400);
  assertTrue(checkAndMarkButtonTime());
  assertFalse(checkAndMarkButtonTime());
  delay(400);
  assertTrue(checkAndMarkButtonTime());
}

test(markAsZero) {
  pos = 0;
  leftStop = 0;
  rightStop = 0;
  spindlePos = 0;
  spindlePosSync = 0;
  markAsZero();
  assertEqual(0L, pos);
  assertEqual(0L, leftStop);
  assertEqual(0L, rightStop);
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
  assertEqual(-1L, rightStop);
  assertEqual(0L, spindlePos);
  assertEqual(0, spindlePosSync);

  pos = 300;
  leftStop = 300;
  rightStop = 100;
  spindlePos = 600;
  spindlePosSync = 0;
  markAsZero();
  assertEqual(0L, pos);
  assertEqual(1L, leftStop);
  assertEqual(-200L, rightStop);
  assertEqual(0L, spindlePos);
  assertEqual(0, spindlePosSync);
}

test(setOutOfSync) {
  hmmpr = 100;
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
  mockDigitalPins[LEFT] = HIGH;
  mockDigitalPins[RIGHT] = HIGH;
  pos = 100;
  hmmpr = 1;
  hmmprPrevious = 0;
  checkPlusMinusButtons();
  assertEqual(100L, pos);
  assertEqual(1, hmmpr);
  assertEqual(1, hmmprPrevious);

  mockDigitalPins[LEFT] = LOW;
  mockDigitalPins[RIGHT] = HIGH;
  checkPlusMinusButtons();
  assertEqual(0L, pos);
  assertEqual(0, hmmpr);
  assertEqual(1, hmmprPrevious);

  checkPlusMinusButtons();
  assertEqual(0L, pos);
  assertEqual(-1, hmmpr);
  assertEqual(1, hmmprPrevious);

  mockDigitalPins[LEFT] = HIGH;
  checkPlusMinusButtons();
  assertEqual(0L, pos);
  assertEqual(-1, hmmpr);
  assertEqual(-1, hmmprPrevious);

  mockDigitalPins[LEFT] = LOW;
  for (int i = 0; i < 200; i++) {
    checkPlusMinusButtons();
  }
  assertEqual(0L, pos);
  assertEqual(-1000, hmmpr);
  assertEqual(-1, hmmprPrevious);

  mockDigitalPins[LEFT] = HIGH;
  checkPlusMinusButtons();
  assertEqual(-1000, hmmprPrevious);

  mockDigitalPins[RIGHT] = LOW;
  for (int i = 0; i < 300; i++) {
    checkPlusMinusButtons();
  }
  assertEqual(0L, pos);
  assertEqual(1000, hmmpr);
  assertEqual(-1000, hmmprPrevious);
}

test(checkOnOffButton) {
  isOn = false;
  mockDigitalPins[ONOFF] = HIGH;
  checkOnOffButton();
  assertFalse(isOn);

  mockDigitalPins[ONOFF] = LOW;
  checkOnOffButton();
  assertTrue(isOn);
  checkOnOffButton();
  assertTrue(isOn);

  mockDigitalPins[ONOFF] = HIGH;
  checkOnOffButton();
  assertTrue(isOn);

  mockDigitalPins[ONOFF] = LOW;
  checkOnOffButton();
  assertFalse(isOn);
  checkOnOffButton();
  assertFalse(isOn);

  hmmpr = 1;
  pos = 2;
  leftStop = 3;
  rightStop = -1;
  for (int i = 0; i < 100; i++) {
    checkOnOffButton();
  }
  assertFalse(isOn);
  assertEqual(0, hmmpr);
  assertEqual(0L, pos);
  assertEqual(0L, leftStop);
  assertEqual(0L, rightStop);
}

test(checkLeftStopButton) {
  isOn = true;
  leftStop = 0;
  hmmpr = 100;
  pos = 200;
  spindlePos = 1200;
  spindlePosSync = 0;
  mockDigitalPins[LEFT_STOP] = HIGH;
  checkLeftStopButton();
  assertEqual(0L, leftStop);

  mockDigitalPins[LEFT_STOP] = LOW;
  checkLeftStopButton();
  assertEqual(200L, leftStop);
  checkLeftStopButton();
  assertEqual(200L, leftStop);

  mockDigitalPins[LEFT_STOP] = HIGH;
  checkLeftStopButton();
  mockDigitalPins[LEFT_STOP] = LOW;
  checkLeftStopButton();
  assertEqual(0L, leftStop);
  assertEqual(0, spindlePosSync);

  mockDigitalPins[LEFT_STOP] = HIGH;
  checkLeftStopButton();
  mockDigitalPins[LEFT_STOP] = LOW;
  checkLeftStopButton();
  assertEqual(200L, leftStop);

  // Go left beyound the left stop.
  mockDigitalPins[ENC_B] = LOW;
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
  delay(100);
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(1194L, spindlePos);
  assertEqual(199L, pos);
  assertEqual(200L, leftStop);
  assertEqual(0, spindlePosSync);

  // Go left beyound the left stop.
  delay(100);
  mockDigitalPins[ENC_B] = LOW;
  spinEncTimes(12);
  nonTestLoop();
  assertEqual(1206L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(200L, leftStop);

  // Remove the stop when spindle is out of sync with the stepper.
  mockDigitalPins[LEFT_STOP] = HIGH;
  checkLeftStopButton();
  mockDigitalPins[LEFT_STOP] = LOW;
  checkLeftStopButton();
  assertEqual(1206L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(0L, leftStop);
  assertEqual(6, spindlePosSync);

  // Move spindle back to the sync position.
  delay(100);
  mockDigitalPins[ENC_B] = HIGH;
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1200L, spindlePos);
  assertEqual(200L, pos);
  assertEqual(0L, leftStop);
  assertEqual(0, spindlePosSync);

  // Move spindle some more to test that stepper is now moving too.
  spinEncTimes(6);
  nonTestLoop();
  assertEqual(1194L, spindlePos);
  assertEqual(199L, pos);
  assertEqual(0L, leftStop);
  assertEqual(0, spindlePosSync);
  spinEncTimes(594);
  nonTestLoop();
  assertEqual(600L, spindlePos);
  assertEqual(100L, pos);
  assertEqual(0L, leftStop);
  assertEqual(0, spindlePosSync);
}

test(turn160Left) {
  isOn = true;
  hmmpr = 100;
  delay(100);
  mockDigitalPins[ENC_B] = LOW;
  long lastPos = pos;
  for (long i = 0; i < 3000; i++) {
    spinEnc();
    nonTestLoop();
    assertLessOrEqual(lastPos, pos);
    lastPos = pos;
  }
  assertEqual(500L, pos);
}

#endif

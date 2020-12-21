#ifdef TEST

#define TEST_ADDR 200

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

  for (int i = 0; i < 498; i++) {
    spinEnc();
  }
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

#endif

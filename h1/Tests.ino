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

#endif

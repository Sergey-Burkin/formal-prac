#include "test.h"
#include <string>
TEST_F(TestMain, sampleTests) {
  ASSERT_EQ(4, solve("acb..bab.c.*.ab.ba.+.+*a.", "cbaa"));
  ASSERT_EQ(2, solve("ab+c.aba.*.bac.+.+*", "babc"));
  ASSERT_EQ(0, solve("1", "abba"));
}

TEST_F(TestMain, testPlus) {
  ASSERT_EQ(1, solve("ab+", "aaaa"));
  ASSERT_EQ(1, solve("ab+", "bbbb"));
  ASSERT_EQ(4, solve("abab...ab.+", "ababababab"));
  ASSERT_EQ(2, solve("ab.ba.+", "bcacba"));
}

TEST_F(TestMain, testDot) {
 ASSERT_EQ(0, solve("abba...", "ccccc"));
 ASSERT_EQ(6, solve("abcabc.....", "aaaaaaaabcabc"));
}

#include "test.h"

TEST_F(TestMain, symbolTests) {
    Symbol c('A');
    Symbol c2('b');
    Symbol c3("A");
    std::string empty;
    Symbol creature(empty);
    ASSERT_EQ(true, creature.isEmpty());
    creature.setRepresentation("A");
    creature.setTerminal( true);
    ASSERT_EQ(false, creature.isEmpty());

    ASSERT_EQ("A", c.getRepresentation());
    ASSERT_EQ(false, c == c2);
    ASSERT_EQ(true, c3 == c);
    ASSERT_EQ(true, c.isTerminal());
    ASSERT_EQ(false, c2.isTerminal());
    ASSERT_EQ(true, c == creature);

    testing::internal::CaptureStdout();
    std::cout << c << c2;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("Ab", output);
}

TEST_F(TestMain, ruleTests) {
    Rule rule1("S   ->   aSb");
    Rule rule2("S aSb");
    Rule rule3("S ");
    Rule rule4("S->A1");
    Rule rule5("S A");
    ASSERT_EQ(true, rule3 < rule1);
    ASSERT_EQ(false, rule1 < rule2);
    ASSERT_EQ(true, rule5 < rule4);
    ASSERT_EQ(true, rule1 == rule2);
    ASSERT_EQ(false, rule1 == rule3);
    ASSERT_EQ(true, rule3 == rule3);
    ASSERT_EQ(false, rule4 == rule5);
    ASSERT_EQ(false, rule1.isEpsilon());
    ASSERT_EQ(true, rule3.isEpsilon());

    testing::internal::CaptureStdout();
    std::cout << rule1;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("S -> aSb", output);
}

TEST_F(TestGrammar, basicTests) {
    Grammar g;
    g.addRule(Rule("S -> SS"));
    g.addRule("S -> a");
    g.addRule("B -> b");
    g.addRule("X -> Y");
    testing::internal::CaptureStdout();

    g.print();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ("B -> b\nS -> SS\nS -> a\nX -> Y\n", output);

}

TEST_F(TestGrammar, chomskyTest1) {
    Grammar g;
    g.addRule("S -> S");
    g.addRule("S -> aSb");
    g.addRule("X -> y");
    g.removeMixedRules();
    testing::internal::CaptureStdout();
    g.print(" ");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("S -> S S -> TERM_aSTERM_b TERM_a -> a TERM_b -> b X -> y ", output);
}

TEST_F(TestGrammar, chomskyTest2) {
    Grammar g;
    g.addRule("S -> S");
    g.addRule("S -> SS");
    g.addRule("S -> ABCDEFG");
    g.addRule("S-> XYZ");
    g.removeLongRules();
    testing::internal::CaptureStdout();
    g.print(" ");
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("LONG_0 -> BLONG_1 LONG_1 -> CLONG_2 LONG_2 -> DLONG_3 LONG_3 -> ELONG_4 LONG_4 -> FG LONG_5 -> YZ S -> ALONG_0 S -> S S -> SS S -> XLONG_5 ", output);
}

TEST_F(TestGrammar, chomskyTest3) {
    Grammar g;
    g.addRule("S -> ");
    g.addRule("S -> XY");
    g.addRule("X -> ");
    g.addRule("Y -> a");
    g.addRule("X -> b");
    g.addRule("Y -> X");
    g.removeEpsilonRules();
    g.print(" ");
}
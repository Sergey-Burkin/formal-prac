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
    ASSERT_EQ(true, rule1 == rule2);
    
}
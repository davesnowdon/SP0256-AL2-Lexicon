#include "gtest/gtest.h"
#include "AcronymExpander.h"
#include "gmock/gmock-matchers.h"

TEST(AcronymExpanderTest, shouldExpandAllCaps) {
    AcronymExpander expander;
    EXPECT_TRUE(expander.shouldExpand("RC"));
}

TEST(AcronymExpanderTest, shouldnotExpandLower) {
    AcronymExpander expander;
    EXPECT_FALSE(expander.shouldExpand("dog"));
}

TEST(AcronymExpanderTest, shouldNotExpandDave) {
    AcronymExpander expander;
    EXPECT_FALSE(expander.shouldExpand("Dave"));
}

TEST(AcronymExpanderTest, expandSingleDigit) {
    AcronymExpander expander;
    EXPECT_THAT(expander.expand("RC"), testing::ElementsAre("R", "C"));
}

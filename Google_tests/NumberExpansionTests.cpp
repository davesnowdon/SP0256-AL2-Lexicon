#include "gtest/gtest.h"
#include "NumberExpander.h"
#include "lib/googlemock/include/gmock/gmock-matchers.h"

TEST(NumberExpanderTest, shouldExpandInteger) {
    NumberExpander expander;
    EXPECT_TRUE(expander.shouldExpand("2014"));
}

TEST(NumberExpanderTest, shouldNotExpandAcronym) {
    NumberExpander expander;
    EXPECT_FALSE(expander.shouldExpand("TLA"));
}

TEST(NumberExpanderTest, shouldNotExpandWord) {
    NumberExpander expander;
    EXPECT_FALSE(expander.shouldExpand("shoulder"));
}

TEST(NumberExpanderTest, expandSingleDigit) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("1"), testing::ElementsAre("one"));
}

TEST(NumberExpanderTest, expandDoubleDigitsLessThanTwenty) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("15"), testing::ElementsAre("fifteen"));
}

TEST(NumberExpanderTest, expandDoubleDigits) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("36"), testing::ElementsAre("thirty", "six"));
}

TEST(NumberExpanderTest, expandTripleDigits) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("196"), testing::ElementsAre("one", "hundred", "ninety", "six"));
}

TEST(NumberExpanderTest, expandThousands) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("2014"), testing::ElementsAre("two", "thousand", "fourteen"));
}

TEST(NumberExpanderTest, expandTenThousands) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("31234"),
                testing::ElementsAre("thirty", "one", "thousand", "two", "hundred", "thirty", "four"));
}

TEST(NumberExpanderTest, expandHundredThousands) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("131234"),
                testing::ElementsAre("one", "hundred", "thirty", "one", "thousand", "two", "hundred", "thirty",
                                     "four"));
}

TEST(NumberExpanderTest, expandMIllion) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("1000000"), testing::ElementsAre("one", "million"));
}

TEST(NumberExpanderTest, expandMIllions) {
    NumberExpander expander;
    EXPECT_THAT(expander.expand("1000001"), testing::ElementsAre("one", "million", "one"));
}
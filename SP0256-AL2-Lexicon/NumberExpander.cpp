//
// Created by dns on 07/04/2021.
//

#include <algorithm>
#include "NumberExpander.h"

std::vector<std::string> LESS_THAN_TWENTY_WORDS = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                                                   "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

std::vector<std::string> TENS_WORDS = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

std::vector<std::vector<std::string>> POWERS_OF_TEN_WORDS = {
        {"one"},
        {"ten"},
        {"hundred"},
        {"thousand"},
        {"ten", "thousand"},
        {"hundred", "thousand"},
        {"million"},
        {"ten", "million"},
        {"hundred", "million"},
        {"billion"}};

int POWERS_OF_TEN[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

std::vector<std::string> POWERS_OF_THOUSAND_WORDS = { "", "thousand", "million", "billion", "trillion"};

int POWERS_OF_THOUSAND[] = {1, 1000, 1000000, 1000000000};

bool NumberExpander::shouldExpand(const std::string &word) {
    return std::all_of(word.begin(), word.end(), ::isdigit);
}

std::vector<std::string> NumberExpander::expand(const std::string &word) {
    return  expand(std::stoi(word));
}

// TODO handler numbers bigger than 10 billion
std::vector<std::string> NumberExpander::expand(int number) {
    std::vector<std::string> result;
    int power = 3;
    int residual = number;
    while (residual > 999) {
        int hundreds_amount = residual / POWERS_OF_THOUSAND[power];
        // assumes < 1000 so will break for 10 billion or more
        if (hundreds_amount > 0) {
            const std::vector<std::string> thousands = expandHundreds(hundreds_amount);
            result.insert(result.end(), thousands.begin(), thousands.end());
            result.insert(result.end(), POWERS_OF_THOUSAND_WORDS[power]);
            residual -= hundreds_amount * POWERS_OF_THOUSAND[power];
        }
        --power;
    }
    if (residual > 0) {
        const std::vector<std::string> thousands = expandHundreds(residual);
        result.insert(result.end(), thousands.begin(), thousands.end());
    }
    return result;
}

std::vector<std::string> NumberExpander::expandHundreds(int number) {
    std::vector<std::string> result;
    int residual = number;
    if (residual >= 100) {
        int digit_amount = residual / 100;
        result.insert(result.end(), LESS_THAN_TWENTY_WORDS[digit_amount]);
        result.insert(result.end(), POWERS_OF_TEN_WORDS[2].begin(), POWERS_OF_TEN_WORDS[2].end());
        residual -= digit_amount * POWERS_OF_TEN[2];
    }
    if (residual < 20) {
        result.insert(result.end(), LESS_THAN_TWENTY_WORDS[residual]);
    } else if (residual < 100) {
        result.insert(result.end(), TENS_WORDS[residual / 10]);
        result.insert(result.end(), LESS_THAN_TWENTY_WORDS[residual % 10]);
    }
    return result;
}




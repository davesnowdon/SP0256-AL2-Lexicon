//
// Created by dns on 07/04/2021.
//

#include <algorithm>
#include "AcronymExpander.h"


bool AcronymExpander::shouldExpand(const std::string &word) {
    return std::all_of(word.begin(), word.end(), ::isupper);
}

std::vector<std::string> AcronymExpander::expand(const std::string &word) {
    std::vector<std::string> result;
    for(std::string::const_iterator it = word.begin(); it != word.end(); ++it) {
        result.insert(result.end(), std::string(1, *it));
    }
    return result;
}


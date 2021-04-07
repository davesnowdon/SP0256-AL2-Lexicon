//
// Created by dns on 07/04/2021.
//

#ifndef SP0256_AL2_LEXICON_WORDEXPANDER_H
#define SP0256_AL2_LEXICON_WORDEXPANDER_H

#include <string>
#include <vector>

class WordExpander {
public:
    virtual bool shouldExpand(const std::string &word) = 0;
    virtual std::vector<std::string> expand(const std::string &word) = 0;
};

#endif //SP0256_AL2_LEXICON_WORDEXPANDER_H

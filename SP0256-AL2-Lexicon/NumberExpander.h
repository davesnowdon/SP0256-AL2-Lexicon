//
// Created by dns on 07/04/2021.
//

#ifndef SP0256_AL2_LEXICON_NUMBEREXPANDER_H
#define SP0256_AL2_LEXICON_NUMBEREXPANDER_H

#include "WordExpander.h"

class NumberExpander : public WordExpander {
public:
    virtual bool shouldExpand(const std::string &word);
    virtual std::vector<std::string> expand(const std::string &word);
    std::vector<std::string> expand(int number);
private:
    std::vector<std::string> expandHundreds(int number);
};


#endif //SP0256_AL2_LEXICON_NUMBEREXPANDER_H

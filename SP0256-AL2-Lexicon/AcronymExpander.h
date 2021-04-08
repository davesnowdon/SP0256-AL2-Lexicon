#ifndef SP0256_AL2_LEXICON_ACRONYMEXPANDER_H
#define SP0256_AL2_LEXICON_ACRONYMEXPANDER_H

#include "WordExpander.h"

class AcronymExpander : public WordExpander {
public:
    virtual bool shouldExpand(const std::string &word);
    virtual std::vector<std::string> expand(const std::string &word);
};


#endif //SP0256_AL2_LEXICON_ACRONYMEXPANDER_H

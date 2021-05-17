#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <locale>
#include <vector>
#include <algorithm>
#include "Lexicon.h"
#include "NumberExpander.h"
#include "AcronymExpander.h"

using namespace std;

void wordsToLower(std::vector<std::string> &words) {
    for (std::string &s : words) {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](char c) { return std::tolower(c); });
    }
}


int main() {
    Lexicon lex;
    string input;
    string line;
    vector<string> wordList;
    vector<string> cmuPhones;
    vector<string> SP0Phones;
    int select = -1;

    cout << "Select an option:\n1) Convert from string\n2) Convert from file\n";
    while (select != 1 && select != 2) cin >> select;
    cout << endl;
    cin.ignore();

    if (select == 1) {
        cout << "Enter a string to convert: ";
        getline(cin, input);
    }
    if (select == 2) {
        ifstream docInput;
        docInput.open("./input.txt");
        if (docInput.is_open()) {
            while (getline(docInput, line)) {
                input.append(line);
            }
            docInput.close();
        } else cout << "Unable to open file";

        cout << "Input: " << input << endl;
    }

    std::vector<WordExpander *> expanders = {
            new NumberExpander(),
            new AcronymExpander()
    };

    // strip punctuation characters
    // hyphens should be replaced by spaces
    input = std::regex_replace(input, std::regex("-"), " ");
    // any other punctuation characters can be removed
    std::string inputWithoutPunctuation;
    std::remove_copy_if(input.begin(), input.end(),
                        std::back_inserter(inputWithoutPunctuation),
                        std::ptr_fun<int, int>(&std::ispunct)
    );
    std::cout << "Without punctuation: " << inputWithoutPunctuation << std::endl;

    wordList = lex.splitInput(inputWithoutPunctuation, ' ');

    std::vector<std::string> expandedWordList;
    for (std::string &word : wordList) {
        bool wasExpanded = false;
        for (std::vector<WordExpander *>::const_iterator it = expanders.begin(); it != expanders.end(); ++it) {
            if ((*it)->shouldExpand(word)) {
                std::vector<std::string> expanded = (*it)->expand(word);
                expandedWordList.insert(expandedWordList.end(), expanded.begin(), expanded.end());
                wasExpanded = true;
                break;
            }
        }
        if (!wasExpanded) {
            expandedWordList.push_back(word);
        }
    }
    wordsToLower(expandedWordList);

    cout << "Expanded word list: ";
    for (int i = 0; i < expandedWordList.size(); i++) cout << expandedWordList[i] << " ";
    cout << endl;

    ifstream dict;
    dict.open("./cmudict/cmudict.dict");
    if (!dict.is_open()) cout << "Unable to open dictionary file";


    for (int i = 0; i < expandedWordList.size(); i++) {
        cout << "Searching dictionary for \"" << expandedWordList[i] << "\"" << "..." << endl;
        lex.findInDict(dict, expandedWordList[i], cmuPhones);
    }

    dict.close();
    cout << endl << endl;
    cout << "cmuPhones:" << endl;
    for (int i = 0; i < cmuPhones.size(); i++) cout << cmuPhones[i] << " ";
    cout << endl;

    SP0Phones = lex.convertPhones(cmuPhones);
    cout << endl << endl;
    cout << "SP0Phones:" << endl;
    for (int i = 0; i < SP0Phones.size(); i++) cout << SP0Phones[i] << " ";
    cout << endl;

    std::vector<int> intPhones = lex.phonesToInt(SP0Phones);
    for (int i = 0; i < intPhones.size() - 1; i++) cout << intPhones[i] << ",";
    cout << intPhones[intPhones.size() - 1];
    cout << endl << SP0Phones.size() << " phonemes" << endl;
    cout << endl << endl;

    ofstream out;
    out.open("./output/speech/speech.ino");
    lex.generateCode(out, SP0Phones);
    out.close();

    system("pause");
    return 0;
}
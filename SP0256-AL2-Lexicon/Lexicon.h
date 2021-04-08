#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "WordExpander.h"

class Lexicon
{
public:
	Lexicon();
	~Lexicon();

	std::vector<std::string> splitInput(const std::string& s, char delimiter);
	void findInDict(std::ifstream & stream, std::string token, std::vector<std::string> &phoneList);
	void findAllInDict(std::ifstream & stream, std::string token);

	std::vector<std::string> convertPhones(std::vector<std::string> &pList);
	std::vector<int> phonesToInt(std::vector<std::string> &pList);
	void generateCode(std::ofstream & stream, std::vector<std::string> &pList);
};


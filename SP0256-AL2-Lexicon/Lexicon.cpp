#include "Lexicon.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>

using namespace std;

static std::map<std::string, int> ALLOPHONE_TO_INT = {
        {"PA1", 0},
        {"PA2", 1},
        {"PA3", 2},
        {"PA4", 3},
        {"PA5", 4},
        {"OY",  5},
        {"AY",  6},
        {"EH",  7},
        {"KK3", 8},
        {"PP",  9},
        {"JH",  10},
        {"NN1", 11},
        {"IH",  12},
        {"TT2", 13},
        {"RR1", 14},
        {"AX",  15},
        {"MM",  16},
        {"TT1", 17},
        {"DH1", 18},
        {"IY",  19},
        {"EY",  20},
        {"DD1", 21},
        {"UW1", 22},
        {"AO",  23},
        {"AA",  24},
        {"YY2", 25},
        {"AE",  26},
        {"HH1", 27},
        {"BB1", 28},
        {"TH",  29},
        {"UH",  30},
        {"UW2", 31},
        {"AW",  32},
        {"DD2", 33},
        {"GG3", 34},
        {"VV",  35},
        {"GG1", 36},
        {"SH",  37},
        {"ZH",  38},
        {"RR2", 39},
        {"FF",  40},
        {"KK2", 41},
        {"KK1", 42},
        {"ZZ",  43},
        {"NG",  44},
        {"LL",  45},
        {"WW",  46},
        {"XR",  47},
        {"WH",  48},
        {"YY1", 49},
        {"CH",  50},
        {"ER1", 51},
        {"ER2", 52},
        {"OW",  53},
        {"DH2", 54},
        {"SS",  55},
        {"NN2", 56},
        {"HH2", 57},
        {"OR",  58},
        {"AR",  59},
        {"YR",  60},
        {"GG2", 61},
        {"EL",  62},
        {"BB2", 63}
};

Lexicon::Lexicon()
{

}

Lexicon::~Lexicon()
{
}

//spit an input sentence into a vector of strings
vector<string> Lexicon::splitInput(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

//Finds the line matching the token
void Lexicon::findInDict(ifstream & stream, string token, vector<string> &phoneList) {
	string line;
	int lineNum = 1;
	int instances = 0;

	vector<string> newPhones;

	while (getline(stream, line)) {
		if (line.find(token) != string::npos) {
			if (token.compare(line.substr(0, token.length())) == 0) {
				cout << "(line #" << lineNum << ")" << "\t" << line << endl;
				instances++;

				newPhones = splitInput(line.substr(token.length() + 1, line.length()), ' ');

				phoneList.insert(phoneList.end(), newPhones.begin(), newPhones.end());
				phoneList.push_back("*BRK*");

				stream.clear();
				stream.seekg(0, ios::beg);
				break;
			}
		}
		lineNum++;
	}
	if (!instances) cout << token << " not found" << endl;
}

//Finds all instances of lines containing the token
void Lexicon::findAllInDict(ifstream & stream, string token) {
	string line;
	int lineNum = 1;
	int instances = 0;
	while (getline(stream, line)) {
		if (line.find(token) != string::npos) {
			cout << "(line #" << lineNum << ")" << "\t" << line << endl;
			instances++;
		}
		lineNum++;
	}
	if (!instances) cout << token << " not found" << endl;
}

//Convert allophones from CMUdictionary to those compatible with the SPO256A
//Note: this isn't entirely perfect, since some allophones are incompatible
vector<string> Lexicon::convertPhones(vector<string> &pList) {
	vector<string> newPhones;
	newPhones.resize(pList.size());
	for (int i = 0; i < pList.size(); i++)
	{
		if (pList[i] == "*BRK*") newPhones[i] = "PA5";
		else if (pList[i] == "OY" || pList[i] == "OY0" || pList[i] == "OY1" || pList[i] == "OY2") newPhones[i] = "OY";
		else if (pList[i] == "AY" || pList[i] == "AY0" || pList[i] == "AY1" || pList[i] == "AY2") newPhones[i] = "AY";
		else if (pList[i] == "EH" || pList[i] == "EH0" || pList[i] == "EH1" || pList[i] == "EH2") newPhones[i] = "EH";
		else if (pList[i] == "K") newPhones[i] = "KK3";
		else if (pList[i] == "P") newPhones[i] = "PP";
		else if (pList[i] == "JH") newPhones[i] = "JH";
		else if (pList[i] == "N") newPhones[i] = "NN1"; //**************
		else if (pList[i] == "IH" || pList[i] == "IH0" || pList[i] == "IH1" || pList[i] == "IH2") newPhones[i] = "IH";
		else if (pList[i] == "T") newPhones[i] = "TT2"; //**************
		else if (pList[i] == "R") newPhones[i] = "RR1"; //**************
		else if (pList[i] == "AH" || pList[i] == "AH0" || pList[i] == "AH1" || pList[i] == "AH2") newPhones[i] = "AX";
		else if (pList[i] == "M") newPhones[i] = "MM";
		else if (pList[i] == "T") newPhones[i] = "TT1"; //**************
		else if (pList[i] == "DH") newPhones[i] = "DH1";
		else if (pList[i] == "IY" || pList[i] == "IY0" || pList[i] == "IY1" || pList[i] == "IY2") newPhones[i] = "IY";
		else if (pList[i] == "EY" || pList[i] == "EY0" || pList[i] == "EY1" || pList[i] == "EY2") newPhones[i] = "EY";
		else if (pList[i] == "D") newPhones[i] = "D1"; //**************
		else if (pList[i] == "UW" || pList[i] == "UW0" || pList[i] == "UW1" || pList[i] == "UW2") newPhones[i] = "UW1";
		else if (pList[i] == "AO" || pList[i] == "AO0" || pList[i] == "AO1" || pList[i] == "AO2") newPhones[i] = "AO";
		else if (pList[i] == "AA" || pList[i] == "AA0" || pList[i] == "AA1" || pList[i] == "AA2") newPhones[i] = "AA";
		else if (pList[i] == "Y") newPhones[i] = "YY2"; //**************
		else if (pList[i] == "AE" || pList[i] == "AE0" || pList[i] == "AE1" || pList[i] == "AE2") newPhones[i] = "AE";
		else if (pList[i] == "HH") newPhones[i] = "HH1"; //**************
		else if (pList[i] == "B") newPhones[i] = "BB1";
		else if (pList[i] == "TH") newPhones[i] = "TH";
		else if (pList[i] == "UH" || pList[i] == "UH0" || pList[i] == "UH1" || pList[i] == "UH2") newPhones[i] = "UH";
		else if (pList[i] == "UW" || pList[i] == "UW0" || pList[i] == "UW1" || pList[i] == "UW2") newPhones[i] = "UW2"; //**************
		else if (pList[i] == "AW" || pList[i] == "AW0" || pList[i] == "AW1" || pList[i] == "AW2") newPhones[i] = "AW";
		else if (pList[i] == "D") newPhones[i] = "D2"; //**************
		else if (pList[i] == "G") newPhones[i] = "GG3";//**************
		else if (pList[i] == "V") newPhones[i] = "VV";
		else if (pList[i] == "G") newPhones[i] = "GG1";//**************
		else if (pList[i] == "SH") newPhones[i] = "SH";
		else if (pList[i] == "ZH") newPhones[i] = "ZH";
		else if (pList[i] == "R") newPhones[i] = "RR2";//**************
		else if (pList[i] == "F") newPhones[i] = "FF";//**************
		else if (pList[i] == "K") newPhones[i] = "KK2";//**************
		else if (pList[i] == "K") newPhones[i] = "KK1";//**************
		else if (pList[i] == "Z") newPhones[i] = "ZZ";
		else if (pList[i] == "NG") newPhones[i] = "NG";
		else if (pList[i] == "L") newPhones[i] = "LL";
		else if (pList[i] == "W") newPhones[i] = "WW";
		else if (pList[i] == "R") newPhones[i] = "XR";//**************
		//if (pList[i] == "") newPhones[i] = "WH";
		else if (pList[i] == "Y") newPhones[i] = "YY1"; //**************
		else if (pList[i] == "CH") newPhones[i] = "CH";
		else if (pList[i] == "ER" || pList[i] == "ER0" || pList[i] == "ER1" || pList[i] == "ER2") newPhones[i] = "ER1";//**************
		else if (pList[i] == "ER" || pList[i] == "ER0" || pList[i] == "ER1" || pList[i] == "ER2") newPhones[i] = "ER2";//**************
		else if (pList[i] == "OW" || pList[i] == "OW0" || pList[i] == "OW1" || pList[i] == "OW2") newPhones[i] = "OW";
		else if (pList[i] == "DH") newPhones[i] = "DH2";
		else if (pList[i] == "S") newPhones[i] = "S";
		else if (pList[i] == "N") newPhones[i] = "NN2";//*************
		else if (pList[i] == "HH") newPhones[i] = "HH2";//*************
		//if (pList[i] == "") newPhones[i] = "OR";
		//if (pList[i] == "") newPhones[i] = "AR";
		//if (pList[i] == "") newPhones[i] = "YR";
		else if (pList[i] == "G") newPhones[i] = "GG2";//**************
		else if (pList[i] == "L") newPhones[i] = "EL";
		else if (pList[i] == "B") newPhones[i] = "BB2";
		else cout << "Allophone " << pList[i] << " not found!" << endl;
	}

	return newPhones;
}

vector<int> Lexicon::phonesToInt(vector<string> &pList) {
    vector<int> intPhones;
    intPhones.resize(pList.size());
    for (int i = 0; i < pList.size(); i++) {
        intPhones[i] = ALLOPHONE_TO_INT[pList[i]];
    }
    return intPhones;
}

//Generates code for the arduino
void Lexicon::generateCode(ofstream & stream, vector<string> &pList) {
	stream << "#include <SpeechChip.h>\nSpeechChip SpeechChip(8);\n\nvoid setup(){}\n\nvoid loop() {\n";
	//for (int i = 0; i < pList.size(); i++)
	for (auto phone : pList)
	{
		stream << "\tSpeechChip." << phone << "();\n";
	}
	stream << "\tdelay(1024);\n}";
	cout << "File successfully generated!" << endl;
}
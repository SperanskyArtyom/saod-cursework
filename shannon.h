#pragma once

#include <string>
#include <vector>

using namespace std;

struct Symbol {
    unsigned char ch;
    float probability;
    unsigned short length;
    string codeword;
};

vector<Symbol> calculateProbabilities(const string& filename, unsigned int& totalSymbols);
void generateShannonCodes(vector<Symbol>& symbols);
void displayResults(const vector<Symbol>& symbols, unsigned int totalSymbols);


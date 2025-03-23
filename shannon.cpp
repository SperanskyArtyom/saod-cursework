#include "shannon.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int compSym(const Symbol& a, const Symbol& b) { return a.probability > b.probability; }

vector<Symbol> calculateProbabilities(const string& filename, unsigned int& totalSymbols) {
    unsigned int freq[256] = {0};
    vector<Symbol> symbols;

    ifstream file("testBase3.dat", ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return symbols;
    }

    char c;
    while (file.get(c)) {
        freq[static_cast<unsigned char>(c)]++;
        totalSymbols++;
    }
    file.close();

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            symbols.push_back({static_cast<unsigned char>(i), static_cast<float>(freq[i]) / totalSymbols, 0, ""});
        }
    }

    sort(symbols.begin(), symbols.end(), compSym);
    return symbols;
}

void generateShannonCodes(vector<Symbol>& symbols) {
    float cumulativeProbability = 0.0;

    for (auto& sym : symbols) {
        sym.length = ceil(-log2(sym.probability));
        float tempCumulative = cumulativeProbability;

        for (unsigned short i = 0; i < sym.length; i++) {
            tempCumulative *= 2;
            sym.codeword += (tempCumulative >= 1.0) ? '1' : '0';
            if (tempCumulative >= 1.0) tempCumulative -= 1.0;
        }

        cumulativeProbability += sym.probability;
    }
}

float calculateEntropy(const vector<Symbol>& symbols) {
    float entropy = 0.0;
    for (const auto& sym : symbols) {
        entropy += sym.probability * log2(sym.probability);
    }
    return -entropy;
}

float calculateAverageLength(const vector<Symbol>& symbols) {
    float avgLength = 0.0;
    for (const auto& sym : symbols) {
        avgLength += sym.length * sym.probability;
    }
    return avgLength;
}

void displayResults(const vector<Symbol>& symbols, unsigned int totalSymbols) {
    float entropy = calculateEntropy(symbols);
    float avgLength = calculateAverageLength(symbols);

    cout << "Всего символов: " << totalSymbols << "\tУникальных символов: " << symbols.size() << endl;
    cout << left<<setw(4)<< "#" <<setw(8) << "Символ" << setw(15) << "Вероятность"
         << setw(8) << "Длина" << setw(10) << "Код" << endl;
    int i = 1;
    for (const auto& sym : symbols) {
        cout << setw(4) << i++
			 << setw(8) << sym.ch
             << setw(15) << sym.probability
             << setw(8) << sym.length
             << setw(10) << sym.codeword << endl;
    }

    cout << "\nЭнтропия: " << entropy
         << "\tСредняя длина кодового слова: " << avgLength
         << "\tИзбыточность: " << (avgLength - entropy) << endl;
}


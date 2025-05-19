#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#include "LexAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "interpretor.cpp"


int main() {
    ifstream lexemesIn("lexemes.txt");
    ifstream source("source.txt");
    ofstream sourcelexemes("sourcelexemes.txt");
    LexAnalyzer lexanalyzer(lexemesIn);
    lexanalyzer.scanFile(source, sourcelexemes);
    ifstream lexemesOut("sourcelexemes.txt");
    SyntaxAnalyzer SyntaxAnalyzer(lexemesOut);
    if (SyntaxAnalyzer.parse()) {
        cout << "Parse successful" << endl;
    }

    ifstream symbols("vars.txt");
    if (!source || !symbols) exit(-1);
    Compiler c(lexemesOut, symbols);
    lexitr = lexemes.begin();
    tokitr = tokens.begin();
    c.compile();
    c.run();
    return 0;
}
#ifndef LEXANALYZER_H
#define LEXANALYZER_H
// above can also be achieved with #pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_set>
using namespace std;

class LexAnalyzer {
private:
    // map to hold language's valid lexeme/token pairs
    map<string, string> tokenmap;

    // parallel vectors to store valid lexemes and tokens from source code file
    vector<string> lexemes;
    vector<string> tokens;

    // other private methods
    void addLexeme(ostream &outfile, const string &type, const string &lexeme);
    bool shadedGrey(char c);
    int checkText(ostream &outfile, const string &line, int idx);
    int checkID(ostream &outfile, const string &line, int idx);
    int incorrectStartofID(ostream &outfile, const string &line, int idx);
    int checkNum(ostream &outfile, const string &line, int idx);
    int specialChar(ostream &outfile, const string &line, int idx);
public:

    LexAnalyzer(istream& infile);
    // pre: parameter refers to open data file consisting of token and
    // lexeme pairs i.e.  s_and and t_begin begin t_int 27
    // Each pair appears on its own input line.
    // post: tokenmap has been populated - key: lexeme, value: token

    void scanFile(istream& infile, ostream& outfile);
    // pre: 1st parameter refers to an open text file that contains source
    // code in the language, 2nd parameter refers to an open empty output
    // file
    // post: If no error, the token and lexeme pairs for the given input
    // file have been written to the output file (token : lexeme).
    // If there is an error, the incomplete token/lexeme pairs, as well as
    // an error message have been written to the output file.
    // A success or fail message has printed to the console.

};


#endif //LEXANALYZER_H



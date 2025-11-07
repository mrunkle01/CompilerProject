/*
 * The LexAnalyzer function scans through a source code file and produce a token/lexeme file where
 * each output line is formatted as token : lexeme
 * The scanFile function scans the source.txt file line by line.
 * If the character is a letter it checks if it is an ID or keyword by passing in the current index into the
 * checkID function.
 * If the character is an _ then we know this is an invalid way to start an ID, and it calls the
 * incorrectStartofID function to iterate through the id.
 * If the character is a digit is calls the checkNum function to ensure it is made up of all numbers.
 * If the character is a " it checks if the text is formatted correctly, enclosed in quotes.
 * Otherwise, it checks for a special character like the operators.
 * The shadedGrey function helps us to check if a number, id, or string is followed by a valid lexeme.
 * The addLexeme adds the lexeme and token to the sourcelexemes.txt file, in the format lexeme : token
*/

#include "LexAnalyzer.h"

// pre: parameter refers to open data file consisting of token and
// lexeme pairs i.e.  s_and and t_begin begin t_int 27
// Each pair appears on its own input line.
// post: tokenmap has been populated - key: lexeme, value: token
void LexAnalyzer::addLexeme(ostream &outfile, const string &type, const string &lexeme) {
    outfile << type << " : " << lexeme << endl;
}

bool LexAnalyzer::shadedGrey(char c) {
    unordered_set<char> charSet = {'"', ',', ':', '(', ')', ';', '}', '{', '<', '>', '=','-', '+', '/'};
    return charSet.find(c) != charSet.end();
}

int LexAnalyzer::checkText(ostream &outfile, const string &line, int idx) {
    int i = idx + 1;
    string s = "";
    char c;
    bool finished = false;
    bool secondQuote = false;
    while (i < line.length() && !finished) {
        c = line.at(i);
        if (c == '"') {
            secondQuote = true;
            finished = true;
        }
        else if (c != '"' && !secondQuote) {
            s += c;
        }
        i++;
    }
    if (secondQuote) {
        addLexeme(outfile, "t_text", s);
    }
    else {
        addLexeme(outfile, "ERROR INVALID TEXT FORMAT", s);
    }
    return i - 1;

}
int LexAnalyzer::checkID(ostream &outfile, const string &line, int idx) {
    int i = idx;
    string s = "";
    char c;
    bool valid = true;
    while (i < line.length() && line.at(i) != ' ' && !shadedGrey(line.at(i))) {
       if (!isdigit(line.at(i)) && line.at(i) != '_' && !isalpha(line.at(i))) {
           valid = false;
       }
        c = line.at(i);
        s += c;
        i++;
    }
    if (tokenmap.find(s) != tokenmap.end()) {
        addLexeme(outfile, tokenmap[s], s);
    }
    else if (valid) {
        addLexeme(outfile, "t_id", s);
    }
    else {
        addLexeme(outfile, "ERROR Unrecognized lexeme ID format: ", s);
    }
    return i-1;
}
int LexAnalyzer::incorrectStartofID(ostream &outfile, const string &line, int idx) {
    int i = idx;
    string s = "";
    char c;
    while (i < line.length() && line.at(i) != ' ' && !shadedGrey(line.at(i))) {
        c = line.at(i);
        s += c;
        i++;
    }
    addLexeme(outfile, "ERROR Unrecognized lexeme ID format: ", s);
    return i-1;
}

int LexAnalyzer::checkNum(ostream &outfile, const string &line, int idx) {
    bool valid = true;
    int i = idx;
    char c;
    string s  = "";
    // while haven't hit a space, end of line, or shaded grey char
    while (i < line.length() && line.at(i) != ' ' && !shadedGrey(line.at(i))) {
        if (!isdigit(line.at(i))) {
            valid = false;
        }
        c = line.at(i);
        s += c;
        i ++;
    }
    if (!valid) {
        addLexeme(outfile, "ERROR Unrecognized lexeme number format: ", s);
    }
    else {
        addLexeme(outfile, "t_number", s);
    }

    return i - 1;
}

int LexAnalyzer::specialChar(ostream &outfile, const string &line, int idx) {
    int i = idx;
    string specialChar = "";
    specialChar += line[i]; //grabs the special character
    bool finished = false;

    // will handle two-character operators like "==" and "!="
    if (i + 1 < line.length()) {
        string twoCharLexeme = specialChar + line.at(i + 1);
        if (tokenmap.find(twoCharLexeme) != tokenmap.end()) {
            addLexeme(outfile, tokenmap[twoCharLexeme], twoCharLexeme);
            return i + 1;
        }
    }
    //handles = < >
    if (tokenmap.find(specialChar) != tokenmap.end()) {
        addLexeme(outfile, tokenmap[specialChar], specialChar);
    } else {
        addLexeme(outfile, "ERROR Unrecognized lexeme:", specialChar);
    }

    return i;
}

LexAnalyzer::LexAnalyzer(istream &infile) {
    if (!infile) {
        cout<< "Error: Failed to open lexemes.txt!" << endl;
    }
    string token;
    string lexeme;
    while (infile >> token >> lexeme) {
        tokenmap[lexeme] = token;
        cout << "Added: " << lexeme << " -> " << token << endl;
    }
}

// pre: 1st parameter refers to an open text file that contains source
// code in the language, 2nd parameter refers to an open empty output
// file
// post: If no error, the token and lexeme pairs for the given input
// file have been written to the output file (token : lexeme).
// If there is an error, the incomplete token/lexeme pairs, as well as
// an error message have been written to the output file.
// A success or fail message has printed to the console.
void LexAnalyzer::scanFile(istream &infile, ostream &outfile) {
    int idx;
    string line;
    char c;
    while (getline(infile, line)) {
        idx = 0;
        while (idx < line.length()) {
            c = line.at(idx);
            if (isalpha(line.at(idx))) {
                idx = checkID(outfile, line, idx);
            } else if ( line.at(idx) == '_') {
                idx = incorrectStartofID(outfile, line, idx);
            }else if (isdigit(line.at(idx))) {
                idx = checkNum(outfile, line, idx);
            } else if (isspace(line.at(idx))) {
                idx++;
                continue;
            }else if (c == '"') {
                idx = checkText(outfile, line, idx);
            }
            else {
                idx = specialChar(outfile, line, idx);
            }
            idx++;
        }
    }
}

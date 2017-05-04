//
//  pa3.h
//  pa3.cpp
//
//  Created by Daniel Ruales on 4/10/17.
//  Copyright © 2017 Daniel Ruales. All rights reserved.


#ifndef pa3_h
#define pa3_h
#include <string>

using namespace std;
// Prompts the user to enter a file
string getFile();
// Receives lines from text file and relocates into queue
deque<string> FileLines(string inputFile);
// Breaks stream of text into recognizable elements
vector< vector<string> > LinesToToken(deque<string> FileLines);
// Removes whitespace from string
string delSpaces(string &str);
// Calculates nested loop depth
int depth_of_loop(vector<string> keywords);
// Directs tokenization
void LexAnalyzer(vector< vector<string> > EndVector);
// Outputs a specific vector
void printVector(vector<string> inputVector);
// Reports if string is a number
bool numberCheck(const string& s);
// Reports if string is a variable
bool lowerCheck(string name);



// present tokens
vector<string>
present_keywordVector,
present_delimiterVector,
present_operatorVector,
present_identifierVector,
present_constants,
presentErrors;

#endif /* pa3_h */














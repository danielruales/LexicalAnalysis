//
//  pa3.cpp
//  pa3.cpp
//
//  Created by Daniel Ruales on 4/10/17.
//  Copyright © 2017 Daniel Ruales. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <deque>
#include <fstream>
#include <vector>
#include <sstream>
#include "pa3.h"



using namespace std;



int main(){
    
    string inputFile;
    
    cout<< "Please enter the name of the input file: ";
    
    cin>> inputFile;
    
    cout << endl;
 
    
    // Retrieves the inputFile lines
    deque<string> inputFileLines = FileLines(inputFile);
    
    // Retrieves Tokenized inputFile lines
    vector< vector<string> > vectorTarget = LinesToToken(inputFileLines);
    
    // Execute Lexical Analyzer
    LexAnalyzer(vectorTarget);
    
    // Return Success
    return 0;
    
}


deque<string> FileLines(string inputFile){
    
    // excepting FileLines
    deque<string> fileLines;
    
    ifstream file(inputFile);
    
    if (file.is_open()){
        while (getline(file, inputFile)){
            fileLines.push_back(inputFile);
        }
        file.close();
        
    }
    else {
        cout<< "File not able to open";
        exit(1);
    }
    
    // Returns fileLines, the lines of the file
    return fileLines;
    
}


vector< vector<string> > LinesToToken(deque<string> FileLines){
    
    // List of Tokens
    // Vector of Keywords
    vector<string> keywordVector{
        "BEGIN", "END", "FOR", "WHILE", "IF", "ELSE", "ELSEIF"
    };
    
    // Vector of delimiterVector
    vector<string> delimiterVector {
        "(", ")", ";", ","
    };
    
    // Vector of operatorVector
    vector<string> operatorVector{
        "*", "/", "++", "--", "==", "+", "-", "=", "<", ">", "&&", "||", "!"
    };
    
    while(!FileLines.empty()){
        
        //File size
         int inputVectorLength = FileLines.size();
        
        // Queue's first element
        string presentLine = FileLines.front();
        
        //Organize lines
        
        // Tokens of Keywords
        
        
        int i = 0;
        while (i<keywordVector.size()){
            string token = keywordVector.at(i);
            while (presentLine.find(token) != string::npos){
                // The word is added to present list and is removed from the past string
                present_keywordVector.push_back(token);
                presentLine.replace(presentLine.find(token),token.length(),"");
            }
            i++;
        }
       

        
        // Delimiter Tokens
        int j=0;
        while (j<delimiterVector.size()){
            string token = delimiterVector.at(j);
            while (presentLine.find(token) != string::npos){
                // The word is added to present list and is removed from the past string
                present_delimiterVector.push_back(token);
                presentLine.replace(presentLine.find(token),token.length(),"");
            }
            j++;
        }
        
        // Operator Tokens
        int k=0;
        while (k<operatorVector.size()){
            string token = operatorVector.at(k);
            while (presentLine.find(token) != string::npos){
                // The word is added to present list and is removed from the past string
                present_operatorVector.push_back(token);
                presentLine.replace(presentLine.find(token),token.length(),"");
            }
            k++;
        }
        
        
        // Discovers unrecognizable elements
        istringstream iss(presentLine);
        string tokenX;
        
        while(getline(iss, tokenX, ' ')) {
            
            string newString = delSpaces(tokenX);
            
            if(find(presentErrors.begin(), presentErrors.end(), newString) == presentErrors.end()){
                
                presentErrors.push_back(newString);
                
            }
            
        }
        
        // Eliminates first element
        FileLines.pop_front();
        
    }
    
    // Instantiates error
    presentErrors.erase(std::remove(presentErrors.begin(), presentErrors.end(), ""), presentErrors.end());
    
    // Errors are analyzed
    int y=0;
    while(y<presentErrors.size()){
        string VecElement = presentErrors.at(y);
        
        // Number is an error if statement
        if(numberCheck(VecElement)){
            
            // The number is added the list of constants
            present_constants.push_back(VecElement);
            presentErrors.at(y) = "DONE";
            
        }
        
        
        // Recognizable variable name is an error if statement
        
        if(!numberCheck(VecElement) && lowerCheck(VecElement)){
            
            // Element is added to list of identifiers
            present_identifierVector.push_back(VecElement);
            presentErrors.at(y) = "DONE";
            
        }
        y++;
        
    }
    
    
    // Deletes the errors that were checked
    presentErrors.erase(std::remove(presentErrors.begin(), presentErrors.end(), "DONE"), presentErrors.end());
    
    // EndVector has vectors added to it
    vector<vector<string>> EndVector{
        present_keywordVector,
        present_delimiterVector,
        present_operatorVector,
        present_identifierVector,
        present_constants,
        presentErrors,
    };
    
    return EndVector;
    
}

//Prints Vector
void printVector(vector<string> inputVector){
    
    // Retrieves size
    int inputSize = inputVector.size();
    
    // Prints all of the elements in terms of vectors
    int x=0;
    while (x<inputSize){
        cout<< inputVector.at(x) << " ";
        x++;
    }
    cout << endl;
    
}

string delSpaces(string &str){
    // Deletes the whitespace
    
    int i = 0;
    while (i<str.length()){
        if(str[i] == ' ' ||
           str[i] == '\t' ||
           str[i] == '\n' ||
           str[i] == '\v' ||
           str[i] == '\f' ||
           str[i] == '\r')
            str.erase(i,1);
        i++;
    }
    return str;
    
}

bool numberCheck(const string& s){
    
    string ::const_iterator ci = s.begin();
    while (ci != s.end() && isdigit(*ci)) ++ci;
    return !s.empty() && ci == s.end();
    
}

bool lowerCheck(string name){
    
    int strSize = name.length();
    bool isLower = true;
    
    //Returns false if uppercase, and true if vice versa
    for(int i = 0; i < strSize; i++){
        
        if(islower(name[i])){
            isLower = true;
        }
        else{
            return false;
        }
        
    }
    
    // Checks to see if string is in all lowercase
    return isLower;
    
}

void LexAnalyzer(vector< vector<string> > EndVector){
    
    // Storage, which is imported
    vector<string> present_keywordVector = EndVector[0];
    vector<string> present_delimiterVector = EndVector[1];
    vector<string> present_operatorVector = EndVector[2];
    vector<string> present_identifierVector = EndVector[3];
    vector<string> present_constants = EndVector[4];
    vector<string> presentErrors = EndVector[5];
    
    // Storage, which is unique to the current situation
    vector<string> unique_keywords = present_keywordVector;
    vector<string> unique_delimiters = present_delimiterVector;
    vector<string> unique_operators = present_operatorVector;
    vector<string> unique_identifier = present_identifierVector;
    vector<string> unique_constants = present_constants;
    vector<string> unique_errors = presentErrors;
    
    
    
    // Vector of keywords turns to unique using the standard vector, unique and sort
    sort( unique_keywords.begin(), unique_keywords.end() );
    unique_keywords.erase( unique( unique_keywords.begin(), unique_keywords.end() ), unique_keywords.end() );
    
    // Vecotr of delimiters turns to unique using the standard vector, unique and sort
    
    sort( unique_delimiters.begin(), unique_delimiters.end() );
    unique_delimiters.erase( unique( unique_delimiters.begin(), unique_delimiters.end() ), unique_delimiters.end() );
    
    // Vector of operators turns to unique using the standard vector, unique and sort
    sort( unique_operators.begin(), unique_operators.end() );
    unique_operators.erase( unique( unique_operators.begin(), unique_operators.end() ), unique_operators.end() );
    
    // Vector of identifiers turns to unique using the standard vector, unique and sort
    sort( unique_identifier.begin(), unique_identifier.end() );
    unique_identifier.erase( unique( unique_identifier.begin(), unique_identifier.end() ), unique_identifier.end() );
    
    // Vector of constants turns to unique using the standard vector, unique and sort
    sort( unique_constants.begin(), unique_constants.end() );
    unique_constants.erase( unique( unique_constants.begin(), unique_constants.end() ), unique_constants.end() );
    
    // Vector of errors turns to unique using the standard vector, unique and sort
    sort( unique_errors.begin(), unique_errors.end() );
    unique_errors.erase( unique( unique_errors.begin(), unique_errors.end() ), unique_errors.end() );
    
    // Evaluates the depth of the loop
    int loopsDepth = depth_of_loop(present_keywordVector);
    
    // Data output
    cout << "The Depth of the Nested Loop(s) is: " << loopsDepth << endl;
    cout << "Keywords: "; printVector(unique_keywords);
    cout << "Identifier: "; printVector(unique_identifier);
    cout << "Constant: "; printVector(unique_constants);
    cout << "Operators: "; printVector(unique_operators);
    cout << "Delimiters: "; printVector(unique_delimiters);
    cout << endl;
    
    // Syntax error analysis
    
    int counter = 0;
    while (counter< unique_errors.size()) {
        
        string present_Error = unique_errors.at(counter);
        
        cout << "Syntax Error(s): " << present_Error << endl;
        
        counter++;
    }
}

int depth_of_loop(vector<string> keywords){
    
    int depth = 0;
    int depthMax = 0;
    
    int counter = 0;
    
    while (counter<keywords.size()){
        string present_word = keywords.at(counter);
        
        // If word is FOR or WHILE, depth is increased by one
        if(present_word == "FOR" || present_word == "WHILE"){
            
            depth = depth + 1;
            
        }
        
        // Evaluate for a new max and minus depth when END is achieved
        if(present_word == "END"){
            if(depth > depthMax){
                depthMax = depth;
            }
            depth = depth - 1;
        }
        counter++;
    }
    
    // Ensures depthMax is either equal to or larger than depth
    if (depth > depthMax){
        depthMax = depth;
    }
    
    // Returns depthMax, the max depth of the nest
    return depthMax;
}









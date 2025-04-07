// front.cpp - a lexical analyzer system for simple arithmetic expressions
#include <iostream>      // For input and output
#include <fstream>       // For file operations
#include <sstream>       // For stringstream to simulate file input
#include <cctype>        // For character classification (e.g., isalpha, isdigit)
#include <string>        // For using string data type

using namespace std;     // Use standard C++ namespace

/* Character classes */
#define LETTER 0          // Character is a letter
#define DIGIT 1           // Character is a digit
#define UNKNOWN 99        // Character is not letter or digit

/* Token codes */
#define INT_LIT 10        // Integer literal token
#define IDENT 11          // Identifier token
#define ASSIGN_OP 20      // Assignment operator token (not used here but reserved)
#define ADD_OP 21         // Addition operator token
#define SUB_OP 22         // Subtraction operator token
#define MULT_OP 23        // Multiplication operator token
#define DIV_OP 24         // Division operator token
#define LEFT_PAREN 25     // Left parenthesis token
#define RIGHT_PAREN 26    // Right parenthesis token
#define END_OF_FILE -1    // End of file token

/* Global variables */
int charClass;            // Character class of the current character
string lexeme;            // String to store the current lexeme
char nextChar;            // Current character being read
int token;                // Token returned by lex (not used directly here)
int nextToken;            // Token identified in lex
istringstream input("(A * B + C)");  // Simulated input stream with formula

/* Function declarations */
void addChar();           // Add nextChar to lexeme
void getChar();           // Get next character and determine its class
void getNonBlank();       // Skip over whitespace characters
int lex();                // Main lexical analyzer function
int lookup(char ch);      // Lookup operator or parenthesis and return token

/* Main driver */
int main() {
    getChar();                                     // Read the first character
    do {
        lex();                                     // Call lexical analyzer
    } while (nextToken != END_OF_FILE);            // Repeat until EOF token
    string input;
    cin >> input;
    return 0;                                      // Successful execution
}

/* lookup - a function to lookup operators and parentheses and return the token */
int lookup(char ch) {
    switch (ch) {
    case '(':                                       // If character is '('
        addChar();                                 // Add to lexeme
        nextToken = LEFT_PAREN;                    // Set token type
        break;
    case ')':                                       // If character is ')'
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':                                       // If character is '+'
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':                                       // If character is '-'
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':                                       // If character is '*'
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':                                       // If character is '/'
        addChar();
        nextToken = DIV_OP;
        break;
    default:                                        // Any other character
        addChar();
        nextToken = END_OF_FILE;
        break;
    }
    return nextToken;                                  // Return the token
}

/* addChar - a function to add nextChar to lexeme */
void addChar() {
    lexeme += nextChar;                                // Append current char to lexeme
}

/* getChar - get the next character of input and determine its character class */
void getChar() {
    if (input.get(nextChar)) {                         // If there's a next char to read
        if (isalpha(nextChar))                          // If it's a letter
            charClass = LETTER;
        else if (isdigit(nextChar))                     // If it's a digit
            charClass = DIGIT;
        else                                            // If neither
            charClass = UNKNOWN;
    }
    else {
        charClass = END_OF_FILE;                        // End of input reached
    }
}

/* getNonBlank - skip over whitespace characters */
void getNonBlank() {
    while (isspace(nextChar))                          // While nextChar is a space
        getChar();                                     // Get next character
}

/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexeme = "";                                       // Clear lexeme
    getNonBlank();                                     // Skip any whitespace
    switch (charClass) {
        /* Parse identifiers */
    case LETTER:
        addChar();                                  // Add first letter
        getChar();                                  // Read next char
        while (charClass == LETTER || charClass == DIGIT) { // Continue if letter/digit
            addChar();
            getChar();
        }
        nextToken = IDENT;                          // Set token to IDENTIFIER
        break;

        /* Parse integer literals */
    case DIGIT:
        addChar();                                  // Add first digit
        getChar();
        while (charClass == DIGIT) {                // While more digits
            addChar();
            getChar();
        }
        nextToken = INT_LIT;                        // Set token to INTEGER LITERAL
        break;

        /* Parentheses and operators */
    case UNKNOWN:
        lookup(nextChar);                           // Look up operator/paren
        getChar();                                  // Read next character
        break;

        /* EOF */
    case END_OF_FILE:
        nextToken = END_OF_FILE;                    // Set EOF token
        lexeme = "EOF";                             // Set lexeme string
        break;
    }

    cout << "Next token is: " << nextToken              // Print token and lexeme
        << ", Next lexeme is " << lexeme << endl;
    return nextToken;                                  // Return token
}

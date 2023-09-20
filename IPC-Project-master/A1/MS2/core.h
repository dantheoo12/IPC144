/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : Daniel Jung
Student ID#: 046435038
Email      : djung1@myseneca.ca
Section    : NGG

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>
#include <string.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// displays cstring in format (###)###-####
// must validate if cstring is 10 characters long and only contains digits
// do not add a newline before or after the print
void displayFormattedPhone(const char* phoneNumber);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// return an int value from keyboard input
int inputInt(void);

// same as inputInt but validate for positive (0 is invalid as well)
int inputIntPositive(void);

// same as inputInt but checks if int is in the entered range (minimum, maximum) inclusive
int inputIntRange(int minimum, int maximum);

// returns a char if in the string valid
char inputCharOption(const char string[]);

// get user input and store to string if string is within minLength and maxLength inclusive
void inputCString(char result[], int minLength, int maxLength);












// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H

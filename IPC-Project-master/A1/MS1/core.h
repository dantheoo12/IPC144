/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Daniel Jung
Student ID#: 046435038
Email      : djung1@myseneca.ca
Section    : NGG

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// mandatory functions
void clearInputBuffer(void); 
void suspend(void);

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

// displays cstring in format (###)###-####
// must validate if cstring is 10 characters long and only contains digits
// do not add a newline before or after the print
void displayFormattedPhone(char* phoneNumber);

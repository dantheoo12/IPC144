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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "core.h"

// mandatory functions

// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer 
// Clear the standard input buffer 
void clearInputBuffer(void) 
{ 
    // Discard all remaining char's from the standard input buffer: 
    while (getchar() != '\n') 
    { 
        ; // do nothing! 
    } 
}

// Wait for user to input the "enter" key to continue 
void suspend(void) 
{ 
    printf("<ENTER> to continue...");
    clearInputBuffer(); 
    putchar('\n'); 
}

// Return user inputted int, output error if invalid and continue prompting until valid int is returned
int inputInt(void)
{
    char newLine = 'x';
    int value = 0;

    while (newLine != '\n')
    {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    }
    return value;
}

// Return valid positive nonzero user inputted int
int inputIntPositive(void)
{
    int value = inputInt();

    while (value <= 0)
    {
        printf("ERROR! Value must be > 0: ");
        value = inputInt();
    }
    return value;
}

// Return valid user int within range minimum and maximum
int inputIntRange(int minimum, int maximum)
{
    int value = inputInt();

    while (value < minimum || value > maximum)
    {
        printf("ERROR! Value must be between %d and %d inclusive: ", minimum, maximum);
        value = inputInt();
    }
    return value;
}

// Return user char iff it is in the string[] 
char inputCharOption(const char validChars[])
{
    int valid = 0,i = 0;
    char inputChar = '\0';

    do
    {
        scanf("%c", &inputChar);
        clearInputBuffer();
        i = 0;
        while (validChars[i] != '\0' && !valid) // stop at end of string OR valid char is found
        {
            if (inputChar == validChars[i]) 
                valid = 1;
            i++;
        }

        if (!valid) // no match found after iterating over string
        {
            // print string of accepted characters
            printf("ERROR: Character must be one of [");
            i = 0;
            while (validChars[i] != '\0')
            {
                printf("%c", validChars[i]); 
                i++;
            }
            printf("]: ");
        }
    } while (!valid); 
    return inputChar;
}

// Store user string to string[] iff it is within minLength and maxLength inclusive
void inputCString(char result[], int minLength, int maxLength)
{
    int valid = 0, i = 0;
    char inputString[100] = { '\0' }; // check if this method is okay, is there way to initialize a local variable length string or use a pointer?

    do
    {
        int length = 0;

        scanf("%[^\n]", inputString);
        clearInputBuffer(); // clear remaining \n from buffer

        // validate inputString
        while (inputString[length] != '\0') 
            length++; 
            
        if (length >= minLength && length <= maxLength)
            valid = 1; 
            
        // error messages for invalid string
        if (!valid)
        {
            if (minLength == maxLength) // explicit string length
                printf("ERROR: String length must be exactly %d chars: ", minLength);
            else if (length > maxLength) // string is too long
                printf("ERROR: String length must be no more than %d chars: ", maxLength);
            else if (length < minLength) // string is too short
                printf("ERROR: String length must be between %d and %d chars: ", minLength, maxLength);
        }
    } while (!valid);

    // write valid inputString to result array
    for (i = 0; inputString[i] != '\0'; i++)
        result[i] = inputString[i];
}

void displayFormattedPhone(char *phoneNumber)
{
    int valid = 0, length = 0, i = 0; // valid = number of valid characters, length = total phoneNumber length, i = iterator
    char *tempPtr = phoneNumber; // traversal pointer
    char digits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; // array of digit characters to check against

    // validate phone number
    if (tempPtr != NULL) // ignore if NULL pointer received
    {
        while (*tempPtr != '\0') // string still has characters
        {
            for (i = 0; i < 10; i++) // iterate over digits and check if *ptr is a digit
            {
                if (digits[i] == *tempPtr)
                    valid++; // counts valid numbers
            }
            length++, tempPtr++;
        }
    }

    // Print formatted phone number if valid or (___)___-____ if not valid
    if (valid == 10 && length == 10) // phone number is ONLY 10 VALID characters
    {
        i = 0;
        tempPtr = phoneNumber; // reset tempPtr to start of phoneNumber string
        // print formatted string
        while (*tempPtr != '\0')
        {
            // added symbols to phone number string
            switch (i)
            {
            case 0:
                printf("("); // print ( before character 0
                break;
            case 3:
                printf(")"); // print ) before character 3
                break;
            case 6:
                printf("-"); // print - before character 6
                break;
            }
            printf("%c", *tempPtr);
            i++, tempPtr++;
        }
    }
    else
    {
        printf("(___)___-____");
    }
}
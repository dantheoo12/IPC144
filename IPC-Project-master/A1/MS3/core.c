/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
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

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

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


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

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

// Return positive nonzero user inputted int
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

// Return user int within range minimum and maximum inclusive
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
    int found = 0;
    char inputChar = '\0', newline = '\0';

    do
    {
        scanf("%c%c", &inputChar, &newline);

        if (strchr(validChars, inputChar) != NULL) // character was found in string
            found = 1;

        if (!found || newline != '\n')
        {
            clearInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
    } while (!found || newline != '\n');
    return inputChar;
}

// Store user string to string[] iff it is within minLength and maxLength inclusive
void inputCString(char result[], int minLength, int maxLength)
{
    int valid = 0, length = 0;
    char inputString[100] = { '\0' };

    do
    {
        scanf("%[^\n]", inputString);
        clearInputBuffer(); // clear remaining \n from buffer
        length = strlen(inputString);
        if (strlen(inputString) >= minLength && strlen(inputString) <= maxLength)
            valid = 1;

        // error messages for invalid string
        if (!valid)
        {
            if (minLength == maxLength) // explicit string length
                printf("Invalid %d-digit number! Number: ", minLength);
            else if (length > maxLength) // string is too long
                printf("ERROR: String length must be no more than %d chars: ", maxLength);
            else if (length < minLength) // string is too short
                printf("ERROR: String length must be between %d and %d chars: ", minLength, maxLength);
        }
    } while (!valid);

    // write valid inputString to result string
    strcpy(result, inputString);
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Display 10 digit-only string in phone number fomat
void displayFormattedPhone(const char* phoneNumber)
{
    int validChars = 0, i = 0, length = strlen(phoneNumber); // validChars = number of valid characters, i = iterator
    char digits[] = "0123456789"; // digit characters to check against

    // validate phone number characters 
    if (phoneNumber != NULL) // ignore if NULL pointer received
    {
        for (i = 0; i < length; i++)
        {
            if (strchr(digits, phoneNumber[i]) != NULL)
                validChars++;
        }
    }

    // Print formatted phone number if valid or (___)___-____ if not valid
    if (validChars == 10 && length == 10) // phone number is ONLY 10 VALID characters
    {
        // print formatted string
        for (i = 0; i < length; i++)
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
            printf("%c", phoneNumber[i]);
        }
    }
    else
    {
        printf("(___)___-____");
    }
}


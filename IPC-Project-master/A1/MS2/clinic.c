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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    
    if (fmt == FMT_TABLE) // FMT_TABLE header
        displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0) // patient exists
            displayPatientData(&(patient[i]), fmt);
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        switch (selection)
        {
        case (1):
            searchPatientByPatientNumber(patient, max);
            break;
        case (2):
            searchPatientByPhoneNumber(patient, max);
            break;
        }
    } while (selection);
    putchar('\n');
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i, emptyIndex = -1, found= 0;

    // check if there is an empty slot in the patient array and set to emptyIndex
    // if none emptyIndex = -1
    for (i = 0; i < max && !found; i++)
    {
        if (patient[i].patientNumber == 0) // there is an available patient slot in the array at i
        {
            emptyIndex = i; // emptyIndex is the index of the available position
            found = 1;
        }
    }

    if (emptyIndex == -1) // no available slots in the array
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    else // there is an available slot at emptyIndex
    {
        patient[emptyIndex].patientNumber = nextPatientNumber(patient, max); // set patientNumber at emptyIndex to next available number
        inputPatient(&patient[emptyIndex]);
        printf("*** New patient record added ***\n");
    }
    putchar('\n');
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNumber, patientIndex;

    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
    putchar('\n');
    if (patientIndex == -1) // patient not found
    {
        printf("ERROR: Patient record not found!\n");
        putchar('\n');
    }
    else // patient found
    {
        menuPatientEdit(&patient[patientIndex]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNumber, patientIndex;
    char selection;

    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
    putchar('\n');
    if (patientIndex == -1) // patient not found
    {
        printf("ERROR: Patient record not found!\n");
    }
    else // patient found
    {
        displayPatientData(&(patient[patientIndex]), 1);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn");
        switch (selection)
        {
        case ('y'):
            patient[patientIndex].patientNumber = 0;
            strcpy(patient[patientIndex].name, "\0");
            strcpy(patient[patientIndex].phone.description, "\0");
            strcpy(patient[patientIndex].phone.number, "\0");
            printf("Patient record has been removed!\n");
            break;
        case ('n'):
            printf("Operation aborted.\n"); 
            break;
        }
    }
    putchar('\n');
}




//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int searchNumber, patientIndex;

    putchar('\n');
    printf("Search by patient number: ");
    searchNumber = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(searchNumber, patient, max);
    putchar('\n');
    if (patientIndex != -1) // patient was found
        displayPatientData(&(patient[patientIndex]), 1);
    else
        printf("*** No records found ***\n");
    putchar('\n');
    suspend();
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char searchPhoneNumber[11]; // extra space for \0
    int i, matches = 0;

    putchar('\n');
    printf("Search by phone number: ");
    inputCString(searchPhoneNumber, 10, 10);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (!strcmp(searchPhoneNumber, patient[i].phone.number)) // searchPhoneNumber matches patient's phone number
        {
            displayPatientData(&(patient[i]), 2);
            matches++;
        }
    }
    if (matches == 0)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int newestPatientNumber = 0, i;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > newestPatientNumber)
            newestPatientNumber = patient[i].patientNumber;
    }
    return newestPatientNumber + 1; // next available patient number
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i, patientIndex = -1, found = 0;

    for (i = 0; i < max && !found; i++)
    {
        if (patient[i].patientNumber == patientNumber) // match found
            patientIndex = i, found = 1;
    }
    return patientIndex;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&(patient->phone));
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;
    
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    switch (selection)
    {
    case (1): // cell
        putchar('\n');
        printf("Contact: CELL\n");
        strcpy(phone->description, "CELL");
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        break;
    case (2): // home
        putchar('\n');
        printf("Contact: HOME\n");
        strcpy(phone->description, "HOME");
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        break;
    case (3): // work
        putchar('\n');
        printf("Contact: WORK\n");
        strcpy(phone->description, "WORK");
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        break;
    case (4): // tbd
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "\0");
        break;
    }
    putchar('\n');
}

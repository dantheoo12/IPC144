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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
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
    int i, emptyIndex = -1, found = 0;

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


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, j;
    struct Appointment sorted[50] = { {0} };
    struct Patient currentPatient = { 0 } ;

    sortAppointments(data->appointments, sorted);

    displayScheduleTableHeader(NULL, 1);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (sorted[i].patientNumber != 0) // there is an appointment
        {
            for (j = 0; j < data->maxPatient; j++)
            {
                // if patient number for the current appointment matches a patient
                if (sorted[i].patientNumber == data->patients[j].patientNumber)
                {
                    currentPatient = data->patients[j];
                }
            }
            displayScheduleData(&currentPatient, &sorted[i], 1);
        }
    }
    putchar('\n');
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i, j;
    struct Appointment appointmentDate = { 0 } ;
    struct Appointment sorted[50] = { {0} };
    struct Patient currentPatient = { 0 };

    sortAppointments(data->appointments, sorted);
    appointmentDate = inputAppointmentDate();

    putchar('\n');
    displayScheduleTableHeader(&appointmentDate.date, 0);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (sorted[i].date.year == appointmentDate.date.year &&
            sorted[i].date.month == appointmentDate.date.month &&
            sorted[i].date.day == appointmentDate.date.day) // current appointment date matches searched 
        {
            for (j = 0; j < data->maxPatient; j++)
            {
                // if patient number for the current appointment matches a patient
                if (sorted[i].patientNumber == data->patients[j].patientNumber)
                {
                    currentPatient = data->patients[j];
                }
            }
            displayScheduleData(&currentPatient, &sorted[i], 0);
        }
    }
    putchar('\n');
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment appointments[], int maxAppointments,
    struct Patient patients[], int maxPatients)
{
    int i, // iterator
        patientNumber = 0, // temporary patient number to store 
        validFormat = 1, available = 1, // validation flags
        appointmentTimeMinutes = 0, appointmentDateMinutes = 0, 
        availableAppointment = 0; // next available appointment index
    struct Appointment appointment = { 0 };

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    do
    {
        appointment = inputAppointmentDate();

        do
        {
            validFormat = 1; // reset validFormat flag
            printf("Hour (0-23)  : ");
            appointment.time.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            appointment.time.min = inputIntRange(0, 59);

            appointmentTimeMinutes = (appointment.time.hour * 60) + appointment.time.min; // convert time to minutes format
            if (appointmentTimeMinutes < STARTTIME * 60 ||
                appointmentTimeMinutes > ENDTIME * 60 ||
                appointment.time.min % APPOINTMENT_INTERVAL != 0) // time is in invalid format
            {
                validFormat = 0;
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n", 
                    STARTTIME, ENDTIME, APPOINTMENT_INTERVAL);
                putchar('\n');
            }            
        } while (!validFormat);

        available = 1; // reset available appointment flag
        appointmentDateMinutes = appointmentTimeToMinutes(appointment); // convert date to minutes format
        for (i = 0; i < maxAppointments && available; i++)
        {
            if (appointmentDateMinutes == appointmentTimeToMinutes(appointments[i])) // date matches existing appointment date
            {
                available = 0;
                putchar('\n');
                printf("ERROR: Appointment timeslot is not available!\n");
            }
        }
        putchar('\n');
    } while (!available);

    // find empty position in appointments array
    for (i = 0; i < maxAppointments; i++)
    {
        if (appointments[i].patientNumber == 0)
        {
            availableAppointment = i;
        }
    }

    appointment.patientNumber = patientNumber;
    appointments[availableAppointment] = appointment;
    printf("*** Appointment scheduled! ***\n");
    putchar('\n');
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appointments[], int maxAppointments,
    struct Patient patients[], int maxPatients)
{
    int i, patientNumber, found = 0, appointmentIndex;
    char selection;
    struct Appointment appointment = { 0 };
    struct Patient patient = { 0 };

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    for (i = 0; i < maxPatients; i++)
    {
        if (patients[i].patientNumber == patientNumber)
        {
            found = 1;
        }
    }

    if (found)
    {
        appointment = inputAppointmentDate();
        appointment.patientNumber = patientNumber;

        // find patient that matches patient number
        for (i = 0; i < maxPatients; i++)
        {
            if (patients[i].patientNumber == patientNumber)
            {
                patient = patients[i];
            }
        }
        putchar('\n');
        displayPatientData(&patient, FMT_FORM);

        printf("Are you sure you want to remove this appointment (y,n): ");
        selection = inputCharOption("yn");

        switch (selection)
        {
        case 'y':
            appointmentIndex = findAppointmentIndexByAppointment(appointment, appointments, maxAppointments);
            appointments[appointmentIndex].patientNumber = 0;
            appointments[appointmentIndex].date.year = 0;
            appointments[appointmentIndex].date.month = 0;
            appointments[appointmentIndex].date.day = 0;
            appointments[appointmentIndex].time.hour = 0;
            appointments[appointmentIndex].time.min = 0;
            putchar('\n');
            printf("Appointment record has been removed!\n");
            break;

        case 'n':
            printf("Operation aborted.\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
        
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
        displayPatientData(&(patient[patientIndex]), FMT_FORM);
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


// Return the next highest patient number
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


// Return the patient array index by patient number (returns -1 if not found)
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

// Take an Appointment and return its date/time in minutes
// 20XX year is applied
int appointmentTimeToMinutes(struct Appointment appointment)
{
    int minutes = 0;

    minutes += (appointment.date.year % 2000) * 525600;
    minutes += appointment.date.month * 43800;
    minutes += appointment.date.day * 1440;
    minutes += appointment.time.hour * 60;
    minutes += appointment.time.min;

    return minutes;
}

// Return array of appointments in chronological order ascending
void sortAppointments(struct Appointment appoints[], struct Appointment sortedAppoints[])
{
    int i, j, // iterators
        lowest = 0, // index of the lowest item
        minutes, // current appointment date converted to minutes
        numAppointments = 0, 
        pastMin = 2000000000, currentMin = 2000000000; // initial values of lowests
    
    // set number of appointments
    for (i = 0; i < 50; i++)
    {
        if (appoints[i].patientNumber != 0)
            numAppointments++;
    }

    // set the first value of the sorted array
    for (i = 0; i < numAppointments; i++)
    {
        if (appoints[i].patientNumber != 0) // there is an appointment at i
        {
            minutes = appointmentTimeToMinutes(appoints[i]); // convert date to minutes format
            if (minutes < currentMin) // if current appointment is earlier than previously found earliest appointment
            {
                currentMin = minutes;
                lowest = i;
            }
        }
    }
    pastMin = currentMin; // pastMin stores the previous lowest value
    sortedAppoints[0] = appoints[lowest];

    // sort the rest of the items in sorted
    for (i = 1; i < numAppointments; i++) // iterating over the sorted array
    {
        currentMin = 2000000000; // reset currentMin to INT_MAX
        // iterate over appoints array and store the lowest index as well as the next lowest minute value
        for (j = 0; j < 50; j++) // iterating over the appoints array
        {
            if (appoints[j].patientNumber != 0) // there is an appointment at j
            {
                minutes = appointmentTimeToMinutes(appoints[j]);

                if (minutes < currentMin && minutes > pastMin) // current item is earlier than previously stored item but still greater than the previous
                {
                    currentMin = minutes;
                    lowest = j; // set currentMin to current minutes, lowest index is j
                }
            }
        }
        sortedAppoints[i] = appoints[lowest];
        pastMin = currentMin;
    }
}

// Returns index of given appointment date, -1 if not found
int findAppointmentIndexByAppointment(struct Appointment appointment, struct Appointment appointments[], int max)
{
    int i, appointmentIndex = -1, found = 0;
    
    for (i = 0; i < max && !found; i++)
    {
        if (appointment.patientNumber == appointments[i].patientNumber &&
            appointment.date.year == appointments[i].date.year &&
            appointment.date.month == appointments[i].date.month &&
            appointment.date.day == appointments[i].date.day)
        {
            appointmentIndex = i;
            found = 1;
        }
    }
    
    return appointmentIndex;
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

// Get user input for date and return as an appointment with patientNumber 0
struct Appointment inputAppointmentDate(void)
{
    int dayMax = 0;
    struct Appointment appointmentDate = { 0 };

    printf("Year        : ");
    appointmentDate.date.year = inputIntPositive();
    printf("Month (1-12): ");
    appointmentDate.date.month = inputIntRange(1, 12);
    
    // set maximum days of the month based on month
    if (appointmentDate.date.month == 1 ||
        appointmentDate.date.month == 3 ||
        appointmentDate.date.month == 5 ||
        appointmentDate.date.month == 7 ||
        appointmentDate.date.month == 8 ||
        appointmentDate.date.month == 10 ||
        appointmentDate.date.month == 12)
    {
        dayMax = 31;
    }
    else if (appointmentDate.date.month == 4 ||
        appointmentDate.date.month == 6 ||
        appointmentDate.date.month == 9 ||
        appointmentDate.date.month == 11)
    {
        dayMax = 30;
    }
    else if (appointmentDate.date.month == 2 && appointmentDate.date.year % 4 == 0) // leap year february
    {
        dayMax = 29;
    }
    else // february
    {
        dayMax = 28;
    }

    printf("Day (1-%d)  : ", dayMax);
    appointmentDate.date.day = inputIntRange(1, dayMax);

    return appointmentDate;
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int numPatients = 0, i;
    FILE* patientFile = NULL;

    patientFile = fopen(datafile, "r");

    if (patientFile != NULL) // file opened successfully
    {
        for (i = 0; i < max; i++)
        {
            if (fscanf(patientFile, "%d|%[^|]|%[^|]|%[^\n]",
                &(patients[i].patientNumber),
                patients[i].name,
                patients[i].phone.description,
                patients[i].phone.number)
                >= 3) // phone number may be blank string
            {
                numPatients++;
            }
        }
        fclose(patientFile);
    }
    else // unsuccessful file open
    {
        printf("Failed to open file.\n");
    }

    return numPatients;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* appointmentFile = NULL;
    int i, numAppointments = 0;

    appointmentFile = fopen(datafile, "r");

    if (appointmentFile != NULL)
    {
        for (i = 0; i < max; i++)
        {
            if (fscanf(appointmentFile, "%d,%d,%d,%d,%d,%d\n",
                &appoints[i].patientNumber,
                &appoints[i].date.year,
                &appoints[i].date.month,
                &appoints[i].date.day,
                &appoints[i].time.hour,
                &appoints[i].time.min)
                == 6) // all 6 fields successfully read
            {
                numAppointments++;
            }
        }
        fclose(appointmentFile);
    }
    else
    {
        printf("Failed to open file.\n");
    }
    return numAppointments;
}

/* ELVIS MUSUNGU SIMIYU */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //Library will allow me to pause the program from 10s when executing.

// Define a structure to store visitor information
struct visitData
{
    char SrNo[3];
    char ticketNo[7];
    char Name[30];
    char ID[20];
};

// Define a linked list structure to store the data
struct ticket
{

struct visitData visitor;
struct ticket *nextPtr;

};

//function to add users generate ticket file and serial number.
void add_users(struct ticket **headPtr, int *count, int *currentSrNo)

{
    // Check if the number of visitors has reached the limit
    if (*count >= 40)
    {
        fprintf(stderr, "Error: visitor limit reached.\n");
        exit(EXIT_FAILURE);
    }

    // Declare and allocate memory for the visitor data variables
    char Name[30];
    char ID[20];

    // Prompt the user to enter the visitor data

    printf("Enter your name( DON'T SPACE! Put an underscore between first and second names): \n");
    scanf("%s",Name);
    printf("\n");

    printf("ID(INDICATE Whether its IC or PASS): \n");
    scanf("%s",ID);
    printf("\n");

    // Allocate memory for a new visitor data structure

    struct visitData *visitorPtr = malloc(sizeof(struct visitData));
    if (visitorPtr == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory for visitor data.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the visitor data

    char SrNo[3];
    sprintf(SrNo, "%02d", *currentSrNo); // Generate serial number with leading zeros
    strcpy(visitorPtr->SrNo, SrNo);

    // Check if the current serial number is greater than 40 and reset it to 01 if necessary
    if (*currentSrNo > 40)
    {
        *currentSrNo = 1;
    }
    else
    {
        (*currentSrNo)++; // Increment the current serial number by 1
    }

    // Generate a unique ticket number using the decimal equivalent of the letters in the name
    char ticketNo[7];
    int ticketNumber = 0;
    for (int i = 0; i < strlen(Name); i++)
    {
    if (Name[i] >= 'A' && Name[i] <= 'Z')
    {
    ticketNumber += Name[i] - 'A';
    }
    else if (Name[i] >= 'a' && Name[i] <= 'z')
    {
    ticketNumber += Name[i] - 'a';
    }
    }
    ticketNumber += *count + 1;
    sprintf(ticketNo, "%d", ticketNumber);
    strcpy(visitorPtr->ticketNo, ticketNo);
    strcpy(visitorPtr->Name, Name);
    strcpy(visitorPtr->ID, ID);

    // Add the visitor data to the linked list

    if (*headPtr == NULL)
    {
        // If the linked list is empty, set the new node as the head of the linked list
        *headPtr = malloc(sizeof(struct ticket));
        if (*headPtr == NULL)
        {
            fprintf(stderr, "Error: unable to allocate memory for new node.\n");
            exit(EXIT_FAILURE);
        }
        (*headPtr)->visitor = *visitorPtr;
        (*headPtr)->nextPtr = NULL;
    }
    else
    {
        // If the linked list is not empty, traverse the linked list to find the last node

        struct ticket *currentPtr = *headPtr;
        while (currentPtr->nextPtr != NULL)
        {
            currentPtr = currentPtr->nextPtr;
        }

        // Create a new node for the visitor data and set its next pointer to NULL

        struct ticket *newPtr = malloc(sizeof(struct ticket));
        if (newPtr == NULL)
        {
            fprintf(stderr, "Error: unable to allocate memory for new node.\n");
            exit(EXIT_FAILURE);
        }

        newPtr->visitor = *visitorPtr;
        newPtr->nextPtr = NULL;

        // Set the next pointer of the last node in the linked list to the new node
        currentPtr->nextPtr = newPtr;
    }
    (*count)++;
    (*currentSrNo)++; // Increment the current serial number

    // Clean up
    free(visitorPtr);
}

//function for search by ticket number
void search_by_ticketno(struct ticket *headPtr, char *ticketno)

{
    // Traverse the linked list and search for the visitor with the specified ticket number
    struct ticket *currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        if (strcmp(currentPtr->visitor.ticketNo, ticketno) == 0)
        {
            // If the ticket number matches, print the visitor information
            printf("%s, %s, %s, %s\n", currentPtr->visitor.SrNo, currentPtr->visitor.ticketNo, currentPtr->visitor.Name, currentPtr->visitor.ID);
            return;
        }
        currentPtr = currentPtr->nextPtr;
    }

    // If the visitor was not found, print an error message
    printf("Error: visitor with ticket number %s not found.\n", ticketno);
}

//function for search by name
void search_user_name(struct ticket *headPtr, char *name)

{
    // Convert the search name to all lowercase
    char searchName[30];
    strcpy(searchName, name);
    for (int i = 0; i < strlen(searchName); i++)
    {
        searchName[i] = tolower(searchName[i]);
    }

    // Traverse the linked list and search for the user with the specified name
    struct ticket *currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        // Convert the visitor name to all lowercase
        char visitorName[30];
        strcpy(visitorName, currentPtr->visitor.Name);
        for (int i = 0; i < strlen(visitorName); i++)
        {
            visitorName[i] = tolower(visitorName[i]);
        }

        if (strcmp(visitorName, searchName) == 0)
        {
            // If the user is found, print their data in a single line
            printf("%s, %s, %s, %s\n", currentPtr->visitor.SrNo, currentPtr->visitor.ticketNo, currentPtr->visitor.Name, currentPtr->visitor.ID);
            return;
        }
        currentPtr = currentPtr->nextPtr;
    }

    // If the user is not found, print an error message
    printf("Error: user not found.\n");
}

//function for search by ID
void search_user_by_ID(struct ticket *headPtr, char *ID)
{
    // Traverse the linked list and search for the user with the specified ID
    struct ticket *currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        if (strcmp(currentPtr->visitor.ID, ID) == 0)
        {
            // If the user is found, print their data in a single line
            printf("%s, %s, %s, %s\n", currentPtr->visitor.SrNo, currentPtr->visitor.ticketNo, currentPtr->visitor.Name, currentPtr->visitor.ID);
            return;
        }
        currentPtr = currentPtr->nextPtr;
    }

    // If the user is not found, print an error message
    printf("Error: user not found.\n");
}

void delete_visitor_ticket(struct ticket **headPtr, int *count, char *ticketNo)
{
    // Check if the linked list is empty
    if (*headPtr == NULL)
    {
        fprintf(stderr, "Error: linked list is empty.\n");
        return;
    }

    // Check if the visitor to be deleted is the first node in the linked list
    if (strcmp((*headPtr)->visitor.ticketNo, ticketNo) == 0)
    {
        // Display the visitor information before deleting the node
        printf("Deleting visitor with ticket number %s and serial number %s\n", (*headPtr)->visitor.ticketNo, (*headPtr)->visitor.SrNo);
        printf("Name: %s\n", (*headPtr)->visitor.Name);
        printf("ID: %s\n", (*headPtr)->visitor.ID);

        // Save a pointer to the first node
        struct ticket *tempPtr = *headPtr;

        // Set the head pointer to the second node
        *headPtr = (*headPtr)->nextPtr;

        // Free the memory allocated for the first node
        free(tempPtr);

        (*count)--; // Decrement the count of visitors by 1

        sleep(10); // Pause the program for 10 seconds

        return;
    }

    // If the visitor is not the first node, traverse the linked list to find the node to be deleted
    struct ticket *currentPtr = *headPtr;
    while (currentPtr->nextPtr != NULL && strcmp(currentPtr->nextPtr->visitor.ticketNo, ticketNo) != 0)
    {
        currentPtr = currentPtr->nextPtr;
    }

    // Check if the visitor was found in the linked list
    if (currentPtr->nextPtr == NULL)
    {
        fprintf(stderr, "Error: visitor not found.\n");
        return;
    }

    // Display the visitor information before deleting the node
    printf("Deleting visitor with ticket number %s and serial number %s, Name: %s, ID: %s\n", (*headPtr)->visitor.ticketNo, (*headPtr)->visitor.SrNo, (*headPtr)->visitor.Name, (*headPtr)->visitor.ID);

    // Save a pointer to the node to be deleted
    struct ticket *tempPtr = currentPtr->nextPtr;

    // Set the next pointer of the current node to the node after the one to be deleted
    currentPtr->nextPtr = currentPtr->nextPtr->nextPtr;

    // Free the memory allocated for the node to be deleted
    free(tempPtr);

    (*count)--; // Decrement the count of visitors by 1
}


//function for delete by name
void delete_user_by_name(struct ticket **headPtr, int *count, char *name)

{
    // Check if the linked list is empty
    if (*headPtr == NULL)
    {
        fprintf(stderr, "Error: linked list is empty.\n");
        return;
    }

    // Check if the visitor to be deleted is the first node in the linked list
    if (strcmp((*headPtr)->visitor.Name, name) == 0)
    {
        // Display the visitor information before deleting the node
        printf("Deleting visitor with ticket number %s and serial number %s, Name: %s, ID: %s\n", (*headPtr)->visitor.ticketNo, (*headPtr)->visitor.SrNo, (*headPtr)->visitor.Name, (*headPtr)->visitor.ID);

        // Save a pointer to the first node
        struct ticket *tempPtr = *headPtr;

        // Set the head pointer to the second node
        *headPtr = (*headPtr)->nextPtr;

        // Free the memory allocated for the first node
        free(tempPtr);

        (*count)--; // Decrement the count of visitors by 1
        return;
    }

    // If the visitor is not the first node, traverse the linked list to find the node to be deleted
    struct ticket *currentPtr = *headPtr;
    while (currentPtr->nextPtr != NULL && strcmp(currentPtr->nextPtr->visitor.Name, name) != 0)
    {
        currentPtr = currentPtr->nextPtr;
    }

    // Check if the visitor was found in the linked list
    if (currentPtr->nextPtr == NULL)
    {
        fprintf(stderr, "Error: visitor not found.\n");
        return;
    }

    // Display the visitor information before deleting the node
    printf("Deleting visitor with ticket number %s and serial number %s, Name: %s, ID: %s\n", (*headPtr)->visitor.ticketNo, (*headPtr)->visitor.SrNo, (*headPtr)->visitor.Name, (*headPtr)->visitor.ID);

    // Save a pointer to the node to be deleted
    struct ticket *tempPtr = currentPtr->nextPtr;

    // Set the next pointer of the current node to the node after the one to be deleted
    currentPtr->nextPtr = currentPtr->nextPtr->nextPtr;

    // Free the memory allocated for the node to be deleted
    free(tempPtr);

    (*count)--; // Decrement the count of visitors by 1
}


//function for delete by ID
void delete_user_by_ID(struct ticket **headPtr, int *count, char *ID)
{
    // Check if the linked list is empty
    if (*headPtr == NULL)
    {
        fprintf(stderr, "Error: linked list is empty.\n");
        return;
    }

    // Check if the visitor to be deleted is the first node in the linked list
    if (strcmp((*headPtr)->visitor.ID, ID) == 0)
    {
    // Display the visitor information before deleting the node
    printf("Deleting visitor with ticket number %s and serial number %s, Name: %s, ID: %s\n", (*headPtr)->visitor.ticketNo, (*headPtr)->visitor.SrNo, (*headPtr)->visitor.Name, (*headPtr)->visitor.ID);

        // Save a pointer to the first node
        struct ticket *tempPtr = *headPtr;

        // Set the head pointer to the second node
        *headPtr = (*headPtr)->nextPtr;

        // Free the memory allocated for the first node
        free(tempPtr);

        (*count)--; // Decrement the count of visitors by 1
        return;
    }

    // If the visitor is not the first node, traverse the linked list to find the node to be deleted
    struct ticket *currentPtr = *headPtr;
    while (currentPtr->nextPtr != NULL && strcmp(currentPtr->nextPtr->visitor.ID, ID) != 0)
    {
        currentPtr = currentPtr->nextPtr;
    }

    // Check if the visitor was found in the linked list
    if (currentPtr->nextPtr == NULL)
    {
        fprintf(stderr, "Error: visitor not found.\n");
        return;
    }

    // Display the visitor information before deleting the node
    printf("Deleting visitor with ticket number %s and serial number %s, Name: %s, ID: %s\n", (*headPtr)->visitor.ticketNo, (*headPtr)->visitor.SrNo, (*headPtr)->visitor.Name, (*headPtr)->visitor.ID);

    // Save a pointer to the node to be deleted
    struct ticket *tempPtr = currentPtr->nextPtr;

    // Set the next pointer of the current node to the node after the one to be deleted
    currentPtr->nextPtr = currentPtr->nextPtr->nextPtr;

    // Free the memory allocated for the node to be deleted
    free(tempPtr);

    (*count)--; // Decrement the count of visitors by 1
}


//FUNCTION FOR VIEWING USERS AND OUTPUTTING VISITOR.TXT
void view_users(struct ticket *headPtr)

{
    // Check if the linked list is empty
    if (headPtr == NULL)
    {
        printf("No users have been added to the system.\n");
        return;
    }

    // Traverse the linked list and count the number of users
    int count = 0;
    struct ticket *currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        currentPtr = currentPtr->nextPtr;
        count++; // Increment the counter
    }

    // Print the total number of users
    printf("Total Visitors: %d\n", count);

    // Traverse the linked list and print the visitor data for each node, sorted in ascending order by name
    currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        struct ticket *nextPtr = currentPtr->nextPtr;
        while (nextPtr != NULL)
        {
            // If the current name is lexicographically greater than the next name, swap the data
            if (strcmp(currentPtr->visitor.Name, nextPtr->visitor.Name) > 0)
            {
                struct visitData temp = currentPtr->visitor;
                currentPtr->visitor = nextPtr->visitor;
                nextPtr->visitor = temp;
            }

            nextPtr = nextPtr->nextPtr;
        }

        currentPtr = currentPtr->nextPtr;
    }

    // Open the output file
    FILE *fp = fopen("visitors.txt", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: unable to open output file.\n");
        return;
    }

    // Write the total number of visitors to the output file
    fprintf(fp, "Total number of visitors: %d\n", count);

    // Traverse the linked list and write the visitor data to the output file and console
    currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        fprintf(fp, "%s, %s, %s, %s\n", currentPtr->visitor.SrNo, currentPtr->visitor.ticketNo, currentPtr->visitor.Name, currentPtr->visitor.ID);
        printf("%s, %s, %s, %s\n", currentPtr->visitor.SrNo, currentPtr->visitor.ticketNo, currentPtr->visitor.Name, currentPtr->visitor.ID);

        currentPtr = currentPtr->nextPtr;
    }

    // Close the output file
    fclose(fp);

}

//Function for output.txt file
void generate_txt_file(struct ticket *headPtr, char *outputFile)

{
    // Check if the linked list is empty
    if (headPtr == NULL)
    {
        printf("No visitors have been added to the system.\n");
        return;
    }

    // Traverse the linked list and sort the data in ascending order by name
    struct ticket *currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        struct ticket *nextPtr = currentPtr->nextPtr;
        while (nextPtr != NULL)
        {
            // If the current name is lexicographically greater than the next name, swap the data
            if (strcmp(currentPtr->visitor.Name, nextPtr->visitor.Name) > 0)
            {
                struct visitData temp = currentPtr->visitor;
                currentPtr->visitor = nextPtr->visitor;
                nextPtr->visitor = temp;
            }

            nextPtr = nextPtr->nextPtr;
        }

        currentPtr = currentPtr->nextPtr;
    }

    // Open the output file
    FILE *fp = fopen(outputFile, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: unable to open output file.\n");
        return;
    }

    // Traverse the linked list and count the number of visitors
    int count = 0;
    currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        currentPtr = currentPtr->nextPtr;
        count++;
    }

    // Write the total number of visitors to the output file
    fprintf(fp, "Total number of visitors: %d\n", count);

    // Traverse the linked list again and write the sorted data to the output file
    currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        fprintf(fp, "%s,%s,%s,%s\n", currentPtr->visitor.SrNo, currentPtr->visitor.ticketNo, currentPtr->visitor.Name, currentPtr->visitor.ID);
        currentPtr = currentPtr->nextPtr;
    }

    // Close the output file
    fclose(fp);

}

int main(void)

{
    struct ticket *headPtr = NULL;
    int count = 0; // Define count as a local variable

    // Display the menu and get the user's choice

    int choice;
    while (1)
    {

        printf("\n\n\n");

        printf("                               ********** WELCOME TO THE THEME PARK BOOKING SYSTEM **********                                 \n\n\n");

        printf("\t\t\t\t\t[1]=> Add Visitor Information\n");
        printf("\n");
        printf("\t\t\t\t\t[2]=> Search for Visitor Information using ticket number\n");
        printf("\n");
        printf("\t\t\t\t\t[3]=> Search for Visitor Information using name\n");
        printf("\n");
        printf("\t\t\t\t\t[4]=> Search for Visitor Information using ID\n");
        printf("\n");
        printf("\t\t\t\t\t[5]=> Delete Visitor Information using ticket number\n");
        printf("\n");
        printf("\t\t\t\t\t[6]=> Delete Visitor Information using name\n");
        printf("\n");
        printf("\t\t\t\t\t[7]=> Delete Visitor Information using ID\n");
        printf("\n");
        printf("\t\t\t\t\t[8]=> View All users that have been added and generate the visitors.txt file\n");
        printf("\n");
        printf("\t\t\t\t\t[9]=> Exit And Print the Output.txt File\n");

        printf("\n");
        printf("\n");

        printf("                                                                                                             \n\n");
        printf("\t\t\tEnter Your Choice:: ");
        scanf("%d", &choice);

        // Perform the selected action

        switch (choice)
        {
            case 1:

            {
                int currentSrNo = 1;
                add_users(&headPtr, &count, &currentSrNo);

                break;
            }

            case 2:

            {
                // Prompt the user to enter the ticket number of the visitor to search for
                char ticketNo[256];
                printf("Enter the ticket number of the visitor to search for: ");
                scanf("%s", ticketNo);

                // Search for the visitor using the ticket number
                search_by_ticketno(headPtr, ticketNo);
                sleep(5); // Pause the program for 5 seconds
                break;
            }

            case 3:

            {
                // Prompt the user to enter the name of the visitor to search for
                char name[256];
                printf("Enter the name of the visitor to search for: ");
                scanf("%s", name);

                // Search for the visitor using the name
                search_user_name(headPtr, name);
                sleep(5); // Pause the program for 5 seconds

                break;
            }

            case 4:

            {
                // Prompt the user to enter the ID of the visitor to search for
                char ID[256];
                printf("Enter the ID of the visitor to search for: ");
                scanf("%s", ID);

                // Search for the visitor using the ID
                search_user_by_ID(headPtr, ID);
                sleep(5); // Pause the program for 5 seconds

                break;

            }

            case 5:

            {
                // Prompt the user to enter the ticket number of the visitor to delete
                char ticketNo[256];
                printf("Enter the ticket number of the visitor to delete: ");
                scanf("%s", ticketNo);

                // Delete the visitor using the ticket number
                delete_visitor_ticket(&headPtr, &count, ticketNo);
                printf("Data Successfully Deleted: ");
                sleep(5);//program loads for 5 secs


                break;

            }

            case 6:

            {
                // Prompt the user to enter the name of the visitor to delete
                char name[256];
                printf("Enter the name of the visitor to delete: ");
                scanf("%s", name);

                // Delete the visitor using the name
                delete_user_by_name(&headPtr, &count, name);
                printf("Data Successfully Deleted: ");
                sleep(5);//program loads for 5 secs


                break;

            }

            case 7:

            {
                // Prompt the user to enter the ID of the visitor to delete
                char ID[256];
                printf("Enter the ID of the visitor to delete: ");
                scanf("%s", ID);

                // Delete the visitor using the ID
                delete_user_by_ID(&headPtr, &count, ID);
                printf("Data Successfully Deleted: ");
                sleep(5);//program loads for 5 secs


                break;

            }

            case 8:

            {
                view_users(headPtr);
                printf("\nVisitors.txt file generated\n");
                sleep(5); //pause the program for 5 seconds

                break;
            }

            case 9:

            {
                generate_txt_file(headPtr, "outputdata.txt");
                printf("Text file generated. Thanks for using my Program\n");


                // Exit the program
                exit(EXIT_SUCCESS);
            }

            default:

                printf("Invalid choice.\n");
                break;

        }

    }

    return 0;

}




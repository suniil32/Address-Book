/**********************************************************************************************************************
Project: Address Book

Description: This project is a basic Address Book Management System developed in C 
that allows users to store, retrieve, and manage contact information efficiently.
 Contacts are stored in a structured format with fields for name, phone number, and email. 
 The program provides functionality to load contact information from a file, view contact information in memory, 
 and save updated contact details back to a file.

Author Name: sunil kumar

Date: 12/11/24
**********************************************************************************************************************/

#include "contact.h"
#include <stdio_ext.h>

// list contact definition
void listContacts(AddressBook *addressBook)
{
    // create a header for list contact
    printf("\n*********************************************************************************\n");
    printf("%-6s%-25s%-25s%-25s\n", "sl.no.", "Name", "Phone", "Email");
    printf("*********************************************************************************\n\n");

    // printf all contact in a list
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d%-25s%-25s%-25s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    printf("\n*********************************************************************************\n");
}

void initialize(AddressBook *addressBook)
{
    FILE *fptr;
    char temp[100];
    fptr = fopen("contact.txt", "r");

    if (fptr == NULL)
    {
        printf("Error: file could not be opened (contact.txt)\n");
        return;
    }
   

    addressBook->contactCount = 0;

    // Read each line from the file
    while (fgets(temp, sizeof(temp), fptr) != NULL)
    {
        // Tokenize the line using strtok
        char *name = strtok(temp, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        // Ensure valid tokens for name, phone, and email
        if (name && phone && email)
        {
            // Prevent writting beyond the array size
            if (addressBook->contactCount < MAX_CONTACTS)
            {
                strncpy(addressBook->contacts[addressBook->contactCount].name, name , sizeof(addressBook->contacts[addressBook->contactCount]).name - 1);
                addressBook->contacts[addressBook->contactCount].name[sizeof(addressBook->contacts[addressBook->contactCount]) -1] = '\0'; // // Null-terminate the string

                strncpy(addressBook->contacts[addressBook->contactCount].phone, phone , sizeof(addressBook->contacts[addressBook->contactCount]).phone - 1);
                addressBook->contacts[addressBook->contactCount].phone[sizeof(addressBook->contacts[addressBook->contactCount]) -1] = '\0'; // // Null-terminate the string

                strncpy(addressBook->contacts[addressBook->contactCount].email, email , sizeof(addressBook->contacts[addressBook->contactCount]).email - 1);
                addressBook->contacts[addressBook->contactCount].email[sizeof(addressBook->contacts[addressBook->contactCount]) -1] = '\0';   // Null-terminate the string

                // Increment contact count after storing contact
                addressBook->contactCount++;
            }
            else
            {
                printf("Address book is full. Cannot add more contacts.\n");
                break; // Stop reading if the address book is full
            }
        }
    }

    fclose(fptr);
}

/*************************************************************************************************************************** */

void createContact(AddressBook *addressBook)
{

    char name[50], phone[20], email[50];

    int validName = 1, validPhone = 1, validEmail = 1;

    printf("\nCreate new contact\n");
    printf("\nEnter full name: ");
    scanf(" %[^\n]%*c", name); // Read full name until newline

    printf("Enter Mobile number: ");
    scanf("%19s", phone); // Read up to 19 characters for phone

    printf("Enter Email ID: ");
    scanf("%49s", email); // read Email

    // validate name should only consiste of  alphabets
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
        {
            validName = 0;
            break;
        }
    }

    // check name should not be available already in the adddressbook
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("\nName already exist\n");
            return;
        }
    }

    // validate phone no. should only number of 10 digits
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!((strlen(phone) == 10) && (strspn(phone, "0123456789") == 10)))
        {
            validPhone = 0;
            break;
        }
    }
    ////check name should not be available already in the adddressbook
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("\nMobile number already exist\n");
            return;
        }
    }

    // validate  email should consista of one @ and one dot (.) dot
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (!((email[i] >= 'A' && email[i] <= 'Z') || (email[i] >= 'a' && email[i] <= 'z') ||
              (email[i] >= '0' && email[i] <= '9') || email[i] == ' ' || email[i] == '.' || email[i] == '@'))
        {

            validEmail = 0;
            break;
        }
    }

    ////check name should not be available already in the adddressbook
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("\nemail already exist\n");
            return;
        }
    }

    // if name phone and contact are valid only the copy it to address book
    if (validName && validPhone && validEmail)
    {
        printf("\nNew Contact Details: %s    %s    %s\n", name, phone, email);

        int contact_Index = addressBook->contactCount;

        strcpy(addressBook->contacts[contact_Index].name, name);
        strcpy(addressBook->contacts[contact_Index].phone, phone);
        strcpy(addressBook->contacts[contact_Index].email, email);

        addressBook->contactCount++; // increase the contact count by adding 1 contact

        printf("\nNew contact added successfully\n press 6 to save contact\n\n");
    }

    else
    {
        printf("\nInvalid credential please do it again\n");
        createContact(addressBook);
    }
}

/*****************************************************************************************************************/

void searchContact(AddressBook *addressBook)
{
    int n, found = 0;
    ;
    char name[50], phone[20], email[50];
    printf("\nSearch contact by\n1.Name\n2.Phone\n3.Email\n");
    printf("\nEnter an option (1 - 3): ");
    scanf("%d", &n);

    switch (n)
    {
    case 1:
        printf("Enter Name : ");
        scanf(" %[^\n]%*c", name);

        // access all the contact
        printf("\n*********************************************************************************\n");
        printf("%-6s%-25s%-25s%-25s\n", "sl.no.", "Name", "Phone", "Email");
        printf("*********************************************************************************\n\n");
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, name) != NULL) // and compair by search contact
            {

                // print that perticular contact
                printf("%-5d%-25s%-25s%-25s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                found = 1;
                // break;
            }
        }
        printf("\n*********************************************************************************\n");
        if (!found)
        {
            printf("\n Contact not found \n");
        }
        break;

    case 2:
        printf("Enter Mobile number : ");
        scanf("%19s", phone);

        printf("\n*********************************************************************************\n");
        printf("%-6s%-25s%-25s%-25s\n", "sl.no.", "Name", "Phone", "Email");
        printf("*********************************************************************************\n\n");

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].phone, phone) != NULL)
            {
                // printf("\nContact found : ");
                printf("%-5d%-25s%-25s%-25s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                found = 1;
                // break;
            }
        }
        printf("\n*********************************************************************************\n");
        if (!found)
        {
            printf("\n******************************* Contact not found *******************************\n");
        }
        break;

    case 3:
        printf("Enter Email Id : ");
        scanf("%49s", email);

        printf("\n*********************************************************************************\n");
        printf("%-6s%-25s%-25s%-25s\n", "sl.no.", "Name", "Phone", "Email");
        printf("*********************************************************************************\n\n");

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].email, email) != NULL)
            {
                // printf("\nContact found : ");
                printf("%-5d%-25s%-25s%-25s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                found = 1;
                break;
            }
        }
        printf("\n*********************************************************************************\n");

        if (!found)
        {
            printf("\nContact not found \n");
        }
        break;

    default:
        printf("\nInvalid input\n");
        break;
    }
}

/*********************************************************************************************************************/

void editContact(AddressBook *addressBook)
{
    int n;
    char name[50], phone[20], email[50];
    printf("\nEdit contact\n\n1.Name\n2.Mobile no.\n3.Email\n");
    printf("\nSelect an option (1 - 3) : ");
    scanf("%d", &n);
    int found = 0;

    printf("Enter name : ");
    scanf(" %[^\n]", name);

    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (strcmp(addressBook->contacts[j].name, name) == 0)
        {
            found = 1;
            switch (n)
            {
            case 1:
                printf("Edit name: ");
                scanf(" %[^\n]", name);

                int validName = 1;

                for (int i = 0; name[i] != '\0'; i++) // validate the name with valid character
                {

                    if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' '))
                    {
                        validName = 0;
                        break;
                    }
                }

                if (validName) // name is valid the copy it to that particular index or contact
                {
                    strcpy(addressBook->contacts[j].name, name);
                    printf("\nName updated successfully\npress 6 to save contact\n");
                }
                else
                {
                    printf("invalid Name\n");
                }
                break;

            case 2:
                printf("Enter new phone number: ");
                scanf("%s", phone);
                // validate phone number and copy that existing number with new
                if ((strlen(phone) == 10) && (strspn(phone, "0123456789") == 10))
                {
                    strcpy(addressBook->contacts[j].phone, phone);
                    printf("update successfully\npress 6 to save contact\n");
                }
                else
                {
                    printf("invalid phone number\n");
                }
                break;

            case 3:
                printf("Enter new Email address: ");
                scanf("%s", email);

                // validate email address
                if (strchr(email, '@') && strchr(email, '.'))
                {
                    strcpy(addressBook->contacts[j].email, email);
                    printf("\nUpdate successfilly\npress 6 to save contact\n");
                }
                else
                {
                    printf("\ninvalid email\n");
                }
                break;

            default:
                printf("\nInvalid number : please select valid number (1 - 3)\n");
                break;
            }
            break;
        }
    }

    if (!found)
    {
        printf("\ncontact not available\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
    char name[50];

    printf("\nEnter a name : ");
    scanf(" %[^\n]", name);
    int found = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0) // search the contact by comparing
        {
            found = 1;

            for (int j = i; j < addressBook->contactCount - 1; j++) // overwrite by shigthing all the contact to left
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }

            addressBook->contactCount--; // decrease the count by one

            printf("\n\nContact deleted successfully!\npress 6 to save contact\n");
            break;
        }
    }

    if (!found)
    {
        printf("\nContact not found\n");
    }
}

// Function to save the contents of AddressBook to "contact.txt"
void saveContacts(AddressBook *addressBook) {
  
    FILE *fptr = fopen("contact.txt", "w");     // Open the file in write mode

    if (fptr == NULL) {
        printf("Error: Could not open file contact.txt for writing.\n");
        return;
    }

    // Write each contact's details to the file in the format: name,phone,email
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n", 
                addressBook->contacts[i].name, 
                addressBook->contacts[i].phone, 
                addressBook->contacts[i].email);
    }

    fclose(fptr);  // Close the file after writing
    printf("Address book saved successfully.");
}
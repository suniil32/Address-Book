#include "contact.h"
// #include "contact.c"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  AddressBook addressBook;

  initialize(&addressBook); // initialize function will call first and copy default contact to contact list

  // create a menu for user
  while (1)
  {
    printf("\n#################################....MENU...##################################\n\n");
    printf("1. Add Contact\n");
    printf("2. Search\n");
    printf("3. Edit\n");
    printf("4. Delete\n");
    printf("5. list\n");
    printf("6. Save\n");
    printf("7. Exit\n\n");
    printf("################################################################################\n\n");

    // read the option
    printf("Please select an option (1 - 7) : ");
    char option;
    scanf(" %c", &option);
    switch (option)
    {
    case '1':
      createContact(&addressBook);
      break;
    case '2':
      searchContact(&addressBook);
      break;
    case '3':
      editContact(&addressBook);
      break;
    case '4':
      deleteContact(&addressBook);
      break;
    case '5':
      listContacts(&addressBook);
      break;
    case '6':
      saveContacts(&addressBook);
      break;
    case '7':
      exit(0);
      break;
    default:
      printf("\nInvalid input : Please select an option (1 - 7) : \n");
      break;
    }
  }
  return 0;
}

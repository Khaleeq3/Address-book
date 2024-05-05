#ifndef MENUS_H
#define MENUS_H
#include <stdio.h>
#include "type.h"

#define MAX_NAME_LENGTH    25
#define MAX_PH_NO_LENGTH   15
#define MAX_EMAIL_LENGTH   30
#define MAX_ADDRESS_LENGTH 256
#define ADDRESS_BOOK_FNAME  "AddressBook.csv"
#define TEMP_ABK_FNAME  "TempAbk.csv"

/* Structure to hold the contact details */
typedef struct _ContactDetails {
    char name[MAX_NAME_LENGTH];

    char ph_number[MAX_PH_NO_LENGTH];
    int is_ph_num_added;

    char email_address[MAX_EMAIL_LENGTH];
    int is_email_added;

    char address[MAX_ADDRESS_LENGTH];
    int is_address_added;

    FILE *fptr_temp_abk;
    
} ContactDetails;

/* Function prototypes to display menus */

Status display_main_menu();

Status display_add_contact_menu();

Status display_add_details_menu();

Status search_contact_menu();

Status modification_menu();

Status edit_phone_number_menu();

Status edit_email_address_menu();

Status edit_address_menu();

#endif
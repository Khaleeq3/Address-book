#ifndef ADD_CONTACT_H
#define ADD_CONTACT_H
#include <stdio.h>
#include "type.h"
#include "menus.h"

/* Function to open files to add contacts */
Status open_files_to_add_contact(ContactDetails *contactDetails);

/* Function to copy a file */
Status copy_src_to_dest_file(char *dest, char *src);

/* Function to add contact */
Status add_contact_details(ContactDetails *contactDetails);

/* Function to check if a contact name is valid or not */
Status is_contact_name_valid(char *name);

/* Function to add further contact details */
Status add_details(ContactDetails *ContactDetails);

/* Function to add phone number */
Status add_phone_number(ContactDetails *contactDetails);

/* Function to add email address */
Status add_email_address(ContactDetails *contactDetails);

/* Function to add address */
Status add_address(ContactDetails *contactDetails);

/* Function to check if the contact name is already exists */
Status is_contact_name_exists(FILE *fptr_abk, char *contact_detail);

#endif
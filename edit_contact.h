#ifndef EDIT_CONTACT_H
#define EDIT_CONTACT_H
#include "type.h"
#include "menus.h"
#include "add_contact.h"
#include "delete_contact.h"
#include "list.h"
#include "edit_contact.h"

/* Function to open the required file to edit */
Status open_files_to_edit(ContactDetails *contactDetails);

/* function to edit contacts details */
Status edit_contact_details(ContactDetails *contactDetails);

/* Function to edit contacts by name */
Status edit_contact_by_name(ContactDetails *contactDetails);

/* Function to edit contact details by phone number */
Status edit_contact_by_phone_number(ContactDetails *contactDetails);

/* Function to edit contact details by email address */
Status edit_contact_by_email_address(ContactDetails *contactDetails);

/* Function to edit contacts by address */
Status edit_contact_by_address(ContactDetails *contactDetails);

/* Function to modify contact details */
Status modify_contact_details(ContactDetails *contactDetails);

/* function to modify contact name */
Status modify_contact_name(ContactDetails *contactDetails);

/* Function to modify contact phone number */
Status modify_phone_number(ContactDetails *contactDetails);

/* Function to modify email address */
Status modify_email_address(ContactDetails *contactDetails);

/* Function to modify address */
Status modify_address(ContactDetails *contactDetails);

#endif
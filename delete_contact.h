#ifndef DELETE_CONTACT_H
#define DELETE_CONTACT_H
#include <stdio.h>
#include "type.h"
#include "menus.h"

/* function to open the files to edit file */
Status open_files_to_edit(ContactDetails *contactDetails);

/* function to delete contact details */
Status delete_contact_details(ContactDetails *contactDetails);

/* function to delete contact by name */
Status delete_contact_by_name(ContactDetails *contactDetails);

/* function to delete a contact */
Status delete_contact(ContactDetails *contactDetails);

/* function to delete contact by phone number */
Status delete_contact_by_phone_number(ContactDetails *contactDetails);

/* function to delete contact by email address */
Status delete_contact_by_email_address(ContactDetails *contactDetails);

/* function to delete contact by address */
Status delete_contact_by_address(ContactDetails *contactDetails);

#endif
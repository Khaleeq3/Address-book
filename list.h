#ifndef LIST_H
#define LIST_H
#include "type.h"

/* Function to open the files to list the contacts */
Status open_files_to_list_contacts(ContactDetails *contactDetails);

/* Function to list all the contacts */
Status list_all_contact_details(ContactDetails *contactDetails);

/* function to search contact details */
Status search_contact_details(ContactDetails *contactDetails);

/* Function to search contacts by names */
Status search_contact_by_name(ContactDetails *contactDetails);

/* Function to search contacts by phone numbers */
Status search_contact_by_phone_number(ContactDetails *contactDetails);

/* Function to search contacts by email address */
Status search_contact_by_email_address(ContactDetails *contactDetails);

/* Function to search contacts by address */
Status search_contact_by_address(ContactDetails *contactDetails);

/* function to read a single contact detail */
Status get_contact_details(ContactDetails *contactDetails);

/* function to display contact details by name */
Status display_contact_details_by_name(ContactDetails *contactDetails, char *search_name);

/* Function to display contact details by phone numebers */
Status display_contact_details_by_phone_number(ContactDetails *contactDetails, char *search_ph_number);

/* Function to display contact details by email address */
Status display_contact_details_by_email_address(ContactDetails *contactDetails, char *search_email_address);

/* Function to display contact details by phone address */
Status display_contact_details_by_address(ContactDetails *contactDetails, char *search_address);

#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "type.h"
#include "menus.h"
#include "add_contact.h"
#include "delete_contact.h"
#include "list.h"
#include "edit_contact.h"

extern int count;
extern int is_saved;

/* function to open the files to edit file */
Status open_files_to_edit(ContactDetails *contactDetails)
{
    contactDetails->fptr_temp_abk = fopen(TEMP_ABK_FNAME, "r+");

    if(contactDetails->fptr_temp_abk == NULL)
    {
        printf("Unable to open %s\n", TEMP_ABK_FNAME);
        return failure;
    }

    return success;
}

/* function to delete contact details */
Status delete_contact_details(ContactDetails *contactDetails)
{
    if(open_files_to_edit(contactDetails) == failure)
    {
        printf("open_files_function failed\n");
        return failure;
    }

    
    while(search_contact_menu() == success)
    {
        char choice;
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("-------------------------------");

        fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);
        switch (choice)
        {
        case 'N':
        case 'n':
            if(delete_contact_by_name(contactDetails) != success)
            {
                puts("delete_contact_by_name function failed");
                return failure;
            }
            break;

        case 'P':
        case 'p':
            if(delete_contact_by_phone_number(contactDetails) != success)
            {
                puts("delete_contact_by_phone_number function failed");
                return failure;
            }
            break;

        case 'E':
        case 'e':
            if(delete_contact_by_email_address(contactDetails) != success)
            {
                puts("delete_contact_by_email_address function failed");
                return failure;
            }
            break;

        case 'A':
        case 'a':
            if(delete_contact_by_address(contactDetails) != success)
            {
                puts("delete_contact_by_address function failed");
                return failure;
            }
            break;

        case 'L':
        case 'l':
            if(list_all_contact_details(contactDetails) == failure)
            {
                puts("list_all_contact_details function failed");
                return 1;
            }
            break;

        case 'X':
        case 'x':
            fclose(contactDetails->fptr_temp_abk);
            return success;
            break;
        
        default:
            puts("-------------------------");
            puts("Invalid Option");
            puts("-------------------------");
            break;
        }
    }
}

/* function to delete contact by name */
Status delete_contact_by_name(ContactDetails *contactDetails)
{
    char search_name[MAX_NAME_LENGTH];
    while(printf("Enter the contact name: "))
    {
        __fpurge(stdin);
        if(scanf("%24[^\n]", search_name) == 0)
        {
            return success;
        }

        if(is_contact_name_valid(search_name) == failure)
        {
            puts("Please enter a valid name: ");
            continue;
        }
        
        if(display_contact_details_by_name(contactDetails, search_name) == failure)
        {
            puts("------------------------------");
            puts("Contact not found");
            puts("------------------------------");
            return success;
        }

        int sl_no, occurance = 0;
        if(count == 1)
        {
            sl_no = 1;
        }
        else
        {
            printf("Choose the serail no. to delete contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to delete this contact [y/n]: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("------------------------------------------");
        if(choice == 'Y' || choice == 'y')
        {
            fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);
            while (get_contact_details(contactDetails) == success)
            {
                if(strstr(contactDetails->name, search_name) != NULL)
                {
                    occurance++;
                    if(sl_no == occurance)
                    {
                        if(delete_contact(contactDetails) == success)
                        {
                            puts("Contact deleted successfully");
                            return success;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }
    }
}

/* function to delete contact by phone number */
Status delete_contact_by_phone_number(ContactDetails *contactDetails)
{
    char search_ph_number[MAX_PH_NO_LENGTH];
    while(printf("Enter the phone number: "))
    {
        __fpurge(stdin);
        if(scanf("%14[0-9]", search_ph_number) == 0)
        {
            return success;
        }

        if(strlen(search_ph_number) != 10)
        {
            puts("Please enter a valid Phone number: ");
            continue;
        }
        
        if(display_contact_details_by_phone_number(contactDetails, search_ph_number) == failure)
        {
            puts("------------------------------");
            puts("Contact not found");
            puts("------------------------------");
            return success;
        }

        int sl_no, occurance = 0;
        if(count == 1)
        {
            sl_no = 1;
        }
        else
        {
            printf("Choose the serail no. to delete contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to delete this contact [y/n]: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("------------------------------------------");
        if(choice == 'Y' || choice == 'y')
        {
            fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);
            while (get_contact_details(contactDetails) == success)
            {
                if(strstr(contactDetails->ph_number, search_ph_number) != NULL)
                {
                    occurance++;
                    if(sl_no == occurance)
                    {
                        if(delete_contact(contactDetails) == success)
                        {
                            puts("Contact deleted successfully");
                            return success;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }
    }
}

/* function to delete contact by email address */
Status delete_contact_by_email_address(ContactDetails *contactDetails)
{
    char search_email_address[MAX_EMAIL_LENGTH];
    while(printf("Enter the email address: "))
    {
        __fpurge(stdin);
        if(scanf("%29[^\n]", search_email_address) == 0)
        {
            return success;
        }

        if(strchr(search_email_address, '@') == NULL || strstr(search_email_address, ".com") == NULL || strchr(search_email_address, ' ') != NULL)
        {
            printf("Please enter a valid email address\n");
            continue;
        }
        
        if(display_contact_details_by_email_address(contactDetails, search_email_address) == failure)
        {
            puts("------------------------------");
            puts("Contact not found");
            puts("------------------------------");
            return success;
        }

        int sl_no, occurance = 0;
        if(count == 1)
        {
            sl_no = 1;
        }
        else
        {
            printf("Choose the serail no. to delete contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to delete this contact [y/n]: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("------------------------------------------");
        if(choice == 'Y' || choice == 'y')
        {
            fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);
            while (get_contact_details(contactDetails) == success)
            {
                if(strstr(contactDetails->email_address, search_email_address) != NULL)
                {
                    occurance++;
                    if(sl_no == occurance)
                    {
                        if(delete_contact(contactDetails) == success)
                        {
                            puts("Contact deleted successfully");
                            return success;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }
    }
}

/* function to delete contact by address */
Status delete_contact_by_address(ContactDetails *contactDetails)
{
    char search_address[MAX_ADDRESS_LENGTH];
    while(printf("Enter the address: "))
    {
        __fpurge(stdin);
        if(scanf("%255[^\n]", search_address) == 0)
        {
            return success;
        }
        
        if(display_contact_details_by_address(contactDetails, search_address) == failure)
        {
            puts("------------------------------");
            puts("Contact not found");
            puts("------------------------------");
            return success;
        }

        int sl_no, occurance = 0;
        if(count == 1)
        {
            sl_no = 1;
        }
        else
        {
            printf("Choose the serail no. to delete contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to delete this contact [y/n]: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("------------------------------------------");
        if(choice == 'Y' || choice == 'y')
        {
            fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);
            while (get_contact_details(contactDetails) == success)
            {
                if(strstr(contactDetails->address, search_address) != NULL)
                {
                    occurance++;
                    if(sl_no == occurance)
                    {
                        if(delete_contact(contactDetails) == success)
                        {
                            puts("Contact deleted successfully");
                            return success;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }
    }
}

/* function to delete a contact */
Status delete_contact(ContactDetails *contactDetails)
{
    int contact_length = strlen(contactDetails->name) + strlen(contactDetails->ph_number) + strlen(contactDetails->email_address) + strlen(contactDetails->address) + 4;
    char *buffer = (char *) malloc(contact_length);
    memset(buffer, 0, contact_length);
    fseek(contactDetails->fptr_temp_abk, -contact_length, SEEK_CUR);
    fwrite(buffer, sizeof(char), contact_length - 1, contactDetails->fptr_temp_abk);
    is_saved = 1;
    free(buffer);
    return success;
}
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
#include "type.h"
#include "menus.h"
#include "add_contact.h"
#include "delete_contact.h"
#include "list.h"
#include "edit_contact.h"

extern int count;

/* function to edit contacts details */
Status edit_contact_details(ContactDetails *contactDetails)
{
    if(open_files_to_edit(contactDetails) == failure)
    {
        puts("Open_files_to_edit function failed");
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
            /* Edit contacts by name */
            if(edit_contact_by_name(contactDetails) != success)
            {
                puts("delete_contact_by_name function failed");
                return failure;
            }
            break;

        case 'P':
        case 'p':
        /* Edit contacts by phone number */
            if(edit_contact_by_phone_number(contactDetails) != success)
            {
                puts("delete_contact_by_phone_number function failed");
                return failure;
            }
            break;

        case 'E':
        case 'e':
        /* Edit contacts by email address */
            if(edit_contact_by_email_address(contactDetails) != success)
            {
                puts("delete_contact_by_email_address function failed");
                return failure;
            }
            break;

        case 'A':
        case 'a':
        /* Edit contacts by address */
            if(edit_contact_by_address(contactDetails) != success)
            {
                puts("delete_contact_by_address function failed");
                return failure;
            }
            break;

        case 'L':
        case 'l':
        /* List all the contacts */
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

/* Function to edit contacts by name */
Status edit_contact_by_name(ContactDetails *contactDetails)
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
            printf("Choose the serail no. to edit contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to edit this contact [y/n]: ");
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
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }

        if(modify_contact_details(contactDetails) == failure)
        {
            puts("modify_contact_details function failed");
            return failure;
        }
        else
        {
            return success;
        }
    }
}

/* Function to edit contact details by phone number */
Status edit_contact_by_phone_number(ContactDetails *contactDetails)
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
            printf("Choose the serail no. to edit contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to edit this contact [y/n]: ");
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
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }

        if(modify_contact_details(contactDetails) == failure)
        {
            puts("modify_contact_details function failed");
            return failure;
        }
        else
        {
            return success;
        }
    }
}

/* Function to edit contact details by email address */
Status edit_contact_by_email_address(ContactDetails *contactDetails)
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
            printf("Choose the serail no. to edit contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to edit this contact [y/n]: ");
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
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }

        if(modify_contact_details(contactDetails) == failure)
        {
            puts("modify_contact_details function failed");
            return failure;
        }
        else
        {
            return success;
        }
    }
}

/* Function to edit contacts by address */
Status edit_contact_by_address(ContactDetails *contactDetails)
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
            printf("Choose the serail no. to edit contact: ");
            scanf("%d", &sl_no);
        }
        
        char choice;
        printf("Do you really want to edit this contact [y/n]: ");
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
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            return success;
        }

        if(modify_contact_details(contactDetails) == failure)
        {
            puts("modify_contact_details function failed");
            return failure;
        }
        else
        {
            return success;
        }
    }
}

/* Function to modify contact details */
Status modify_contact_details(ContactDetails *contactDetails)
{
    while(modification_menu() == success)
    {
        char choice;
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("-------------------------------");
        switch (choice)
        {
        case 'C':
        case 'c':
            if(modify_contact_name(contactDetails) != success)
            {
                puts("modify_contact_function failed");
                return failure;
            }
            break;

        case 'P':
        case 'p':
            if(modify_phone_number(contactDetails) != success)
            {
                puts("modify_phone_number function failed");
                return failure;
            }
            break;

        case 'E':
        case 'e':
            if(modify_email_address(contactDetails) != success)
            {
                puts("modify_email_address function failed");
                return failure;
            }
            break;
        
        case 'A':
        case 'a':
            if(modify_address(contactDetails) != success)
            {
                puts("modify_address function failed");
                return failure;
            }
            break;

        case 'X':
        case 'x':
            fseek(contactDetails->fptr_temp_abk, 0, SEEK_END);
            fprintf(contactDetails->fptr_temp_abk, "%s,", contactDetails->name);
            fprintf(contactDetails->fptr_temp_abk, "%s,", contactDetails->ph_number);
            fprintf(contactDetails->fptr_temp_abk, "%s,", contactDetails->email_address);
            fprintf(contactDetails->fptr_temp_abk, "%s\n", contactDetails->address);
            return success;
            break;

        default:
            puts("--------------------------------");
            puts("Invalid Option");
            puts("--------------------------------");
            break;
        }
    }
}

/* function to modify contact name */
Status modify_contact_name(ContactDetails *contactDetails)
{
    while(printf("Enter the new contact name: "))
    {
        __fpurge(stdin);
        if(scanf("%24[^\n]", contactDetails->name) == 0)
        {
            puts("----------------------------");
            puts("Name cannot be empty");
            puts("----------------------------");
            return success;
        }
        else if(is_contact_name_valid(contactDetails->name) == failure)
        {
            puts("Please enter a valid name: ");
            continue;
        }
        else
        {
            puts("---------------------------------");
            puts("Contact name modified successfully");
            puts("---------------------------------");
            return success;
        }
    }
}

/* Function to modify contact phone number */
Status modify_phone_number(ContactDetails *contactDetails)
{
    char choice;
    while (edit_phone_number_menu() == success)
    {
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("-------------------------------");

        switch (choice)
        {
        case 'M':
        case 'm':
            char ph_number[MAX_PH_NO_LENGTH];
            while(printf("Enter new phone number: "))
            {
                __fpurge(stdin);
                if(scanf("%14[0-9]", ph_number) == 0)
                {
                    break;
                }
                else if(strlen(ph_number) != 10)
                {
                    puts("--------------------------------------------");
                    puts("Please enter a 10 digit valid phone number");
                    puts("--------------------------------------------");
                    continue;
                }
                else
                {
                    strcpy(contactDetails->ph_number, ph_number);
                    puts("--------------------------------------------");
                    puts("Phone number modified successfully");
                    puts("--------------------------------------------");
                    break;
                }
            }
            
            break;

        case 'D':
        case 'd':
            *contactDetails->ph_number = '\0';
            puts("--------------------------------------------");
            puts("Phone number deleted successfully");
            puts("--------------------------------------------");
            break;

        case 'X':
        case 'x':
            return success;
            break;
        
        default:
            puts("--------------------------------------------");
            puts("Invalid Option");
            puts("--------------------------------------------");
            break;
        }
    }
}

/* Function to modify email address */
Status modify_email_address(ContactDetails *contactDetails)
{
    char choice;
    while (edit_email_address_menu() == success)
    {
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("----------------------------------");

        switch (choice)
        {
        case 'M':
        case 'm':
            char email_address[MAX_EMAIL_LENGTH];
            while (printf("Enter new email address: "))
            {
                __fpurge(stdin);
                if(scanf("%29[^\n]", email_address) == 0)
                {
                    break;
                }
                else if(strchr(email_address, '@') == NULL || strstr(email_address, ".com") == NULL || strchr(email_address, ' ') != NULL)
                {
                    puts("--------------------------------------------");
                    printf("Please enter a valid email address\n");
                    puts("--------------------------------------------");
                    continue;
                }
                else
                {
                    strcpy(contactDetails->email_address, email_address);
                    puts("--------------------------------------------");
                    puts("Email address modified successfully");
                    puts("--------------------------------------------");
                    break;
                }
            }
            
            break;

        case 'D':
        case 'd':
            *contactDetails->email_address = '\0';
            puts("--------------------------------------------");
            puts("Email address deleted successfully");
            puts("--------------------------------------------");
            break;

        case 'X':
        case 'x':
            return success;
            break;
        
        default:
            puts("--------------------------------------------");
            puts("Invalid Option");
            puts("--------------------------------------------");
            break;
        }
    }
    
}

/* Function to modify address */
Status modify_address(ContactDetails *contactDetails)
{
    char choice;
    while (edit_address_menu() == success)
    {
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("----------------------------");

        switch (choice)
        {
        case 'M':
        case 'm':
            char address[MAX_ADDRESS_LENGTH];
            while (printf("Enter new address: "))
            {
                __fpurge(stdin);
                if(scanf("%255[^\n]", address) == 0)
                {
                    break;
                }
                else
                {
                    strcpy(contactDetails->address, address);
                    puts("--------------------------------------------");
                    puts("Address modified successfully");
                    puts("--------------------------------------------");
                    break;
                }
            }
            break;
        
        case 'D':
        case 'd':
            *contactDetails->address = '\0';
            puts("--------------------------------------------");
            puts("Address deleted successfully");
            puts("--------------------------------------------");
            break;

        case 'X':
        case 'x':
            return success;
            break;

        default:
            puts("------------------------------------");
            puts("Invalid Option");
            puts("------------------------------------");
            break;
        }
    }
}
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include "type.h"
#include "menus.h"
#include "add_contact.h"
#include "delete_contact.h"
#include "list.h"
#include "edit_contact.h"

int count;

/* Function to open the files to list the contacts */
Status open_files_to_list_contacts(ContactDetails *contactDetails)
{
    contactDetails->fptr_temp_abk = fopen(TEMP_ABK_FNAME, "r");

    if(contactDetails->fptr_temp_abk == NULL)
    {
        printf("Unable to open %s\n", TEMP_ABK_FNAME);
        return failure;
    }
    
    return success;
}

/* Function to list all the contacts */
Status list_all_contact_details(ContactDetails *contactDetails)
{
    
    fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);
    puts("--------------------------------------------------------------------------------------------");
    printf("%-7s %-20s %-20s %-25s %s\n","SL.No", "Name", "Phone Number", "email address", "Address");
    puts("--------------------------------------------------------------------------------------------");

    int count = 0;

    while (get_contact_details(contactDetails) == success)
    {
        if(*contactDetails->name != '\0')
        {
            printf("%-7d %-20s %-20s %-25s %s\n", ++count, contactDetails->name, contactDetails->ph_number, contactDetails->email_address, contactDetails->address);
        }
    }
    puts("--------------------------------------------------------------------------------------------");

    return success;
}

/* function to read a single contact detail */
Status get_contact_details(ContactDetails *contactDetails)
{
    char ch;
    *contactDetails->name = '\0';
    *contactDetails->ph_number = '\0';
    *contactDetails->email_address = '\0';
    *contactDetails->address = '\0';

    if((ch = getc(contactDetails->fptr_temp_abk)) == EOF)
    {
        return failure;
    }
    else if(ch == '\0')
    {
        while(getc(contactDetails->fptr_temp_abk) != '\n');
        return success;
    }
    else
    {
        fseek(contactDetails->fptr_temp_abk, -1, SEEK_CUR);

        if(fscanf(contactDetails->fptr_temp_abk, "%[^,]", contactDetails->name) != EOF)
        {
            getc(contactDetails->fptr_temp_abk);    // get ','
            fscanf(contactDetails->fptr_temp_abk, "%[^,]", contactDetails->ph_number);

            getc(contactDetails->fptr_temp_abk);    // get ','
            fscanf(contactDetails->fptr_temp_abk, "%[^,]", contactDetails->email_address);

            getc(contactDetails->fptr_temp_abk);    // get ','
            fscanf(contactDetails->fptr_temp_abk, "%[^\n]", contactDetails->address);
            getc(contactDetails->fptr_temp_abk);   // get '\n'

            return success;
        }
        else
        {
            return failure;
        }
    }
}

/* function to search contact details */
Status search_contact_details(ContactDetails *contactDetails)
{
    char choice;
    while (search_contact_menu() == success)
    {
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("-------------------------------");

        switch (choice)
        {
        case 'N':
        case 'n':
            if(search_contact_by_name(contactDetails) != success)
            {
                puts("search_contact_by_name function failed");
                return failure;
            }
            break;

        case 'P':
        case 'p':
            if(search_contact_by_phone_number(contactDetails) != success)
            {
                puts("search_contact_by_name function failed");
                return failure;
            }
            break;

        case 'E':
        case 'e':
            if(search_contact_by_email_address(contactDetails) != success)
            {
                puts("search_contact_by_name function failed");
                return failure;
            }
            break;

        case 'A':
        case 'a':
            if(search_contact_by_address(contactDetails) != success)
            {
                puts("search_contact_by_name function failed");
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
            return success;
            break;
        
        default:
            puts("--------------------------");
            puts("Invalid choice");
            puts("--------------------------");
            break;
        }
    }
    
}

/* Function to search contacts by names */
Status search_contact_by_name(ContactDetails *contactDetails)
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
        }

        return success;
    }
}

/* Function to search contacts by phone numbers */
Status search_contact_by_phone_number(ContactDetails *contactDetails)
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
            puts("Please enter a valid phone number: ");
            continue;
        }

        if(display_contact_details_by_phone_number(contactDetails, search_ph_number) == failure)
        {
            puts("------------------------------");
            puts("Phone number not found");
            puts("------------------------------");
        }

        return success;
    }
}

/* Function to search contacts by email address */
Status search_contact_by_email_address(ContactDetails *contactDetails)
{
    char search_email_address[MAX_EMAIL_LENGTH];
    while(printf("Enter the an email address: "))
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
            puts("email address not found");
            puts("------------------------------");
        }

        return success;
    }
}

/* Function to search contacts by address */
Status search_contact_by_address(ContactDetails *contactDetails)
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
            puts("Address not found");
            puts("------------------------------");
        }

        return success;
    }
}

/* function to display contact details by name */
Status display_contact_details_by_name(ContactDetails *contactDetails, char *search_name)
{
    fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);

    int one_time = 1;
    count = 0;
    while (get_contact_details(contactDetails) == success)
    {
        if(strstr(contactDetails->name, search_name) != NULL)
        {
            if(one_time == 1)
            {
                puts("--------------------------------------------------------------------------------------------");
                printf("%-7s %-20s %-20s %-25s %s\n", "SL.No", "Name", "Phone Number", "email address", "Address");
                puts("--------------------------------------------------------------------------------------------");
                one_time = 0;
            }
            printf("%-7d %-20s %-20s %-25s %s\n", ++count, contactDetails->name, contactDetails->ph_number, contactDetails->email_address, contactDetails->address);
        }
    }
    
    if(one_time == 1)
    {
        return failure;
    }
    else
    {
        puts("--------------------------------------------------------------------------------------------");
        return success;
    }
}

/* function to display contact details by phone number */
Status display_contact_details_by_phone_number(ContactDetails *contactDetails, char *search_ph_number)
{
    fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);

    int one_time = 1;
    count = 0;
    while (get_contact_details(contactDetails) == success)
    {
        if(strcmp(contactDetails->ph_number, search_ph_number) == 0)
        {
            if(one_time == 1)
            {
                puts("--------------------------------------------------------------------------------------------");
                printf("%-7s %-20s %-20s %-25s %s\n", "SL.No", "Name", "Phone Number", "email address", "Address");
                puts("--------------------------------------------------------------------------------------------");
                one_time = 0;
            }
            printf("%-7d %-20s %-20s %-25s %s\n", ++count, contactDetails->name, contactDetails->ph_number, contactDetails->email_address, contactDetails->address);
        }
    }
    
    if(one_time == 1)
    {
        return failure;
    }
    else
    {
        puts("--------------------------------------------------------------------------------------------");
        return success;
    }
}

/* function to display contact details by email address */
Status display_contact_details_by_email_address(ContactDetails *contactDetails, char *search_email_address)
{
    fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);

    int one_time = 1;
    count = 0;
    while (get_contact_details(contactDetails) == success)
    {
        if(strstr(contactDetails->email_address, search_email_address) != NULL)
        {
            if(one_time == 1)
            {
                puts("--------------------------------------------------------------------------------------------");
                printf("%-7s %-20s %-20s %-25s %s\n","SL.No", "Name", "Phone Number", "email address", "Address");
                puts("--------------------------------------------------------------------------------------------");
                one_time = 0;
            }
            printf("%-7d %-20s %-20s %-25s %s\n",++count, contactDetails->name, contactDetails->ph_number, contactDetails->email_address, contactDetails->address);
        }
    }
    
    if(one_time == 1)
    {
        return failure;
    }
    else
    {
        puts("--------------------------------------------------------------------------------------------");
        return success;
    }
}

/* function to display contact details by address */
Status display_contact_details_by_address(ContactDetails *contactDetails, char *search_address)
{
    fseek(contactDetails->fptr_temp_abk, 0, SEEK_SET);

    int one_time = 1;
    count = 0;
    while (get_contact_details(contactDetails) == success)
    {
        if(strstr(contactDetails->address, search_address) != NULL)
        {
            if(one_time == 1)
            {
                puts("--------------------------------------------------------------------------------------------");
                printf("%-7s %-20s %-20s %-25s %s\n","SL.No", "Name", "Phone Number", "email address", "Address");
                puts("--------------------------------------------------------------------------------------------");
                one_time = 0;
            }
            printf("%-7d %-20s %-20s %-25s %s\n",++count, contactDetails->name, contactDetails->ph_number, contactDetails->email_address, contactDetails->address);
        }
    }
    
    if(one_time == 1)
    {
        return failure;
    }
    else
    {
        puts("--------------------------------------------------------------------------------------------");
        return success;
    }
}
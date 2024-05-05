#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio_ext.h>
#include "type.h"
#include "menus.h"
#include "add_contact.h"
#include "delete_contact.h"
#include "list.h"
#include "edit_contact.h"

extern int is_saved; 

/* Function to open files to add contacts */
Status open_files_to_add_contact(ContactDetails *contactDetails)
{
    contactDetails->fptr_temp_abk = fopen(TEMP_ABK_FNAME, "a+");

    if(contactDetails->fptr_temp_abk == NULL)
    {
        perror("fopen");
        printf("Unabel to open %s\n", TEMP_ABK_FNAME);
        return failure;
    }

    return success;
}

/* Function to add contact */
Status add_contact_details(ContactDetails *contactDetails)
{
    if(open_files_to_add_contact(contactDetails) == failure)
    {
        printf("ERROR: open_file_to_add_contact function is failed\n");
        return failure;
    }
    
    while (1)
    {
        puts("-------------------------------");
        printf("Enter the contact name*: ");
        __fpurge(stdin);
        if(scanf("%24[^\n]", contactDetails->name) == 0)
        {
            puts("Contact name Cannot be empty");
            fclose(contactDetails->fptr_temp_abk);
            return success;
        }

        if(is_contact_name_valid(contactDetails->name) == failure)
        {
            puts("--------------------------------------------");
            puts("Enter a Valid name (Only alphabets are allowed)");
            puts("Ex: \"Tingu\"");
            puts("----------------------------");
            continue;
        }
        

        if(is_contact_name_exists(contactDetails->fptr_temp_abk, contactDetails->name) == exists)
        {
            puts("------------------------------------------");
            printf("ERROR: Contact name already exists\n");
            continue;
        }
        else
        {
            fprintf(contactDetails->fptr_temp_abk, "%s,", contactDetails->name);
            is_saved = 1;
            break;
        }
    }
    

    *contactDetails->ph_number = '\0';
    contactDetails->is_ph_num_added = 0;
    
    *contactDetails->email_address = '\0';
    contactDetails->is_email_added = 0;
    
    *contactDetails->address = '\0';
    contactDetails->is_address_added = 0;

    char choice;
    
    while(display_add_contact_menu() == success)
    {
        puts("-------------------------------");
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        switch (choice)
        {
        case 'A':
        case 'a':
            if(add_details(contactDetails) == failure)
            {
                printf("add_details function failed\n");
                return failure;
            }
            break;
        case 'X': 
        case 'x':
            fprintf(contactDetails->fptr_temp_abk, "%s,", contactDetails->ph_number);
            fprintf(contactDetails->fptr_temp_abk, "%s,", contactDetails->email_address);
            fprintf(contactDetails->fptr_temp_abk, "%s\n", contactDetails->address);
            fclose(contactDetails->fptr_temp_abk);
            return success;
            break;
        default:
            puts("-------------------------------");
            puts("ERROR: Invalid option");
            break;
        }
    }
    
}

/* Function to check if a contact name is valid or not */
Status is_contact_name_valid(char *name)
{
    while (*name)
    {
        if(isalpha(*name) == 0 && *name != ' ')
        {
            return failure;
        }
        name++;
    }
    return success;
}

/* Function to add further contact details */
Status add_details(ContactDetails *contactDetails)
{
    char choice;
    
    while(display_add_details_menu() == success)
    {
        puts("-------------------------------");
        printf("Choose an option: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        puts("-------------------------------");
        switch (choice)
        {
        case 'P':
        case 'p':
            if(add_phone_number(contactDetails) != success)
            {
                puts("add_phone_number function failed\n");
                return failure;
            }
            break;
        case 'E':
        case 'e':
            if(add_email_address(contactDetails) != success)
            {
                puts("add_email_address function failed\n");
                return failure;
            }
            break;
        
        case 'A':
        case 'a':
            if(add_address(contactDetails) != success)
            {
                puts("add_address function failed\n");
                return failure;
            }
            break;
        case 'X':
        case 'x':
            return success;
        default:
            printf("Inavlid Input\n");
            break;
        }
    }
}

/* Function to add phone number */
Status add_phone_number(ContactDetails *contactDetails)
{
    if(contactDetails->is_ph_num_added != 0)
    {
        char choice;
        printf("ERROR: Phone number is already added, Do you want to modify? [y/n]: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        if(choice != 'Y' && choice != 'y')
        {
            return success;
        }
    }
    printf("Enter phone number: ");
    __fpurge(stdin);
    scanf("%14[0-9]", contactDetails->ph_number);
    if(strlen(contactDetails->ph_number) != 10)
    {
        puts("--------------------------------------------");
        puts("Please enter a 10 digit valid phone number");
        *contactDetails->ph_number = '\0';
        return success;
    }
    else
    {
        contactDetails->is_ph_num_added = 1;
    }

    return success;
}

/* Function to add email address */
Status add_email_address(ContactDetails *contactDetails)
{
    if(contactDetails->is_email_added != 0)
    {
        char choice;
        printf("ERROR: email id is already added, Do you want to modify? [y/n]: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        if(choice != 'Y' && choice != 'y')
        {
            return success;
        }
    }
    printf("Enter email id: ");
    __fpurge(stdin);
    if(scanf("%29[^\n]", contactDetails->email_address) == 0)
    {
        return success;
    }
    else if(strchr(contactDetails->email_address, '@') == NULL || strstr(contactDetails->email_address, ".com") == NULL || strchr(contactDetails->email_address, ' ') != NULL)
    {
        puts("--------------------------------------------");
        printf("Please enter a valid email address\n");
        *contactDetails->email_address = '\0';
        return success;
    }
    else
    {
        contactDetails->is_email_added = 1;
    }

    return success;
}

/* Function to add address */
Status add_address(ContactDetails *contactDetails)
{
    if(contactDetails->is_address_added != 0)
    {
        char choice;
        printf("ERROR: Address is already entered, Do you want to modify[y/n]: ");
        __fpurge(stdin);
        scanf("%c", &choice);
        if(choice != 'Y' && choice != 'y')
        {
            return success;
        }
    }

    printf("Enter Address: ");
    __fpurge(stdin);
    scanf("%255[^\n]", contactDetails->address);
    contactDetails->is_address_added = 1;

    return success;
}

/* Function to copy a file */
Status copy_src_to_dest_file(char *dest, char *src)
{
    char ch;
    FILE *fptr_dest, *fptr_src;
    char line[1024];

    if((fptr_dest = fopen(dest, "w")) == NULL)
    {
        printf("Unable to open %s\n", dest);
        return failure;
    }

    if((fptr_src = fopen(src, "r")) == NULL)
    {
        printf("Unable to open %s\n", src);
        return failure;
    }

    while (fread(&ch, sizeof(char), 1, fptr_src) == 1)
    {
        if(ch == '\0')
        {
            while((ch = getc(fptr_src)) != '\n');
            continue;
        }
        fwrite(&ch, sizeof(char), 1, fptr_dest);
    }

    fclose(fptr_dest);
    fclose(fptr_src);
    return success;
}

/* Function to check if the contact name is already exists */
Status is_contact_name_exists(FILE *fptr_temp_abk, char *search_name)
{
    char contact_name[MAX_NAME_LENGTH];
    fseek(fptr_temp_abk, 0, SEEK_SET);
    char ch;
    while((ch = getc(fptr_temp_abk)) != EOF)
    {
        if(ch == '\0')
        {
            while(getc(fptr_temp_abk) != '\n');
            continue;
        }
        else
        {
            fseek(fptr_temp_abk, -1, SEEK_CUR);

            fscanf(fptr_temp_abk, "%24[^,]", contact_name);
            while(getc(fptr_temp_abk) != '\n');     // Skip a line

            if(strcmp(contact_name, search_name) == 0)
            {
                return exists;
            }
        }
    }

    return not_exists;
}
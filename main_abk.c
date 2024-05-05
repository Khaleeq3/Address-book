#include <stdio.h>
#include <stdio_ext.h>
#include "type.h"
#include "menus.h"
#include "add_contact.h"
#include "delete_contact.h"
#include "list.h"
#include "edit_contact.h"


int is_saved = 0;   // low -> saved , high -> unsaved

int main()
{

    ContactDetails contactDetails;

    // copy source file to temp file
    if(copy_src_to_dest_file(TEMP_ABK_FNAME, ADDRESS_BOOK_FNAME) == failure)
    {
        printf("copy_src_to_dest_file function failed\n");
        return failure;
    }

    char main_manu_choice;
    while (display_main_menu() == success)
    {   
        printf("Select an option: ");
        __fpurge(stdin);
        scanf("%c", &main_manu_choice);
        switch (main_manu_choice)
        {
        case 'A':
        case 'a':
        /* Add new contact details */
            if(add_contact_details(&contactDetails) == failure)
            {
                printf("add_contact_details function failed\n");
                return 1;
            }
            break;

        case 'E':
        case 'e':
        /* Edit contact details */
            if(edit_contact_details(&contactDetails) == failure)
            {
                puts("edit_contact_details function failed");
                return 1;
            }
            break;

        case 'S':
        case 's':
        /* Search contact details */
            if(open_files_to_list_contacts(&contactDetails) == failure)
            {
                puts("open_files_to_list_contact function failed\n");
                return failure;
            }
            if(search_contact_details(&contactDetails) == failure)
            {
                puts("search_contact_details function failed");
                return 1;
            }
            fclose(contactDetails.fptr_temp_abk);
            break;

        case 'L':
        case 'l':
        /* List contact details */
            if(open_files_to_list_contacts(&contactDetails) == failure)
            {
                puts("open_files_to_list_contact function failed\n");
                return failure;
            }
            if(list_all_contact_details(&contactDetails) == failure)
            {
                puts("list_all_contact_details function failed");
                return 1;
            }
            fclose(contactDetails.fptr_temp_abk);
            break;

        case 'D':
        case 'd':
        /* Delete contact details */
            if(delete_contact_details(&contactDetails) == failure)
            {
                puts("delete_contact_details function failed");
                return 1;
            }
            break;

        case 'V':
        case 'v':
        /* copy modified temp to source file (Save changes)*/
            if(copy_src_to_dest_file(ADDRESS_BOOK_FNAME, TEMP_ABK_FNAME) == failure)
            {
                printf("copy_src_to_dest_file function failed\n");
                return 1;
            }
            else
            {
                is_saved = 0;
                puts("----------------------------");
                puts("Changes Saved");
            }
            break;

        case 'Z':
        case 'z':
        /* copy source file to modified temp file (Undo changes)*/
            if(copy_src_to_dest_file(TEMP_ABK_FNAME, ADDRESS_BOOK_FNAME) == failure)
            {
                printf("copy_src_to_dest_file function failed\n");
                return 1;
            }
            is_saved = 0;
            puts("------------------------------");
            puts("Changes discarded");
            puts("------------------------------");
            break;
        case 'X':
        case 'x':
        /* Exit from program */
            if(is_saved == 1)
            {
                char choice;
                printf("You have some unsaved changes, Do you want to save before exit [y/n]: ");
                __fpurge(stdin);
                scanf("%c", &choice);
                if(choice == 'Y' || choice == 'y')
                {
                    if(copy_src_to_dest_file(ADDRESS_BOOK_FNAME, TEMP_ABK_FNAME) == failure)
                    {
                        printf("copy_src_to_dest_file function failed\n");
                        return 1;
                    }
                    else
                    {
                        is_saved = 0;
                        puts("--------------------------");
                        puts("Changes Saved");
                    }
                }
            }
            puts("-------------------------------");
            printf("Exiting.........\n");
            remove(TEMP_ABK_FNAME);
            return 0;
            break;
        default:
            puts("-------------------------------");
            printf("Invalid choice\n");
            break;
        }
    }
}
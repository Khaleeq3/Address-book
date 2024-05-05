#include <stdio.h>
#include "menus.h"
#include "type.h"

Status display_main_menu()
{
    puts("-------------------------------");
    puts("A -> Add Contact");
    puts("E -> Edit Contact");
    puts("S -> Search Contact");
    puts("L -> List all Contacts");
    puts("D -> Delete Contact");
    puts("V -> Save Contact Information");
    puts("Z -> Discard Changes");
    puts("X -> Exit Application");
    puts("-------------------------------");

    return success;
}

Status display_add_contact_menu()
{
    puts("-------------------------------");
    puts("A -> Add Details");
    puts("X -> Exit to main menu");
    puts("-------------------------------");

    return success;
}

Status display_add_details_menu()
{
    puts("-------------------------------");
    puts("P -> Add Phone number");
    puts("E -> Add Email address");
    puts("A -> Add Address");
    puts("X -> Exit to add contact menu");
    puts("-------------------------------");

    return success;
}

Status search_contact_menu()
{
    puts("-------------------------------");
    puts("N -> Search by name");
    puts("P -> Search by phone number");
    puts("E -> Search by email address");
    puts("A -> Search by Address");
    puts("L -> List all the contacts");
    puts("X -> Exit to main menu");
    puts("-------------------------------");

    return success;
}

Status modification_menu()
{
    puts("-------------------------------");
    puts("C -> Modify contact name");
    puts("P -> Modify or Delete phone number");
    puts("E -> Modify or Delete email address");
    puts("A -> Modify or Delete address");
    puts("X -> Exit to edit contact menu");
    puts("-------------------------------");

    return success;
}

Status edit_phone_number_menu()
{
    puts("-------------------------------");
    puts("M -> Modify phone number");
    puts("D -> Delete phone number");
    puts("X -> Exit to modification menu");
    puts("-------------------------------");

    return success;
}

Status edit_email_address_menu()
{
    puts("-------------------------------");
    puts("M -> Modify email address");
    puts("D -> Delete email address");
    puts("X -> Exit to modification menu");
    puts("-------------------------------");

    return success;
}

Status edit_address_menu()
{
    puts("-------------------------------");
    puts("M -> Modify address");
    puts("D -> Delete address");
    puts("X -> Exit to modification menu");
    puts("-------------------------------");

    return success;
}
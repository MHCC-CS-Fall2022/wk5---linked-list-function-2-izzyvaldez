/*
 wk5_Linked_List_Functions_2_ivaldez.cxx

 Summary:        Demonstrate manipulation of a linear linked list.
 Specifications: Program will prompt the user to enter numbers until they enter -1 to stop.
                 Program will then test 4 functions that manipulate the linked list.
 Test cases:     Positive integers

 Author:         Isaias Valdez
 Created:        October 30, 2022
 Summary of Modifications:
 */

#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include "bag3.h"       // With Item defined as an int
using namespace std;
using namespace main_savitch_5;

// PROTOTYPES for functions used by this demonstration program:
void get_ages(bag& ages);
// Postcondition: The user has been prompted to type in the ages of family
// members. These ages have been read and placed in the ages bag, stopping
// when the user types a negative number.

void check_ages(bag& ages);
// Postcondition: The user has been prompted to type in the ages of family
// members once again. Each age is removed from the ages bag when it is typed,
// stopping when the bag is empty.


int main( )
{
    bag ages;

    cout << "\t\tLINKED LIST FUNCTIONS 2\n\n";
    cout << "This program will test 4 functions: "
         << "copy_first_to_last(), sum_of_all_nodes(),\nremove_last_node, "
         << "remove_duplicate_values().\n\n";
    get_ages(ages);
    cout << "Here are the results:\n";
    ages.printList();
    cout << "Testing the copy_first_to_last() function...\n";
    ages.copy_first_to_last(ages);
    ages.printList();
    cout << "Testing sum_of_all_nodes() function..." << endl;
    ages.sum_of_all_nodes();
    ages.printList();
    cout << "Testing remove_last_node() function..." << endl;
    ages.remove_last_node();
    ages.printList();
    cout << "Testing the remove_duplicate_values() function...\n";
    ages.sort_list();
    ages.remove_duplicate_values();
    ages.printList();
   // check_ages(ages);
    cout << "May your family live long and prosper." << endl;
    return EXIT_SUCCESS;
}


void get_ages(bag& ages)
{
    int user_input; // An age from the user's family

    cout << "Type the ages in your family. ";
    cout << "Type a negative number when you are done:" << endl;
    cin >> user_input;
    while (user_input >= 0)
    {
        ages.insert(user_input);
        cin >> user_input;
    }
}

void check_ages(bag& ages)
{
    int user_input; // An age from the user's family

    cout << "Type those ages again. Press return after each age:" << endl;
    while (ages.size( ) > 0)
    {
        cin >> user_input;
        if (ages.erase_one(user_input))
            cout << "Yes, I've got that age and have removed it." << endl;
        else
            cout << "No, that age does not occur!" << endl;
    }
}

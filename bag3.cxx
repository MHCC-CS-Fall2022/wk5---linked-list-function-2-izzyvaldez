// FILE: bag3.cxx
// CLASS implemented: bag (see bag3.h for documentation)
// INVARIANT for the bag ADT:
//   1. The items in the bag are stored on a linked list;
//   2. The head pointer of the list is stored in the member variable head_ptr;
//   3. The total number of items in the list is stored in the member variable
//      many_nodes.

#include <cassert>  // Provides assert
#include <cstdlib>  // Provides NULL, rand, size_t
#include "node1.h"  // Provides node and the linked list functions
#include "bag3.h"
#include <iostream>
using namespace std;

namespace main_savitch_5
{

    bag::bag( )
    // Library facilities used: cstdlib
    {
	head_ptr = NULL;
	many_nodes = 0;
    }

    bag::bag(const bag& source)
    // Library facilities used: node1.h
    {
        node *tail_ptr;  // Needed for argument of list_copy

        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
    }

    bag::~bag( )
    // Library facilities used: node1.h
    {
        list_clear(head_ptr);
        many_nodes = 0;
    }

    bag::size_type bag::count(const value_type& target) const
    // Library facilities used: cstdlib, node1.h
    {
	size_type answer;
	const node *cursor; // Use const node* since we don't change the nodes.

	answer = 0;
	cursor = list_search(head_ptr, target);
	while (cursor != NULL)
	{
	    // Each time that cursor is not NULL, we have another occurrence of
	    // target, so we add one to answer, and move cursor to the next
	    // occurrence of the target.
	    ++answer;
	    cursor = cursor->link( );
	    cursor = list_search(cursor, target);
	}
	return answer;
    }

    bag::size_type bag::erase(const value_type& target)
    // Library facilities used: cstdlib, node1.h
    {
        size_type answer = 0;
        node *target_ptr;

        target_ptr = list_search(head_ptr, target);
        while (target_ptr != NULL)
        {
            // Each time that target_ptr is not NULL, we have another occurrence
	    // of target. We remove this target using the same technique that
	    // was used in erase_one.
            target_ptr->set_data( head_ptr->data( ) );
            target_ptr = target_ptr->link( );
            target_ptr = list_search(target_ptr, target);
            list_head_remove(head_ptr);
	    --many_nodes;
            ++answer;
        }
        return answer;
    }

    bool bag::erase_one(const value_type& target)
    // Library facilities used: cstdlib, node1.h
    {
	node *target_ptr;

	target_ptr = list_search(head_ptr, target);
	if (target_ptr == NULL)
	    return false; // target isn't in the bag, so no work to do
	target_ptr->set_data( head_ptr->data( ) );
	list_head_remove(head_ptr);
	--many_nodes;
	return true;
    }

    bag::value_type bag::grab( ) const
    // Library facilities used: cassert, cstdlib, node1.h
    {
	size_type i;
	const node *cursor; // Use const node* since we don't change the nodes.

	assert(size( ) > 0);
	i = (rand( ) % size( )) + 1;
	cursor = list_locate(head_ptr, i);
	return cursor->data( );
    }

    void bag::insert(const value_type& entry)
    // Library facilities used: node1.h
    {
	list_head_insert(head_ptr, entry);
	++many_nodes;
    }

    void bag::operator +=(const bag& addend)
    // Library facilities used: cstdlib, node1.h
    {
	node *copy_head_ptr;
	node *copy_tail_ptr;

	if (addend.many_nodes > 0)
	{
	    list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);
	    copy_tail_ptr->set_link( head_ptr );
	    head_ptr = copy_head_ptr;
	    many_nodes += addend.many_nodes;
	}
    }

    void bag::operator =(const bag& source)
    // Library facilities used: node1.h
    {
	node *tail_ptr; // Needed for argument to list_copy

	if (this == &source)
            return;

	list_clear(head_ptr);
	many_nodes = 0;
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
    }

    bag operator +(const bag& b1, const bag& b2)
    {
	bag answer;

	answer += b1;
	answer += b2;
	return answer;
    }

    //Copies the value of the head pointer to tail_ptr, creates a new node at the end of the list and copies the value from the head pointer
    void bag::copy_first_to_last(bag& b1)
    {
        //If linked list is empty, exit function
        if (head_ptr == NULL)
            return;

        node *tail_ptr;

        tail_ptr = head_ptr;

        //tail pointer will point to the NULL link of the last node in the list
        while (tail_ptr->link() != NULL)
        {
            tail_ptr = tail_ptr->link();
        }

        //Creates a new node, sets the data value equal to head_ptr's data value, then sets the tail_ptr link to point to the newly created node.
        node *insert_ptr;
        insert_ptr = new node;
        insert_ptr->set_data(head_ptr->data());

        tail_ptr->set_link(insert_ptr);

        return;
    }

    //Adds the value of all the nodes and places it in a new node at the top of the list.
    void bag::sum_of_all_nodes()
    {

        if (head_ptr == NULL)
            return;

        node::value_type sum = 0;
        node* cursor;
        for(cursor = head_ptr; cursor != NULL; cursor = cursor->link())
        {
            sum += cursor->data();
        }

        list_head_insert(head_ptr, sum);

        return;
    }

    void bag::printList()
    {
        node* cursor;

        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            cout << cursor->data() << endl;
        return;
    }

    //removes the last node from the linked list
    void bag::remove_last_node()
    {
        node *cursor;
        node *previous_ptr;

        //If linked list is empty, exit function
        if (head_ptr == NULL)
            return;

        node *tail_ptr = new node;

        tail_ptr = head_ptr;

        //tail pointer will point to the NULL link of the last node in the list
        while (tail_ptr->link()->link() != NULL)
        {
            tail_ptr = tail_ptr->link();
        }

        list_remove(tail_ptr);

     return;
    }

    //removes duplicate values from list and sorts the data from smallest to largest.
    void bag::remove_duplicate_values()
    {
        node *cursor, *next_ptr;

        cursor = head_ptr;

    //This is where the remove duplicate portion of this function starts
    while (cursor != NULL)
    {
       next_ptr = cursor->link();

        while (next_ptr != NULL)
        {
            if (cursor->data() == next_ptr->data())
        {
            list_remove(cursor);
            next_ptr = cursor->link();
        }
            else
                next_ptr = next_ptr->link();
        }
        cursor = cursor->link();
    }
        return;
    }

    //sorts the data in the linked list from smallest to largest. This function is executed before running the
    //remove_duplicate_values() function.
    void bag::sort_list()
    {
        node *cursor, *next_ptr;
        value_type data;

        if (head_ptr == NULL)
		return;

	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
        {
            for (next_ptr = cursor; next_ptr != NULL; next_ptr = next_ptr->link())
            {
                if (cursor->data() > next_ptr->data())
                {
                    data = cursor->data();
                    cursor->set_data(next_ptr->data());
                    next_ptr->set_data(data);

                }
            }
        }
	return;
    }
}

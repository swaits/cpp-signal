#include <cassert>
#include "signal_base.h"

signal_base::signal_base() : head(0), tail(0)
{
	// empty
}

signal_base::~signal_base()
{
	// clear the list
	clear_list();
}

bool signal_base::bind(const slot_base& slot)
{
	// add it to our signal list
	return add_to_list(slot);
}

bool signal_base::unbind(const slot_base& slot)
{
	// look for corresponding list_node in list
	list_node* n = find_in_list(slot);

	// see if we found a match
	if ( !n )
	{
		return false; // no match found
	}

	// take it out of the linked list
	remove_from_list(n);

	// free it
	delete n;

	// found a match, success
	return true;
}

void signal_base::clear_list()
{
	// start at head
	list_node* cur = head;

	// iterate
	while ( cur )
	{
		// save off next so we can safely delete
		list_node* next = cur->next;

		// free
		delete cur;

		// advance
		cur = next;
	}

	// reset head & tail
	head = tail = 0;
}

signal_base::list_node* signal_base::find_in_list(const slot_base& slot) const
{
	// start search at head of list
	list_node* cur  = head;

	// search list for slot
	while ( cur )
	{
		// see if this is a match
		if ( cur->slot == slot )
		{
			// we have a match, return it
			return cur;
		}

		// advance to next in list
		cur = cur->next;
	}

	// no match
	return 0;
}

bool signal_base::add_to_list(const slot_base& slot)
{
	// a sanity check
	assert((head && tail) || (!head && !tail));

	// make a new list_node to hold this slot in the list
	list_node* n = new list_node;
	if ( !n )
	{
		return false;
	}

	// initialize new list_node
	n->slot = slot; // copy slot into list_node
	n->prev = tail; // prev is tail because we'll put this list_node behind it (i.e. the new tail)
	n->next = 0;    // next is 0 because we'll put this list_node on the tail

	// add to tail
	if ( tail )
	{
		// tail exists, just append
		tail->next = n; // insert item after current tail
		tail       = n; // now have a new tail
	}
	else
	{
		// list is currently empty, add this new list_node
		head = tail = n; // now have a single list_node, which is also both the head and tail
	}
	
	return true;
}

void signal_base::remove_from_list(list_node* n)
{
	// do a little sanity checking
	assert((head && tail) || (!head && !tail));
	assert(n->prev == 0 || n->prev->next == n);
	assert(n->next == 0 || n->next->prev == n);

	// if this is the head, set the new head
	if ( n == head )
	{
		head = n->next;
	}

	// if this is the tail, set the new tail
	if ( n == tail )
	{
		tail = n->prev;
	}

	// set list to skip over this list_node
	if ( n->prev )
	{
		n->prev->next = n->next;
	}
	if ( n->next )
	{
		n->next->prev = n->prev;
	}
}




#include <cassert>
#include "signal_base.h"


signal_base::signal_base() : head(0), tail(0), bEmitting(false)
{
	// empty
}

signal_base::~signal_base()
{
	// clear the list
	clear_list();
}

signal_base::signal_base( const signal_base& rSource ) : head(0), tail(0), bEmitting(false)
{
	// Set an assert to let the user know that we don't support signal copying.
	// There are too many places where the signals are directly connected to objects, 
	// where copying them would create a disconnect between the signal and the objects 
	// that want to react to the signal execution.
	assert( 0 );
}

signal_base& signal_base::operator=( const signal_base& rSource )
{
	// Set an assert to let the user know that we don't support signal copying.
	// There are too many places where the signals are directly connected to objects, 
	// where copying them would create a disconnect between the signal and the objects 
	// that want to react to the signal execution.
	assert( 0 );
	return *this;
}

int signal_base::count( void )
{
	int count = 0;
	list_node* cur = head;

	while( cur )
	{
		cur = cur->next;
		count++;
	}

	return count;
}

bool signal_base::bind(slot_base* slot)
{
	// add it to our signal list
	return add_to_list(slot);
}

bool signal_base::unbind(slot_base* slot)
{
	// look for corresponding list_node in list
	list_node* n = find_in_list(slot);

	// see if we found a match
	if( n )
	{
		// If we are not processing a signal emit sequence, then release the node.
		if( !emitting )
		{
			// take it out of the linked list
			remove_from_list(n);

			// found a match, return success
			return true;
		}
		// Otherwise mark it for removal.
		else
		{
			n->deleted = true;
			return true;
		}
	}

	// no match
	return false;
}

signal_base::list_node::list_node(slot_base* s) : slot(s), prev(0), next(0), deleted(false)
{
	// empty
}

signal_base::list_node::~list_node()
{
	// release the slot
	delete slot;
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

signal_base::list_node* signal_base::find_in_list(slot_base* slot) const
{
	// start search at head of list
	list_node* cur  = head;

	// search list for slot
	while ( cur )
	{
		// see if this is a match
		if ( *(cur->slot) == *(slot) ) // note comparing values, not addresses !!!
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

bool signal_base::add_to_list(slot_base* slot)
{
	// a sanity check
	assert((head && tail) || (!head && !tail));

	// make a new list_node to hold this slot in the list
	// and initialize with this slot pointer
	list_node* node = new list_node(slot);
	assert(node);
	if ( !node )
	{
		return false;
	}

	// setup new list_node
	node->prev = tail; // prev is tail because we'll put this list_node behind it (i.e. the new tail)
	node->next = 0;    // next is 0 because we'll put this list_node on the tail

	// add to tail
	if ( tail )
	{
		// tail exists, just append
		tail->next = node; // insert item after current tail
		tail       = node; // now have a new tail
	}
	else
	{
		// list is currently empty, add this new list_node
		head = tail = node; // now have a single list_node, which is also both the head and tail
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

	// finally, destroy the node
	delete n;
}

void signal_base::remove_pending_nodes( void )
{
	list_node* cur = head;
	list_node* next;

	while( cur )
	{
		// Prepare the next link in the list the removal stage.
		next = cur->next;

		// Do we need to remove this link.
		if( cur->deleted )
		{
			remove_from_list( cur );
		}

		// Go to the next item.
		cur = next;
	}
}


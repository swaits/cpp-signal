#ifndef __signal_base_h__
#define __signal_base_h__

#include "slot_base.h"


/**
 * -----------------------------------------------------------------------------------------------------------------------------------------
 * Signals - An elegant system of that manages software events and the callbacks that respond to them.
 * -----------------------------------------------------------------------------------------------------------------------------------------
 * 
 *     Each discrete signal represents a moment within your application that might require some reaction. A signal might represent a 
 * basketball going through the basket, or hitting the ground. Another signal might identify when a bullet was fired out of a gun.
 * There is no limit to what the signal represents.
 * 
 *     The reactions that need to be processed through the signal system are called "Slots". Slots are nothing more than a common interface
 * that the Signal can use to call many variations of callbacks with a single interface. Some have labelled slots as "Delegates" as they are
 * not the actual code that performs the reaction, but instead are used to translate the common reaction request into the actual callback that
 * is desired. Please see slot_base.h for more information.
 *  
 */
class signal_base
{
	public:

		signal_base();
		virtual ~signal_base();

		signal_base( const signal_base& rSource );
		signal_base& operator=( const signal_base& rSource );

		/**
		 * Determines the number of slots that are connected to the signal.
		 */
		int count( void );

	protected:
		// linked list data structure
		// used to maintain a list of pointers to slot_base.. no memory management is 
		// performed on the slot_base data - derived class should take care of this.
		struct list_node
		{
			list_node(slot_base* s);
			~list_node();

			slot_base* slot;
			list_node* prev;
			list_node* next;

			bool deleted;
		};

		/**
		 * Request to add a slot to the signals reaction list that is processed when a signal is executed.
		 * 
		 * @param slot   A pointer to a slot base class that contains the required callback mechanism.
		 * 
		 * @return true  if the signal is able to add the slot.
		 *         false if the signal could NOT add the slot.
		 */
		bool bind(slot_base* slot);

		/**
		 * Request to remove a slot from the signals reaction list.
		 * 
		 * @param slot   A pointer to a slot base class that contains the required callback mechanism.
		 * 
		 * @return true  if the signal is able to remove the slot.
		 *         false if the signal could NOT remove the slot.
		 */
		bool unbind(slot_base* slot);

		/**
		 * Functions used to maintain the status of a signal. When a signal is active it means that it is "Emitting". During the emitting
		 * stage, we are walking the list of slots to allow each slot to react to the signal. There are special considerations that
		 * must be made when walking the list, such as adding or removing slots during the emit stage. 
		 */

	private:
		/**
		 * Removes all slots that are connected to the signal
		 */
		void clear_list( );

		/**
		 * Searches the slot list to find a slot that contains the same components. The location within the list is returned.
		 */
		list_node* find_in_list(slot_base* slot) const;

		/**
		 * Performs the actual operation of adding the slot to signal's internal list.
		 */
		bool add_to_list(slot_base* slot);

		/** 
		 * Performs the actual operation of removing the slot from the signal's internal list.
		 */
		void remove_from_list(list_node* n);

	protected:

		/**
		 * Removes any nodes that were tagged for deletion during the signal emit sequence
		 */
		void remove_pending_nodes( void );

		//-----------------------------------------------------------------------------------------------------------------------------------------
	protected:

		list_node* head;
		list_node* tail;

		bool       emitting;
};

#endif // __signal_base_h__


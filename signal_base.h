#ifndef __signal_base_h__
#define __signal_base_h__

#include "slot_base.h"

class signal_base
{
	public:

		signal_base();
		virtual ~signal_base();

	protected:

		bool bind(const slot_base& slot);
		bool unbind(const slot_base& slot);

// TEMP HACK	private:

		// linked list data structure
		struct list_node
		{
			slot_base slot;
			list_node* prev;
			list_node* next;
		};
		list_node* head;
		list_node* tail;

		// linked list manipulation
		void clear_list();
		list_node* find_in_list(const slot_base& slot) const;
		bool add_to_list(const slot_base& slot);
		void remove_from_list(list_node* n);
};

#endif // __signal_base_h__


#ifndef __signal0_h__
#define __signal0_h__

#include "signal_base.h"
#include "slot.h"

class signal0: public signal_base
{
	public:
		/*
		signal0();
		virtual ~signal0();
*/

		void operator() () const
		{
			// TODO: need a way to iterate the bound signal_base list ...
			list_node* cur = head;
			while(cur)
			{
				(cur->slot)();
				cur = cur->next;
			}
		}

		template <class T_object, typename T_member>
		void connect(T_object* p_object, T_member p_member)
		{
			bind( slot0_method<T_object,T_member>(p_object,p_member) );
		}
};

#include "signal0.inl"

#endif // __signal0_h__


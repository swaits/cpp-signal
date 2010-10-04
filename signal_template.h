#ifndef __signal===NARG===_h__
#define __signal===NARG===_h__

#include "horrible_cast.h"
#include "slot_base.h"
#include "signal_base.h"



//
// Slot ===NARG===
//

//
// Abstract base class for Slots with ===NARG=== parameter(s).
//
template<typename T_return===TEMPLATE_ARG_DECL===>
class Slot===NARG=== : public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (===FORMAL_ARG_DECL===) const = 0;
};


//
// A concrete Slot class for a normal function.
//
template <typename T_return===TEMPLATE_ARG_DECL===>
class Slot===NARG===_function: public Slot===NARG===<T_return===TEMPLATE_ARG===>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(===FORMAL_ARG_DECL===);

		Slot===NARG===_function( const FUNCTION_POINTER func )
		{
			// convert and store function pointer in slot_base
			this->data[0] = safe_horrible_cast<data_container>(func);
		}

		T_return operator() (===FORMAL_ARG_DECL===) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(===FORMAL_ARG===);
		}
};

//
// A concrete Slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return===TEMPLATE_ARG_DECL===> 
class Slot===NARG===_method: public Slot===NARG===<T_return===TEMPLATE_ARG===>
{
	public:

		Slot===NARG===_method(const T_object* p_object, const T_member p_member)
		{
			// convert and store object pointer and member function pointer in slot_base
			this->data[0] = safe_horrible_cast<data_container>(p_object);
			this->data[1] = safe_horrible_cast<data_container>(p_member);
		}

		T_return operator() (===FORMAL_ARG_DECL===) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(===FORMAL_ARG===);
		}
};



//
// Signal ===NARG===
//
template< typename T_return===TEMPLATE_ARG_DECL=== >
class Signal===NARG===: public signal_base
{
	public:

		// Emit the signal. Iterate through the list of slots, and call each one.
		void operator() (===FORMAL_ARG_DECL===)
		{
			// if we're already emitting, return (i.e. no re-entrancy)
			if( IsSignalEmitting() )
			{
#if defined( _DEBUG )
				printf("WARNING: Signal===NARG===<...> @ 0x%p recursive Emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			BeginEmit();

			// iterate through the list
			list_node* cur = GetFirstNode();
			while( cur )
			{
				// make the slot_base pointer a Slot===NARG=== pointer
				Slot===NARG===<T_return===TEMPLATE_ARG===>* s = static_cast<Slot===NARG===<T_return===TEMPLATE_ARG===>*>(cur->slot);

				// call the Signal
				(*s)(===FORMAL_ARG===);

				// move to next Slot in the list.
				cur = cur->next;
			}

			// clear emitting flag
			EndEmit( );
		}


		//
		// Signal connections
		//

		// connect to normal functions
		typedef T_return (*FUNCTION_POINTER)(===FORMAL_ARG_DECL===);  // helper typedef
		bool Connect( FUNCTION_POINTER func )
		{
			// make a copy of the Slot to store in our list
			Slot===NARG===<T_return===TEMPLATE_ARG===>* sNewFunc = new Slot===NARG===_function<T_return===TEMPLATE_ARG===>( func );

			// add it to the end of our linked list
			return bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool Connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the Slot to store in our list
			Slot===NARG===<T_return===TEMPLATE_ARG===>* sNewMethod = new Slot===NARG===_method<T_object,T_member,T_return===TEMPLATE_ARG===>( p_object, p_member );

			// add it to the end of our linked list
			return bind(sNewMethod);
		}


		//
		// signal disconnections
		//

		// disconnect from a normal function
		bool Disconnect( FUNCTION_POINTER func )
		{
			// make a temporary Slot we can use to find a match in the list
			Slot===NARG===_function<T_return===TEMPLATE_ARG===> sTest( func );

			// search and remove it
			return unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool Disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary Slot we can use to find a match in the list
			Slot===NARG===_method<T_object,T_member,T_return===TEMPLATE_ARG===> sTemp(p_object,p_member);

			// search and remove it
			return unbind(&sTemp);
		}
};

#endif // __signal===NARG===_h__

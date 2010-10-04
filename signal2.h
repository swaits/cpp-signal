
#ifndef __Signal2_h__
#define __Signal2_h__

#include "horrible_cast.h"
#include "slot_base.h"
#include "signal_base.h"


//=========================================================================================================================================
// Slot tempplate.
//=========================================================================================================================================
/**
 * Abstract base class for Slots with 2 parameter(s).
 */
template<typename T_return, typename T_arg0, typename T_arg1>
class Slot2 : public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (T_arg0 a0, T_arg1 a1) const = 0;
};


//
// a concrete Slot class for a normal function
//
template <typename T_return, typename T_arg0, typename T_arg1>
class Slot2_function: public Slot2<T_return, T_arg0, T_arg1>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1);

		Slot2_function( const FUNCTION_POINTER func )
		{
			// convert and store function pointer in slot_base
			this->data[0] = safe_horrible_cast<slot_base::data_container>(func);
		}

		T_return operator() (T_arg0 a0, T_arg1 a1) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0, a1);
		}
};


//
// a concrete Slot class for an object pointer and method (usually 'this' and 'Class::Method')
//
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1> 
class Slot2_method: public Slot2<T_return, T_arg0, T_arg1>
{
	public:

		Slot2_method(const T_object* p_object, const T_member p_member)
		{
			// convert and store object pointer and member function pointer in slot_base
			this->data[0] = safe_horrible_cast<slot_base::data_container>(p_object);
			this->data[1] = safe_horrible_cast<slot_base::data_container>(p_member);
		}

		T_return operator() (T_arg0 a0, T_arg1 a1) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0, a1);
		}
};

//=========================================================================================================================================
// Signal tempplate.
//=========================================================================================================================================
template< typename T_return, typename T_arg0, typename T_arg1 >
class Signal2: public signal_base
{
	public:

		//-----------------------------------------------------------------------------------------------------------------------------------------
		// Execute the Signal: 
		// - Walk the list of Slot nodes.
		//-----------------------------------------------------------------------------------------------------------------------------------------
		void operator() (T_arg0 a0, T_arg1 a1)
		{
			if( IsSignalEmitting( ) )
			{
#if defined( _DEBUG )
				printf("WARNING: Signal2<...> @ 0x%p recursive Emit attempt\n", this);
#endif
				return;
			}

			BeginEmit( );

			list_node* cur = GetFirstNode( );

			// iterate through the list
			while( cur )
			{
				// make the slot_base pointer a Slot2 pointer
				Slot2<T_return, T_arg0, T_arg1>* s = static_cast<Slot2<T_return, T_arg0, T_arg1>*>(cur->slot);

				// call the Signal
				(*s)(a0, a1);

				// move to next Slot in the list.
				cur = cur->next;
			}

			EndEmit( );
		}

		//=========================================================================================================================================
		// Signal connections
		//=========================================================================================================================================
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1);

		// Functions
		//-----------------------------------------------------------------------------------------------------------------------------------------
		bool Connect( FUNCTION_POINTER func )
		{
			// make a copy of the Slot to store in our list
			Slot2<T_return, T_arg0, T_arg1>* sNewFunc = new Slot2_function<T_return, T_arg0, T_arg1>( func );

			// add it to the end of our linked list
			return bind(sNewFunc);
		}

		// Object methods
		//-----------------------------------------------------------------------------------------------------------------------------------------
        template <class T_object, typename T_member>
		bool Connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the Slot to store in our list
			Slot2<T_return, T_arg0, T_arg1>* sNewMethod = new Slot2_method<T_object,T_member,T_return, T_arg0, T_arg1>( p_object, p_member );

			// add it to the end of our linked list
			return bind(sNewMethod);
		}


		//=========================================================================================================================================
		// Signal Disconnections
		//=========================================================================================================================================
		// Functions
		//-----------------------------------------------------------------------------------------------------------------------------------------
		bool Disconnect( FUNCTION_POINTER func )
		{
			// make a temporary Slot we can use to find a match in the list
			Slot2_function<T_return, T_arg0, T_arg1> sTest( func );

			// search and remove it
			return unbind(&sTest);
		}


		// Object method
		//-----------------------------------------------------------------------------------------------------------------------------------------
        template <class T_object, typename T_member>
		bool Disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary Slot we can use to find a match in the list
			Slot2_method<T_object,T_member,T_return, T_arg0, T_arg1> sTemp(p_object,p_member);

			// search and remove it
			return unbind(&sTemp);
		}
};

#endif // __Signal2_h__

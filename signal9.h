#ifndef __signal9_h__
#define __signal9_h__

#include "horrible_cast.h"
#include "slot_base.h"
#include "signal_base.h"



//
// classes slot9, slot9_function, and slot9_method
//

//
// Abstract base class for slots with 9 parameter(s).
//
template<typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8>
class slot9 : public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8) const = 0;
};

//
// A concrete slot class for a normal function.
//
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8>
class slot9_function: public slot9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot9_function( const FUNCTION_POINTER func )
		{
			// convert and store function pointer in slot_base
			this->data[0] = safe_horrible_cast<slot_base::data_container>(func);
		}

		/**
		 * Perform callback.
		 *
		 * Converts raw data back into a function pointer, and calls it.
		 *
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8> 
class slot9_method: public slot9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot9_method(const T_object* p_object, const T_member p_member)
		{
			// convert and store object pointer and member function pointer in slot_base
			this->data[0] = safe_horrible_cast<slot_base::data_container>(p_object);
			this->data[1] = safe_horrible_cast<slot_base::data_container>(p_member);
		}

		/**
		 * Perform callback.
		 *
		 * Converts raw data back into a method pointer, and calls it.
		 *
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		}
};



//
// class signal9
//
template< typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8 >
class signal9: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal9<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot9 pointer (converts from raw memory to pointer again)
				slot9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>* s = static_cast<slot9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(a0, a1, a2, a3, a4, a5, a6, a7, a8);
				}

				// move to next slot in the list.
				cur = cur->next;
			}

			// delete any pending slot deletions
			signal_base::remove_pending_nodes( );

			// clear emitting flag
			signal_base::emitting = false;
		}


		//
		// signal connections to slots
		//

		// convenience typedef
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8);

		// connect to normal functions
		bool Connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>* sNewFunc = new slot9_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool Connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>* sNewMethod = new slot9_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool Disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot9_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool Disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot9_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal9_h__

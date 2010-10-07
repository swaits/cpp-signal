#ifndef __signal_h__
#define __signal_h__

#include "horrible_cast.h"
#include "slot_base.h"
#include "signal_base.h"


/*
 * Begin signal[X] definitions
 */


#ifndef __signal0_h__
#define __signal0_h__

//
// classes slot0, slot0_function, and slot0_method
//

//
// Abstract base class for slots with 0 parameter(s).
//
template<typename T_return>
class slot0: public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() () const = 0;
};

//
// A concrete slot class for a normal function.
//
template <typename T_return>
class slot0_function: public slot0<T_return>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot0_function( const FUNCTION_POINTER func )
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
		T_return operator() () const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func();
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return> 
class slot0_method: public slot0<T_return>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot0_method(const T_object* p_object, const T_member p_member)
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
		T_return operator() () const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)();
		}
};



//
// class signal0
//
template< typename T_return >
class signal0: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() ()
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal0<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot0 pointer (converts from raw memory to pointer again)
				slot0<T_return>* s = static_cast<slot0<T_return>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)();
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
		typedef T_return (*FUNCTION_POINTER)();

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot0<T_return>* sNewFunc = new slot0_function<T_return>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot0<T_return>* sNewMethod = new slot0_method<T_object,T_member,T_return>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot0_function<T_return> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot0_method<T_object,T_member,T_return> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal0_h__


#ifndef __signal1_h__
#define __signal1_h__

//
// classes slot1, slot1_function, and slot1_method
//

//
// Abstract base class for slots with 1 parameter(s).
//
template<typename T_return, typename T_arg0>
class slot1: public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (T_arg0 a0) const = 0;
};

//
// A concrete slot class for a normal function.
//
template <typename T_return, typename T_arg0>
class slot1_function: public slot1<T_return, T_arg0>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot1_function( const FUNCTION_POINTER func )
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
		T_return operator() (T_arg0 a0) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return, typename T_arg0> 
class slot1_method: public slot1<T_return, T_arg0>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot1_method(const T_object* p_object, const T_member p_member)
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
		T_return operator() (T_arg0 a0) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0);
		}
};



//
// class signal1
//
template< typename T_return, typename T_arg0 >
class signal1: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (T_arg0 a0)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal1<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot1 pointer (converts from raw memory to pointer again)
				slot1<T_return, T_arg0>* s = static_cast<slot1<T_return, T_arg0>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(a0);
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
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0);

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot1<T_return, T_arg0>* sNewFunc = new slot1_function<T_return, T_arg0>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot1<T_return, T_arg0>* sNewMethod = new slot1_method<T_object,T_member,T_return, T_arg0>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot1_function<T_return, T_arg0> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot1_method<T_object,T_member,T_return, T_arg0> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal1_h__


#ifndef __signal2_h__
#define __signal2_h__

//
// classes slot2, slot2_function, and slot2_method
//

//
// Abstract base class for slots with 2 parameter(s).
//
template<typename T_return, typename T_arg0, typename T_arg1>
class slot2: public slot_base
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
// A concrete slot class for a normal function.
//
template <typename T_return, typename T_arg0, typename T_arg1>
class slot2_function: public slot2<T_return, T_arg0, T_arg1>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot2_function( const FUNCTION_POINTER func )
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
		T_return operator() (T_arg0 a0, T_arg1 a1) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0, a1);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1> 
class slot2_method: public slot2<T_return, T_arg0, T_arg1>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot2_method(const T_object* p_object, const T_member p_member)
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
		T_return operator() (T_arg0 a0, T_arg1 a1) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0, a1);
		}
};



//
// class signal2
//
template< typename T_return, typename T_arg0, typename T_arg1 >
class signal2: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (T_arg0 a0, T_arg1 a1)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal2<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot2 pointer (converts from raw memory to pointer again)
				slot2<T_return, T_arg0, T_arg1>* s = static_cast<slot2<T_return, T_arg0, T_arg1>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(a0, a1);
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
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1);

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot2<T_return, T_arg0, T_arg1>* sNewFunc = new slot2_function<T_return, T_arg0, T_arg1>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot2<T_return, T_arg0, T_arg1>* sNewMethod = new slot2_method<T_object,T_member,T_return, T_arg0, T_arg1>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot2_function<T_return, T_arg0, T_arg1> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot2_method<T_object,T_member,T_return, T_arg0, T_arg1> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal2_h__


#ifndef __signal3_h__
#define __signal3_h__

//
// classes slot3, slot3_function, and slot3_method
//

//
// Abstract base class for slots with 3 parameter(s).
//
template<typename T_return, typename T_arg0, typename T_arg1, typename T_arg2>
class slot3: public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2) const = 0;
};

//
// A concrete slot class for a normal function.
//
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2>
class slot3_function: public slot3<T_return, T_arg0, T_arg1, T_arg2>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot3_function( const FUNCTION_POINTER func )
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0, a1, a2);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1, typename T_arg2> 
class slot3_method: public slot3<T_return, T_arg0, T_arg1, T_arg2>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot3_method(const T_object* p_object, const T_member p_member)
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0, a1, a2);
		}
};



//
// class signal3
//
template< typename T_return, typename T_arg0, typename T_arg1, typename T_arg2 >
class signal3: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal3<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot3 pointer (converts from raw memory to pointer again)
				slot3<T_return, T_arg0, T_arg1, T_arg2>* s = static_cast<slot3<T_return, T_arg0, T_arg1, T_arg2>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(a0, a1, a2);
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
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2);

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot3<T_return, T_arg0, T_arg1, T_arg2>* sNewFunc = new slot3_function<T_return, T_arg0, T_arg1, T_arg2>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot3<T_return, T_arg0, T_arg1, T_arg2>* sNewMethod = new slot3_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot3_function<T_return, T_arg0, T_arg1, T_arg2> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot3_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal3_h__


#ifndef __signal4_h__
#define __signal4_h__

//
// classes slot4, slot4_function, and slot4_method
//

//
// Abstract base class for slots with 4 parameter(s).
//
template<typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3>
class slot4: public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3) const = 0;
};

//
// A concrete slot class for a normal function.
//
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3>
class slot4_function: public slot4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot4_function( const FUNCTION_POINTER func )
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0, a1, a2, a3);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3> 
class slot4_method: public slot4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot4_method(const T_object* p_object, const T_member p_member)
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0, a1, a2, a3);
		}
};



//
// class signal4
//
template< typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3 >
class signal4: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal4<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot4 pointer (converts from raw memory to pointer again)
				slot4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>* s = static_cast<slot4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(a0, a1, a2, a3);
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
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3);

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>* sNewFunc = new slot4_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>* sNewMethod = new slot4_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot4_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot4_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal4_h__


#ifndef __signal5_h__
#define __signal5_h__

//
// classes slot5, slot5_function, and slot5_method
//

//
// Abstract base class for slots with 5 parameter(s).
//
template<typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class slot5: public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4) const = 0;
};

//
// A concrete slot class for a normal function.
//
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class slot5_function: public slot5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot5_function( const FUNCTION_POINTER func )
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0, a1, a2, a3, a4);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4> 
class slot5_method: public slot5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot5_method(const T_object* p_object, const T_member p_member)
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0, a1, a2, a3, a4);
		}
};



//
// class signal5
//
template< typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class signal5: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal5<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot5 pointer (converts from raw memory to pointer again)
				slot5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>* s = static_cast<slot5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(a0, a1, a2, a3, a4);
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
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4);

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>* sNewFunc = new slot5_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>* sNewMethod = new slot5_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot5_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot5_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal5_h__


#ifndef __signal6_h__
#define __signal6_h__

//
// classes slot6, slot6_function, and slot6_method
//

//
// Abstract base class for slots with 6 parameter(s).
//
template<typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class slot6: public slot_base
{
	public:
		/**
		 * Method which performs the actual callback.  Must be overridden.
		 * 
		 * @return Returns an object of type T_return; the result of the user callback.
		 */
		virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5) const = 0;
};

//
// A concrete slot class for a normal function.
//
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class slot6_function: public slot6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot6_function( const FUNCTION_POINTER func )
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(a0, a1, a2, a3, a4, a5);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5> 
class slot6_method: public slot6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot6_method(const T_object* p_object, const T_member p_member)
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
		T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5) const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			return (p_object->*p_member)(a0, a1, a2, a3, a4, a5);
		}
};



//
// class signal6
//
template< typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class signal6: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal6<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot6 pointer (converts from raw memory to pointer again)
				slot6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>* s = static_cast<slot6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(a0, a1, a2, a3, a4, a5);
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
		typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5);

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>* sNewFunc = new slot6_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>* sNewMethod = new slot6_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>( p_object, p_member );

			// add it to the end of our linked list
			return signal_base::bind(sNewMethod);
		}


		//
		// signal disconnections from slots
		//

		// disconnect from a normal function
		bool disconnect( FUNCTION_POINTER func )
		{
			// make a temporary slot we can use to find a match in the list
			slot6_function<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot6_method<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal6_h__

/*
 * Begin signal template definitions and specilizations
 */

struct nilarg;

// full template for signal<> (signal<> inherits signal6<>)
template <typename T_return, typename T_arg0=nilarg, typename T_arg1=nilarg, typename T_arg2=nilarg, typename T_arg3=nilarg, typename T_arg4=nilarg, typename T_arg5=nilarg>
class signal: public signal6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 { /* empty class */ };

// partial specialization for signal<> with 5 parameters (signal<> inherits signal5<>)
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>: public signal5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4> { /* empty class */ };

// partial specialization for signal<> with 4 parameters (signal<> inherits signal4<>)
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3>: public signal4<T_return, T_arg0, T_arg1, T_arg2, T_arg3> { /* empty class */ };

// partial specialization for signal<> with 3 parameters (signal<> inherits signal3<>)
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2>
class signal<T_return, T_arg0, T_arg1, T_arg2>: public signal3<T_return, T_arg0, T_arg1, T_arg2> { /* empty class */ };

// partial specialization for signal<> with 2 parameters (signal<> inherits signal2<>)
template <typename T_return, typename T_arg0, typename T_arg1>
class signal<T_return, T_arg0, T_arg1>: public signal2<T_return, T_arg0, T_arg1> { /* empty class */ };

// partial specialization for signal<> with 1 parameters (signal<> inherits signal1<>)
template <typename T_return, typename T_arg0>
class signal<T_return, T_arg0>: public signal1<T_return, T_arg0> { /* empty class */ };

// partial specialization for signal<> with 0 parameters (signal<> inherits signal0<>)
template <typename T_return>
class signal<T_return>: public signal0<T_return> { /* empty class */ };

#endif // __signal_h__

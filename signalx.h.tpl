
#ifndef __signal===NARG===_h__
#define __signal===NARG===_h__

//
// classes slot===NARG===, slot===NARG===_function, and slot===NARG===_method
//

//
// Abstract base class for slots with ===NARG=== parameter(s).
//
template<typename T_return===TEMPLATE_ARG_DECL===>
class slot===NARG===: public slot_base
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
// A concrete slot class for a normal function.
//
template <typename T_return===TEMPLATE_ARG_DECL===>
class slot===NARG===_function: public slot===NARG===<T_return===TEMPLATE_ARG===>
{
	public:

		typedef T_return (*FUNCTION_POINTER)(===FORMAL_ARG_DECL===); // convenience typedef

		/**
		 * Constructor.
		 *
		 * Converts a function pointer into raw data.
		 */
		slot===NARG===_function( const FUNCTION_POINTER func )
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
		T_return operator() (===FORMAL_ARG_DECL===) const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			return func(===FORMAL_ARG===);
		}
};

//
// A concrete slot class for an object pointer and method (usually 'this' and 'Class::Method').
//
template <class T_object, typename T_member, typename T_return===TEMPLATE_ARG_DECL===> 
class slot===NARG===_method: public slot===NARG===<T_return===TEMPLATE_ARG===>
{
	public:

		/**
		 * Constructor.
		 *
		 * Converts an object and method pointer into raw data.
		 */
		slot===NARG===_method(const T_object* p_object, const T_member p_member)
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
// class signal===NARG===
//
template< typename T_return===TEMPLATE_ARG_DECL=== >
class signal===NARG===: public signal_base
{
	public:

		/**
		 * Emit the signal.
		 *
		 * Iterate through the list of slots, and call each one.
		 */
		void operator() (===FORMAL_ARG_DECL===)
		{
			// if we're already emitting, return (i.e. no re-entrancy allowed)
			if( signal_base::emitting )
			{
#if defined( _DEBUG )
				printf("WARNING: signal===NARG===<...> @ 0x%p recursive emit attempt\n", this);
#endif
				return;
			}

			// set emitting flag
			signal_base::emitting = true;

			// iterate through the list
			signal_base::list_node* cur = signal_base::head;
			while( cur )
			{
				// cast the slot_base pointer to a slot===NARG=== pointer (converts from raw memory to pointer again)
				slot===NARG===<T_return===TEMPLATE_ARG===>* s = static_cast<slot===NARG===<T_return===TEMPLATE_ARG===>*>(cur->slot);

				// call the signal as long as it's still valid
				if ( !cur->deleted )
				{
					(*s)(===FORMAL_ARG===);
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
		typedef T_return (*FUNCTION_POINTER)(===FORMAL_ARG_DECL===);

		// connect to normal functions
		bool connect( FUNCTION_POINTER func )
		{
			// make a copy of the slot to store in our list
			slot===NARG===<T_return===TEMPLATE_ARG===>* sNewFunc = new slot===NARG===_function<T_return===TEMPLATE_ARG===>( func );

			// add it to the end of our linked list
			return signal_base::bind(sNewFunc);
		}

		// connect to an object's method
		template <class T_object, typename T_member>
		bool connect(T_object* p_object, T_member p_member)
		{
			// make a copy of the slot to store in our list
			slot===NARG===<T_return===TEMPLATE_ARG===>* sNewMethod = new slot===NARG===_method<T_object,T_member,T_return===TEMPLATE_ARG===>( p_object, p_member );

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
			slot===NARG===_function<T_return===TEMPLATE_ARG===> sTest( func );

			// search and remove it
			return signal_base::unbind(&sTest);
		}

		// disconnect from an object's method
		template <class T_object, typename T_member>
		bool disconnect(T_object* p_object, T_member p_member)
		{
			// make a temporary slot we can use to find a match in the list
			slot===NARG===_method<T_object,T_member,T_return===TEMPLATE_ARG===> sTemp(p_object,p_member);

			// search and remove it
			return signal_base::unbind(&sTemp);
		}
};

#endif // __signal===NARG===_h__


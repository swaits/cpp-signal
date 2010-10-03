#ifndef __slot_h__
#define __slot_h__


#include "slot_base.h"
#include "horrible_cast.h"


// TODO: do return types really matter???
//       if we get rid of them, slot0 untemplates, making signal completely untemplate as well!
//       maybe signal::Emit() should simply return the number of signals it emits?


//
// abstract base class for a slot taking 0 arguments
//
// this is basically just slot_base with the pure virtual "operator(...)" added
//
// each derivative of this should have NO storage of its own.  Instead it should 
// store data in the slot_base (parent class) members 'data[]'.  Use horrible_cast<>()
// to subvert C++'s type system.
//
class slot0: public slot_base
{
	public:

		virtual void operator() () const = 0;
};


//
// a concrete slot class for a normal function
//
template <typename T_return>
class slot0_function: public slot0
{
	public:

		typedef T_return (*FUNCTION_POINTER)();

		slot0_function(const FUNCTION_POINTER func)
		{
			// convert and store function pointer in slot_base
			this->data[0] = safe_horrible_cast<data_container>(func);
		}

		void operator() () const
		{
			// retrieve data from slot_base and convert back to a function pointer
			FUNCTION_POINTER func = dangerous_horrible_cast<FUNCTION_POINTER>(this->data[0]);

			// call function
			func();
		}
};


//
// a concrete slot class for an object pointer and method (usually 'this' and 'Class::Method')
//
template <class T_object, typename T_member> 
class slot0_method: public slot0
{
	public:

		slot0_method(const T_object* p_object, const T_member p_member)
		{
			// convert and store object pointer and member function pointer in slot_base
			this->data[0] = safe_horrible_cast<data_container>(p_object);
			this->data[1] = safe_horrible_cast<data_container>(p_member);
		}

		void operator() () const
		{
			// retrieve data from slot_base and convert back to an object pointer and member function pointer
			T_object* p_object = dangerous_horrible_cast<T_object*>(this->data[0]);
			T_member  p_member = dangerous_horrible_cast<T_member> (this->data[1]);

			// call member function
			(p_object->*p_member)();
		}
};


#endif // __slot_h__


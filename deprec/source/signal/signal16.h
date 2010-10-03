#ifndef __signal16_h__
#define __signal16_h__



#if defined(_DEBUG)
#	include <cstdio>
#endif



/**
 * Abstract base class for Slots with 16 parameter(s).
 */
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13, typename T_arg14, typename T_arg15>
class Slot16
{ 
public:
	
	/**
	 * Method which performs the actual callback.  Must be overridden.
	 * 
	 * @return Returns an object of type T_return; the result of the user callback.
	 */
	virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const = 0;
	
	/**
	 * Equality operator.
	 * 
	 * @param other  Pointer to another Slot.
	 * 
	 * @return true if this slot is equivalent to other; false otherwise
	 */
	virtual bool operator== (const Slot16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>* other) const = 0;
	
	/**
	 * Create a copy of this slot.
	 * 
	 * @return a new copy constructed instance of this slot object.
	 */
	virtual Slot16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>* clone() const = 0;

};



/**
 * Concrete slot class for calling a global function with 16 parameter(s).
 */
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13, typename T_arg14, typename T_arg15>
class SlotFunction16 : public Slot16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>
{
public:

	/**
	 * Convenience typedef of a regular function pointer.
	 */
	typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15);

	/**
	 * Convenience typedef to our base slot type.
	 */
	typedef Slot16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15> SlotBase;

	/**
	 * Constructor with function pointer initializer.
	 * 
	 * @param func   function pointer to be called by this slot.
	 */
	SlotFunction16 (FUNCTION_POINTER func):
		pFunction(func)
	{ 
	}

	/**
	 * Method which performs the callback of the global function.
	 * 
	 * @return The result of the user global function; type T_return.
	 */
	virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const
	{
		return pFunction(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
	}

	/**
	 * Equality operator.
	 * 
	 * @param other  slot object to compare against
	 * 
	 * @return true if this slot object is equivalent to other; false otherwise.
	 */
	virtual bool operator== (const SlotBase* other) const
	{
		const SlotFunction16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>* pother = dynamic_cast<const SlotFunction16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>*>(other);
		if ( pother )
		{
			return ( this->pFunction == pother->pFunction );
		}
		else
		{
			return false;
		}
	}

	/**
	 * Create a copy of this slot.
	 * 
	 * @return a new copy constructed instance of this slot object.
	 */
	virtual SlotBase* clone() const
	{
		SlotFunction16* copy = new SlotFunction16(pFunction);
		return copy;
	}

private:

	/**
	 * Actual function pointer.
	 */
	FUNCTION_POINTER pFunction;

};



/**
 * Concrete slot class for calling a member function with 16 parameter(s).
 */
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13, typename T_arg14, typename T_arg15>
class SlotMember16 : public Slot16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>
{
public:

	/**
	 * Convenience typedef to our base slot type.
	 */
	typedef Slot16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15> SlotBase;

	/**
	 * Constructor with object pointer and class member (pointer) initializers.
	 * 
	 * @param func   function pointer to be called by this slot.
	 */
	SlotMember16 (T_object* c, T_member m):
		pObject(c),
		pMember(m)
	{ 
	}

	/**
	 * Method which performs the callback of the object member.
	 * 
	 * @return The result of the user global function; type T_return.
	 */
	virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const
	{
		return (pObject->*pMember)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
	}

	/**
	 * Equality operator.
	 * 
	 * @param other  slot object to compare against
	 * 
	 * @return true if this slot object is equivalent to other; false otherwise.
	 */
	virtual bool operator== (const SlotBase* other) const
	{
		const SlotMember16<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>* pother = dynamic_cast<const SlotMember16<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>*>(other);
		if ( pother )
		{
			return ( this->pObject == pother->pObject && this->pMember == pother->pMember );
		}
		else
		{
			return false;
		}
	}

	/**
	 * Create a copy of this slot.
	 * 
	 * @return a new copy constructed instance of this slot object.
	 */
	virtual SlotBase* clone() const
	{
		SlotMember16* copy = new SlotMember16(pObject,pMember);
		return copy;
	}

private:

	/**
	 * Pointer to object of callback.
	 */
	T_object* pObject;
	
	/**
	 * Class member function pointer.
	 */
	T_member pMember;

};



/**
 * Signal with 16 parameter(s).
 */
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13, typename T_arg14, typename T_arg15>
class Signal16
{
public:

	/**
	 * Convenience typedef to a regular function pointer.
	 */
	typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15);

	/**
	 * Convenience typedef to our base slot type.
	 */
	typedef Slot16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15> SlotBase;

	/**
	 * Default constructor.
	 * 
	 * Initializes Slot list to empty.
	 */
	Signal16():
		head(0),
		emitting(false)
	{
	}

	/**
	 * Copy constructor.
	 * 
	 * Create a copy of other signal object's Slot list.
	 * 
	 * @param other  signal object to copy.
	 */
	Signal16(const Signal16& other)
	{
#if defined(_DEBUG)
		if ( emitting )
		{
			printf("ERROR!: Signal16<...> @ 0x%p is being copy constructed during Emit!\n",this);
		}
#endif

		// defer to assignment operator
		*this = other;
	}

	/**
	 * Assignment operator.
	 * 
	 * Create a copy of other signal object's Slot list.
	 * 
	 * @param other  signal object to copy.
	 * 
	 * @return reference to '*this' after copy.
	 */
	Signal16& operator= (const Signal16& other)
	{
#if defined(_DEBUG)
		if ( emitting )
		{
			printf("ERROR!: Signal16<...> @ 0x%p is being assigned during Emit!\n",this);
		}
#endif

		// destroy current slot list
		clear();

		// walk other slot list, copying as we go
		slotitem* current = other.head;
		while ( current )
		{
			// make a local copy of slot
			SlotBase* slotcopy = current->slot->clone();

			// add to our list
			insertslot(slotcopy,current->lifetime);

			// move to next item
			current = current->next;
		}

		return *this;
	}

	/**
	 * Destructor.
	 * 
	 * Release all heap and empty Slot list.
	 */
	~Signal16()
	{		
		// warn if slots still attached
#if defined(_DEBUG)
		if ( !Empty() )
		{
			printf("WARNING: Signal16<...> @ 0x%p destroyed with %d slots still connected!\n",this,Count());
		}
#endif

		// delete slots on list
		clear();
	}

	/**
	 * Determine if a signal is empty (no slots attached).
	 */
	bool Empty()
	{
		return ( head == 0 );
	}

	/**
	 * Count number of slots attached.
	 * 
	 * @return count of slots attached to this signal
	 */
	unsigned int Count()
	{
		unsigned int count   = 0;
		slotitem*    current = head;
		while ( current ) 
		{
			++count;
			current = current->next;
		}
		return count;
	}

	/**
	 * Connect to a slot.
	 * 
	 * @param slot   slot to connect to.
	 * @param lifetime number of times to signal slot before automatic removal.
	 * 
	 * @return true on success; false otherwise.
	 */
	bool Connect(const SlotBase& slot, int lifetime = -1)
	{
		return connect_slot(slot,lifetime);
	}

	/**
	 * Connect to a regular function pointer.
	 * 
	 * @param func   function pointer to callback.
	 * @param lifetime number of times to signal slot before automatic removal.
	 * 
	 * @return true on success; false otherwise.
	 */
	bool Connect(FUNCTION_POINTER func, int lifetime = -1)
	{
		return connect_function(func,lifetime);
	}

	/**
	 * Connect to a functor.
	 * 
	 * @param T_object type of object
	 * @param object pointer to functor object to callback.
	 * @param lifetime number of times to signal slot before automatic removal.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool Connect(T_object* object, int lifetime = -1)
	{
		return connect_member(object, &T_object::operator(),lifetime);
	}

	/**
	 * Connect to a member function.
	 * 
	 * @param T_object type of object
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to class method to callback to.
	 * @param lifetime number of times to signal slot before automatic removal.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool Connect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15), int lifetime = -1)
	{
		return connect_member(object, method,lifetime);
	}

	/**
	 * Connect to a const member function.
	 * 
	 * @param T_object type of object
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to class method to callback to.
	 * @param lifetime number of times to signal slot before automatic removal.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool Connect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const, int lifetime = -1)
	{
		return connect_member(object, method,lifetime);
	}

	/**
	 * Connect to a parent member function.
	 * 
	 * @param T_object type of object
	 * @param T_parent type of parent class
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to parent class method to callback to.
	 * @param lifetime number of times to signal slot before automatic removal.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object, typename T_parent>
	bool Connect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15), int lifetime = -1)
	{
		T_parent* ancestor = dynamic_cast<T_parent*>(object);
		if ( ancestor )
		{
			return connect_member(ancestor, method,lifetime);
		}
		else
		{
			return false;
		}
	}

	/**
	 * Connect to a const parent member function.
	 * 
	 * @param T_object type of object
	 * @param T_parent type of parent class
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to parent class method to callback to.
	 * @param lifetime number of times to signal slot before automatic removal.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object, typename T_parent>
	bool Connect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const, int lifetime = -1)
	{
		T_parent* ancestor = dynamic_cast<T_parent*>(object);
		if ( ancestor )
		{
			return connect_member(ancestor, method,lifetime);
		}
		else
		{
			return false;
		}
	}

	/**
	 * Disconnect from a slot.
	 * 
	 * @param slot   slot to disconnect from.
	 * 
	 * @return true on success; false otherwise.
	 */
	bool Disconnect(const SlotBase& slot)
	{
		return disconnect_slot(slot);
	}

	/**
	 * Disconnect from a regular function pointer.
	 * 
	 * @param func   function pointer to callback.
	 * 
	 * @return true on success; false otherwise.
	 */
	bool Disconnect(FUNCTION_POINTER func)
	{
		return disconnect_function(func);
	}

	/**
	 * Disconnect from a functor.
	 * 
	 * @param T_object type of object
	 * @param object pointer to functor object to callback.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool Disconnect(T_object* object)
	{
		return disconnect_member(object, &T_object::operator());
	}

	/**
	 * Disconnect from a member function.
	 * 
	 * @param T_object type of object
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool Disconnect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15))
	{
		return disconnect_member(object, method);
	}

	/**
	 * Disconnect from a const member function.
	 * 
	 * @param T_object type of object
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool Disconnect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const)
	{
		return disconnect_member(object, method);
	}

	/**
	 * Disconnect from a parent member function.
	 * 
	 * @param T_object type of object
	 * @param T_parent type of parent class
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to parent class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object, typename T_parent>
	bool Disconnect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15))
	{
		T_parent* ancestor = dynamic_cast<T_parent*>(object);
		if ( ancestor )
		{
			return disconnect_member(ancestor, method);
		}
		else
		{
			return false;
		}
	}

	/**
	 * Disconnect from a const parent member function.
	 * 
	 * @param T_object type of object
	 * @param T_parent type of parent class
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to parent class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object, typename T_parent>
	bool Disconnect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const)
	{
		T_parent* ancestor = dynamic_cast<T_parent*>(object);
		if ( ancestor )
		{
			return disconnect_member(ancestor, method);
		}
		else
		{
			return false;
		}
	}

	/**
	 * Disconnect all slots.
	 */
	void DisconnectAll()
	{
		clear();
	}

	/**
	 * Search for a connected slot.
	 * 
	 * @param slot   slot to connect to.
	 * 
	 * @return true on success; false otherwise.
	 */
	bool IsConnected(const SlotBase& slot)
	{
		return search_slot(slot);
	}

	/**
	 * Search for a connected regular function pointer.
	 * 
	 * @param func   function pointer to callback.
	 * 
	 * @return true on success; false otherwise.
	 */
	bool IsConnected(FUNCTION_POINTER func)
	{
		return search_function(func);
	}

	/**
	 * Search for a connected functor.
	 * 
	 * @param T_object type of object
	 * @param object pointer to functor object to callback.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool IsConnected(T_object* object)
	{
		return search_member(object, &T_object::operator());
	}

	/**
	 * Search for a connected member function.
	 * 
	 * @param T_object type of object
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool IsConnected(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15))
	{
		return search_member(object, method);
	}

	/**
	 * Search for a connected const member function.
	 * 
	 * @param T_object type of object
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object>
	bool IsConnected(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const)
	{
		return search_member(object, method);
	}

	/**
	 * Search for a connected parent member function.
	 * 
	 * @param T_object type of object
	 * @param T_parent type of parent class
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to parent class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object, typename T_parent>
	bool IsConnected(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15))
	{
		T_parent* ancestor = dynamic_cast<T_parent*>(object);
		if ( ancestor )
		{
			return search_member(ancestor, method);
		}
		else
		{
			return false;
		}
	}

	/**
	 * Search for a connected const parent member function.
	 * 
	 * @param T_object type of object
	 * @param T_parent type of parent class
	 * @param object   pointer to object to callback to.
	 * @param method   pointer to parent class method to callback to.
	 * 
	 * @return true on success; false otherwise.
	 */
	template <typename T_object, typename T_parent>
	bool IsConnected(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15) const)
	{
		T_parent* ancestor = dynamic_cast<T_parent*>(object);
		if ( ancestor )
		{
			return search_member(ancestor, method);
		}
		else
		{
			return false;
		}
	}

	/**
	 * Emit signal.
	 * 
	 * Calls all slots connected to this signal.
	 */
	void operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15)
	{
		Emit(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
	}

	/**
	 * Emit signal.
	 * 
	 * Calls all slots connected to this signal.
	 */
	void Emit(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7, T_arg8 a8, T_arg9 a9, T_arg10 a10, T_arg11 a11, T_arg12 a12, T_arg13 a13, T_arg14 a14, T_arg15 a15)
	{
		// if already emitting bail, disallow recursive emission
		if ( emitting )
		{
#if defined(_DEBUG)
			printf("WARNING: Signal16<...> @ 0x%p recursive Emit attempt\n",this);
#endif

			return;
		}

		// set emission flag
		emitting = true;

		// get pointer to first slot
		slotitem* current = head;
		slotitem* prev    = 0;

		// walk slot list, call all slots
		while ( current )
		{
			// call slot
			(*(current->slot))(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
			
			// is this current's last call?
			if ( current->lifetime != 1 )
			{
				// not current's last call, count and move forward normally
				
				// current has a valid lifetime?
				if ( current->lifetime > 0 )
				{
					// decrement call count
					--current->lifetime;
				}
				
				// move to next item
				prev    = current;
				current = current->next;
			}
			else
			{
				// this was current's last call, delete it from our slot list
				
				// save next item
				slotitem* next = current->next;
				
				// set list to skip over current element
				if ( prev )
				{
					// set prev's next to current's next
					prev->next = next;
				}
				else
				{
					// nothing previous, set head to next
					head = next;
				}
				
				// delete current element
				delete current->slot;
				delete current;
				
				// move to next item
				current = next;
			}
		} // while( current )

		// done emitting
		emitting = false;

		// now delete any slots we may have added during emission
		erasepending();
	}

private:

	/**
	 * Structure to hold a slot element (for linked list).
	 */
	typedef struct slotitem
	{
		SlotBase* slot;
		int       lifetime;
		slotitem* next;
		bool      erase;
	} slotitem;

	/**
	 * Head of our slot linked list.
	 */
	slotitem* head;

	/**
	 * true if we're emitting
	 */
	bool emitting;

	/**
	 * Insert a new slot at head of linked list.
	 */
	bool insertslot(const SlotBase* slot, int lifetime)
	{
		// check slot
		if ( !slot || lifetime == 0 )
		{
			return false;
		}

		// create a slot item
		slotitem* item = new slotitem;
		if ( !item )
		{
			return false;
		}

		// put slot in new item
		item->slot     = const_cast<SlotBase*>( slot );
		item->lifetime = lifetime;
		item->erase    = false;

		// add item to list
		item->next = head;
		head       = item;

		// success
		return true;
	}

	/**
	 * Mark a slot for erase (search using equality operator) from linked list.
	 */
	bool queueeraseslot(const SlotBase* slot)
	{
		slotitem* current  = head;

		while ( current ) 
		{
			if ( *current->slot == slot )
			{
				// found a match.  set list to skip over it
				current->erase = true;

				// done
				return true;
			}
			else
			{
				// no match, move to next item normally
				current  = current->next;
			}
		}

		// not found
		return false;
	}

	/**
	 * Remove any marked-for-erase slots.
	 */
	bool erasepending()
	{
		if ( !emitting )
		{
			slotitem* previous = 0;
			slotitem* current  = head;

			while ( current ) 
			{
				if ( current->erase )
				{
					// found something to delete.  set list to skip over it
					if ( previous )
					{
						previous->next = current->next;
					}
					else
					{
						head = current->next;
					}

					// now mark item for erasue
					delete current->slot;
					delete current;

					// done
					return true;
				}
				else
				{
					// no match, move to next item normally
					previous = current;
					current  = current->next;
				}
			}
		}

				// now delete item
		return false;
	}

	/**
	 * Remove a slot (using equality operator) from linked list.
	 */
	bool eraseslot(const SlotBase* slot)
	{
				// done
		if ( queueeraseslot(slot) )
		{
				// no match, move to next item normally
			return erasepending();
		}

		// not found
		return false;
	}

	/**
	 * Empty slot list.
	 */
	void clear()
	{
		slotitem* current = head;
		while ( current )
		{
			// remember next item
			slotitem* next = current->next;

			// delete current
			delete current->slot;
			delete current;

			// set to next 
			current = next;
		}

		// set our list to empty
		head = 0;
	}

	/**
	 * Add a function slot.
	 */
	bool connect_function(FUNCTION_POINTER func, int lifetime)
	{
		// create temp slot and attempt connect
		return connect_slot( SlotFunction16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>(func), lifetime );
	}

	/**
	 * Remove a function slot.
	 */
	bool disconnect_function(FUNCTION_POINTER func)
	{
		// create temp slot and attempt disconnect
		return disconnect_slot( SlotFunction16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>(func) );
	}

	/**
	 * Test to search for an equivalent slot already connected.
	 * 
	 * @return true if this slot is already connected
	 */
	bool search_function(FUNCTION_POINTER func)
	{
		// create temp slot and attempt disconnect
		return search_slot( SlotFunction16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>(func) );
	}

	/**
	 * Add a member function slot.
	 */
	template <typename T_object, typename T_member>
	bool connect_member(T_object* object, T_member method, int lifetime)
	{
		// create temp slot and attempt connect
		return connect_slot( SlotMember16<T_object, T_member, T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>(object, method), lifetime );
	}

	/**
	 * Remove a member function slot.
	 */
	template <typename T_object, typename T_member>
	bool disconnect_member(T_object* object, T_member method)
	{
		// create temp slot and attempt disconnect
		return disconnect_slot( SlotMember16<T_object, T_member, T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>(object, method) );
	}

	/**
	 * Test to search for an equivalent slot already connected.
	 * 
	 * @return true if this slot is already connected
	 */
	template <typename T_object, typename T_member>
	bool search_member(T_object* object, T_member method)
	{
		// create temp slot and search
		return search_slot( SlotMember16<T_object, T_member, T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>(object, method) );
	}

	/**
	 * Add a generic slot.
	 */
	bool connect_slot(const SlotBase& slot, int lifetime)
	{
		// create a new slot
		SlotBase* newslot = slot.clone();
		if ( !newslot )
		{
			return false;
		}

		// insert slot into list
		if ( !insertslot(newslot,lifetime) )
		{
			delete newslot;
			return false;
		}

		// success
		return true;
	}

	/**
	 * Remove a generic slot.
	 */
	bool disconnect_slot(const SlotBase& slot)
	{
		return eraseslot(&slot);
	}
	
	/**
	 * Tests to see if an equivalent slot is already connected.
	 *
	 * @return true if slot is already connected
	 */
	bool search_slot(const SlotBase& slot)
	{
		slotitem* current = head;
		while ( current )
		{
			if ( *current->slot == &slot )
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}

};



#endif // __signal16_h__


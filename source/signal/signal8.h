#ifndef __signal8_h__
#define __signal8_h__



#if defined(_DEBUG)
#	include <cstdio>
#endif



/**
 * Abstract base class for Slots with 8 parameter(s).
 */
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class Slot8
{ 
public:
	
	/**
	 * Method which performs the actual callback.  Must be overridden.
	 * 
	 * @return Returns an object of type T_return; the result of the user callback.
	 */
	virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const = 0;
	
	/**
	 * Equality operator.
	 * 
	 * @param other  Pointer to another Slot.
	 * 
	 * @return true if this slot is equivalent to other; false otherwise
	 */
	virtual bool operator== (const Slot8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>* other) const = 0;
	
	/**
	 * Create a copy of this slot.
	 * 
	 * @return a new copy constructed instance of this slot object.
	 */
	virtual Slot8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>* clone() const = 0;

};



/**
 * Concrete slot class for calling a global function with 8 parameter(s).
 */
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class SlotFunction8 : public Slot8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
public:

	/**
	 * Convenience typedef of a regular function pointer.
	 */
	typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7);

	/**
	 * Convenience typedef to our base slot type.
	 */
	typedef Slot8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> SlotBase;

	/**
	 * Constructor with function pointer initializer.
	 * 
	 * @param func   function pointer to be called by this slot.
	 */
	SlotFunction8 (FUNCTION_POINTER func):
		pFunction(func)
	{ 
	}

	/**
	 * Method which performs the callback of the global function.
	 * 
	 * @return The result of the user global function; type T_return.
	 */
	virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const
	{
		return pFunction(a0, a1, a2, a3, a4, a5, a6, a7);
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
		const SlotFunction8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>* pother = dynamic_cast<const SlotFunction8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>*>(other);
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
		SlotFunction8* copy = new SlotFunction8(pFunction);
		return copy;
	}

private:

	/**
	 * Actual function pointer.
	 */
	FUNCTION_POINTER pFunction;

};



/**
 * Concrete slot class for calling a member function with 8 parameter(s).
 */
template <class T_object, typename T_member, typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class SlotMember8 : public Slot8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
public:

	/**
	 * Convenience typedef to our base slot type.
	 */
	typedef Slot8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> SlotBase;

	/**
	 * Constructor with object pointer and class member (pointer) initializers.
	 * 
	 * @param func   function pointer to be called by this slot.
	 */
	SlotMember8 (T_object* c, T_member m):
		pObject(c),
		pMember(m)
	{ 
	}

	/**
	 * Method which performs the callback of the object member.
	 * 
	 * @return The result of the user global function; type T_return.
	 */
	virtual T_return operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const
	{
		return (pObject->*pMember)(a0, a1, a2, a3, a4, a5, a6, a7);
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
		const SlotMember8<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>* pother = dynamic_cast<const SlotMember8<T_object,T_member,T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>*>(other);
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
		SlotMember8* copy = new SlotMember8(pObject,pMember);
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
 * Signal with 8 parameter(s).
 */
template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class Signal8
{
public:

	/**
	 * Convenience typedef to a regular function pointer.
	 */
	typedef T_return (*FUNCTION_POINTER)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7);

	/**
	 * Convenience typedef to our base slot type.
	 */
	typedef Slot8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> SlotBase;

	/**
	 * Default constructor.
	 * 
	 * Initializes Slot list to empty.
	 */
	Signal8():
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
	Signal8(const Signal8& other)
	{
#if defined(_DEBUG)
		if ( emitting )
		{
			printf("ERROR!: Signal8<...> @ 0x%p is being copy constructed during Emit!\n",this);
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
	Signal8& operator= (const Signal8& other)
	{
#if defined(_DEBUG)
		if ( emitting )
		{
			printf("ERROR!: Signal8<...> @ 0x%p is being assigned during Emit!\n",this);
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
	~Signal8()
	{		
		// warn if slots still attached
#if defined(_DEBUG)
		if ( !Empty() )
		{
			printf("WARNING: Signal8<...> @ 0x%p destroyed with %d slots still connected!\n",this,Count());
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
	bool Connect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7), int lifetime = -1)
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
	bool Connect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const, int lifetime = -1)
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
	bool Connect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7), int lifetime = -1)
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
	bool Connect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const, int lifetime = -1)
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
	bool Disconnect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7))
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
	bool Disconnect(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const)
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
	bool Disconnect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7))
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
	bool Disconnect(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const)
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
	bool IsConnected(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7))
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
	bool IsConnected(T_object* object, T_return (T_object::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const)
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
	bool IsConnected(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7))
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
	bool IsConnected(T_object* object, T_return (T_parent::*method)(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7) const)
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
	void operator() (T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7)
	{
		Emit(a0, a1, a2, a3, a4, a5, a6, a7);
	}

	/**
	 * Emit signal.
	 * 
	 * Calls all slots connected to this signal.
	 */
	void Emit(T_arg0 a0, T_arg1 a1, T_arg2 a2, T_arg3 a3, T_arg4 a4, T_arg5 a5, T_arg6 a6, T_arg7 a7)
	{
		// if already emitting bail, disallow recursive emission
		if ( emitting )
		{
#if defined(_DEBUG)
			printf("WARNING: Signal8<...> @ 0x%p recursive Emit attempt\n",this);
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
			(*(current->slot))(a0, a1, a2, a3, a4, a5, a6, a7);
			
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
		return connect_slot( SlotFunction8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func), lifetime );
	}

	/**
	 * Remove a function slot.
	 */
	bool disconnect_function(FUNCTION_POINTER func)
	{
		// create temp slot and attempt disconnect
		return disconnect_slot( SlotFunction8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func) );
	}

	/**
	 * Test to search for an equivalent slot already connected.
	 * 
	 * @return true if this slot is already connected
	 */
	bool search_function(FUNCTION_POINTER func)
	{
		// create temp slot and attempt disconnect
		return search_slot( SlotFunction8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func) );
	}

	/**
	 * Add a member function slot.
	 */
	template <typename T_object, typename T_member>
	bool connect_member(T_object* object, T_member method, int lifetime)
	{
		// create temp slot and attempt connect
		return connect_slot( SlotMember8<T_object, T_member, T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(object, method), lifetime );
	}

	/**
	 * Remove a member function slot.
	 */
	template <typename T_object, typename T_member>
	bool disconnect_member(T_object* object, T_member method)
	{
		// create temp slot and attempt disconnect
		return disconnect_slot( SlotMember8<T_object, T_member, T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(object, method) );
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
		return search_slot( SlotMember8<T_object, T_member, T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(object, method) );
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



#endif // __signal8_h__


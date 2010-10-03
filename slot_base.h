#ifndef __slot_base_h__
#define __slot_base_h__

class slot_base
{
	public:

		slot_base ();  // constructor
		virtual ~slot_base (); // destructor

		/* Use compiler-generated copy constructor, assignment operator */

		bool operator== (const slot_base& other) const;

	protected:

		// a generic type to hold a pointer, virtual method function pointer, etc.
		struct data_container
		{
			// should be at least as large as the largest type you want
			// to store in one of these
			enum { SIZE_IN_WORDS = 4 };
			enum { SIZE_IN_BYTES = SIZE_IN_WORDS*sizeof(unsigned int) };

			// the actual storage space
			unsigned int data[SIZE_IN_WORDS];

			// an equality operator
			bool operator== (const data_container& other) const;

			// a method to set to empty (zero)
			void zero();
		};

		// number of pointers, etc. we'll track in this class
		enum { NUM_DATA_ITEMS = 2 };

		// storage for function pointers, etc. hoisted out of derivative slots
		data_container data[NUM_DATA_ITEMS];
};

#endif // __slot_base_h__


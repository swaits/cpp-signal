#include "slot_base.h"

		
bool slot_base::data_container::operator== (const slot_base::data_container& other) const
{
	// do a wordwise comparison
	for (int i=0;i<SIZE_IN_WORDS;++i)
	{
		if ( this->data[i] != other.data[i] )
		{
			return false;
		}
	}

	// must be a perfect match
	return true;
}
		
void slot_base::data_container::zero()
{
	// do a bytewise zeroing
	for (int i=0;i<SIZE_IN_WORDS;++i)
	{
		this->data[i] = 0;
	}
}

slot_base::slot_base ()
{
	for (int i=0;i<NUM_DATA_ITEMS;++i)
	{
		data[i].zero();
	}
}

slot_base::~slot_base ()
{
	// empty
}

bool slot_base::operator== (const slot_base& other) const
{
	// check each data item for inequality
	for (int i=0;i<NUM_DATA_ITEMS;++i)
	{
		if ( !(this->data[i] == other.data[i]) )
			return false;
	}
	
	// all data matched
	return true;
}


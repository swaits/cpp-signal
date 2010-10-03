#ifndef __horrible_cast_h__
#define __horrible_cast_h__


// horrible_union is used by {safe|dangerous}_horrible_cast to copy one arbitrary type to another
template <typename t_out, typename t_in>
union horrible_union
{
	t_in in;
	t_out out;
};


// dangerous_horrible_cast uses horrible_union to blindly copy one arbitrary type to another
//
// the data is zeroed out (via memset) before copying, in the case that he input type is smaller
// than the output type
template <typename t_out, typename t_in>
inline t_out dangerous_horrible_cast(t_in in)
{
	// instance the union
	horrible_union<t_out,t_in> data;

	// zero out the output part of the union (only if the input is actually smaller than the output)
	if ( sizeof(t_in) < sizeof(t_out) )
	{
		memset(&data.out,0,sizeof(data.out));
	}

	// copy the input into the union
	data.in = in;

	// return the output part out of the union
	return data.out;
}


// safe_horrible_cast is exactly like dangerous_horrible_cast, except it statically checks to make
// certain that the output type (t_out) is at least large enough (in size) to store an instance of
// the input type (t_in)
//
// note: if you use safe_horrible_cast to copy an instance of A to B, then you may safely use
// dangerous_horrible_cast to copy an instance of B back to A.
template <typename t_out, typename t_in>
inline t_out safe_horrible_cast(t_in in)
{
	// statically (compile-time) test if t_out is at least as big as t_in
	typedef int ERROR___horrible_union_is_too_small_to_store_input_type[(sizeof(t_in) <= sizeof(t_out)) ? 1 : -1];

	// now just do the regular horrible_cast
	return dangerous_horrible_cast<t_out,t_in>(in);
}


#endif // __horrible_cast_h__


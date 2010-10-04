#include <cstdio>
#include <cstring>


#include "slot.h"
#include "signal0.h"

class ParentFoo
{
public:
	virtual bool Bar()
	{
		printf("ParentFoo::Bar!\n");
		return false;
	}

	virtual ~ParentFoo()
	{
		// empty
	}
};

class Foo: public ParentFoo
{
public:
	bool Bar()
	{
		printf("Foo::Bar!\n");
		return true;
	}

	virtual ~Foo()
	{
		// empty
	}
};

Foo f;

bool somefunc()
{
	printf("some func\n");
	return true;
}

template <class T_class, typename T_method>
slot0_method<T_class,T_method>* make_slot(T_class* c, T_method m)
{
	return new slot0_method<T_class,T_method>(c,m);
}

int main(int argc, char** argv)
{
	slot0* s = make_slot(&f,&Foo::Bar);
	slot0* t = make_slot(&f,&ParentFoo::Bar);

	slot0_function<bool> x( somefunc );
	slot0* u = &x;

	if ( *s == *t )
		(*s)();

	(*u)();

	signal0 sig;
	sig.connect(&f,&Foo::Bar);
	sig();
}




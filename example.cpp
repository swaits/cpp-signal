#include <cstdio>
#include <cstring>


#include "signal.h"

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

bool somefunc()
{
	printf("some func\n");
	return true;
}

void anotherfunc(int x)
{
	printf("got %d\n",x);
}

int main(int argc, char** argv)
{
	Foo f;

	signal<bool> sig;
	sig.connect(&f,&Foo::Bar);
	sig.connect(&f,&ParentFoo::Bar);
	sig.connect(&somefunc);
	sig();

	signal<void,int> sigx;
	sigx.connect(&anotherfunc);
	sigx(12);
	sigx(999);
}
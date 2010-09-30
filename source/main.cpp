#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>



#include "Signal.h"



void Function()
{
	printf("Function()\n");
}

void Function1(int x)
{
	printf("Function1(%d)\n",x);
}

void Function5(int a,int b, int c, int d, int e)
{
	printf("Function5(%d,%d,%d,%d,%d)\n",a,b,c,d,e);
}



class Dummy
{
public:

	virtual void member()
	{
		printf("Dummy::member()\n");
	}

	void operator() ()
	{
		printf("Dummy::operator()()\n");
	}

	void member5(int a,int b, int c, int d, int e) const
	{
		printf("Dummy::member5(%d,%d,%d,%d,%d)\n",a,b,c,d,e);
	}

};



class DummyChild: public Dummy
{
public:

	virtual void member()
	{
		printf("DummyChild::member()\n");
	}
};



class OverloadedMembers
{
public:

	void member(int x)
	{
		printf("OverloadedMembers::member(%d)\n",x);
	}

	void member(int x, int y)
	{
		printf("OverloadedMembers::member(%d,%d)\n",x,y);
	}
};



class MySlot: public Signal<void>::SlotBase
{
public:

	MySlot(int id)
	{
		this->some_id = id;
	}

	virtual void operator() () const
	{
		printf("MySlot::operator() [some_id = %d]\n",some_id);
	}

	virtual bool operator== (const Slot0<void>* other) const
	{
		const MySlot* pother = dynamic_cast<const MySlot*>(other);
		if ( pother )
		{
			return this->some_id == pother->some_id;
		}
		else
		{
			return false;
		}
	}

	virtual Slot0<void>* clone() const
	{
		return new MySlot(some_id);
	}

private:

	int some_id;
};



MySlot Create_MySlot(int x)
{
	return MySlot(x);
}



int main()
{
	Signal<void> sig;
	Signal<void> sig_copy;
	Signal<void,int> sig1;
	Signal<void,int,int> sig2;
	Signal<void,int,int,int,int,int> sig5;
	Signal<void> count_test;

	assert( !count_test.IsConnected(Function) );
	count_test.Connect(Function,2);
	assert( count_test.IsConnected(Function) );
	count_test();
	count_test();
	count_test();

	OverloadedMembers bf;

	assert( !sig1.IsConnected(&bf,&OverloadedMembers::member) );
	assert( !sig2.IsConnected(&bf,&OverloadedMembers::member) );
	sig1.Connect(&bf,&OverloadedMembers::member);
	sig2.Connect(&bf,&OverloadedMembers::member);
	assert( sig1.IsConnected(&bf,&OverloadedMembers::member) );
	assert( sig2.IsConnected(&bf,&OverloadedMembers::member) );
	sig1(10);
	sig2(1,2);

	assert( !sig.IsConnected(Create_MySlot(1)) );
	sig.Connect(Create_MySlot(1));
	assert( sig.IsConnected(Create_MySlot(1)) );
	sig.Disconnect(Create_MySlot(1));
	assert( !sig.IsConnected(Create_MySlot(1)) );

	sig1.Connect(Function1);
	sig1(0);
	sig1(1);
	sig1(2);
	sig1(3);

	Dummy d;
	Dummy d2;
	DummyChild dc;

	sig5.Connect(Function5);
	sig5.Connect(&d,&Dummy::member5);
	sig5.Connect(&dc,&Dummy::member5);
	sig5(0,1,2,3,4);

	printf("\n---\n\n");
	sig.Connect(Function);

	sig.Connect(&d);
	sig.Connect(&d2);
	sig.Connect(&d,&Dummy::member);
	sig.Connect(&dc,&DummyChild::member);
	sig.Connect(&dc,&Dummy::member);
	sig.Connect(&dc);

	sig.Emit();
	
	printf("\n---\n\n");
	sig.Disconnect(Function);
	sig.Emit();
	
	printf("\n---\n\n");

	sig_copy = sig;
	sig_copy.Emit();

	return 0;
}



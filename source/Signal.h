#ifndef __Signal_h__
#define __Signal_h__



#include "signal/signal0.h"
#include "signal/signal1.h"
#include "signal/signal2.h"
#include "signal/signal3.h"
#include "signal/signal4.h"
#include "signal/signal5.h"
#include "signal/signal6.h"
#include "signal/signal7.h"
#include "signal/signal8.h"
#include "signal/signal9.h"
#include "signal/signal10.h"
#include "signal/signal11.h"
#include "signal/signal12.h"
#include "signal/signal13.h"
#include "signal/signal14.h"
#include "signal/signal15.h"
#include "signal/signal16.h"



struct nilarg;

template <typename T_return, typename T_arg0=nilarg, typename T_arg1=nilarg, typename T_arg2=nilarg, typename T_arg3=nilarg, typename T_arg4=nilarg, typename T_arg5=nilarg, typename T_arg6=nilarg, typename T_arg7=nilarg, typename T_arg8=nilarg, typename T_arg9=nilarg, typename T_arg10=nilarg, typename T_arg11=nilarg, typename T_arg12=nilarg, typename T_arg13=nilarg, typename T_arg14=nilarg, typename T_arg15=nilarg>
class Signal : 
	public Signal16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13, typename T_arg14>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14> : 
	public Signal15<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13> : 
	public Signal14<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12> : 
	public Signal13<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11> : 
	public Signal12<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10> : 
	public Signal11<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9> : 
	public Signal10<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8> : 
	public Signal9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> : 
	public Signal8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> : 
	public Signal7<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> : 
	public Signal6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4> : 
	public Signal5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3>
class Signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3> : 
	public Signal4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2>
class Signal<T_return, T_arg0, T_arg1, T_arg2> : 
	public Signal3<T_return, T_arg0, T_arg1, T_arg2>
{
};

template <typename T_return, typename T_arg0, typename T_arg1>
class Signal<T_return, T_arg0, T_arg1> : 
	public Signal2<T_return, T_arg0, T_arg1>
{
};

template <typename T_return, typename T_arg0>
class Signal<T_return, T_arg0> : 
	public Signal1<T_return, T_arg0>
{
};

template <typename T_return>
class Signal<T_return> : 
	public Signal0<T_return>
{
};


#endif // __Signal_h__

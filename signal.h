#ifndef __signal_h__
#define __signal_h__



#include "signal0.h"
#include "signal1.h"
#include "signal2.h"
#include "signal3.h"
#include "signal4.h"
#include "signal5.h"
#include "signal6.h"
#include "signal7.h"
#include "signal8.h"
#include "signal9.h"
#include "signal10.h"
#include "signal11.h"
#include "signal12.h"
#include "signal13.h"
#include "signal14.h"
#include "signal15.h"
#include "signal16.h"



struct nilarg;

template <typename T_return, typename T_arg0=nilarg, typename T_arg1=nilarg, typename T_arg2=nilarg, typename T_arg3=nilarg, typename T_arg4=nilarg, typename T_arg5=nilarg, typename T_arg6=nilarg, typename T_arg7=nilarg, typename T_arg8=nilarg, typename T_arg9=nilarg, typename T_arg10=nilarg, typename T_arg11=nilarg, typename T_arg12=nilarg, typename T_arg13=nilarg, typename T_arg14=nilarg, typename T_arg15=nilarg>
class signal :
	public signal16<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14, T_arg15>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13, typename T_arg14>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14> :
	public signal15<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13, T_arg14>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12, typename T_arg13>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13> :
	public signal14<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12, T_arg13>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11, typename T_arg12>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12> :
	public signal13<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11, T_arg12>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10, typename T_arg11>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11> :
	public signal12<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10, T_arg11>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9, typename T_arg10>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10> :
	public signal11<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9, T_arg10>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8, typename T_arg9>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9> :
	public signal10<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8, T_arg9>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_arg8>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8> :
	public signal9<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_arg8>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> :
	public signal8<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> :
	public signal7<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> :
	public signal6<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4> :
	public signal5<T_return, T_arg0, T_arg1, T_arg2, T_arg3, T_arg4>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2, typename T_arg3>
class signal<T_return, T_arg0, T_arg1, T_arg2, T_arg3> :
	public signal4<T_return, T_arg0, T_arg1, T_arg2, T_arg3>
{
};

template <typename T_return, typename T_arg0, typename T_arg1, typename T_arg2>
class signal<T_return, T_arg0, T_arg1, T_arg2> :
	public signal3<T_return, T_arg0, T_arg1, T_arg2>
{
};

template <typename T_return, typename T_arg0, typename T_arg1>
class signal<T_return, T_arg0, T_arg1> :
	public signal2<T_return, T_arg0, T_arg1>
{
};

template <typename T_return, typename T_arg0>
class signal<T_return, T_arg0> :
	public signal1<T_return, T_arg0>
{
};

template <typename T_return>
class signal<T_return> :
	public signal0<T_return>
{
};


#endif // __signal_h__

//===-------------------------- abort_message.h-----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef __ABORT_MESSAGE_H_
#define __ABORT_MESSAGE_H_

#include "cxxabi.h"

#include <vector>
#include <string>
#include <type_traits>

namespace utility
{
	template<typename T, typename = enable_if<!is_same<T, char>::value>::type>
	typename decltype(to_string(T{})) stringify(T && t)
	{
		return to_string(forward<T>(t));
	}

	template<typename T>
	typename enable_if<is_same<T, char>::value, string>::type stringify(T && t)
	{
		return string(1, t);
	}

	template<typename T>
	typename enable_if<!is_arithmetic<T>::value, string>::type stringify(T && t)
	{
		return string(forward<T>(t));
	}

	template<typename T, typename... Args>
	void convert(vector<string> &tab, size_t i, T && v, Args... && args)
	{
		tab[i] = stringify(forward<T>(v));
		convert(tab, i + 1, forward<Args>(args)...);
	}

	template<typename T,
		typename = enable_if<is_convertible<T, string>::value>::type>
		void convert(vector<string> &tab, size_t i, T && v)
	{
		tab[i] = stringify(forward<T>(v));
	}

	_LIBCXXABI_HIDDEN _LIBCXXABI_NORETURN void
		print_abort_message(vector<string> &v);
}

template<typename... Args>
void abort_message(Args... args)
{
	vector<string> val(sizeof...(Args));
	utility::convert(val, 0, forward<Args>(args)...);
	print_abort_message(val);
}

#endif


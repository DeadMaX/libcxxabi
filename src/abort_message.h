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
	template<typename T>
	typename std::enable_if<std::is_same<T, char>::value, std::string>::type stringify(T && t)
	{
		return std::string(1, t);
	}

	template<typename T>
	typename std::enable_if<!std::is_arithmetic<T>::value, std::string>::type stringify(T && t)
	{
		return std::string(std::forward<T>(t));
	}

	template<std::size_t i, typename T>
	void convert(std::vector<std::string> &tab, T v)
	{
		tab[i] = stringify(std::forward<T>(v));
	}

	template<std::size_t i, typename T, typename... Args>
	void convert(std::vector<std::string> &tab, T v, Args... args)
	{
		tab[i] = stringify(std::forward<T>(v));
		convert<i + 1, Args...>(tab, std::forward<Args>(args)...);
	}

	_LIBCXXABI_HIDDEN _LIBCXXABI_NORETURN void
		print_abort_message(std::vector<std::string> &v);
}

template<typename... Args>
void abort_message(Args... args)
{
	std::vector<std::string> val(sizeof...(Args));
	utility::convert<0, Args...>(val, std::forward<Args>(args)...);
	utility::print_abort_message(val);
}

#endif


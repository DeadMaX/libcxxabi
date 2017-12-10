//===------------------------ cxa_aux_runtime.cpp -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//
// This file implements the "Auxiliary Runtime APIs"
// http://mentorembedded.github.io/cxx-abi/abi-eh.html#cxx-aux
//===----------------------------------------------------------------------===//

#include "cxxabi.h"
#include <new>
#include <typeinfo>

namespace __cxxabiv1 {
	_LIBCXXABI_NORETURN _LIBCXXABI_HIDDEN static inline void __thow_bad_cast()
	{
#ifndef _LIBCXXABI_NO_EXCEPTIONS
		throw std::bad_cast();
#else
		std::terminate();
#endif
	}

	_LIBCXXABI_NORETURN _LIBCXXABI_HIDDEN static inline void __thow_bad_typeid()
	{
#ifndef _LIBCXXABI_NO_EXCEPTIONS
		throw std::bad_typeid();
#else
		std::terminate();
#endif
	}

	_LIBCXXABI_NORETURN _LIBCXXABI_HIDDEN static inline void __thow_bad_array_new_length()
	{
#ifndef _LIBCXXABI_NO_EXCEPTIONS
		throw std::bad_array_new_length();
#else
		std::terminate();
#endif
		}

extern "C" {
_LIBCXXABI_FUNC_VIS _LIBCXXABI_NORETURN void __cxa_bad_cast(void) {
	__thow_bad_cast();
}

_LIBCXXABI_FUNC_VIS _LIBCXXABI_NORETURN void __cxa_bad_typeid(void) {
	__thow_bad_typeid();
}

_LIBCXXABI_FUNC_VIS _LIBCXXABI_NORETURN void
__cxa_throw_bad_array_new_length(void) {
	__thow_bad_array_new_length();
}
} // extern "C"
} // abi

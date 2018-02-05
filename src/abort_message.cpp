//===------------------------- abort_message.cpp --------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//


#include "abort_message.h"
#include <iostream>

namespace utility
{

void
print_abort_message(std::vector<std::string> &v)
{
	for (const auto &i : v)
		std::cerr << i;
	std::cerr << std::endl;
    std::terminate();
}

}

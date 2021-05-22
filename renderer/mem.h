#pragma once

#include <vector>

namespace mem
{
	uintptr_t get_ptr(uintptr_t ptr, std::vector<unsigned int> offsets);
}
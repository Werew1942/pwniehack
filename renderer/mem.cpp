#include "mem.h"

namespace mem
{
	uintptr_t get_ptr(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = ptr;
		for (size_t i = 0; i < offsets.size(); i++)
		{
			addr = *(uintptr_t*)(addr);
			if (addr == 0)
			{
				return 0;
			}

			addr += offsets[i];
		}
		return addr;
	}
}
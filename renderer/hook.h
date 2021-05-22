#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

class hook
{
public:
	bool setup(uintptr_t to_hook, uintptr_t hook, size_t len, uintptr_t*& org);
	void disable();
private:
	uintptr_t addr_to_hook;
	uintptr_t trampoline;
	size_t len;
};


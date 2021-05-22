#include "hook.h"

bool detour(uintptr_t addr, uintptr_t func, size_t len)
{
	if (len < 5)
		return false;

	DWORD prot;
	VirtualProtect(reinterpret_cast<void*>(addr), len, PAGE_EXECUTE_READWRITE, &prot);

	uintptr_t rel = (func - addr) - 5;
	std::cout << "Jmp Rel Addr: 0x" << std::hex << rel << std::dec << std::endl;

	*(BYTE*)addr = 0xE9; // jmp
	*(uintptr_t*)(addr + 1) = rel;

	DWORD temp;
	VirtualProtect(reinterpret_cast<void*>(addr), len, prot, &temp);

	return true;
}

bool hook::setup(uintptr_t to_hook, uintptr_t hook, size_t len, uintptr_t*& org)
{
	if (len < 5)
		return false;

	org = reinterpret_cast<uintptr_t*>(VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
	
	// set class variables
	this->trampoline = reinterpret_cast<uintptr_t>(org);
	this->addr_to_hook = to_hook;
	this->len = len;

	memcpy_s(org, len, reinterpret_cast<BYTE*>(to_hook), len);

	uintptr_t rel = to_hook - reinterpret_cast<uintptr_t>(org) - 5;

	*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(org) + len) = 0xE9; // jmp
	*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(org) + len + 1) = rel;

	detour(to_hook, hook, len);

	return true;
}

void hook::disable()
{
	DWORD prot;
	VirtualProtect(reinterpret_cast<void*>(addr_to_hook), len, PAGE_EXECUTE_READWRITE, &prot);

	memcpy_s(reinterpret_cast<void*>(addr_to_hook), len, reinterpret_cast<void*>(trampoline), len);
	VirtualFree(reinterpret_cast<void*>(trampoline), len, MEM_DECOMMIT);

	DWORD temp;
	VirtualProtect(reinterpret_cast<void*>(addr_to_hook), len, prot, &temp);
}

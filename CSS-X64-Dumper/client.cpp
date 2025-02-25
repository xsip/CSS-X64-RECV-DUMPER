#include "client.h"
#include "memory.h"

ClientClass* VClient017::GetAllClasses() {
	int index = -1;

	for (int i = 0; i < 16; i++)
	{
		auto pdwClient = *(uintptr_t**)this;
		std::uint8_t* function = (std::uint8_t*)pdwClient[i];
		if (function[0] == 0x48 && function[7] == 0xC3) // currentIndex: 8
		{
			// printf("FOUND!! %i | 0x%p\n", i, function);
			index = i;
			break;
		}
	}

	if (index == -1)
		return nullptr;

	typedef ClientClass* (__thiscall* tGetAllClasses)(void*);
	tGetAllClasses pGetAllClasses = g_Memory.getvfunc<tGetAllClasses>(this, index);

	if (!pGetAllClasses)
		return nullptr;

	return pGetAllClasses(class_ptr_);
}

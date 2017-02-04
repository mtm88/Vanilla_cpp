#pragma once
#include "Wowtypes.h"

inline uint64 GetLocalPlayerGuid()
{
	if (*(int*)(0x00B41414))
		return *(uint64*)(*(int*)(0x00B41414) + 0xC0);
	return 0;
}	

inline int GetLocalPlayer()
{	
	uint64 lpguid = GetLocalPlayerGuid();
	return lpguid? ((int(__fastcall*)(int, const char*, uint64, int))0x00468460)(TYPEMASK_PLAYER, nullptr, lpguid, 0) : 0;
}

inline int GetObjectByGuidTypeCheck(uint64 guid, int typemask = -1)
{
	return  guid ? ((int(__fastcall*)(int, const char*, uint64, int))0x00468460)(typemask, nullptr, guid, 0) : 0;
}

inline int PerformanceCount() { return ((int(__cdecl*)())0x0042C010)(); }

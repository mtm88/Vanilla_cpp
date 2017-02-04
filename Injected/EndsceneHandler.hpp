#pragma once
#include <map>
#include <string>
#include <d3d9.h>
#include "..\Microsoft DirectX SDK2010\Include\d3dx9core.h"
#include "Memory\Detour.hpp"
#include "Memory\Patch.hpp"
#include "Util\Timer.hpp"
#include "Util\Helpers.hpp"
#include "Lua\Lua.hpp"
#include "WowStuff\WowFuncs.hpp"
#include "Objects\Spell.hpp"
#include "Routines\PaladinLeveling.hpp"
#include "Graphics.hpp"
#include "Pather.hpp"

bool shouldRemoveEndSceneInjection{};
bool endSceneUnhooked{};
std::map<std::string, MemoryOperation*> g_memops{};
bool should_exit{};
bool do_something{};

int frameCount = 0;
Graphics* graph = nullptr;
timer afk_timer;
int dummy_counter;

inline void mrint(const std::string name, const std::string value)
{
	if (graph == nullptr)
		return;

	std::string line = name + " = " + value;
	graph->AddTextLine(line);
}

//---------------- END SCENE DETOUR ------------------
//int __stdcall EndSceneDetour(int device)
int __fastcall EndSceneDetour(int s_device, int EDX_Dummy)	//is a __thiscall
{
	if (*(int*)(s_device + 0x3A38))
	{

		if (frameCount % 30 == 0)
			printf(".");

		if (frameCount == 0)
			chat("_vanilla_cpp started.");

		if (afk_timer.elapsedTime() > 150)
		{
			afk_timer.start();
			*(int*)0x00CF0BC8 = PerformanceCount();
		}

		OM_Pulse();

		int device = *(int*)(s_device + 0x38A8);
		if (graph == nullptr && device)
			graph = new Graphics();

		graph->Pulse(device);

		if (me)
		{

#pragma region TestRegion

			// here is an area for random tests
			if (do_something)
			{
				PathTest(me->Coords());

				++dummy_counter;
				printf("player pointer = %X\n", me->addr);
				chat("okok");
				do_something = false;
			}

			auto sp = Spell("Chimera Shot");

			/*mrint("IsAutoshooting", BoolToString(me->IsAutoshootingH()));
			mrint("GetAutoshooting", std::to_string(me->GetAutoshootingH()));*/

			if (target)
			{
				//mrint("target", target->Name());
			}
#pragma endregion

		}

		//Common();

		frameCount++;
	}

	//-------- return to the original function (and remove injection if needed) --------
	auto det = g_memops["EndSceneCall"];
	det->Restore();
	//int res = ((int(__stdcall*)(int))det->target)(device);
	int res = ((int(__thiscall*)(int))det->target)(s_device);
	if (shouldRemoveEndSceneInjection)
	{
		chat("Removing EndSceneCall injection");
		auto it = g_memops.find("EndSceneCall");
		delete it->second;
		g_memops.erase(it);

		if (graph != nullptr)
			delete graph;

		endSceneUnhooked = true;
	}
	else
	{
		det->Apply();
	}
	return res;
}

int __stdcall ResetDetour(int device, int pp)
{
	printf("\nResetDetour\n");
	chat("ResetDetour");

	if (graph != nullptr)
		graph->ReleaseFont();

	//---------------- return to the original function ----------------
	auto det = g_memops["Reset"];
	det->Restore();
	int res = ((int(__stdcall*)(int, int))det->target)(device, pp);
	det->Apply();
	return res;
}
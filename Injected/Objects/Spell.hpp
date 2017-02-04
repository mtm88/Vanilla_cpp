#pragma once

#include "..\WowStuff\WowFuncs.hpp"
#include "..\WowStuff\WowClientDB.hpp"

std::map<int, timer> casted;

inline auto GetSpellSlotBySpellName(const char* spell, int is_pet)
{
	return ((int(__fastcall*)(const char*, int))0x004B3950)(spell, is_pet);
}

inline auto GetKnownSpell(const char* spell)
{
	auto slot = GetSpellSlotBySpellName(spell, 0);			//0 - is_pet = false
	return *(int*)(0x00B700F0 + slot * 4);					//SpellBookKnownSpellsPlayer
}

class Spell
{
public:
	int id;
	SpellRec record;
	const char* name;

	Spell() :id{}, name{} {}

	Spell(int arg_id) :id{ arg_id }
	{			
		record = *(SpellRec*)((int)ClientDB::Spell + 8 + id * 4);
		name = record.SpellName[0];
	}	

	Spell(const char* arg_name)
	{	
		id = GetKnownSpell(arg_name);
		record = *(SpellRec*)((int)ClientDB::Spell + 8 + id * 4);
		name = record.SpellName[0];
	}	

	bool Cast(uint64 at_guid, int itemAddr = 0)
	{
		if (!at_guid)
			return false;

		if (casted.find(id) != casted.end() && casted[id].elapsedTime() < 0.2)
			return false;

		casted[id] = timer();

		return ((bool(__fastcall*)(int, int, uint64))0x006E5A90)(id, itemAddr, at_guid);
	}

	bool InRange(uint64 from_guid)
	{
		if (!from_guid)
			return false;

		return ((bool(__fastcall*)(int, SpellRec&, uint64, int))(0x006E4440))(GetLocalPlayer(), record, from_guid, 0);
	}		

	float CoolDown()
	{
		int start = 0;
		int duration = 0;
		bool isReady = false;

		((bool(__fastcall*)(int, bool, int&, int&, bool&))(0x006E2EA0))(id, /*isPet*/ false, duration, start, isReady);

		int result = start + duration - PerformanceCount();
		return isReady ? (result > 0 ? result / 1000.0f : 0) : FLT_MAX;
	}

	bool IsReady() { return CoolDown() <= 0; }		

	bool IsUsable()
	{
		bool noMana = false;
		return ((bool(__fastcall*)(SpellRec&, bool&))(0x006E3D60))(record, noMana);
	}

	bool HasRange(int pet_addr = 0)
	{
		int addr = pet_addr ? pet_addr : GetLocalPlayer();
		float min{}, max{};
		((bool(__fastcall*)(int, int, float&, float&, int))0x006E3480)(addr, id, min, max, 0);
		return min > 0 || max > 0;
	}

	bool CanUse(uint64 at_guid, bool castedTimeCheck = true)
	{
		if (!at_guid)
			return false;

		if (castedTimeCheck
			&& (casted.find(id) != casted.end())
			&& casted[id].elapsedTime() < 0.2)
			return false;

		return (IsUsable() 
			&& IsReady()
			&& (!HasRange() || InRange(at_guid)));		// && unit->InLos());  put this guy in Unit class
	}	

	bool Use(uint64 at_guid)
	{
		return CanUse(at_guid) ? Cast(at_guid) : false;
	}
};
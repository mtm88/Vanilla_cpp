#pragma once
#include "Player.hpp"

timer last_petattack;

class LocalPlayer :public Player
{
public:
	LocalPlayer(int pointer) :Player(pointer) {}		
	
	/*bool IsInInstance() const
	{
		int cur_map_id = *(int*)0x00AB63BC;
		int map = db_tables[ClientDB::Map].GetRowPtr(cur_map_id);
		if (!map)
			return false;
		int instance_type = *(int*)(map + 2 * 4);
		return instance_type != 0;
	}*/

	/*bool IsAutoshootingH() const { return addr? *(int*)(addr + 0x1858) == 6 : false; }

	int GetAutoshootingH() const { return addr ? *(int*)(addr + 0x1858) : 0; }*/

	auto GetAutoattack() const { return *(int*)(addr + 3144); }

	auto AutoRepeatSpellId() const { return *(int*)0x00CEAC30; }
	auto IsAutoRepeatSpell(const char* name) const { return GetKnownSpell(name) == AutoRepeatSpellId(); }

	auto CastingSpellId() const { return *(int*)0x00CECA88; }
	auto CastingSpell() const { return Spell(CastingSpellId()); }

	auto GetSpeed() const { return *(float*)(addr + 0xA34); }
	auto SetSpeed(const float speed)
	{
		*(float*)(addr + 0xA34) = speed;	//speed
		*(float*)(addr + 0xA3C) = speed;	//swimming speed
	}

	auto StopCasting()
	{
		((void(__fastcall*)(int, int, int))0x006E4940)(1, 0, SPELL_FAILED_ERROR);
		return false;
	}

	auto StopCasting(const char* spell)
	{
		if (CastingSpellId() == GetKnownSpell(spell))
			StopCasting();
		return false;
	}

	auto StopAutoRepeat()
	{
		if (AutoRepeatSpellId())
			((void(__cdecl*)())0x006EA080)();
		return false;
	}

	auto SpellPendingId() const { return *(int*)(0x00CECA88); }

	auto SpellPendingName() const
	{
		auto sp = Spell(SpellPendingId());
		return std::string(sp.name);
	}
	
	//bool SendPetAction(Unit* unit, int action)
	//{
	//	if (!unit || !HavePet())
	//		return false;

	//	int _action = action;
	//	uint64 guid = unit->Guid();

	//	((void(__cdecl*)(int&, uint64&, int))0x005D4210)(action, guid, 1);
	//	return true;
	//}

	//bool PetAttack(Unit* unit)
	//{
	//	if (HavePet() && Pet()->Target() == unit)
	//		return false;
	//	if (last_petattack.elapsedTime() < 0.1)
	//		return false;
	//	last_petattack.start();
	//	int action = 0x07000002;        //petattack     
	//	return SendPetAction(unit, action);
	//}	
};
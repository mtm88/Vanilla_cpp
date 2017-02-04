#pragma once
#include "Objects\LocalPlayer.hpp"
#include "Objects\Container.hpp"
#include "Objects\GameObject.hpp"
#include "Objects\Corpse.hpp"
#include "Objects\DynamicObject.hpp"
#include "EndSceneHandler.hpp"

std::vector<GameObject*> gameobjects{};
std::vector<Item*> items{};
std::vector<Unit*> units{};
std::vector<Player*> players{};
std::map<uint64, Object*> objects{};

LocalPlayer* me{};
Unit* target{};
Unit* pet{};

uint64 playerGuid{};
uint64 targetGuid{};

inline CurMgr* ClntCurMgr() { return *(CurMgr**)0x00B41414; }
inline auto GetTargetGuid() { return *(uint64*)0x00B4E2D8; }
inline auto GetObjectByGuid(uint64 guid) { return objects[guid]; }

// -----------------------------------  P u l s e ------------------------------------------
auto EnumVisibleObjects()
{
	auto s_curMgr = ClntCurMgr();
	auto addr = s_curMgr->firstObj;

	if (addr & 1 || !addr)
		addr = 0;
	while (!(addr & 1) && addr)
	{		
		auto type = *(int*)(addr + 0x14);
		auto guid = *(uint64*)(addr + 0x30);

		if (type == TYPEID_PLAYER)
		{
			if (guid == playerGuid)
			{
				me = new LocalPlayer(addr);
				objects[guid] = me;
				if (guid == targetGuid)
				{
					target = me;
				}
			}
			else
			{
				auto pl = new Player(addr);
				units.push_back(pl);
				players.push_back(pl);
				objects[guid] = pl;
				if (guid == targetGuid)
				{
					target = pl;
				}
			}
		}
		else if (type == TYPEID_UNIT)
		{
			auto uni = new Unit(addr);
			objects[guid] = uni;
			if (uni->GetCreatureType() != CREATURE_TYPE_CRITTER)
			{
				units.push_back(uni);
			}
			if (guid == targetGuid)
			{
				target = uni;
			}
		}
		else if (type == TYPEID_CONTAINER)
		{
			auto con = new Container(addr);
			items.push_back(con);
			objects[guid] = con;
		}
		else if (type == TYPEID_ITEM)
		{
			auto ite = new Item(addr);
			items.push_back(ite);
			objects[guid] = ite;
		}
		else if (type == TYPEID_GAMEOBJECT)
		{
			auto go = new GameObject(addr);
			gameobjects.push_back(go);
			objects[guid] = go;
		}
		else if (type == TYPEID_CORPSE)
		{
			auto cor = new WoWCorpse(addr);
			objects[guid] = cor;
		}
		else if (type == TYPEID_DYNAMICOBJECT)
		{
			auto dyno = new DynamicObject(addr);
			objects[guid] = dyno;
		}
		else
		{
			auto ob = new Object(addr);
			objects[guid] = ob;
		}

		addr = *(int*)(addr + 4 + s_curMgr->nextObj);
	}
}

void OM_Pulse()
{
	for (auto& obj : objects)
		delete obj.second;	
	
	me = nullptr;
	target = nullptr;

	gameobjects.clear();
	items.clear();
	units.clear();
	players.clear();
	objects.clear();
	
	if(GetLocalPlayer() == 0) 
		return;

	playerGuid = GetLocalPlayerGuid();
	targetGuid = GetTargetGuid();

	EnumVisibleObjects();	
}

//--------------------------------- G R O U P ----------------------------------------

inline auto PartyCount()
{
	int result{};
	int i{};
	do
	{
		if ((*(uint64*)(0x00BC6F48 + i * 8 + 4) | *(uint64*)(0x00BC6F48 + i * 8)) != 0)
			++result;
		++i;
	} while (i < 4);
	return result;
}

inline auto Party()
{
	std::vector<Player*> party{};

	for (int i = 0; i != 4; ++i)
	{
		auto guid = *(uint64*)(0x00BC6F48 + i * 8);    //0x00BC6F48 - party array
		if (guid)
		{
			auto player = (Player*)GetObjectByGuid(guid);
			if (player)
				party.push_back(player);
		}
	}
	return party;
}

inline auto RaidCount() { return *(int*)0x00B713E0; }

inline auto Raid()
{
	std::vector<Player*> raid{};

	auto count = *(int*)0x00B713E0;

	for (int i = 0; i != count; ++i)					//0x00B713E0 - raid count
	{
		auto guid = *(uint64*)(0x00B712A8 + i * 8);		//0x00B712A8 - Raid Array
		if (guid)
		{
			auto player = (Player*)GetObjectByGuid(guid);
			if (player)
				raid.push_back(player);
		}
	}
	return raid;
}

inline auto RaidOrParty()
{
	if (RaidCount())
		return Raid();
	else if (PartyCount())
		return Party();
	else
		return std::vector<Player*>();
}

inline auto PartyLeader() { return (Player*)GetObjectByGuid(*(uint64*)(0x00BC75F8)); }
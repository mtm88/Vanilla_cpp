#pragma once
#include "Object.hpp"

class GameObject : public Object
{
public:
	GameObject(int pointer)	:Object(pointer) {}

	auto CreatedBy(){ return GetDescriptor<uint64>(OBJECT_FIELD_CREATED_BY); }

	auto Hooked() const { return *(byte*)(addr + 0x27C); }

	auto DisplayId(){ return GetDescriptor<int>(GAMEOBJECT_DISPLAYID); }

	auto Flags(){ return GetDescriptor<int>(GAMEOBJECT_FLAGS); }

	auto Faction(){ return GetDescriptor<int>(GAMEOBJECT_FACTION); }
	
	auto Level(){ return GetDescriptor<int>(GAMEOBJECT_LEVEL); }

	auto Locked(){ return (Flags() & GO_FLAG_LOCKED) > 0; }

	auto InUse(){ return (Flags() & GO_FLAG_IN_USE) > 0; }

	auto IsTransport(){ return (Flags() & GO_FLAG_TRANSPORT) > 0; }

	auto CreatedByMe(){ return CreatedBy() == GetLocalPlayerGuid(); }
};
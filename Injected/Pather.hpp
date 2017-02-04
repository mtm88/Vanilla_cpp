#pragma once
#include<sstream>
#include<iomanip>
#include "WowStuff\Wowtypes.h"
#include "Lua\Lua.hpp"
#include "..\Detour\Include\DetourNavMesh.h"
#include "..\Detour\Include\DetourNavMeshQuery.h"

const float TILESIZE = 533.33333f;

struct MmapTileHeader
{
	uint32 mmapMagic;
	uint32 dtVersion;
	uint32 mmapVersion;
	uint32 size;
	bool usesLiquids : 1;
};

inline auto PathTest(C3Vector start)
{
	std::string fileName = "D:\\MANGOS_ZERO\\server_build\\bin\\Debug\\mmaps\\000.mmap";

	FILE* file = fopen(fileName.c_str(), "rb");
	if (!file)
	{
		chat("Could not open mmap file " + fileName);
		return false;
	}
	dtNavMeshParams params;
	size_t file_read = fread(&params, sizeof(dtNavMeshParams), 1, file);
	if (file_read <= 0)
	{
		chat("Failed to load mmap 1 from file " + fileName);
		fclose(file);
		return false;
	}
	fclose(file);

	dtNavMesh* mesh = dtAllocNavMesh();
	dtStatus dtResult = mesh->init(&params);
	if (dtStatusFailed(dtResult))
	{
		dtFreeNavMesh(mesh);
		chat("Failed to initialize dtNavMesh for mmap 1 from file " + fileName);
		return false;
	}

	int x = (int)(32 - start.x / TILESIZE);
	int y = (int)(32 - start.y / TILESIZE);

	fileName = "D:\\MANGOS_ZERO\\server_build\\bin\\Debug\\mmaps\\000";
	fileName = string_format(fileName + "%02i%02i.mmtile", x, y);

	file = fopen(fileName.c_str(), "rb");
	if (!file)
	{
		chat("ERROR: MMAP:loadMap: Could not open mmtile file " + fileName);
		return false;
	}

	// read header
	MmapTileHeader fileHeader;
	file_read = fread(&fileHeader, sizeof(MmapTileHeader), 1, file);

	if (file_read <= 0)
	{
		chat("MMAP:loadMap: Could not load .mmtile" + std::to_string(x) + ", " + std::to_string(y));
		fclose(file);
		return false;
	}

	unsigned char* data = (unsigned char*)dtAlloc(fileHeader.size, DT_ALLOC_PERM);

	size_t result = fread(data, fileHeader.size, 1, file);
	if (!result)
	{
		chat("MMAP:loadMap: Bad header or data in .mmtile" + std::to_string(x) + ", " + std::to_string(y));
		fclose(file);
		return false;
	}

	fclose(file);

	dtMeshHeader* header = (dtMeshHeader*)data;
	dtTileRef tileRef = 0;

	// memory allocated for data is now managed by detour, and will be deallocated when the tile is removed
	dtResult = mesh->addTile(data, fileHeader.size, DT_TILE_FREE_DATA, 0, &tileRef);
	if (dtStatusFailed(dtResult))
	{
		chat("MMAP:loadMap: Could not load .mmtile into navmesh" + std::to_string(x) + ", " + std::to_string(y));
		dtFree(data);
		return false;
	}

	// allocate mesh query
	dtNavMeshQuery* query = dtAllocNavMeshQuery();
	auto res1 = query->init(mesh, 1024);
	if (dtStatusFailed(res1))
	{
		dtFreeNavMeshQuery(query);
		chat("MMAP:GetNavMeshQuery: Failed to initialize dtNavMeshQuery for mapId %03u instanceId %u");
		return false;
	}

	int tx = 0;
	int ty = 0;
	float startPoint[3] = { start.y, start.z, start.x };

	mesh->calcTileLoc(startPoint, &tx, &ty);
	if (!(mesh->getTileAt(tx, ty, 0) != NULL))
	{
		chat("no tile");
	}

	float distToStartPoly = 0;


	float extents[3] = { 5.0f, 5.0f, 5.0f };    // bounds of poly search area
	float closestPoint[3] = { 0.0f, 0.0f, 0.0f };
	dtPolyRef polyRef = 0;
	dtQueryFilter filter;
	filter.setIncludeFlags(0x81);	//(NAV_GROUND | NAV_WATER);
	filter.setExcludeFlags(0);

	if (dtStatusSucceed(query->findNearestPoly(startPoint, extents, &filter, &polyRef, closestPoint)) && polyRef != 0)
	{
		chat("yeeeee!");
	}

	return true;
}
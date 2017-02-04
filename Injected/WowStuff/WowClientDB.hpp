#pragma once

#include <map>

enum class ClientDB
{
	AnimationData = 0xC0E06C,
	AreaPOI = 0xC0E058,
	AreaTable = 0xC0E044,
	AreaTrigger = 0xC0E030,
	AttackAnimKits = 0xC0E01C,
	AttackAnimTypes = 0xC0E004,
	AuctionHouse = 0xC0DFF0,
	BankBagSlotPrices = 0xC0DFDC,
	CameraShakes = 0xC0DFC8,
	Cfg_Categories = 0xC0DFB4,
	Cfg_Configs = 0xC0DFA0,
	CharBaseInfo = 0xC0DF8C,
	CharHairGeosets = 0xC0DF78,
	CharSections = 0xC0DF64,
	CharStartOutfit = 0xC0DF50,
	CharVariations = 0xC0DF3C,
	CharacterFacialHairStyles = 0xC0DF28,
	ChatChannels = 0xC0DF14,
	ChatProfanity = 0xC0DF00,
	ChrClasses = 0xC0DEEC,
	ChrRaces = 0xC0DED8,
	CinematicCamera = 0xC0DEC4,
	CinematicSequences = 0xC0DEB0,
	CreatureDisplayInfo = 0xC0DE88,
	CreatureDisplayInfoExtra = 0xC0DE9C,
	CreatureFamily = 0xC0DE74,
	CreatureModelData = 0xC0DE60,
	CreatureSoundData = 0xC0DE4C,
	CreatureSpellData = 0xC0DE38,
	CreatureType = 0xC0DE24,
	DeathThudLookups = 0xC0DE10,
	DurabilityQuality = 0xC0DDE8,
	DurabilityCosts = 0xC0DDFC,
	Emotes = 0xC0DDD4,
	EmotesText = 0xC0DD98,
	EmotesTextData = 0xC0DDC0,
	EmotesTextSound = 0xC0DDAC,
	EnvironmentalDamage = 0xC0DD84,
	Exhaustion = 0xC0DD70,
	Faction = 0xC0DD48,
	FactionGroup = 0xC0DD5C,
	FactionTemplate = 0xC0DD34,
	FootprintTextures = 0xC0DD20,
	FootstepTerrainLookup = 0xC0DD0C,
	GameObjectArtKit = 0xC0DCF8,
	GameObjectDisplayInfo = 0xC0DCE4,
	GameTips = 0xC0DCD0,
	GMSurveyCurrentSurvey = 0xC0DCBC,
	GMSurveyQuestions = 0xC0DCA8,
	GMSurveySurveys = 0xC0DC94,
	GMTicketCategory = 0xC0DC80,
	GroundEffectDoodad = 0xC0DC6C,
	GroundEffectTexture = 0xC0DC58,
	HelmetGeosetVisData = 0xC0DC44,
	ItemBagFamily = 0xC0DC30,
	ItemClass = 0xC0DC1C,
	ItemDisplayInfo = 0xC0DC08,
	ItemGroupSounds = 0xC0DBF4,
	ItemPetFood = 0xC0DBE0,
	ItemRandomProperties = 0xC0DBCC,
	ItemSet = 0xC0DBB8,
	ItemSubClass = 0xC0DB90,
	ItemSubClassMask = 0xC0DBA4,
	ItemVisualEffects = 0xC0DB7C,
	ItemVisuals = 0xC0DB68,
	LanguageWords = 0xC0DB54,
	Languages = 0xC0DB40,
	LfgDungeons = 0xC0DB2C,
	Light = 0xCE9D60,
	LightFloatBand = 0xCE9D88,
	LightIntBand = 0xCE9D9C,
	LightParams = 0xCE9D74,
	LightSkybox = 0xCE9DB0,
	LiquidType = 0xC0DB18,
	LoadingScreens = 0xC0DB04,
	LoadingScreenTaxiSplines = 0xC0DAF0,
	Lock = 0xC0DADC,
	LockType = 0xC0DAC8,
	MailTemplate = 0xC0DAB4,
	Map = 0xC0DAA0,
	Material = 0xC0DA8C,
	NameGen = 0xC0DA78,
	NPCSounds = 0xC0DA64,
	NamesProfanity = 0xC0DA50,
	NamesReserved = 0xC0DA3C,
	Package = 0xC0DA28,
	PageTextMaterial = 0xC0DA14,
	PaperDollItemFrame = 0xC0DA00,
	PetLoyalty = 0xC0D9EC,
	PetPersonality = 0xC0D9D8,
	QuestInfo = 0xC0D9C4,
	QuestSort = 0xC0D9B0,
	Resistances = 0xC0D99C,
	ServerMessages = 0xC0D988,
	SheatheSoundLookups = 0xC0D974,
	SkillCostsData = 0xC0D960,
	SkillLineAbility = 0xC0D94C,
	SkillLineCategory = 0xC0D938,
	SkillLine = 0xC0D924,
	SkillRaceClassInfo = 0xC0D910,
	SkillTiers = 0xC0D8FC,
	SoundAmbience = 0xC0D8E8,
	SoundEntries = 0xC0D8D4,
	SoundProviderPreferences = 0xC0D8C0,
	SoundSamplePreferences = 0xC0D8AC,
	SoundWaterType = 0xC0D898,
	SpamMessages = 0xC0D884,
	SpellCastTimes = 0xC0D870,
	SpellCategory = 0xC0D85C,
	SpellChainEffects = 0xC0D848,
	Spell = 0xC0D780,
	SpellDispelType = 0xC0D834,
	SpellDuration = 0xC0D820,
	SpellEffectCameraShakes = 0xC0D80C,
	SpellFocusObject = 0xC0D7F8,
	SpellIcon = 0xC0D7E4,
	SpellItemEnchantment = 0xC0D7D0,
	SpellMechanic = 0xC0D7BC,
	SpellRadius = 0xC0D7A8,
	SpellRange = 0xC0D794,
	SpellShapeshiftForm = 0xC0D76C,
	SpellVisual = 0xC0D730,
	SpellVisualEffectName = 0xC0D758,
	SpellVisualKit = 0xC0D744,
	StableSlotPrices = 0xC0D71C,
	Stationery = 0xC0D708,
	StringLookups = 0xC0D6F4,
	Talent = 0xC0D6E0,
	TalentTab = 0xC0D6CC,
	TaxiNodes = 0xC0D6B8,
	TaxiPath = 0xC0D690,
	TaxiPathNode = 0xC0D6A4,
	TerrainType = 0xC0D67C,
	TerrainTypeSounds = 0xC0D668,
	TransportAnimation = 0xC0D654,
	UISoundLookups = 0xC0D640,
	UnitBlood = 0xC0D618,
	UnitBloodLevels = 0xC0D62C,
	VocalUISounds = 0xC0D604,
	WMOAreaTable = 0xC0D5F0,
	WeaponImpactSounds = 0xC0D5DC,
	WeaponSwingSounds2 = 0xC0D5C8,
	WorldMapArea = 0xC0D5B4,
	WorldMapContinent = 0xC0D5A0,
	WorldMapOverlay = 0xC0D58C,
	WorldSafeLocs = 0xC0D578,
	WorldStateUI = 0xC0D564,
	ZoneIntroMusic = 0xC0D550,
	ZoneMusic = 0xC0D53C,
};

class DBTable
{
private:
	int addr;

public:
	DBTable() :addr{} {}

	DBTable(int arg_addr) :addr{ arg_addr }	{}

	int GetRowPtr(int index)
	{		
		/*if (index < header.minIndex || index > header.maxIndex)
			return 0;
		return *(int*)(header.Rows + 4 * (index - header.minIndex));*/

		return ((int(__thiscall*)(int, int))0x0065C290)(addr, index + 0x18);
	}

	template <typename ROW>
	bool WowClient_GetLocalizedRow(int index, ROW& row)
	{
		return ((bool(__thiscall*)(int, int, ROW&))0x004CFD20)(addr, index, row);
	}

	/*template <typename FIELD>
	bool WowClient_GetFieldFromRowPtr(int row_ptr, int index)
	{
		return *(FIELD*)(row_ptr + index *4);
	}*/
};

std::map<ClientDB, DBTable> db_tables{};

inline auto GetDBTable(ClientDB db)
{
	if (db_tables.find(db) != db_tables.end())
		db_tables[db] = DBTable((int)db);
	return db_tables[db];
}

void InitDBTables()
{
	for (int tableBase = 0x006337D0 /*RegisterBase*/; *(byte*)tableBase != 0xC3 /*return*/; tableBase += 0x11)
	{
		int index = *(int*)(tableBase + 1);
		int tablePtr = *(int*)(tableBase + 0xB);
		db_tables[(ClientDB)index] = DBTable(tablePtr);
	}
}
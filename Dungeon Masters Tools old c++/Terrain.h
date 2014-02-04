#pragma once
#include "Room.h"

class Terrain
{
public:
	Terrain(HWND hwndIn);
	void ShowGrid(HDC hdc);
	void GenerateGrid();
	void ToggleView()						{ view = (VIEW)!view; }
	VIEW View()								{ return view; }
	void Var(float varIn)					{ variation = varIn; }
	float Var()								{ return variation; }
	void TargetRooms(int targetRoomsIn)		{ targetRooms = targetRoomsIn; }
	int TargetRooms()						{ return targetRooms; }
	void Height(int gridHeighIn);
	int Height()							{ return gridHeight; }
	void Width(int gridWidthIn);
	int Width()								{ return gridWidth; }
	void Resolution(int resolutionIn)		{ resolution = resolutionIn; }
	int Resolution()						{ return resolution; }
	int Running()							{ return run; }
	void RoomSize(int sizeIn)				{ roomSize = sizeIn; }
	int RoomSize()							{ return roomSize; }
	unsigned int Seed()						{ return seed; }
	void ToggleTools()						{ tools = !tools; }
	bool Tools()							{ return tools; }
	void ToggleDmTools()					{ dmTools = !dmTools; }
	bool DmTools()							{ return dmTools; }
	void ToggleShowTraps()					{ showTraps = !showTraps; }
	bool ShowTraps()						{ return showTraps; }
	void ToggleShowEncounters()				{ showEncounters = !showEncounters; }
	bool ShowEncounters()					{ return showEncounters; }
	void ToggleShowTreasures()				{ showTreasures = !showTreasures; }
	bool ShowTreasures()					{ return showTreasures; }
	void PartyLevel(int partyLevelIn)		{ partyLevel = partyLevelIn; }
	int PartyLevel()						{ return partyLevel; } 
	void TrapScroll(int trapScrollIn)		{ trapScroll = trapScrollIn; }
	int TrapScroll()						{ return trapScroll; }
	void TrapThumb(int trapThumbIn)			{ trapThumb = trapThumbIn; }
	int TrapThumb()							{ return trapThumb; }
	void CurrentHeight(int currentHeightIn) { currentHeight = currentHeightIn; }
	int CurrentHeight()						{ return currentHeight; }
	vector <Trap> traps;
	vector <Treasure> treasures;
	vector <Encounter> encounters;
private:
	void TraceBack(list <Path>::iterator iPaths);
	void GenerateRoom();
	vector <vector<int> > grid;
	vector <vector<int> > map;
	Room start;
	HWND hwnd;
	HWND child;
	float variation;
	list <Path> paths;
	vector <Room> rooms;
	int opened;
	VIEW view;
	int targetRooms;
	int gridWidth;
	int gridHeight;
	int resolution;
	bool run;
	int roomSize;
	unsigned int seed;
	bool tools;
	bool showTraps;
	bool showEncounters;
	bool showTreasures;
	int partyLevel;
	void GenerateTrap(FROM from,int xIn, int yIn);
	int trapsPerRoom;
	int dmTools;
	int trapScroll;
	int trapThumb;
	int currentHeight;
};


//trapsPerRoom, partyLevel, DM;bool showTraps;bool showEncounter;bool showTreasure;


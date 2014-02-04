#pragma once


#include <Windows.h>
#include <list>
#include <vector>
#include <time.h>
#include <process.h>
#include <math.h>
#include <string>
#include <sstream>


#define PI 3.14159265

using namespace std;


#define OFFSET 25


#define PATH (*iPaths)
#define PATHS ((*PATH.path.begin()))
#define TG(x) ((OFFSET+(x*Resolution())))
#define RG(x) (((x*res)))
#define _G(x) (x+OFFSET)

#define WM_FOCUS 0x0401
#define WM_RESIZE 0x0402
#define WM_BUILD 0x0403
#define WM_RESET 0x0404






enum SHAPE{S_ROUND,	//safe
		   S_SQUARE,
		   S_COUNT};

enum VIEW{GRID,
		  MAP};

enum TOOLS{HIDE,
			SHOW};


enum TRIGGER{TR_TRIP,
			 TR_AREA,
			 TR_CHEST,
			 TR_DOOR,
			 TR_COUNT};
enum RESET{R_AUTO,
		   R_MANUAL,
		   R_NON,
		   R_COUNT};
enum FROM{F_PATH,
		  F_ROOM,
		  F_CHEST,
		  F_COUNT};
enum SCROLL{SC_TRAPS,
		    SC_COUNT};
enum TREASURETYPE{T_GOLD,
				  T_ART,
				  T_OBJ,
				  T_WEOPON,
				  T_MAGICAL};
struct Point
{
	float x;
	float y;
};

struct Path
{
	float x;
	float y;
	float angle;
	int steps;
	float turn;
	bool met;
	list <Point> path;
	int wait; // the offsett required before settinga path to met.
};

struct Trap
{
	int x;
	int y;
	TRIGGER trigger;
	RESET   reset;
	int		findDc;
	int		disableDc;
	int		dammage;
	int		die;
	int		ID;
	int roomNum;

};

struct Treasure
{
	int x;
	int y;
	TREASURETYPE type;
	bool trapped;
};

struct Encounter
{};
import math




#room shapes
S_ROUND = 1
S_SQUARE = 2

# trap triggers
TR_TRIP = 1
TR_AREA = 2
TR_CHEST = 3
TR_DOOR = 4


enum RESET{R_AUTO,
		   R_MANUAL,
		   R_NON,


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

#pragma once
#include "Definitions.h"


class Room
{
public:
	void showRoom(HDC hdc, int res,VIEW view);
	SHAPE shape;
	int x;
	int y;
	int size;
	float angle;

};


#pragma once
#include "MapTools.h"

class TabControll
{
public:
	TabControll(HWND hwndIn);
	~TabControll(void);
	void SwitchTab();
	void TabControll::resize(int width, int height);
private:
	HWND hSelf, hParent;
	int current;
	vector <HWND> children;
	vector <string> titles;
	MapTools map;
};


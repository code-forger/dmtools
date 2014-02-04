#pragma once
#include <Windows.h>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment( lib, "comctl32.lib" )
#include "Terrain.h"
class MapTools
{
public:
	MapTools(void);
	~MapTools(void);
	HWND Initialise(HWND hParent);
	static LRESULT CALLBACK MapProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK InputProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	Terrain *terrain;
	static MapTools* self;
	HPEN hBorderPen;
	HWND hParent, hSelf;
	HWND hViewButton, hToolsButton;
	HWND hVarInput, hRoomsInput, hRoomsizeInput, hWidthInput, hHeightInput, hResInput, hPartyInput;
	HWND hVarEdit, hRoomsEdit, hRoomsizeEdit, hWidthEdit, hHeightEdit, hResEdit, hPartyEdit;
};

 
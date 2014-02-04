#include "MapTools.h"

MapTools *MapTools::self = NULL;

MapTools::MapTools(void)
{
	self = this;


}


MapTools::~MapTools(void)
{

}

HWND MapTools::Initialise(HWND hParentIn)
{

	hParent = hParentIn;
	static TCHAR szAppName[] = TEXT ("MapTools");
	HWND		 hwnd,hwndTab;
	MSG          msg ;
	WNDCLASS     wndclass ;
	RECT rect;
	
	hBorderPen = CreatePen(NULL,1,RGB(100,100,100));
	

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = MapTools::MapProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = NULL ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	RegisterClass (&wndclass);

	wndclass.lpfnWndProc   = MapTools::InputProc ;
	wndclass.lpszClassName = "Input" ;

	RegisterClass (&wndclass);

	GetClientRect(hParent,&rect);
	
	hSelf = CreateWindow (szAppName, szAppName,WS_CHILD,
		1,24,rect.right-4,rect.bottom-26,
							hParent, NULL, NULL, NULL) ;
	terrain = new Terrain(hSelf);

	return hSelf;
}

LRESULT CALLBACK MapTools::MapProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	LPARAM lpar;
	switch (message)
	{
	case WM_CREATE:
		self->hToolsButton = CreateWindow("BUTTON","Hide Tools",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON
			,400+(OFFSET*2),
			OFFSET,100,OFFSET,hwnd,NULL,NULL,NULL);
		self->hViewButton = CreateWindow("BUTTON","View: Grid",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON
			,400+(OFFSET*2),
			OFFSET*3,100,OFFSET,hwnd,NULL,NULL,NULL);

		self->hVarInput = CreateWindow("Input", "",WS_CHILD|WS_VISIBLE,
			400+(OFFSET*2),OFFSET*5,100,OFFSET*2,hwnd,(HMENU)0,NULL,NULL);

		self->hRoomsInput = CreateWindow("Input", "",WS_CHILD|WS_VISIBLE,
			400+(OFFSET*2),OFFSET*8,100,OFFSET*2,hwnd,(HMENU)1,NULL,NULL);

		self->hRoomsizeInput = CreateWindow("Input", "",WS_CHILD|WS_VISIBLE,
			400+(OFFSET*2),OFFSET*11,100,OFFSET*2,hwnd,(HMENU)2,NULL,NULL);

		self->hWidthInput = CreateWindow("Input", "",WS_CHILD|WS_VISIBLE,
			400+(OFFSET*2),OFFSET*14,100,OFFSET*2,hwnd,(HMENU)3,NULL,NULL);

		self->hHeightInput = CreateWindow("Input", "",WS_CHILD|WS_VISIBLE,
			400+(OFFSET*2),OFFSET*17,100,OFFSET*2,hwnd,(HMENU)4,NULL,NULL);
		
		self->hResInput = CreateWindow("Input", "",WS_CHILD|WS_VISIBLE,
			400+(OFFSET*2),OFFSET*20,100,OFFSET*2,hwnd,(HMENU)5,NULL,NULL);
		
		self->hPartyInput = CreateWindow("Input", "",WS_CHILD|WS_VISIBLE,
			400+(OFFSET*2),OFFSET*23,100,OFFSET*2,hwnd,(HMENU)6,NULL,NULL);

		PostMessage(self->hVarInput,WM_BUILD,NULL,NULL);
		return 0;
	case WM_LBUTTONDOWN:
   		SetFocus(self->hSelf);
 		return 0;
	case WM_COMMAND:
		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			if ((self->hToolsButton == (HWND)lParam))
			{
				self->terrain->ToggleTools();
				if (self->terrain->Tools() == SHOW)
				{
					SetWindowText(self->hToolsButton, "Hide Tools");
					ShowWindow(self->hViewButton, SW_SHOW);
					ShowWindow(self->hVarInput, SW_SHOW);
					ShowWindow(self->hRoomsInput, SW_SHOW);
					ShowWindow(self->hRoomsizeInput, SW_SHOW);
					ShowWindow(self->hWidthInput, SW_SHOW);
					ShowWindow(self->hHeightInput, SW_SHOW);
					ShowWindow(self->hResInput, SW_SHOW);
					ShowWindow(self->hPartyInput, SW_SHOW);
				}
				else
				{
					SetWindowText(self->hToolsButton, "Show Tools");
					ShowWindow(self->hViewButton, SW_HIDE);
					ShowWindow(self->hVarInput, SW_HIDE);
					ShowWindow(self->hRoomsInput, SW_HIDE);
					ShowWindow(self->hRoomsizeInput, SW_HIDE);
					ShowWindow(self->hWidthInput, SW_HIDE);
					ShowWindow(self->hHeightInput, SW_HIDE);
					ShowWindow(self->hResInput, SW_HIDE);
					ShowWindow(self->hPartyInput, SW_HIDE);
				}
			}
 			else if ((self->hViewButton == (HWND)lParam))
			{
				self->terrain->ToggleView();
				if (self->terrain->View() == MAP)
					SetWindowText(self->hViewButton, "View: Map");
				else 
					SetWindowText(self->hViewButton, "View: Grid");
				InvalidateRect(self->hSelf,NULL,NULL);
			}
			SetFocus(self->hSelf);
		}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
				self->terrain->GenerateGrid();
				InvalidateRect(self->hSelf,NULL,NULL);
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		self->terrain->ShowGrid(hdc); //Double buffered
		EndPaint(hwnd,&ps);
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}


LRESULT CALLBACK MapTools::InputProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int tempInt;
	char tempStr[256];
	switch (message)
	{
	case WM_CREATE:
		if (GetWindowLong(hwnd,GWL_ID) == 0)
			self->hVarEdit = CreateWindow("EDIT","",WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL |
						  ES_LEFT | ES_MULTILINE, 5,OFFSET,100-10,OFFSET-5,hwnd,NULL,NULL,NULL);
		
		if (GetWindowLong(hwnd,GWL_ID) == 1)
			self->hRoomsEdit = CreateWindow("EDIT","",WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL |
						  ES_LEFT | ES_MULTILINE, 5,OFFSET,100-10,OFFSET-5,hwnd,NULL,NULL,NULL);
		
		if (GetWindowLong(hwnd,GWL_ID) == 2)
			self->hRoomsizeEdit = CreateWindow("EDIT","",WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL |
						  ES_LEFT | ES_MULTILINE, 5,OFFSET,100-10,OFFSET-5,hwnd,NULL,NULL,NULL);
		
		if (GetWindowLong(hwnd,GWL_ID) == 3)
			self->hWidthEdit = CreateWindow("EDIT","",WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL |
						  ES_LEFT | ES_MULTILINE, 5,OFFSET,100-10,OFFSET-5,hwnd,NULL,NULL,NULL);
		
		if (GetWindowLong(hwnd,GWL_ID) == 4)
			self->hHeightEdit = CreateWindow("EDIT","",WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL |
						  ES_LEFT | ES_MULTILINE, 5,OFFSET,100-10,OFFSET-5,hwnd,NULL,NULL,NULL);
		
		if (GetWindowLong(hwnd,GWL_ID) == 5)
			self->hResEdit = CreateWindow("EDIT","",WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL |
						  ES_LEFT | ES_MULTILINE, 5,OFFSET,100-10,OFFSET-5,hwnd,NULL,NULL,NULL);
		
		if (GetWindowLong(hwnd,GWL_ID) == 6)
			self->hPartyEdit = CreateWindow("EDIT","",WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL |
						  ES_LEFT | ES_MULTILINE, 5,OFFSET,100-10,OFFSET-5,hwnd,NULL,NULL,NULL);
		return 0;
	case WM_BUILD:
		itoa((self->terrain->Var()*100),tempStr,10);
		SetWindowText(self->hVarEdit,tempStr);

		itoa(self->terrain->TargetRooms(),tempStr,10);
		SetWindowText(self->hRoomsEdit,tempStr);

		itoa(self->terrain->RoomSize(),tempStr,10);
		SetWindowText(self->hRoomsizeEdit,tempStr);

		itoa(self->terrain->Width(),tempStr,10);
		SetWindowText(self->hWidthEdit,tempStr);

		itoa(self->terrain->Height(),tempStr,10);
		SetWindowText(self->hHeightEdit,tempStr);

		itoa(self->terrain->Resolution(),tempStr,10);
		SetWindowText(self->hResEdit,tempStr);

		itoa(self->terrain->PartyLevel(),tempStr,10);
		SetWindowText(self->hPartyEdit,tempStr);
		return 0;
	case WM_LBUTTONDOWN:
 		return 0;
	case WM_COMMAND:
		switch(HIWORD(wParam))
		{
		case EN_CHANGE:
			GetWindowText((HWND)lParam,tempStr,10);
			tempInt = atoi(tempStr);
			if (hwnd == self->hVarInput)
				self->terrain->Var((float)tempInt/(float)100);

			if (hwnd == self->hRoomsInput)
				self->terrain->TargetRooms(tempInt);

			if (hwnd == self->hRoomsizeInput)
				self->terrain->RoomSize(tempInt);

			if (hwnd == self->hWidthInput)
				self->terrain->Width(tempInt);

			if (hwnd == self->hHeightInput)
				self->terrain->Height(tempInt);

			if (hwnd == self->hResInput)
				self->terrain->Resolution(tempInt);

			if (hwnd == self->hPartyInput)
				self->terrain->PartyLevel(tempInt);
			break;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		if (hwnd == self->hVarInput)
			TextOut(hdc,5,5,"Variation:",10);
		if (hwnd == self->hRoomsInput)
			TextOut(hdc,5,5,"Rooms:",6);
		if (hwnd == self->hRoomsizeInput)
			TextOut(hdc,5,5,"Room size:",10);
		if (hwnd == self->hWidthInput)
			TextOut(hdc,5,5,"Grid width:",11);
		if (hwnd == self->hHeightInput)
			TextOut(hdc,5,5,"Grid height:",12);
		if (hwnd == self->hResInput)
			TextOut(hdc,5,5,"Resolution:",11);
		if (hwnd == self->hPartyInput)
			TextOut(hdc,5,5,"Party Level:",12);




		SelectObject(hdc,GetStockObject(NULL_BRUSH));
		SelectObject(hdc,self->hBorderPen);
		RoundRect(hdc,0,0,100,OFFSET*2,6,6);
		EndPaint(hwnd,&ps);
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}

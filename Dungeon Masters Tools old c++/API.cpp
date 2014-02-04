
#include "TabControll.h"

TabControll* tabs;
HINSTANCE hInst;

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


TCHAR szButtonClass[] = TEXT("Button Class");
TCHAR szTextClass[] = TEXT("Text Class");
TCHAR szTrapClass[] = TEXT("Trap Class");
TCHAR szScrollClass[] = TEXT("Scroll Class");

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Terrain generation");
	HWND		 hwnd,hwndTab;
	MSG          msg ;
	WNDCLASS     wndclass ;
	hInst=hInstance;
	RECT rect;
	
	

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1); ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("Program requires Windows NT!"), 
		szAppName, MB_ICONERROR) ;
		return 0 ;
	}


	
	hwnd = CreateWindow (szAppName, szAppName,
	WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
	50,
	50,
	1000,
	800
	,
	NULL, NULL, hInstance, NULL) ;
	
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	GetClientRect(hwnd,&rect);
	tabs = new TabControll(hwnd);
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	return msg.wParam ;
}



LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) // Proticall for the entire window
{
	switch(message)
	{
	case WM_SIZE:
		tabs->resize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == NM_CLICK);
			tabs->SwitchTab();
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}


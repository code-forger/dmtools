#include "TabControll.h"


TabControll::TabControll(HWND hwndIn)
{
	hParent = hwndIn;
	current = 0;
	char buffer[256];
	RECT rect;
	INITCOMMONCONTROLSEX icex;
	TCITEM tie;
	

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;
	InitCommonControlsEx(&icex);
	
	GetClientRect(hParent, &rect); 
	hSelf = CreateWindow(WC_TABCONTROL, "", 
						WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 
						0, 0, rect.right, rect.bottom, 
						hParent, NULL, NULL, NULL); 
	
	
	tie.mask = TCIF_TEXT | TCIF_IMAGE; 
	tie.iImage = -1; 
	children.push_back(map.Initialise(hSelf));
	titles.push_back("MapTools");
	for (int i = 0; i < children.size(); ++i)
	{
		strcpy(buffer,titles[i].c_str()); 
		tie.pszText = buffer;
		(TabCtrl_InsertItem(hSelf, i, &tie));
	}
	SwitchTab();
}


TabControll::~TabControll(void)
{

}

void TabControll::SwitchTab()
{
	int i = TabCtrl_GetCurFocus(hSelf);
	ShowWindow(children[current],SW_HIDE);
	ShowWindow(children[i],SW_SHOW);
	current = i;
}

void TabControll::resize(int width, int height)
{
	SetWindowPos(hSelf,NULL,0,0,width,height,NULL);
	for (int i = 0; i < children.size(); ++i)
	{
		SetWindowPos(children[i],NULL,1,24,width-4,height-26,NULL);
	}
}
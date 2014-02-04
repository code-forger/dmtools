#include "Room.h"

void Room::showRoom(HDC hdc, int res,VIEW view)
{
	static HPEN hPen,hPenW;
	hPen = CreatePen(NULL,res,RGB(150,150,150));
	hPenW = CreatePen(NULL,res,RGB(255,255,255));
	SelectObject(hdc,hPen);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	switch (shape)
	{
	case S_ROUND:
		if (view == GRID)
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Ellipse(hdc,RG((x-(size/2))),RG((y-(size/2))),RG((x+(size/2))),RG((y+(size/2))));
		break;
	case S_SQUARE:
		SelectObject(hdc,hPenW);
		if (view == MAP)
			for (int i = 0; i < size; i++)
			{
  				MoveToEx(hdc,RG((x+(size-i)*cos(angle))),RG((y+(size-i)*sin(angle))),NULL);			
				angle -= (PI/2);
				LineTo(hdc,RG((x+(size-i)*cos(angle))),RG((y+(size-i)*sin(angle))));
				angle -= (PI/2);
				LineTo(hdc,RG((x+(size-i)*cos(angle))),RG((y+(size-i)*sin(angle))));
				angle -= (PI/2);
				LineTo(hdc,RG((x+(size-i)*cos(angle))),RG((y+(size-i)*sin(angle))));
				angle -= (PI/2);
				LineTo(hdc,RG((x+(size-i)*cos(angle))),RG((y+(size-i)*sin(angle))));
			}
		SelectObject(hdc,hPen);
		MoveToEx(hdc,RG((x+size*cos(angle))),RG((y+size*sin(angle))),NULL);
		angle -= (PI/2);
		LineTo(hdc,RG((x+size*cos(angle))),RG((y+size*sin(angle))));
		angle -= (PI/2);
		LineTo(hdc,RG((x+size*cos(angle))),RG((y+size*sin(angle))));
		angle -= (PI/2);
		LineTo(hdc,RG((x+size*cos(angle))),RG((y+size*sin(angle))));
		angle -= (PI/2);
		LineTo(hdc,RG((x+size*cos(angle))),RG((y+size*sin(angle))));
		
		break;
	}
	DeleteObject(hPen);
	DeleteObject(hPenW);
}
#include "Terrain.h"


Terrain::Terrain(HWND hwndIn)
{
	trapScroll = 0;
	tools = 1;
	showTraps = 1;
	showEncounters = 1;
	showTreasures = 1;
	dmTools = 0;

	trapsPerRoom = 5;
	partyLevel = 1;
	roomSize = 15;
	run = 0;
	gridHeight = 100;
	gridWidth = 100;
	resolution = 4;
	grid.resize(gridWidth);
	map.resize(gridWidth);
	for (int i = 0; i < gridWidth; i++)
	{
		grid[i].resize(gridHeight);
		map[i].resize(gridHeight);
	}
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			grid[j][i] = 0;
			map[j][i] = 0;
		}
	}
	hwnd = hwndIn;
	view = GRID;
	variation = (float)0.3 ; //.5
	targetRooms = 6;
}

void Terrain::ShowGrid(HDC hdc)
{
	HDC bufferDC;
	HBITMAP bufferBit;
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(BS_NULL);
	bufferDC = CreateCompatibleDC(hdc);
	bufferBit = CreateCompatibleBitmap(hdc,(gridWidth+1) * resolution,(gridHeight+1) * resolution);
	SelectObject(bufferDC,bufferBit);
	Rectangle(bufferDC,-1,-1,(gridWidth+1) * resolution+1,(gridHeight+1) * resolution+1);
	char temp[10];
	static vector <int> roomsTraps;
	
	switch (view)
	{
	case GRID:
		for (int i = 0; i < gridHeight; i++)
		{
			for (int j = 0; j < gridWidth; j++)
			{
				if (grid[j][i] == 1)
					for (int k=0; k < resolution; k++)
						for (int l=0; l < resolution; l++)
						{
							SetPixel(bufferDC,j*resolution+l,i*resolution+k,RGB(0,0,0));
						}
				else if (grid[j][i] == 2)
					for (int k=0; k < resolution; k++)
						for (int l=0; l < resolution; l++)
						{
							SetPixel(bufferDC,j*resolution+l,i*resolution+k,RGB(255,0,0));
						}
				else if (grid[j][i] == 3)
					for (int k=0; k < resolution; k++)
						for (int l=0; l < resolution; l++)
						{
							SetPixel(bufferDC,j*resolution+l,i*resolution+k,RGB(0,0,255));
						}
				else if (grid[j][i] == 4)
					for (int k=0; k < resolution; k++)
						for (int l=0; l < resolution; l++)
						{
							SetPixel(bufferDC,j*resolution+l,i*resolution+k,RGB(0,255,0));
						}
			}
		}
		for (int i = 0; i < rooms.size(); i++)
			rooms[i].showRoom(bufferDC,resolution,view);

		roomsTraps.resize(0);
		roomsTraps.resize(rooms.size());
		for (int i = 0; i < traps.size() && ShowTraps() == 0; i++)
		{
			itoa(i,temp,10);
			if (traps[i].roomNum >= 0)
				TextOut(bufferDC,traps[i].x*resolution,traps[i].y*resolution+(roomsTraps[traps[i].roomNum]++ * 18),temp,strlen(temp));
			else
				TextOut(bufferDC,traps[i].x*resolution,traps[i].y*resolution,temp,strlen(temp));
		}
		break;
	case MAP:
		for (int i = 0; i < gridHeight; i++)
		{
			for (int j = 0; j < gridWidth; j++)
			{
				if (map[j][i] == 1)
					for (int k=0; k < resolution; k++)
						for (int l=0; l < resolution; l++)
						{
							SetPixel(bufferDC,j*resolution+l,i*resolution+k,RGB(0,0,0));
						}
			}
		}
		for (int i = 0; i < rooms.size(); i++)
			rooms[i].showRoom(bufferDC,resolution,view);
		break;
	}
	SelectObject(bufferDC,GetStockObject(NULL_BRUSH));
	SelectObject(bufferDC,GetStockObject(BLACK_PEN));
	Rectangle(bufferDC,0,0,(gridWidth) * resolution,(gridHeight) * resolution);

	BitBlt(hdc, OFFSET, OFFSET,(gridWidth) * resolution,(gridHeight) * resolution,bufferDC,0,0,SRCCOPY);
	DeleteObject(hBrush);
	DeleteObject(bufferDC);
	DeleteObject(bufferBit);
}

void Terrain::GenerateGrid()
{
	//double test,test2,test3,test4;
	//if (seed == 0)
	//{
		seed = (unsigned int)time(NULL);
		srand(seed);
	//}
	//else
	//{
	//	srand(seed);
	//}

	int met = 0;
	bool trace = 0;
	RECT rect;

	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{		
			grid[j][i] = 0;
		}
	}

	GenerateRoom();

	for (list <Path>::iterator iPaths = paths.begin();
		 paths.size() > 0; )
	{
		iPaths++;
		if (iPaths == paths.end())
		{
  			if (met >= (signed int)paths.size())
				trace = 1;
			met = 0;
			iPaths = paths.begin();
		}

		
		if (trace == 1)
		{
			TraceBack(iPaths);
			
			paths.erase(iPaths);
			iPaths = paths.begin();
			continue;
			
		}
		else
		{
			if (PATH.steps == 0)
			{
				PATH.angle = ((atan2(((gridHeight / 2) - PATH.y), ((gridWidth / 2) - PATH.x))) + ((((float)rand() / RAND_MAX) * (variation * 2)) - variation));
				PATH.turn = ((((float)rand() / RAND_MAX) * (variation * 2)) - variation);
				PATH.angle += PATH.turn;
			}
				 
		

			if (PATH.x + cos(PATH.angle) > gridWidth -1 || 
			    PATH.x + cos(PATH.angle) < 1 ||
				PATH.y + sin(PATH.angle) > gridHeight -1 || 
				PATH.y + sin(PATH.angle) < 1)
			{
				if (PATH.met == 1)
				{
					opened--;
					TraceBack(iPaths);
				}
				paths.erase(iPaths);
				iPaths = paths.begin();
				continue;
			}
			else
			{
				PATH.x += cos(PATH.angle);
				PATH.y += sin(PATH.angle);

				Point point;
				point.x = (float)(int)PATH.x;
				point.y = (float)(int)PATH.y;
				PATH.path.push_front(point);

				PATH.turn = ((((float)rand() / RAND_MAX) * (variation * 2)) - variation);
				PATH.angle += PATH.turn;

				if (PATH.wait > 0)
				{
				
					PATH.wait--;
					switch (PATH.wait)
					{
					case 1:
						PATH.met = 1;
						break;
					case 2:
						break;
					case 0:
						break;
					}
				}
				if (PATH.met == 1)
					met++;

				if (PATH.wait == 0 && (
					grid[(int)PATH.x + ((cos(PATH.angle) > 0) ? 1 : -1)][(int)PATH.y] == 1 ||
					grid[(int)PATH.x][(int)PATH.y + ((sin(PATH.angle) > 0) ? 1 : -1)] == 1 ||
					grid[(int)PATH.x + ((cos(PATH.angle) > 0) ? 1 : -1)][(int)PATH.y + ((sin(PATH.angle) > 0) ? 1 : -1)] == 1))
				{
					PATH.wait = 3;
				}

				int randTrap = ((((float)rand() / RAND_MAX) * 99));

				if (randTrap == 1)
				{
					GenerateTrap(F_PATH,(int)PATH.x,(int)PATH.y);
					
				}

				if (PATH.steps == 0 && grid[(int)PATH.x][(int)PATH.y] != 4)
					grid[(int)PATH.x][(int)PATH.y] = 2;
				else
				{
					if (PATH.wait > 0 &&
						grid[(int)PATH.x][(int)PATH.y] == 1)
						grid[(int)PATH.x][(int)PATH.y] = 3;
					else if (grid[(int)PATH.x][(int)PATH.y] == 0)
					{
						grid[(int)PATH.x][(int)PATH.y] = 1;
					}
				}
			}
			PATH.steps++;
		}
	}


	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			map[j][i] = 0;
		}
	}
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			if (grid[j][i] > 0)
			{
				map[j][i] = 1;
				if(j < gridWidth-1)
  					map[j + 1][i] = 1;
				if(j > 0)
					map[j - 1][i] = 1;
				if(i < gridHeight-1)
					map[j][i + 1] = 1;
				if(i > 0)
					map[j][i - 1] = 1;
			}
		}
	}
	rect.left = 0;
	rect.top = 0;
	rect.bottom = _G(TG(gridHeight)-1)+roomSize;
	rect.right = _G(TG(gridWidth)-1)+roomSize;
	InvalidateRect(hwnd,&rect,1);
	InvalidateRect(child,NULL,1);
	PostMessage(hwnd,WM_RESIZE,0,0);
	run = 0;
}

void Terrain::Height(int gridHeightIn)
{
	gridHeight = gridHeightIn;	
	grid.resize(gridWidth);
	map.resize(gridWidth);
	rooms.resize(0);
	for (int i = 0; i < gridWidth; i++)
	{
		grid[i].resize(gridHeight);
		map[i].resize(gridHeight);
	}
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			grid[j][i] = 0;
			map[j][i] = 0;
		}
	}
}

void Terrain::Width(int gridWidthIn)
{
	gridWidth = gridWidthIn;	
	grid.resize(gridWidth);
	map.resize(gridWidth);
	rooms.resize(0);
	for (int i = 0; i < gridWidth; i++)
	{
		grid[i].resize(gridHeight);
		map[i].resize(gridHeight);
	}
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			grid[j][i] = 0;
			map[j][i] = 0;
		}
	}
}
 

void Terrain::TraceBack(list <Path>::iterator iPaths)
{
	while (PATH.path.size() > 0 && (
		   grid[(int)PATHS.x][(int)PATHS.y] == 1 ||
		   //grid[(int)PATHS.x][(int)PATHS.y] == 4 ||
		   grid[(int)PATHS.x][(int)PATHS.y] == 0))
	{
		grid[(int)PATHS.x][(int)PATHS.y] = 0;
		PATH.path.pop_front();
	}
}

void Terrain::GenerateRoom()
{
	vector <Point> points(gridWidth * gridHeight);
	int numPoint = 0;
	Path path;
	//Point point;
	Room room;
	int temp;
	opened = 0;

	traps.resize(0);

	rooms.resize(0);

	for (int i = 0; i < gridHeight; i++) // initialise a list of points refering to every
	{									 // grid position available
		for (int j = 0; j < gridWidth; j++)
		{
			points[j+(i*gridWidth)].x = (float)j;
			points[j+(i*gridWidth)].y = (float)i;
			numPoint++;
		}
	}
	
	for (int j = 0, random; j < targetRooms; j++)
	{
		random = (int)(((float)rand() / RAND_MAX) * --numPoint); //chose random point

		path.x = points[random].x;
		path.y = points[random].y;
		room.x = (int)points[random].x;
		room.y = (int)points[random].y;
		points[random] = points[numPoint];
	
		room.shape = (SHAPE)(int)(((float)rand() / RAND_MAX) * (S_COUNT));

		room.size = (int)(((float)rand() / RAND_MAX) * (roomSize/2) + (roomSize/2));

		room.angle = (((float)rand() / RAND_MAX) * (2 * PI));

		path.steps = 0;
		path.met = 0;
		path.wait = 0;

		paths.push_back(path);
		rooms.push_back(room);

		for (int i = 0; i < trapsPerRoom; i++)
		{
			int randTrap = ((((float)rand() / RAND_MAX) * 99));
			if (randTrap <= 15)		// 15% * trapsPerRoom chance of traps in this room
			{
				GenerateTrap(F_ROOM,room.x,room.y);
			}
		}
		opened++;
	}
}

void Terrain::GenerateTrap(FROM from,int xIn,int yIn)
{
	Trap trap;
	int random;

	trap.x = xIn;
	trap.y = yIn;

	switch (from)
	{
	case F_PATH:
		trap.roomNum = -1;
		trap.trigger = (TRIGGER)(int)(((float)rand() / RAND_MAX) * (TR_AREA+1));
		trap.x = xIn;
		trap.y = yIn;
		break;
	case F_ROOM:
		trap.roomNum = rooms.size()-1;
		trap.trigger = (TRIGGER)(int)(((float)rand() / RAND_MAX) * (TR_DOOR+1)); 
		if (trap.trigger == TR_CHEST)
			trap.trigger == TR_AREA;
		trap.x = xIn;
		trap.y = yIn;
		break;
	case F_CHEST:
		trap.roomNum = -1;
		trap.trigger = TR_CHEST; 
		trap.x = _G(_G(gridHeight));
		trap.y = yIn;
		break;
	}
	trap.reset  = (RESET)(int)(((float)rand() / RAND_MAX) * (R_COUNT)); 
	random = (((float)rand() / RAND_MAX) * (3+partyLevel*2)); 
	trap.findDc = (15  + random);
	trap.disableDc = (20  + random);
	trap.dammage = (((float)rand() / RAND_MAX) * (partyLevel/2))+(partyLevel/2)+1; 
	trap.die  = (((int)((((float)rand() / RAND_MAX) * (3))+2))*2);
	trap.ID = traps.size();

	if (from == F_ROOM)
	{
		if((int)trap.x < gridWidth-1)
  			grid[(int)trap.x+1][(int)trap.y] = 4;
		if((int)trap.x > 0)
			grid[(int)trap.x-1][(int)trap.y] = 4;
		if((int)trap.y < gridHeight-1)
			grid[(int)trap.x][(int)trap.y+1] = 4;
		if((int)trap.y > 0)
			grid[(int)trap.x][(int)trap.y-1] = 4;
	}

	grid[(int)trap.x][(int)trap.y] = 4;

	traps.push_back(trap);
}
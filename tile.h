#pragma once

#include "gameObject.h"

#define TILEX 12
#define TILEY 12
#define TILESIZE 56
#define MAPX 7
#define MAPY 7
#define MAPSIZE MAPX*MAPY
#define MAPTILEX MAPX*TILEX
#define MAPTILEY MAPY*TILEY

class tile : public gameObject {
public:
	string terrKey;
	int terrainFrameX;
	int terrainFrameY;
	bool hasBuilding;
};



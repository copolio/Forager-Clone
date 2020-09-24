#pragma once
#define TILEX 12
#define TILEY 12
#define TILESIZE 56
#define MAPX 7
#define MAPY 7
#define MAPSIZE MAPX*MAPY
#define MAPTILEX MAPX*TILEX
#define MAPTILEY MAPY*TILEY
#define CAMRANGE TILESIZE*4
#define CAMSPEED 10

enum GROUNDLEVEL {
	TERRAIN, OBJECT
};

struct tile {
	RECT rc;
	GROUNDLEVEL level;
	string terrKey;
	string objKey;
	int terrainHp;
	int terrainFrameX;
	int terrainFrameY;
	int objHp;
	int objFrameX;
	int objFrameY;
};

struct dropItem {
	RECT rc;
	//image* dropItems;
	string itemKey;
	string imgName;
	float dropItemX;
	float dropItemY;

};

#pragma once
#include "gameNode.h"
#define TILEX 12
#define TILEY 12
#define TILESIZE 56
#define MAPX 7
#define MAPY 7
#define MAPSIZE MAPX*MAPY
#define MAPTILEX MAPX*TILEX
#define MAPTILEY MAPY*TILEY
enum GROUNDLEVEL {
	TERRAIN, OBJECT
};
struct tile {
	RECT rc;
	GROUNDLEVEL level;
	image* terrain;
	image* object;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};
class basicmap : public gameNode
{
private:
	image* watertile;
	image* plaintile;
	image* plainedge;
	image* wave;
	image* underwater;
	int _count;
	int wavetick;
private:
	tile _tiles[TILEY][TILEX];
	vector<tile> _vTiles;
	RECT _rcCam;
	RECT _rcPlayer;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};



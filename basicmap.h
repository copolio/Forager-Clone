#pragma once
#include "gameNode.h"
#define TILEX 10
#define TILEY 10
#define TILESIZE 56
enum GROUNDLEVEL {
	TERRAIN, OBJECT
};
struct tile {
	RECT rc;
	GROUNDLEVEL level;
	image* terrain;
	image* object;
};
class basicmap : public gameNode
{
private:
	image* watertile;
	image* plaintile;
	image* plainedge;
private:
	tile _tiles[TILEY][TILEX];
public:
	HRESULT init();
	void release();
	void update();
	void render();
};



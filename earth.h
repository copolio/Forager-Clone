#pragma once
#include "gamemap.h"
#include "unit.h"
#include "building.h"
#include "resource.h"
class earth : public gamemap
{
private:
	vector<tile> _vTile;
	vector<unit> _vUnit; //아이템, 빌딩
private:
	image* watertile;
	image* plaintile;
	image* plainedge;
	image* wave;
	image* underwater;
	int _count;
	int _frameCount;
	int wavetick;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapSetup();
	void setRandomObject();
	float getResRatio();
	int getPlayerPos();
	void setIsland(int x, int y);
};


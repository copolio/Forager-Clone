#pragma once
#include "gamemap.h"
class earth : public gamemap
{
private:
	vector<tile> _vTile;
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
	void animation();
};


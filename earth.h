#pragma once
#include "gamemap.h"
#include "unit.h"
#include "building.h"
#include "inGameResource.h"
#include "fieldItem.h"
#include "ForagerPlayer.h"

class earth : public gamemap
{
private:
	ForagerPlayer* _player; // 플레이어

private:
	image* watertile;
	image* plaintile;
	image* plainedge;
	image* wave;
	image* underwater;
	int _count;
	int _frameCount;
	int wavetick;
	bool waveUp;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapSetup();
	void setRandomObject();
	float getResRatio();
	int GetTileX(int index);
	int GetTileY(int index);
	void setIsland(int x, int y);
	int GetIslandX(int index);
	int GetIslandY(int index);
	RECT GetIslandRc(int x, int y);
	bool HasIsland(int x, int y);
	void setLinkPlayer(ForagerPlayer *player) { _player = player; };
	int GetIslandCount();
public:
	tile* tileMouseTarget();
	int tileMouseTargetIndex();
	int tileColMouseTargetIndex();
	void setTileHasUnit(int index) { 
		_vTile[index].hasUnit = true;
		_vTile[index].canPass = false;
	};
};


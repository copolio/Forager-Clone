#pragma once
#include "gamemap.h"
#include "unit.h"
#include "building.h"
#include "resource.h"
#include "fieldItem.h"
#include "ForagerPlayer.h"
class ForagerPlayer;

class earth : public gamemap
{
private:
	vector<tile> _vTile;
	ForagerPlayer* _player; // 플레이어

private:
	image* watertile;
	image* plaintile;
	image* plainedge;
	image* wave;
	image* underwater;
	int _count;
	int _frameCount;
	int islandCount;
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
	int GetIslandCount() { return islandCount; }
public:
	vector<tile> GetTiles() { return _vTile; }

	tile GetTile(int index) { return _vTile[index]; };
	tile* GetTileP(int index) { return &_vTile[index]; };
	RECT GetTileRc(int index) { return _vTile[index].rc; }
	tile* tileMouseTarget();
	int tileMouseTargetIndex();
	int tileColMouseTargetIndex();
	void setTileHasUnit(int index) { 
		_vTile[index].hasUnit = true;
		_vTile[index].canPass = false;
	};
};


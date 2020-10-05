#pragma once
#include "gamemap.h"
#include "unit.h"
#include "building.h"
#include "resource.h"
#include "ForagerPlayer.h"
class ForagerPlayer;

class earth : public gamemap
{
private:
	vector<tile> _vTile;
	vector<unit*> _vUnit; //아이템, 빌딩
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
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapSetup();
	void setRandomObject();
	float getResRatio();
	void setLinkPlayer(ForagerPlayer *player) { _player = player; };
public:
	vector<tile> GetTiles() { return _vTile; }
	tile GetTile(int index) { return _vTile[index]; };
	RECT GetTileRc(int index) { return _vTile[index].rc; }

	vector<unit*> GetUnits() { return _vUnit; };



	// 임시용 (드롭 매니저 구현시 제거될 예정)
private:
	bool _canCreateDropItem = false;
	POINT _ptItemPos;
	string _itemKey;
	void AddUnits();
};


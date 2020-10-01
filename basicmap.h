#pragma once
#include "gameNode.h"
#include "ForagerPlayer.h"
#include "ForagerStatManager.h"
#include "targetingBox.h"
#include "inventory.h"
#include "tile.h"

#define PLAINHP 100
#define NUMOBJECTS 3
#define RESRATIOLIMIT 0.7
#define RESGENTIME 100

class basicmap : public gameNode
{
private:
	image* watertile;
	image* plaintile;
	image* plainedge;
	image* wave;
	image* underwater;
	int _count;
	int _frameCount;
	int wavetick;
private:
	image* steelwork;
private:
	image* berry;
	image* rock;
	image* tree;
private:
	image* treeDrop;
	image* rockDrop;
	image* berryDrop;
	
private:
	vector<tile> _vTiles;
	RECT _rcCam;
	RECT _rcPlayer;
	targetingBox* _targetingBox;
private:
	ForagerPlayer* _player;
	int _playerPos;
	POINT _ptPlayerPos;
	ForagerStatManager* _statManager;
	inGameMenu* _inventory;

private:
	vector<dropItem> _vDropItems;
	bool is_item_check = false;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void mapSetup();
	void setTile();

	/* 카메라 매니저로 대체
	void cameraMove();
	void cameraFocus();
	*/

	//무작위 타일에 자원 생성
	void setRandomTile();
	float getResRatio();

	
	int getPlayerPos();				// 플레이어의 최초 좌표값 구하기
	void setPlayerPosTile(); 		// 플레이어 좌표 세팅
	bool checkCanMove(int index);	// 플레이어가 이동할 타일 이동 가능 여부 체크

	void createDropItem(int i, int j, string pitemName, int minDrop, int maxDrop);
	void removeDropItem(int index);
	void dropItemCollision();
	void save();
	void load();
	vector<tile> getTiles() { return _vTiles; };
	void setMapTiles(vector<tile> checkTiles) { _vTiles = checkTiles; }
	void setTiles(vector<tile> _tiles) { _vTiles = _tiles; };
	tile tileMouseTarget();

	void animation();
};



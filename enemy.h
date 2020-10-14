#pragma once
#include "unit.h"
#include "ForagerPlayer.h"

#define PI 3.1415926f


enum SKULLSTATE
{
	STAY,	//걸어다니는 이미지랑 
	ATTACK,
	APPEAR,
	IDLE2
};

enum COWSTATE
{
	IDLE3,
	WALK,
	DASH,

};

enum WRAITHSTATE
{
	FLY,
	SHOOT
};

class earth;
class enemy :public unit
{
protected:
	
	ForagerPlayer* _target;
	earth* _map;


	int FindEnemyTilePos();


protected : 

	SKULLSTATE _state;
	COWSTATE _state2;
	WRAITHSTATE _state3;
	int _index;
	int _attackIndex;
	int _count;
	int _enemyMoveCount;
	int _appearCount;
	float enemySpeedX;
	float enemySpeedY;
	float _angle;
	bool isLeft;
	bool isAngle;
	bool enemyMoving;
	bool checkDestination;

	int _enemyTilePos;


	
	vector<int> _vDestTileIndex;
	int _destCount;

public:
	void setLinkMap(earth* map) { _map = map; };
	earth* getMap() { return _map; };
	 void setEnemy(string key, string itemkey, ForagerPlayer* target, POINT pos);
	 void render(HDC hdc) override ;
	 void update() override;
	 void dead()override;
	
	//virtual void move(vector<int> vDestTileIndex);
};


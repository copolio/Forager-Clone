#pragma once
#include "unit.h"
#include "earth.h"


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
	WALK,
	DASH,
};

class earth;
class enemy :public unit
{
protected:
	
	unit* _target;
	earth* _map;


	int FindEnemyTilePos();


protected : 

	SKULLSTATE _state;
	COWSTATE _state2;
	int _index;
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
	virtual void setEnemy(string key, string itemkey, unit* target);
	virtual void render(HDC hdc) override;
	virtual void update() override;
	virtual void dead() override;
	

	
	

	
	
	
	
	
	

	

};


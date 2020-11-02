#pragma once
#include "unit.h"
#include "ForagerPlayer.h"

#define PI 3.1415926f


class earth;
class enemy :public unit
{
protected:
	
	ForagerPlayer* _target;
	earth* _map;


	int FindEnemyTilePos();


protected : 

	
	
	
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
	 void setEnemy(string key, string itemkey, ForagerPlayer* target, POINT pos, int p_hp = 100);
	 void render(HDC hdc) override ;
	 void update() override;
	 void hurt(int damage, bool onlyEffect = false) override;
	 void dead() override;

	 float shootToTarget();
	 
	//virtual void move(vector<int> vDestTileIndex);
};


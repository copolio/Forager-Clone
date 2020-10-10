#pragma once
#include "unit.h"

#define PI 3.1415926f


enum SKULLSTATE
{
	STAY,	//걸어다니는 이미지랑 
	ATTACK,
	APPEAR
};

enum COWSTATE
{
	WALK,
	DASH,
};

class enemy :public unit
{
protected:
	
	unit* _target;
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

public:
	
	
	

	virtual void setEnemy(string key, string itemkey, unit* target);
	virtual void render(HDC hdc) override;
	virtual void update() override;
	virtual void dead() override;
	
	
	
	
	

	

};


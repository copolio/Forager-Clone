#include "stdafx.h"
#include "enemy.h"

void enemy::render(HDC hdc)
{
	
	

}

void enemy::update()
{
	

}

void enemy::setEnemy(string key, string itemkey, unit* target)
{
	maxHp = 30;
	currentHp = 30;
	tag = TAG::ENEMY;
	layer = LAYER::OBJECT;
	_state = SKULLSTATE::APPEAR;

	//_state2 = COWSTATE::WALK;
	_target = target;

	x = WINSIZEX / 2 + 200;
	y = WINSIZEY / 2 ;
	rc = RectMakeCenter(x, y, 25, 25);
	exp = 0;
	dropItem.itemKey = itemkey;
	objKey = key;
	objFrameX = 0;
	objFrameY = 0;

	enemySpeedX = 3;
	enemySpeedY = 3;
	_index = 0;
	_count = 0;
	_appearCount = 0;
	
	enemyMoving = false;
	isLeft = false;
	isAngle = false;
}



void enemy::dead()
{
	UNITMANAGER->AddUnits(dropItem.itemKey, { GetCenterX(),GetCenterY() });
}







	

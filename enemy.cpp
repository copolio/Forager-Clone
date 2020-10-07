#include "stdafx.h"
#include "enemy.h"



void enemy::render(HDC hdc)
{
	
	

}

void enemy::update()
{
	this->skullAnimation();
}

void enemy::setEnemy()
{
	maxHp = 10;
	currentHp = 10;
	tag = TAG::ENEMY;
	layer = LAYER::OBJECT;
	_state = SKULLSTATE::STAY;
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 50, 50);
	exp = 0;
	dropItem.itemKey = "dropBerry";
	objKey = "skull";
	objFrameX = 0;
	objFrameY = 0;

	isLeft = false;
	_index = 0;
	_count = 0;
}

void enemy::dead()
{
	UNITMANAGER->AddUnits(dropItem.itemKey, { GetCenterX(),GetCenterY() });
}

void enemy::skullAnimation()
{
	switch (_state)
	{
	case STAY:
			
		if (isLeft)
		{
			objFrameY = 1;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index-- <= 0)
					_index = 4;
			}
		}
		else
		{
			objFrameY = 0;
			objFrameX = _index;
			if (_count++ % 10 == 0)
			{
				if (_index++ > 5)
					_index = 0;
			}

		}

		break;
	}

}

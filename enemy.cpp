#include "stdafx.h"
#include "enemy.h"



void enemy::render(HDC hdc)
{
	
	

}

void enemy::update()
{
	this->skullAnimation();
	this->skullMove();
}

void enemy::setEnemy()
{
	maxHp = 30;
	currentHp = 30;
	tag = TAG::ENEMY;
	layer = LAYER::OBJECT;
	_state = SKULLSTATE::STAY;
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 25, 25);
	exp = 0;
	dropItem.itemKey = "dropBerry";
	objKey = "skull";
	objFrameX = 0;
	objFrameY = 0;
	dir.x = RANDOM->range(-1,1);
	dir.y = RANDOM->range(-1, 1);

	_index = 0;
	_count = 0;
	_isMoveVertical = false;
	isLeft = false;
	_isUp = false;
	isAngle = false;

	
	skullMoveRandomTileCount = 0;
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

void enemy::skullMove()
{
	if (_isMoveVertical)
	{
		if (isLeft)
		{
			bool _cantMove = false;
			int applySpeed = (isLeft) ? -1 : 1;
			applySpeed = (_isUp) ? -1 : 1;

			if (!_cantMove)
			{
				OffsetRect(&rc, applySpeed * dir.x, applySpeed * dir.y);
			}
		}
		

		//else
		//{
		//	float x = applySpeed * cosf(angle);
		//	float y = applySpeed * sinf(angle);
		//	OffsetRect(&rc, x, y);
		//}
	}
}

float enemy::skullToPlayerAngle()
{
	




	return 0.0f;
}






	

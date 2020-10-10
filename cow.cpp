#include "stdafx.h"
#include "cow.h"

HRESULT cow::init()
{

	cowMoveCount = 0;
	cowIdleCount = 0;
	cowAttackRange = 300;
	_state = STAY;
	return S_OK;
}

void cow::update()
{
	cowAnimation();
	//cowMove();
	cowLookDirection();
}

void cow::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom + 16));
		_hpBar.render(hdc);
	}

	switch (_state)
	{
	case STAY:
		
		IMAGEMANAGER->frameRender("cow", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	case ATTACK:
		
		IMAGEMANAGER->frameRender("cowDash", hdc, CAMERA->GetRelativeX(rc.left - 13),
			CAMERA->GetRelativeY(rc.top - 10), objFrameX, objFrameY, CAMERA->GetZoom());
		break;
	}
}

void cow::cowMove()
{
	if (!isAngle)
	{
		_angle = RANDOM->range(0.0f, 360.0f);
		enemyMoving = true;
		isAngle = true;
		_state = ATTACK;
		cowMoveCount = 0;
	}

	if (cowIdleCount < 50 && enemyMoving == false && isAngle)
	{
		cowIdleCount++;
	}
	else if (cowIdleCount >= 50 && enemyMoving == false && isAngle) {
		isAngle = false;
		cowIdleCount = 0;
	}

	if (enemyMoving)
	{
		if (cowMoveCount < 50)
		{
			cowMoveCount++;
			x += cosf(_angle*(PI / 180))*enemySpeedX;
			y += -sinf(_angle*(PI / 180))*enemySpeedY;
			rc = RectMakeCenter(x, y, 25, 25);
		}
		else
		{
			enemyMoving = false;
			cowIdleCount = 0;
			_state = STAY;
		}
	}
}

void cow::canAttackCheck()
{
	if (abs(_target->rc.left - rc.left) <= cowAttackRange && abs(_target->rc.top - rc.top) <= cowAttackRange)
		_state = ATTACK;
	else
		_state = STAY;
}

void cow::cowAnimation()
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
					_index = 5;
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
	case ATTACK:
		if (isLeft)
		{
			objFrameY = 1;
			objFrameX = _index;
			if (_count++ % 5 == 0)
			{
				if (_index-- <= 0)
					_index = 7;		
			}
		}
		else
		{
			objFrameY = 0;
			objFrameX = _index;
			if (_count++ % 5 == 0)
			{
				if (_index++ > 7)
					_index = 0;
			}
		}
		break;
	
	}
}

void cow::cowLookDirection()
{
	if (_state == STAY || _state == ATTACK)
	{
		if (rc.right > _target->rc.right && rc.left > _target->rc.left)
			isLeft = true;
		else
			isLeft = false;
	}
}

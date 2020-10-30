#include "stdafx.h"
#include "slimeBoss.h"

HRESULT slimeBoss::init()
{
	currentJumpSpeed = 0;
	lerpRatio = 0.03f;
	jumpTime = 300;
	jumpWaitTime = 0;
	slimeFireCount = 0;
	shootDelayTime = 0;
	searchCount = 0;
	slimeShootCount = 0;
	_isJump = false;
	_canJump = false;
	_slimeGotDamage = false;
	isattacking = false;
	originPos = { GetCenterX(), GetCenterY() };


	return S_OK;
}

void slimeBoss::update()
{
	
	slimeBossAnimation();
	if (isHit)
	{
		targetDest();
		slimeMove();
	}

	slimeShootCount++;
	if (slimeShootCount == 180)
	{
		if (abs(_target->GetCenterX() - x) < MOVEMAX * 2.0f && abs(_target->GetCenterY() - y) < MOVEMAX * 2.0f);
		slimeFire();
		slimeShootCount = 0;
	}
	
}

void slimeBoss::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(x), CAMERA->GetRelativeY(y + 15));
		_hpBar.render(hdc);
	}
	IMAGEMANAGER->frameRender("slimeBoss", hdc, CAMERA->GetRelativeX(x - 55),
		CAMERA->GetRelativeY(y - 55), objFrameX, objFrameY, CAMERA->GetZoom());
}

void slimeBoss::slimeBossAnimation()
{
	objFrameX = _index;
	if (_count++ % 10 == 0)
	{
		if (_index++ > 4)
			_index = 0;
	}
}

void slimeBoss::targetDest()
{
	destPos.x = _target->GetCenterX();
	destPos.y = _target->GetCenterY();
}

void slimeBoss::slimeFire()
{
	UNITMANAGER->GetProjectileMG()->CreateProjectile("slimeBossMissile", x, y, 10, shootToTarget(), 4, 30, true, false);
}

void slimeBoss::slimeMove()
{
	
	if (abs(x - destPos.x) > enemySpeedX || abs(y - destPos.y) > enemySpeedY)
	{
		if (destPos.x < x)
			x += -enemySpeedX;
		else if (destPos.x > x)
			x += enemySpeedX;
		if (destPos.y > y)
			y += enemySpeedY;
		else if (destPos.y < y)
			y += -enemySpeedY;
	}
}




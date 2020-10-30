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
	_canSpawn = false;
	return S_OK;
}

void slimeBoss::update()
{
	
	slimeBossAnimation();

	if (s_allAttack) {
		isHit = true;
	}

	if (isHit)
	{
		targetDest();
		slimeMove();
	}

	slimeShootCount++;
	if (slimeShootCount == 180)
	{
		s_allAttack = false;
		if (abs(_target->GetCenterX() - x) < MOVEMAX * 2.0f && abs(_target->GetCenterY() - y) < MOVEMAX * 2.0f);
		slimeFire();
		slimeShootCount = 0;
	}
	if (_canSpawn) {
		if (searchCount++ % 250 == 0 && searchCount <= 10000) {
			SPAWNMANAGER->SpawnPatternOne("slime", 1);
		}
	}
}

void slimeBoss::hurt(int Damage, bool onlyEffect)
{
	unit::hurt(Damage, onlyEffect);
	s_allAttack = true;
}

void slimeBoss::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(x-23), CAMERA->GetRelativeY(y + 63));
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
	UNITMANAGER->GetProjectileMG()->CreateProjectile("slimeBossMissile", x, y, atk, shootToTarget(), 4, 30, true, false);
}

void slimeBoss::slimeMove()
{

	if (abs(x - destPos.x) > 100) {
		if (destPos.x < x)
			x += -enemySpeedX;
		else if (destPos.x > x)
			x += enemySpeedX;
	}
	if (abs(y - destPos.y) > 100) {

		if (destPos.y > y)
			y += enemySpeedY;
		else if (destPos.y < y)
			y += -enemySpeedY;
	}
	_fRc = fRectMakeCenter(x, y, 56, 70);	//이미지 출력용 렉트
	rc = RectMakeCenter(x, y, 56, 70);		//충돌용 렉트
}





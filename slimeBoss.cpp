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
	_isJump = false;
	_canJump = false;
	_slimeGotDamage = false;
	originPos = { GetCenterX(), GetCenterY() };


	return S_OK;
}

void slimeBoss::update()
{
	if (!_canJump)
	{
		jumpWaitTime++;
		if (jumpWaitTime >= jumpTime)
		{
			if (isHit) {
				_canJump = true;
				targetDest();
			}
			jumpWaitTime = 0;
		}
		if (jumpWaitTime == 180)
		{
			if (abs(_target->GetCenterX() - x) < MOVEMAX * 2.0f && abs(_target->GetCenterY() - y) < MOVEMAX * 2.0f)
			{
				slimeFire();
			}
			
		}
	}

	currentPos = { GetCenterX(), GetCenterY() };

	if (isHit)
		slimeJump();
	slimeBossAnimation();
}

void slimeBoss::render(HDC hdc)
{
	if (0 < currentHp && currentHp < maxHp) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom + 15));
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

void slimeBoss::slimeJump()
{
	if (_canJump)	//점프할 수 있을 때, 
	{
		if (abs(currentPos.x - destPos.x) > 2)
		{
			//이동한 거리에서의 3% 씩 다가가.
			float lerpSpdX = (destPos.x - currentPos.x) * (lerpRatio);
			x += lerpSpdX;

			if (originPos.x < destPos.x)
			{
				if (currentPos.x < midPos.x)
					jumpUp();
				else if (destPos.y >= currentPos.y)
					jumpDown();
			}
			else
			{
				if (currentPos.x > midPos.x)
					jumpUp();
				else if (destPos.y >= currentPos.y)
					jumpDown();
			}
		}
		else if (destPos.y >= currentPos.y)
			jumpDown();
		else
			jumpStop();

		_fRc = fRectMakeCenter(x, y, 112, 112);	//이미지 출력용 렉트
		rc = RectMakeCenter(x, y, 112, 112);		//충돌용 렉트
	}
}

void slimeBoss::jumpUp()
{
	float lerpSpdY = 0.0f;
	// 타겟이 위
	if (originPos.y > destPos.y)
	{
		lerpSpdY = (midPos.y + JUMPMAX - currentPos.y) * (0.05f);
	}
	// 타겟이 아래
	else {
		lerpSpdY = (midPos.y - currentPos.y) * (0.05f);
		if (lerpSpdY >= 10.0f)
			lerpSpdY = 10.0f;
	}
		
	y += -abs(lerpSpdY);
	cout << lerpSpdY << endl;
}

void slimeBoss::jumpDown()
{
	y += currentJumpSpeed;

	currentJumpSpeed += 0.07f;
	if (currentJumpSpeed >= 4.0f)
		currentJumpSpeed = 4.0f;
}

void slimeBoss::jumpStop()
{
	_canJump = false;
	jumpWaitTime = 0;
	originPos = destPos;
	UNITMANAGER->GetProjectileMG()->CreateProjectile(x, y, 20, 70, 70);
}

void slimeBoss::targetDest()
{
	destPos.x = _target->GetCenterX();
	destPos.y = _target->GetCenterY();
	midPos.y = destPos.y + JUMPMAX;
	midPos.x = (originPos.x + destPos.x) / 2;
	currentJumpSpeed = 0.0f;
}

void slimeBoss::slimeFire()
{
	UNITMANAGER->GetProjectileMG()->CreateProjectile("slimeBossMissile", x, y, 10, shootToTarget(), 4, 30, true, false);
}


#include "stdafx.h"
#include "slime.h"

void slime::jumpUp()
{
	float lerpSpdY = (midPos.y + JUMPMAX - currentPos.y) * (0.05f);
	y += -abs(lerpSpdY);
}

void slime::jumpDown()
{
	y += currentJumpSpeed;

	currentJumpSpeed += 0.07f;
	if (currentJumpSpeed >= 4.0f)
		currentJumpSpeed = 4.0f;
	
}

void slime::jumpStop()
{
	_canJump = false;
	jumpWaitTime = 0;
	originPos = destPos;
	UNITMANAGER->GetProjectileMG()->CreateProjectile(x, y, 20, 70, 70);
	slimeFire();
}

HRESULT slime::init()
{
	currentJumpSpeed = 0;
	lerpRatio = 0.03f;
	jumpTime = 180;
	jumpWaitTime = 0;
	slimeFireCount = 0;
	_isJump = false;
	_canJump = false;
	originPos = { GetCenterX(), GetCenterY() };
	
	return S_OK;
}

void slime::update()
{
	if (!_canJump)
	{
		jumpWaitTime++;
		if (jumpWaitTime >= jumpTime)
		{
			_canJump = true;
			targetDest();
			jumpWaitTime = 0;
		}
	}
		
	currentPos = { GetCenterX(), GetCenterY() };
	slimeJump();
	slimeAnimation();
	
}

void slime::render(HDC hdc)
{
	IMAGEMANAGER->frameRender("slime", hdc, CAMERA->GetRelativeX(x - 25),
		CAMERA->GetRelativeY(y - 25), objFrameX, objFrameY, CAMERA->GetZoom());
}

void slime::slimeAnimation()
{
	objFrameX = _index;
	if (_count++ % 10 == 0)
	{
		if (_index++ > 5)
			_index = 0;
	}
}

void slime::slimeJump()
{
	if (_canJump)
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

		_fRc = fRectMakeCenter(x, y, 56, 70);	//이미지 출력용 렉트
		rc = RectMakeCenter(x, y, 56, 70);		//충돌용 렉트
	}
}

void slime::targetDest()
{
	if (abs(_target->GetCenterX() - x) < MOVEMAX && abs(_target->GetCenterY() - y) < MOVEMAX)
	{
		destPos.x = _target->GetCenterX();
		destPos.y = _target->GetCenterY();
		midPos.y = (originPos.y + destPos.y) / 2;
	}
	else
	{
		//가로 좌우 랜덤 점프 
		destPos.x = RANDOM->range(originPos.x - MOVEMAX, originPos.x + MOVEMAX);
		destPos.y = originPos.y;
		midPos.y = (originPos.y + destPos.y) / 2;
	}

	midPos.x = (originPos.x + destPos.x) / 2;
	currentJumpSpeed = 0.0f;
}

void slime::slimeFire()
{
	UNITMANAGER->GetProjectileMG()->CreateProjectile("slimeMissile", x,y, 10, shootToTarget(), 5, 50, true, false);
}

float slime::shootToTarget()
{
	int l = rc.left;
	int r = rc.right;
	int t = rc.top;
	int b = rc.bottom;

	int cX = l + (r - l) / 2;
	int cY = t + (b - t) / 2;

	int pL = _target->rc.left;
	int pR = _target->rc.right;
	int pT = _target->rc.top;
	int pB = _target->rc.bottom;

	int cPx = pL + (pR - pL) / 2;
	int cPy = pT + (pB - pT) / 2;

	return atan2(-(cPy - cY), (cPx - cX))/PI*180;
	
}



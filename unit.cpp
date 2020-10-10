#include "stdafx.h"
#include "unit.h"

void unit::hurt(int damage)
{
	currentHp -= damage;

	if (currentHp <= 0)
		dead();

	else
		isHit = true;
}



void unit::update()
{
	animation();
}

void unit::animation()
{
	if (isHit) {
		if (currentCount++ >= nextCount) {
			currentCount = 0;
			if (objFrameX++ >= objMaxFrameX)
			{
				objFrameX = 0;
				isHit = false;
			}
		}
	}
}

void unit::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY);
}

bool unit::isDead()
{
	if (currentHp <= 0) 
		return true; 
	else 
		return false;
}



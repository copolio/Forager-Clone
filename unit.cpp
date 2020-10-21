#include "stdafx.h"
#include "unit.h"

void unit::hurt(int damage)
{
	currentHp -= damage;

	if (currentHp <= 0)
		dead();

	else
		isHit = true;
	SOUNDMANAGER->play("나무타격");
}


void unit::update()
{
	animation();
	count++;
}

void unit::animation() 
{
	if (frameX < 0) frameX = 0;
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
	if (objKey == "bridge") {
		if (frameX > 3) frameX = 0;
		objFrameX = frameX;
		if (count%15 == 0) frameX++;
	}
	if (objKey == "fishtrap") {
		if (frameX > 2) frameX = 0;
		objFrameX = frameX;
		if (count % 20 == 0) frameX++;
	}
}

void unit::dead()
{
	SOUNDMANAGER->play("바위파괴");
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



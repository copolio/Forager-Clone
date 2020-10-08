#include "stdafx.h"
#include "unit.h"

void unit::hurt(int damage)
{
	currentHp -= damage;
	if (currentHp <= 0)
		dead();
}

void unit::update()
{

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

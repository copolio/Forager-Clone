#include "stdafx.h"
#include "fieldItem.h"

void fieldItem::animation()
{


	if (rc.top <= minY)
		isUp = false;
	else if (rc.top >= maxY)
		isUp = true;

	int applySpeed = (isUp) ? -1 : 1;

	if (currentCount++ % 35 == 0)
		OffsetRect(&rc, 0, applySpeed);

	if (_disappearCount-- <= 0) {
		currentHp = 0;
	}
}

void fieldItem::setFieldItem(POINT ptPos, string itemKey)
{
	tileIndex = 0;
	_disappearCount = 600;

	objKey = itemKey;
	dropItem.itemKey = itemKey;


	x = ptPos.x + RANDOM->range(-40, 40);
	y = ptPos.y + RANDOM->range(-80, 0);
	rc = RectMakeCenter(x, y, 56, 56);
	minY = rc.top - 5;
	maxY = rc.top;
	OffsetRect(&rc, 0, RANDOM->range(-5, 0));

	layer = LAYER::OBJECT;
	tag = TAG::ITEM;

	maxHp = 100;
	currentHp = 100;
	objFrameX = 0;
	objFrameY = 0;	
	objMaxFrameX = 0;
	objMaxFrameY = 0;
	currentCount = 0;
	nextCount = 0;
}

void fieldItem::collision()
{
	currentHp = 0;
}

void fieldItem::render(HDC hdc)
{
	IMAGEMANAGER->render(objKey, hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom), CAMERA->GetZoom());
}

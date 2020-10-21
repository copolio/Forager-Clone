#include "stdafx.h"
#include "fishTrap.h"

void fishTrap::setFishTrap(string buildingName, tile* _tile, int tileindex)
{
	building::setBuilding(buildingName, _tile, tileindex);

	_cntfishWait = 0;
	_fishWait = 300;
	hasRes = false;
	nextCount = 60;
}

void fishTrap::update()
{

	if (!hasRes) {
		if (_cntfishWait++ >= _fishWait) {
			_cntfishWait = 0;
			hasRes = true;
		}
	}


}

void fishTrap::render(HDC hdc)
{
	if (hasRes) {
		TEXTMANAGER->ShowText(hdc, true, "ÀâÈû", { rc.left+30, rc.top-25 }, 25, 1, RGB(255, 255, 255), true, RGB(0, 30, 0), 1);
	}

	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY);
}


#include "stdafx.h"
#include "fishTrap.h"

void fishTrap::setFishTrap(string buildingName, tile* _tile, int tileindex)
{
	building::setBuilding(buildingName, _tile, tileindex);

	_cntfishWait = 0;
	_fishWait = 3000;
	hasRes = false;
	nextCount = 60;
}

void fishTrap::update()
{
	count++;
	if (!hasRes) {
		if (_cntfishWait++ >= _fishWait) {
			_cntfishWait = 0;
			hasRes = true;
		}
	}

	if (objKey == "fishtrap") {
		if (objFrameX < 0) objFrameX = 0;
		if (count % 15 == 0) {
			objFrameX += waveUp ? 1 : -1;

			if (objFrameX > 2 || objFrameX < 1) {
				waveUp = !waveUp;
			}
		}
	}
}

void fishTrap::render(HDC hdc)
{
	if (hasRes && CAMERA->movelimit) {
		TEXTMANAGER->ShowText(hdc, true, "ÀâÈû", { long((rc.left+30)), long((rc.top-25)) }, 25, 1, RGB(255, 255, 255), true, RGB(0, 30, 0), 1);
	}

	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY, CAMERA->GetZoom());
}


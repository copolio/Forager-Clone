#include "stdafx.h"
#include "fishTrap.h"

#define INTERACTION_DISTANCE 70
void fishTrap::setFishTrap(string buildingName, tile* _tile, int tileindex)
{
	building::setBuilding(buildingName, _tile, tileindex);
	_cntfishWait = 0;
	_fishWait = 1000;
	_isCatch = false;
	nextCount = 60;
	sizeMin = 15;
	sizeCurrent = 20;
	sizeMax = 25;
	sizeUp = true;
	waveUp = false;
	objFrameX = 1;
}

void fishTrap::update()
{
	animation();
	fish();
}

void fishTrap::animation()
{
	// 애니메이션
	if (count++ % 15 == 0) {
		objFrameX += waveUp ? 1 : -1;
		if (objFrameX > 2 || objFrameX < 1) {
			waveUp = !waveUp;
		}
	}

	// "잡힘" 스케일 조절
	if (_isCatch) {
		if (count % 5 == 0) {
			sizeCurrent += sizeUp ? 1 : -1;

			if (sizeCurrent <= sizeMin || sizeCurrent >= sizeMax)
				sizeUp = !sizeUp;
		}
	}
}

void fishTrap::fish()
{
	if (!_isCatch) {
		if (_cntfishWait++ >= _fishWait) {
			_cntfishWait = 0;
			_isCatch = true;
		}
	}
	else {
		POINT t_relMouse = CAMERA->GetMouseRelativePos(_ptMouse);
		if (abs(t_relMouse.x - GetCenterX()) <= INTERACTION_DISTANCE && abs(t_relMouse.y - GetCenterY()) <= INTERACTION_DISTANCE) {
			if (INPUT->GetKeyDown('E')) {
				unit* t_target = _cursor->GetTargetUnit();
				_isCatch = false;
				UNITMANAGER->AddUnits("fish", CAMERA->GetMouseRelativePos(_ptMouse));
			}
		}
	}
}

void fishTrap::render(HDC hdc)
{
	int relX = CAMERA->GetRelativeX(rc.left);
	int relY = CAMERA->GetRelativeY(rc.bottom);

	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY, CAMERA->GetZoom());

	if (_isCatch && CAMERA->movelimit) {
		TEXTMANAGER->ShowText(hdc, true, "잡힘", { long((rc.left + 28)), long((rc.top - 15)) }, sizeCurrent, 1, RGB(255, 255, 255), true, RGB(0, 30, 0), 1);
		POINT t_relMouse = CAMERA->GetMouseRelativePos(_ptMouse);
		if (abs(t_relMouse.x - GetCenterX()) <= INTERACTION_DISTANCE && abs(t_relMouse.y - GetCenterY()) <= INTERACTION_DISTANCE) {
			IMAGEMANAGER->render("E", hdc, relX + 45, relY - 35, CAMERA->GetZoom());
		}
	}

}


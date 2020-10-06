#include "stdafx.h"
#include "building.h"

void building::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY);
}

void building::setBuilding(string buildingName, vector<tile*> tiles)
{
	_tiles = tiles;
	this->rc = _tiles[0]->rc;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::OBJECT;
	this->objFrameX = 0;
	this->objFrameY = 0;
	this->objKey = buildingName;
	this->dropItem.itemKey = "treeDrop";
	this->maxHp = BUILDINGHP;
	currentHp = maxHp;
}

void building::dead()
{
	// 파괴되면 필드아이템 생성
	UNITMANAGER->AddUnits(dropItem.itemKey, { GetCenterX(), GetCenterY() - 25 });

	for (int i = 0; i < _tiles.size(); i++) {
		_tiles[i]->hasUnit = false;
	}
}

#include "stdafx.h"
#include "building.h"

void building::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY, CAMERA->GetZoom());
}

void building::setBuilding(string buildingName, tile* _tile)
{
	_tiles.push_back(_tile);
	RECT temp = _tile->rc;
	this->rc = temp;
	this->layer = LAYER::OBJECT;
	this->objMaxFrameX = 2;
	this->objMaxFrameY = 0;
	if (buildingName == "bridge") {
		_tile->canPass = true;
		this->layer = LAYER::TERRAIN; 
		this->objMaxFrameX = 3;
	}
	this->tag = TAG::BUILDING;
	this->objFrameX = 0;
	this->objFrameY = 0;
	this->currentCount = 0;
	this->nextCount = 2;
	this->objKey = buildingName;
	this->dropItem.itemKey = "treeDrop";
	this->maxHp = BUILDINGHP;
	this->exp = 0;
	currentHp = maxHp;
}

void building::setBuilding(string buildingName, vector<tile*> tiles)
{
	_tiles = tiles;
	RECT temp = { _tiles[0]->rc.left, _tiles[0]->rc.top, _tiles[3]->rc.right, _tiles[3]->rc.bottom };
	this->rc = temp;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::BUILDING;
	this->objFrameX = 0;
	this->objFrameY = 0;
	this->objMaxFrameX = 2;
	this->objMaxFrameY = 0;
	this->currentCount = 0;
	this->nextCount = 2;
	this->objKey = buildingName;
	this->dropItem.itemKey = "treeDrop";
	this->maxHp = BUILDINGHP;
	this->exp = 0;
	currentHp = maxHp;
}

void building::dead()
{
	// 파괴되면 필드아이템 생성
	UNITMANAGER->AddUnits(dropItem.itemKey, { GetCenterX(), GetCenterY() - 25 });

	for (int i = 0; i < _tiles.size(); i++) {
		_tiles[i]->hasUnit = false;
		_tiles[i]->canPass = (objKey == "bridge") ? false : true;
	}
}

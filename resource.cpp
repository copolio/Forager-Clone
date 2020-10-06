#include "stdafx.h"
#include "resource.h"

void resource::setRandomRes(tile* tile)
{
	_tile = tile;
	this->rc = _tile->rc;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::OBJECT;
	this->objFrameX = 0;
	this->objFrameY = 0;
	switch (RANDOM->range(NUMRES)) {
	case 0:
		this->objKey = "berry";
		this->dropItem.itemKey = "berryDrop";
		this->hp = BERRYHP;
		break;
	case 1:
		this->objKey = "rock";
		this->dropItem.itemKey = "rockDrop";
		this->hp = ROCKHP;
		break;
	case 2:
		this->objKey = "tree";
		this->dropItem.itemKey = "treeDrop";
		this->hp = TREEHP;
		break;
	}
	currentHp = hp;
}

void resource::dead()
{
	POINT ptCenterPos = { GetCenterX(), GetCenterY() - 10 };

	// 파괴되면 필드아이템 생성
	UNITMANAGER->AddUnits(dropItem.itemKey, ptCenterPos);

	// 연기 이펙트
	EFFECTMANAGER->ShowEffectFrame(EFFECTMANAGER->smokeEff, ptCenterPos, 4, true);

	if(_tile != nullptr)
		_tile->hasUnit = false;
}

void resource::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY);
}

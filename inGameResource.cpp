#include "stdafx.h"
#include "inGameResource.h"

void inGameResource::setRandomRes(tile* tile, int ptileIndex)
{
	tileIndex = ptileIndex;
	_tile = tile;
	this->rc = _tile->rc;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::OBJECT;
	this->objFrameX = 0;
	this->objFrameY = 0;
	this->objMaxFrameY = 0;
	this->currentCount = 0;
	this->nextCount = 2;
	SOUNDMANAGER->play("아이템탄생");
	switch (RANDOM->range(NUMRES)) {
	case 0:
		this->objKey = "berry";
		this->dropItem.itemKey = "berryDrop";
		this->maxHp = BERRYHP;
		this->exp = 2;
		this->objMaxFrameX = 1;
		break;
	case 1:
		this->objKey = "rock";
		this->dropItem.itemKey = "rockDrop";
		this->exp = 10;
		this->maxHp = ROCKHP;
		this->objMaxFrameX = 1;
		break;
	case 2:
		this->objKey = "tree";
		this->dropItem.itemKey = "treeDrop";
		this->exp = 8;
		this->maxHp = TREEHP;
		this->objMaxFrameX = 4;
		break;
	}
	currentHp = maxHp;

	_hpBar.init("hpBar", "hpBarBG");
}

void inGameResource::setResource(string key, tile* p_tile, int p_tileIndex)
{
	_hpBar.init("hpBar", "hpBarBG");
	tileIndex = p_tileIndex;
	_tile = p_tile;
	this->rc = _tile->rc;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::OBJECT;
	this->objFrameX = 0;
	this->objFrameY = 0;
	this->objMaxFrameY = 0;
	this->currentCount = 0;
	this->nextCount = 2;
	
	if (key == "berry") {
		this->objKey = key;
		this->dropItem.itemKey = "berryDrop";
		this->maxHp = BERRYHP;
		this->exp = 7;
		this->objMaxFrameX = 1;
	}
	else if (key == "rock") {
		this->objKey = key;
		this->dropItem.itemKey = "rockDrop";
		this->exp = 7;
		this->maxHp = ROCKHP;
		this->objMaxFrameX = 1;
	}
	else if (key == "tree") {
		this->objKey = key;
		this->dropItem.itemKey = "treeDrop";
		this->exp = 7;
		this->maxHp = TREEHP;
		this->objMaxFrameX = 4;
	}
	currentHp = maxHp;
}

void inGameResource::dead()
{
	POINT ptCenterPos = { GetCenterX(), GetCenterY() - 10 };

	// 파괴되면 필드아이템 생성
	UNITMANAGER->AddUnits(dropItem.itemKey, ptCenterPos);

	// 연기 이펙트
	EFFECTMANAGER->ShowEffectFrame(EFFECTMANAGER->smokeEff, ptCenterPos, 4, true);

	if (_tile != nullptr)
	{
		_tile->hasUnit = false;
		_tile->canPass = true;
	}

	if (this->objKey == "berry") {
		SOUNDMANAGER->play("과일파괴");
	}
	if (this->objKey == "tree") {
		SOUNDMANAGER->play("나무파괴");
	}
	if (this->objKey == "rock") {
		SOUNDMANAGER->play("바위파괴");
	}
}

void inGameResource::render(HDC hdc)
{
	if ((float)currentHp / maxHp <= 0.8f) {
		_hpBar.setGauge(maxHp, currentHp, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.bottom));
		_hpBar.render(hdc);
	}

	IMAGEMANAGER->frameRender(objKey, hdc,
		CAMERA->GetRelativeX(rc.left),
		CAMERA->GetRelativeY(rc.bottom - IMAGEMANAGER->findImage(objKey)->getFrameHeight()),
		objFrameX, objFrameY, CAMERA->GetZoom());
}

void inGameResource::hurt(int damage, bool onlyEffect)
{
	if (this->objKey == "berry") {
		SOUNDMANAGER->play("과일타격");
	}
	if (this->objKey == "tree") {
		SOUNDMANAGER->play("나무타격");
	}
	if (this->objKey == "rock") {
		SOUNDMANAGER->play("바위타격");
	}
	isHit = true;

	if (onlyEffect)
		return;
	currentHp -= damage;
	if (currentHp <= 0)
		dead();
}



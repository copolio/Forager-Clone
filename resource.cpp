#include "stdafx.h"
#include "resource.h"

void resource::setRandomRes(tile* tile)
{
	_tile = tile;
	this->rc = _tile->rc;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::OBJECT;
	switch (RANDOM->range(NUMRES)) {
	case 0:
		this->objKey = "berry";
		this->dropItem.itemKey = "berryDrop";
		this->objFrameX = 0;
		this->objFrameY = 0;
		this->hp = BERRYHP;
		break;
	case 1:
		this->objKey = "rock";
		this->dropItem.itemKey = "rockDrop";
		this->objFrameX = 0;
		this->objFrameY = 0;
		this->hp = ROCKHP;
		break;
	case 2:
		this->objKey = "tree";
		this->dropItem.itemKey = "treeDrop";
		this->objFrameX = 0;
		this->objFrameY = 0;
		this->hp = TREEHP;
		break;
	}
	currentHp = hp;
}

void resource::setFieldItem(POINT ptPos, string itemKey)
{
	_tile = nullptr;
	x = ptPos.x + RANDOM->range(-30, 30);
	y = ptPos.y + RANDOM->range(-30, 30);
	objKey = itemKey;
	layer = LAYER::OBJECT;
	tag = TAG::ITEM;
	hp = 100;
	currentHp = 100;
	objFrameX = 0;
	objFrameY = 0;
	rc = RectMakeCenter(x, y, 56, 56);
}

void resource::getItem()
{
	currentHp = 0;
	// 인벤 겟 구현 필요
}

void resource::dead()
{
	if(_tile != nullptr)
		_tile->hasUnit = false;
}

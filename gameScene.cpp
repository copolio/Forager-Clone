#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	_map = new earth;
	return S_OK;
}

void gameScene::release()
{
	_map->release();
	SAFE_DELETE(_map);
}

void gameScene::update()
{
	_map->update();
}

void gameScene::render()
{
	_map->render(getMemDC());
}

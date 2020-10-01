#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	_map = new earth;
	_map->init();
	CAMERA->init(WINSIZEX/2, WINSIZEY/2, WINSIZEX / 2, WINSIZEY / 2, 0.5f, 0.5f, WINSIZEX + 250, WINSIZEX + 250, -2000, -2000, 2000, 2000);
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

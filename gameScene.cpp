#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	_player = new ForagerPlayer;
	_Meun = new inGameMenu;
	inven_open = false;
	_player->init();
	CAMERA->init(_player->getX(), _player->getY(), _player->getX(), _player->getY(), 0.5f, 0.5f, WINSIZEX, WINSIZEY, -2000, -2000, 2000, 2000);
	_Meun->init();
	return S_OK;
}

void gameScene::release()
{

	_player->release();
	_Meun->release();
}

void gameScene::update()
{
	_player->update();
	if (inven_open) {
		_Meun->update();
	}
	if (INPUT->GetKeyDown('I')) {
		if (inven_open) {
			inven_open = false;
			_player->setInvenOpen(false);
		}
		else {
			_player->setInvenOpen(true);
			inven_open = true;
		}
	}
	CAMERA->targetFollow(_player->getX(), _player->getY());
}

void gameScene::render()
{
	_player->render(getMemDC());
	if (inven_open) {
		_Meun->render(getMemDC());
	}
}

HRESULT gameScene::init()
{
	_map = new earth;
	_map->init();
	CAMERA->init(0, 0, WINSIZEX / 2, WINSIZEY / 2, 0.5f, 0.5f, WINSIZEX + 250, WINSIZEX + 250, -2000, -2000, 2000, 2000);
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

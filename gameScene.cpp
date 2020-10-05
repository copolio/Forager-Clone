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
		}
		else {
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

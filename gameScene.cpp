#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	_map = new earth;
	_player = new ForagerPlayer;
	_Meun = new inGameMenu;
	inven_open = false;
	_player->init();
	CAMERA->init(_player->getX(), _player->getY(), _player->getX(), _player->getY(), 0.5f, 0.5f, WINSIZEX, WINSIZEY, -2000, -2000, 2000, 2000);
	_Meun->init();
	_map->init();
	return S_OK;
}

void gameScene::release()
{

	_player->release();
	_Meun->release();
	_map->release();
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
	CAMERA->camFocusCursor(_ptMouse); // 마우스 커서에 따른 카메라 포거싱.
	_map->update();
}

void gameScene::render()
{
	_map->render(getMemDC());
	_player->render(getMemDC());
	if (inven_open) {
		_Meun->render(getMemDC());
	}
}

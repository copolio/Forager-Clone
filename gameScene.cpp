#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	_map = new earth;
	_map->init();
	_player = new ForagerPlayer;
	_player->setPMLink(_map);
	_player->init();
	_map->setLinkPlayer(_player);

	_cursor = new cursor;
	_cursor->init();
	_cursor->LinkMap(_map);
	_player->setCursorLink(_cursor);

	_Meun = new inGameMenu;
	_Meun->init();
	_player->setInvenLink(_Meun->GetInven());

	inven_open = false;
	
	CAMERA->init(_player->x, _player->y, _player->x, _player->y, 0.5f, 0.5f, WINSIZEX + 400, WINSIZEY + 300, -2000, -2000, 2000, 2000);
	UNITMANAGER->AddUnits(_player);
	return S_OK;
}

void gameScene::release()
{

	_player->release();
	_Meun->release();
	_map->release();
	SAFE_DELETE(_cursor);
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
	CAMERA->targetFollow(_player->rc.left, _player->rc.top);
	CAMERA->camFocusCursor(_ptMouse); // 마우스 커서에 따른 카메라 포거싱.
	EFFECTMANAGER->update();
	_map->update();

	// 인벤토리 열면 커서 타겟팅 업데이트 중지
	if(!inven_open)
		_cursor->update();
}

void gameScene::render()
{
	_map->render(getMemDC());
	EFFECTMANAGER->render(getMemDC());
	_cursor->render(getMemDC());
	if (inven_open) {
		_Meun->render(getMemDC());
	}
}

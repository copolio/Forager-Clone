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

	_Menu = new inGameMenu;
	_Menu->init();
	_Menu->setMapLink(_map);
	_player->setInvenLink(_Menu->GetInven());


	inven_open = false;
	
	_quick_slot = new quick_slot;
	_quick_slot->init();
	_quick_slot->quick_slot_update();
	_quick_slot->target(0);
	CAMERA->init(_player->x, _player->y, _player->x, _player->y, 0.5f, 0.5f, WINSIZEX + 400, WINSIZEY + 300, -2000*5, -2000 * 5, 2000 * 5, 2000 * 5);
	UNITMANAGER->AddUnits(_player);


	//스폰 매니져 구현시, 삭제!
	enemy* _enemy = new enemy;

	UNITMANAGER->AddUnits(_enemy,"skull");
	_enemy = new enemy;
	UNITMANAGER->AddUnits(_enemy,"cow");
	money_pos.x = 55;
	money_pos.y = WINSIZEY - 50;
	SCENEMANAGER->set_ischeck(true);
	return S_OK;
}

void gameScene::release()
{
	if (SCENEMANAGER->get_ischeck()) {

	
	_player->release();
	_Menu->release();
	_map->release();
	SAFE_DELETE(_cursor);
	_quick_slot->release();
	}
}

void gameScene::update()
{
	if (!_cursor->InteractionOpen()) {
		_player->update();

		if (INPUT->GetKeyDown('I')) {
			if (!CAMERA->movelimit) {
				CAMERA->forceZoomIn(0, 0.01f, false);
				CAMERA->movelimit = true;
			}
			if (inven_open) {
				inven_open = false;
				_player->setInvenOpen(false);
			}
			else {
				_player->setInvenOpen(true);
				inven_open = true;
				_Menu->settion();
			}
		}
	}
	if (inven_open && !_cursor->InteractionOpen()) {
		_Menu->update();
	}
	else {
		_quick_slot->update();
	}
	
	
	CAMERA->targetFollow(_player->rc.left, _player->rc.top);
	CAMERA->camFocusCursor(_ptMouse); // 마우스 커서에 따른 카메라 포거싱.
	CAMERA->update();
	EFFECTMANAGER->update();
	TEXTMANAGER->update();
	_map->update();

	// 인벤토리 열면 커서 타겟팅 업데이트 중지
	if(!inven_open)
		_cursor->update();

}

void gameScene::render()
{
	_map->render(getMemDC());
	EFFECTMANAGER->render(getMemDC());
	TEXTMANAGER->render(getMemDC());
	if (inven_open) {
		_Menu->render(getMemDC());
	}
	else {
		_quick_slot->render(getMemDC());
	}
	IMAGEMANAGER->render("img_game_money_icon", getMemDC(), 10, WINSIZEY - 50);
	
	TEXTMANAGER->ShowText(getMemDC(), to_string(ITEMMANAGER->getMoney()), money_pos, 38);
	_cursor->render(getMemDC());

	IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

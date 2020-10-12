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
	PRODUCTIONMANAGER->init();
	CAMERA->init(_player->x, _player->y, _player->x, _player->y, 0.5f, 0.5f, WINSIZEX + 400, WINSIZEY + 300, -2000*5, -2000 * 5, 2000 * 5, 2000 * 5);
	UNITMANAGER->AddUnits(_player);
	UNITMANAGER->setLinkMap(_map);

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
	PRODUCTIONMANAGER->relese();
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
	PRODUCTIONMANAGER->update();
	if (inven_open && !_cursor->InteractionOpen()) {
		_Menu->update();
	}
	else {
		_quick_slot->update();
	}
	
	CAMERA->update();
	CAMERA->targetFollow(_player->rc.left, _player->rc.top);
	CAMERA->camFocusCursor(_ptMouse); // ¸¶¿ì½º Ä¿¼­¿¡ µû¸¥ Ä«¸Þ¶ó Æ÷°Å½Ì.


	EFFECTMANAGER->update();
	TEXTMANAGER->update();
	_map->update();

	// ÀÎº¥Åä¸® ¿­¸é Ä¿¼­ Å¸°ÙÆÃ ¾÷µ¥ÀÌÆ® ÁßÁö
	if(!inven_open)
		_cursor->update();

}

void gameScene::render()
{
	_map->render(getMemDC());				// ¸Ê ·»´õ
	EFFECTMANAGER->render(getMemDC());		// ÀÌÆåÆ® ·»´õ
	TEXTMANAGER->render(getMemDC());		// ÅØ½ºÆ® ·»´õ
	PRODUCTIONMANAGER->render(getMemDC());	// »ý»êÇ° ·»´õ
	if (inven_open) 						// ¸Þ´º ·»´õ
		_Menu->render(getMemDC());
	else 
		_quick_slot->render(getMemDC());
	
											// °ñµå ·»´õ
	IMAGEMANAGER->render("img_game_money_icon", getMemDC(), 10, WINSIZEY - 50);
	TEXTMANAGER->ShowText(getMemDC(), to_string(ITEMMANAGER->getMoney()), money_pos, 38);
	_cursor->render(getMemDC());			// Å¸°ÙÆÃ ¹Ú½º ·»´õ
	CAMERA->render(getMemDC());				// Ä«¸Þ¶ó Å×½ºÆ® FrameRect ·»´õ
											// ¸¶¿ì½º Ä¿¼­ ·»´õ
	IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

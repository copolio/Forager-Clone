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

	//스폰 매니져 구현시, 삭제!
	//enemy* _enemy = new enemy;
	//skull* _skull = new skull;
	//_skull->setLinkMap(_map);
	//_skull->setEnemy("skull", "skullHeadDrop", _player);
	//_skull->init();

	//wraith* _wraith = new wraith;
	//_wraith->setLinkMap(_map);
	//_wraith->setEnemy("wraithIdle", "skullHeadDrop", _player);
	//_wraith->init();


	//UNITMANAGER->AddUnits(_skull ,true);

	//UNITMANAGER->AddUnits(_wraith,true);
	//_enemy = new enemy;
	//UNITMANAGER->AddUnits(_enemy,"cow");
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
	CAMERA->camFocusCursor(_ptMouse); // 마우스 커서에 따른 카메라 포거싱.


	EFFECTMANAGER->update();
	TEXTMANAGER->update();
	DIALOGUE->update();
	_map->update();

	// 인벤토리 열면 커서 타겟팅 업데이트 중지
	if(!inven_open)
		_cursor->update();

}

void gameScene::render()
{
	_map->render(getMemDC());				// 맵 렌더
	EFFECTMANAGER->render(getMemDC());		// 이펙트 렌더
	TEXTMANAGER->render(getMemDC());		// 텍스트 렌더
	PRODUCTIONMANAGER->render(getMemDC());	// 생산품 렌더
	DIALOGUE->render(getMemDC());			// 말풍선 렌더
	if (inven_open) 						// 메뉴 렌더
		_Menu->render(getMemDC());
	else 
		_quick_slot->render(getMemDC());
	
											// 골드 렌더
	IMAGEMANAGER->render("img_game_money_icon", getMemDC(), 10, WINSIZEY - 50);
	TEXTMANAGER->ShowText(getMemDC(), false, to_string(ITEMMANAGER->getMoney()), money_pos, 38);

	if (!_player->IsBow())
		_cursor->render(getMemDC());		// 타겟팅 박스 렌더
	CAMERA->render(getMemDC());				// 카메라 테스트 FrameRect 렌더
											// 마우스 커서 렌더
	

	if (_player->IsBow()){
		POINT clampPos = _player->GetBowXY();
		IMAGEMANAGER->findImage("BowCursor")->render(getMemDC(), clampPos.x, clampPos.y);
	}else
		IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}

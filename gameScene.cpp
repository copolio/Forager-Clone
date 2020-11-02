#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	IMAGEMANAGER->addImage("게임 오버","Images/이미지/NPC/game_over_scene.bmp", 1280, 720);

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
	_quick_slot->changeQuickSlot(0);
	_cursor->quick_slot_info(_quick_slot);
	SAVEMANAGER->set_quick_slot_info(_quick_slot);
	PRODUCTIONMANAGER->init();
	CAMERA->init(_player->x, _player->y, _player->x, _player->y, 0.5f, 0.5f, WINSIZEX + 400, WINSIZEY + 300, -2000*5, -2000 * 5, 2000 * 5, 2000 * 5);
	
	UNITMANAGER->setLinkMap(_map);
	UNITMANAGER->AddUnits(_player);
	

	_player->getquick_slotInfo(_quick_slot);
	STATMANAGER->ForagerPlayerinfo(_player);
	money_pos.x = 55;
	money_pos.y = WINSIZEY - 50;
	SCENEMANAGER->set_ischeck(true);

	SAVEMANAGER->set_Tile_info(_map);
	SAVEMANAGER->load();
	

	if (SOUNDMANAGER->isPlaySound("배경음악"))
	{
		SOUNDMANAGER->stop("배경음악");
	}
	SOUNDMANAGER->play("배경음악", true);
	ITEMMANAGER->quick_slot_info(_quick_slot);

	//UNITMANAGER->AddUnits("slimeBoss", { 300,300 });

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

		if (INPUT->GetKeyDown(VK_TAB)) {
			if (!CAMERA->movelimit) {
				CAMERA->forceZoomIn(0, 0.01f, false);
				CAMERA->movelimit = true;
			}
			if (inven_open) {
				inven_open = false;
				SOUNDMANAGER->play("인벤토리닫기");
				_player->setInvenOpen(false);
			}
			else {
				SOUNDMANAGER->play("인벤토리오픈");
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

	TEXTMANAGER->update();
	DIALOGUE->update();
	_map->update();

	// 인벤토리 열면 커서 타겟팅 업데이트 중지
	if(!inven_open)
		_cursor->update();
	
	if (INPUT->GetKeyDown(VK_F1)) {
		SAVEMANAGER->save();
	}
	if (INPUT->GetKeyDown(VK_F2)) {
		SAVEMANAGER->load();
	}
}


void gameScene::render()
{
	_map->render(getMemDC());				// 맵 렌더
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
	

	if (_player->IsBow() && !inven_open) {
		POINT clampPos = _player->GetBowXY();
		IMAGEMANAGER->findImage("BowCursor")->render(getMemDC(), clampPos.x, clampPos.y);
	}
	STATMANAGER->render(getMemDC());
	IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);

	
}

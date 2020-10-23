#include "stdafx.h"
#include "inGameMenu.h"

HRESULT inGameMenu::init()
{
	inven_imgs = new inventory_images;
	_inven_Kind = INVENTORY;

	_inven = new inventory;
	_equip = new equipMent;
	_construction = new construction;
	_purchaese = new purchase_land;
	_game_setting = new gamesetting;
	_buildinginteraction = new buildinginteraction;
	_buildinginteraction->init();
	inven_imgs->init();
	for (int i = 0; i < 5; i++) {
		MOUSEMENU *menu = new MOUSEMENU;
		menu->rc = RectMake(410 + i * 92, 30, 80, 80);
		ingameMenuRc.push_back(menu);
	}

	ingameMenuRc[0]->kinds = EQUIP;
	ingameMenuRc[1]->kinds = INVENTORY;
	ingameMenuRc[2]->kinds = CONSTRUCTION;
	ingameMenuRc[3]->kinds = PURCHASE_LAND;
	ingameMenuRc[4]->kinds = GAME_SETTING;
	_inven->init();
	_equip->init();
	_construction->init();
	_purchaese->init();
	_game_setting->init();

	ITEMMANAGER->setvInventory_info(_inven->get_inven());
	ITEMMANAGER->set_equip_info(_equip->getequip());
	ITEMMANAGER->setMoney(_inven->getMoney());

	IMAGEMANAGER->addImage("greentile", "Images/이미지/타일/img_tile_green.bmp", 56, 56);
	IMAGEMANAGER->addImage("redtile", "Images/이미지/타일/img_tile_red.bmp", 56, 56);

	return S_OK;
}

void inGameMenu::release()
{
	if (SCENEMANAGER->get_ischeck())
	{
		_inven->release();
		_equip->release();
		_construction->release();
		_purchaese->release();
		_game_setting->release();
		SAFE_DELETE(_inven);
		SAFE_DELETE(_equip);
		SAFE_DELETE(_construction);
		SAFE_DELETE(_purchaese);
		SAFE_DELETE(_game_setting);

		_inven = NULL;
		_equip = NULL;
		_construction = NULL;
		_purchaese = NULL;
		_game_setting = NULL;
	}
	for (int i = 0; i < ingameMenuRc.size(); i++) {
		SAFE_DELETE(ingameMenuRc[i]);
		ingameMenuRc[i] = NULL;
	}
}

void inGameMenu::update()
{
	inven_Change_Key_Down();
	if (_inven_Kind != PURCHASE_LAND && !CAMERA->movelimit) {
		CAMERA->forceZoomIn(0, 0.01f, false);
		CAMERA->movelimit = true;
	}
	switch (_inven_Kind)
	{
	case INVENTORY:
		_inven->update();
		break;
	case EQUIP:
		_equip->update();
		break;
	case CONSTRUCTION:
		_construction->update();
		break;
	case PURCHASE_LAND:
		if (CAMERA->movelimit) {
			CAMERA->forceZoomIn(-0.5f, -0.01f, false);
		 	CAMERA->movelimit = false;
		}
		_purchaese->update();
		break;
	case GAME_SETTING:
		_game_setting->update();
		break;
	}
	
	
}

void inGameMenu::render(HDC hdc)
{
	switch (_inven_Kind)
	{
	case INVENTORY:
		_inven->render(hdc);
		break;
	case EQUIP:
		_equip->render(hdc);
		break;
	case CONSTRUCTION:
		_construction->render(hdc);
		break;
	case PURCHASE_LAND:
		_purchaese->render(hdc);
		break;
	case GAME_SETTING:
		_game_setting->render(hdc);
		break;
	}
	mouse_touch_icon(hdc);
}

void inGameMenu::inven_Change_Key_Down()
{
	if (INPUT->GetKeyDown('Q') || INPUT->GetKeyDown('E')) {
		bool key = INPUT->GetKey('Q') ? true : false;
		SOUNDMANAGER->play("클릭");
		if (key) {
			switch (_inven_Kind)
			{
			case EQUIP:
				_purchaese->setIsCheck(false);
				_inven_Kind = GAME_SETTING;
				break;
			case INVENTORY:
				_equip->setIsCheck(false);
				_inven_Kind = EQUIP;
				break;
			case CONSTRUCTION:
				_inven->setIsCheck(false);
				_inven_Kind = INVENTORY;
				break;
			case PURCHASE_LAND:
				_construction->setIsCheck(false);
				_construction->setisTargetBox(false);
				_inven_Kind = CONSTRUCTION;
				break;
			case GAME_SETTING:
				_inven_Kind = PURCHASE_LAND;
				break;
			}
		
		}else {
			switch (_inven_Kind)
			{
			case EQUIP:
				_inven->setIsCheck(false);
				_inven_Kind = INVENTORY;
				break;
			case INVENTORY:
				_construction->setIsCheck(false);
				_construction->setisTargetBox(false);
				_inven_Kind = CONSTRUCTION;
				break;
			case CONSTRUCTION:
				_purchaese->setIsCheck(false);
				_inven_Kind = PURCHASE_LAND;
				break;
			case PURCHASE_LAND:
				_equip->setIsCheck(false);
				_inven_Kind = GAME_SETTING;
				break;
			case GAME_SETTING:
				_inven_Kind = EQUIP;
				break;
			}

		}

	}

}

void inGameMenu::mouse_touch_icon(HDC hdc)
{
	for (int i = 0; i < ingameMenuRc.size(); i++) {
		if (PtInRect(&ingameMenuRc[i]->rc, _ptMouse) && ingameMenuRc[i]->kinds != _inven_Kind) {
			switch (ingameMenuRc[i]->kinds)
			{
			case EQUIP:
				IMAGEMANAGER->render("mouse_equip_icon", hdc, ingameMenuRc[i]->rc.left+10, ingameMenuRc[i]->rc.top);
				break;
			case INVENTORY:
				IMAGEMANAGER->render("mouse_item_icon", hdc, ingameMenuRc[i]->rc.left, ingameMenuRc[i]->rc.top);
				break;
			case CONSTRUCTION:
				IMAGEMANAGER->render("mouse_construction_icon", hdc, ingameMenuRc[i]->rc.left+13, ingameMenuRc[i]->rc.top);
				break;
			case PURCHASE_LAND:
				IMAGEMANAGER->render("mouse_purchase_land", hdc, ingameMenuRc[i]->rc.left-20, ingameMenuRc[i]->rc.top);
				break;
			case GAME_SETTING:
				IMAGEMANAGER->render("mouse_game_setting", hdc, ingameMenuRc[i]->rc.left+9, ingameMenuRc[i]->rc.top);
				break;
			}
			if (INPUT->GetKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("클릭");
				_inven_Kind = ingameMenuRc[i]->kinds;
				switch (ingameMenuRc[i]->kinds)
				{
				case EQUIP:
					_equip->setIsCheck(false);			
					break;
				case INVENTORY:
					_inven->setIsCheck(false);			
					break;
				case CONSTRUCTION:
					_construction->setIsCheck(false);
					_construction->setisTargetBox(false);
					break;
				case PURCHASE_LAND:
					_purchaese->setIsCheck(false);
					break;
				case GAME_SETTING:
					break;
				}
			}
		}
	}
}

void inGameMenu::settion()
{
	_inven_Kind = INVENTORY;
	_construction->setting();
}

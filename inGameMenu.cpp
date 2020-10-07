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

	inven_imgs->init();


	_inven->init();
	_equip->init();
	_construction->init();
	_purchaese->init();
	_game_setting->init();

	ITEMMANAGER->setvInventory_info(_inven->get_inven());

	return S_OK;
}

void inGameMenu::release()
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

void inGameMenu::update()
{
	inven_Change_Key_Down();
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

	
}

void inGameMenu::inven_Change_Key_Down()
{
	if (INPUT->GetKeyDown('Q') || INPUT->GetKeyDown('E')) {
		bool key = INPUT->GetKey('Q') ? true : false;

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

void inGameMenu::settion()
{
	_inven_Kind = INVENTORY;
	_construction->setting();
}

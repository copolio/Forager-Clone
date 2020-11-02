#include "stdafx.h"
#include "buildinginteraction.h"

HRESULT buildinginteraction::init()
{
	
	for (int i = 0; i < 9; i++) {
		targetMenu *_tar = new targetMenu;
		_tar->intouch = false;
		_tar->rc = RectMake(464, (WINSIZEY / 2 - 173) + i * 55, 315, 47);
		switch (i)
		{
		case 0:
			_tar->item_name = "img_game_money_icon";
			break;
		case 1:
			_tar->item_name = "";
			break;
		case 2:
			_tar->item_name = "arrowDrop"; 
			break;
		case 3:
			_tar->item_name = "pickaxe2";
			break;
		case 4:
			_tar->item_name = "";
			break;
		case 5:
			_tar->item_name = "swordDrop1";
			break;
		case 6:
			_tar->item_name = "bowDrop1";
			break;
		case 7:
			_tar->item_name = "";
			break;
		case 8:
			_tar->item_name = "";
			break;
		}

		_anvil_menu.push_back(_tar);
	}


	for (int i = 0; i < 7; i++) {
		targetMenu *_tar = new targetMenu;
		_tar->intouch = false;
		_tar->rc = RectMake(464, (WINSIZEY / 2 - 173) + i * 55, 315, 47);
		switch (i)
		{
		case 0:
			_tar->item_name = "threadDrop";
			break;
		case 1:
			_tar->item_name = "";
			break;
		case 2:
			_tar->item_name = "";
			break;
		case 3:
			_tar->item_name = "" ;
			break;
		case 4:
			_tar->item_name = "";
			break;
		case 5:
			_tar->item_name = "";
			break;
		case 6:
			_tar->item_name = "Flag" + to_string(1);
			break;
		}
		sewingmachine_menu.push_back(_tar);
	}
	for (int i = 0; i < 10; i++) {
		targetMenu *_tar = new targetMenu;
		_tar->intouch = false;
		_tar->rc = RectMake(464, (WINSIZEY / 2 - 227) + i * 55, 315, 47);
		switch (i)
		{
		case 0:
			_tar->item_name = "coalDrop";
			break;
		case 1:
			_tar->item_name = "brickDrop";
			break;
		case 2:
			_tar->item_name = "ironBarDrop";
			break;
		case 3:
			_tar->item_name = "goldBarDrop";
			break;
		case 4:
			_tar->item_name = "SteelhDrop";
			break;
		case 5:
			_tar->item_name = "high_class_SteelDrop";
			break;
		case 6:
			_tar->item_name = "GlassDrop";
			break;
		case 7:
			_tar->item_name = "";
			break;
		case 8:
			_tar->item_name = "roast_fishDrop";
			break;
		case 9:
			_tar->item_name = "";
			break;
		}
		steelwork_menu.push_back(_tar);
	}
	_upgradeBow = 1;
	_upgradePickaxe = 2;
	_upgradeSword =1 ;
	_upgradeFlag = 1;

	return S_OK;
}

void buildinginteraction::release()
{
	for (int i = 0; i < steelwork_menu.size(); i++) {
		SAFE_DELETE(steelwork_menu[i]);
		steelwork_menu[i] = NULL;
	}
	for (int i = 0; i < sewingmachine_menu.size(); i++) {
		SAFE_DELETE(sewingmachine_menu[i]);
		sewingmachine_menu[i] = NULL;
	}

	for (int i = 0; i < _anvil_menu.size(); i++) {
		SAFE_DELETE(_anvil_menu[i]);
		_anvil_menu[i] = NULL;
	}
	steelwork_menu.clear();
	sewingmachine_menu.clear();
	_anvil_menu.clear();


}

void buildinginteraction::targertrender(HDC hdc, string key)
{


	if (key == "steelwork") {
		IMAGEMANAGER->render("img_steelwork_menu", hdc, 450, 45);
		
		for (int i = 0; i < steelwork_menu.size(); i++) {
			if (PtInRect(&steelwork_menu[i]->rc,_ptMouse)) {
				if (!steelwork_menu[i]->intouch) {
					if (SOUNDMANAGER->isPlaySound("커서음1")) {
						SOUNDMANAGER->play("커서음2");
					}
					else {
						SOUNDMANAGER->play("커서음1");
					}
				}
				steelwork_menu[i]->intouch = true;
				_steelworktooltip.render(hdc, i, steelwork_menu[i]->rc, steelwork_menu[i]->item_name);
				IMAGEMANAGER->render("targetMenu", hdc, steelwork_menu[i]->rc.left, steelwork_menu[i]->rc.top);
			}
			else {
				steelwork_menu[i]->intouch = false;
			}
		}
	}	
	else if (key == "sewingmachine") {
		IMAGEMANAGER->render("img_sewingmachine_menu", hdc, 450, 100);
		for (int i = 0; i < sewingmachine_menu.size(); i++) {
			
			if (PtInRect(&sewingmachine_menu[i]->rc, _ptMouse)) {
				if (!sewingmachine_menu[i]->intouch) {
					if (SOUNDMANAGER->isPlaySound("커서음1")) {
						SOUNDMANAGER->play("커서음2");
					}
					else {
						SOUNDMANAGER->play("커서음1");
					}
				}
				sewingmachine_menu[i]->intouch = true;
				_sewingmachinetooltip.render(hdc, i, sewingmachine_menu[i]->rc, sewingmachine_menu[i]->item_name);
				IMAGEMANAGER->render("targetMenu", hdc, sewingmachine_menu[i]->rc.left, sewingmachine_menu[i]->rc.top);
			}
			else {
				sewingmachine_menu[i]->intouch = false;
			}
		}
	}
	else if (key == "anvil") {
		IMAGEMANAGER->render("img_anvil_menu", hdc, 450, 100);
		for (int i = 0; i < _anvil_menu.size(); i++) {
			if (PtInRect(&_anvil_menu[i]->rc, _ptMouse)) {
				if (!_anvil_menu[i]->intouch) {
					if (SOUNDMANAGER->isPlaySound("커서음1")) {
						SOUNDMANAGER->play("커서음2");
					}
					else {
						SOUNDMANAGER->play("커서음1");
					}
				}
				_anvil_menu[i]->intouch = true;
				_anviltooltip.render(hdc, i, _anvil_menu[i]->rc, _anvil_menu[i]->item_name);
				IMAGEMANAGER->render("targetMenu", hdc, _anvil_menu[i]->rc.left, _anvil_menu[i]->rc.top);
			}
			else {
				_anvil_menu[i]->intouch = false;
			}
		}
	}
	else if (key =="tombCenter"|| key == "goddess"||key == "elvenstatue") {
		_stone_statue.render(key,hdc);
	}

}


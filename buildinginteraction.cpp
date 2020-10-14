#include "stdafx.h"
#include "buildinginteraction.h"

HRESULT buildinginteraction::init()
{
	
	for (int i = 0; i < 9; i++) {
		targetMenu *_tar = new targetMenu;
		_tar->intouch = false;
		_tar->rc = RectMake(464, (WINSIZEY / 2 - 173) + i * 55, 315, 47);
		_anvil_menu.push_back(_tar);
	}
	for (int i = 0; i < 7; i++) {
		targetMenu *_tar = new targetMenu;
		_tar->intouch = false;
		_tar->rc = RectMake(464, (WINSIZEY / 2 - 173) + i * 55, 315, 47);
		sewingmachine_menu.push_back(_tar);
	}
	for (int i = 0; i < 10; i++) {
		targetMenu *_tar = new targetMenu;
		_tar->intouch = false;
		_tar->rc = RectMake(464, (WINSIZEY / 2 - 227) + i * 55, 315, 47);
		steelwork_menu.push_back(_tar);
	}
	

	return S_OK;
}

void buildinginteraction::release()
{
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
				_steelworktooltip.render(hdc, i, steelwork_menu[i]->rc);
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
				_sewingmachinetooltip.render(hdc, i, sewingmachine_menu[i]->rc);
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
				_anviltooltip.render(hdc, i, _anvil_menu[i]->rc);
				IMAGEMANAGER->render("targetMenu", hdc, _anvil_menu[i]->rc.left, _anvil_menu[i]->rc.top);
			}
			else {
				_anvil_menu[i]->intouch = false;
			}
		}
	}
}


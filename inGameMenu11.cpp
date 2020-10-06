#include "stdafx.h"
#include "inGameMenu11.h"
//
//
//
//HRESULT inGameMenu11::init()
//{
//	greentile = IMAGEMANAGER->findImage("greentile");
//	redtile = IMAGEMANAGER->findImage("redtile");
//	StaminaMax = IMAGEMANAGER->findImage("스테미나")->getWidth();
//	for (int i = 1; i < 10; i++) {
//		item_count[i - 1] = i;
//	}
//	inven_kinds = ITEM;
//	_targetBox->init();
//	for (int i = 0; i < 2; i++){
//		for (int j = 0; j < 8; j++) {
//
//			inventory_slot* inven = new inventory_slot;
//			inven->isCheck = false;
//			inven->Kinds = ITEM_NULL;
//			inven->x = 80 + j * 95;
//			inven->y = 150 + i * 95;
//			inven->count = 0;
//			inven->item_name = "";
//			inven->img_name = "";
//			inven->_rc = RectMake( inven->x, inven->y, 88, 88);
//			player_inventory.push_back(inven);
//		}
//	}
//
//	for (int i = 0; i < 7; i++) {
//		inventory_slot* inven = new inventory_slot;
//		inven->isCheck = false;
//		inven->Kinds = ITEM_NULL;
//		inven->x = 364+ i * 80;
//		inven->y = WINSIZEY/2+15 ;
//		inven->count = 0;
//		inven->img_name = "";
//		inven->_rc = RectMake(inven->x, inven->y, 72, 72);
//		player_equip.push_back(inven);
//	}
//	player_equip[0]->Kinds = ITEM_EQUIP;
//	player_equip[0]->img_name = "pick";
//
//	istargetBox = false;
//	isCheck = false;
//	iserection - false;
//	is_erection_select = false;
//	return S_OK;
//}
//
//void inGameMenu11::release()
//{
//	player_inventory.clear();
//	player_equip.clear();
//	_targetBox = NULL;
//	
//}
//
//void inGameMenu11::update()
//{
//	/*_targetBox->update();
//	keyDown();
//	if (isCheck) {
//		mouse_targetBox();
//		food_eat();
//	}
//	item_check();
//
//	if (INPUT->GetKeyDown(VK_RBUTTON)) {
//		if (is_erection_select) {
//			for (int i = 0; i < player_inventory.size(); i++) {
//				if (player_inventory[i]->item_name != "목재")continue;
//				player_inventory[i]->count += 2;
//				break;
//			}
//			is_erection_select = false;
//		}
//	}// 건물 선택 후 건설을 하지 않고 취소 하였을 경우*/ 
//
//}
//
//void inGameMenu11::render()
//{
//
//	/*for (int i = 0; i < player_equip.size();i++) {
//
//		if (player_equip[i]->Kinds != ITEM_EQUIP) continue;
//			player_Quick_slot.push_back(player_equip[i]);
//		
//		
//	}
//	if (isCheck) {
//		if (inven_kinds != ERECTION) {
//
//			IMAGEMANAGER->alphaRender("inventory_background", getMemDC(),0,0,180);
//		}
//		else {
//			IMAGEMANAGER->alphaRender("inventory_background", getMemDC(), WINSIZEX-300, 0, 180);
//		}
//		IMAGEMANAGER->render("inventory_Kinds", getMemDC(), WINSIZEX/2-180, 15);
//		IMAGEMANAGER->render("Q", getMemDC(), 400, 70);
//		IMAGEMANAGER->render("E", getMemDC(), 850, 70);
//		switch (inven_kinds)
//		{
//		case ITEM:
//
//			IMAGEMANAGER->render("img_item_icon", getMemDC(), 562, 30);
//			for (int i = 0; i < player_inventory.size(); i++) {
//				//Rectangle(getMemDC(), player_inventory[i]->_rc);
//				IMAGEMANAGER->render("item_slot", getMemDC(), player_inventory[i]->_rc.left, player_inventory[i]->_rc.top);
//				if (player_inventory[i]->img_name != "") {
//					IMAGEMANAGER->render(player_inventory[i]->img_name, getMemDC(), player_inventory[i]->_rc.left + 15, player_inventory[i]->_rc.top + 15);
//				}
//				int item_count = player_inventory[i]->count;
//				int c = 0;
//				while (item_count != NULL) {
//					switch (item_count % 10)
//					{
//					case 0:
//						IMAGEMANAGER->render(to_string(0), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 1:
//						IMAGEMANAGER->render(to_string(1), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 2:
//						IMAGEMANAGER->render(to_string(2), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 3:
//						IMAGEMANAGER->render(to_string(3), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 4:
//						IMAGEMANAGER->render(to_string(4), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 5:
//						IMAGEMANAGER->render(to_string(5), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 6:
//						IMAGEMANAGER->render(to_string(6), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 7:
//						IMAGEMANAGER->render(to_string(7), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 8:
//						IMAGEMANAGER->render(to_string(8), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					case 9:
//						IMAGEMANAGER->render(to_string(9), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
//						break;
//					}
//					c++;
//					item_count /= 10;
//
//				}
//				if (player_inventory[i]->count > 0) {
//					IMAGEMANAGER->render(to_string(player_inventory[i]->count), getMemDC(), player_inventory[i]->_rc.left + 55, player_inventory[i]->_rc.top + 55);
//				}
//			}
//
//			if (istargetBox) {
//				for (int i = 0; i < 4; i++) {
//					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
//				}
//				IMAGEMANAGER->render("img_UI_ItemTooltip", getMemDC(), 900, 150);
//
//			}
//			break;
//		case EQUIP:
//			IMAGEMANAGER->render("img_equip_icon", getMemDC(), 470, 30);
//
//			IMAGEMANAGER->render("img_equip_slot", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("img_equip_slot")->getWidth() / 2), WINSIZEY / 2);
//
//			for (int i = 0; i < player_equip.size(); i++) {
//				if (player_equip[i]->Kinds == ITEM_NULL)continue;
//				IMAGEMANAGER->render("Img_UI_EquipmentSlotFilled", getMemDC(), player_equip[i]->_rc.left, player_equip[i]->_rc.top);
//				IMAGEMANAGER->render(player_equip[i]->img_name, getMemDC(), player_equip[i]->_rc.left + 15, player_equip[i]->_rc.top);
//			}
//			if (istargetBox) {
//				for (int i = 0; i < 4; i++) {
//					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
//				}
//			}
//			break;
//
//		case ERECTION:
//			IMAGEMANAGER->render("img_erection_icon", getMemDC(), 660, 30);
//			IMAGEMANAGER->render("img_industry_icon", getMemDC(), WINSIZEX - 250, 30);
//
//			if (istargetBox) {
//				for (int i = 0; i < 4; i++) {
//					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
//				}
//			}
//			if (iserection) {
//
//				IMAGEMANAGER->render("img_steelwork_icon", getMemDC(), WINSIZEX - 240, 100);
//				IMAGEMANAGER->render("img_anvil_icon", getMemDC(), WINSIZEX - 240, 100+59);
//				IMAGEMANAGER->render("img_sewingmachine_icon", getMemDC(), WINSIZEX - 240, 100+59*2);
//
//			}
//			if (is_erection_select) {
//				//건설 가능 타일 렌더
//				if (PtInRect(&_map->tileMouseTarget().rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
//					if (_map->tileMouseTarget().objHp > 0 ||
//						_map->tileMouseTarget().terrKey != ("plaintile")) {
//						redtile->alphaRender(getMemDC(), CAMERA->GetRelativeX(_map->tileMouseTarget().rc.left), CAMERA->GetRelativeY(_map->tileMouseTarget().rc.top), 100);
//					}
//					else {
//						greentile->alphaRender(getMemDC(), CAMERA->GetRelativeX(_map->tileMouseTarget().rc.left), CAMERA->GetRelativeY(_map->tileMouseTarget().rc.top), 100);
//					}
//					IMAGEMANAGER->alphaRender("용광로", getMemDC(), CAMERA->GetRelativeX(CAMERA->GetMouseRelativePos(_ptMouse).x - IMAGEMANAGER->findImage("용광로")->getWidth() / 2)  , CAMERA->GetRelativeY(CAMERA->GetMouseRelativePos(_ptMouse).y - IMAGEMANAGER->findImage("용광로")->getHeight() / 2), 160);
//				}
//				//POINT _ptBuilding = { _ptMouse.x - 1, _ptMouse.y + IMAGEMANAGER->findImage("용광로")->getHeight() / 2 };
//				//	for (int i = 0; i < TILEY*MAPY; i++) {
//				//		bool stop = false;
//				//		for (int j = 0; j < MAPTILEX; j++) {
//				//			if (PtInRect(&_map->getTiles()[i*MAPTILEY + j].rc, _ptMouse)) {
//				//				if (_map->getTiles()[i*MAPTILEY + j].objHp > 0 ||
//				//					_map->getTiles()[i*MAPTILEY + j].terrain != IMAGEMANAGER->findImage("plaintile")) {
//				//					redtile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
//				//				}
//				//				else {
//				//					greentile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
//				//				}
//				//				if (_map->getTiles()[i*MAPTILEY + j+1].objHp > 0 ||
//				//					_map->getTiles()[i*MAPTILEY + j + 1].terrain != IMAGEMANAGER->findImage("plaintile")) {
//				//					redtile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j+1].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
//				//				}
//				//				else {
//				//					greentile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j+1].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
//				//				}
//				//				if (_map->getTiles()[(i - 1)*MAPTILEY + j].objHp > 0 ||
//				//					_map->getTiles()[(i - 1) *MAPTILEY + j].terrain != IMAGEMANAGER->findImage("plaintile")) {
//				//					redtile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j].rc.top, 100);
//				//				}
//				//				else {
//				//					greentile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j].rc.top, 100);
//				//				}
//				//				if (_map->getTiles()[(i - 1)*MAPTILEY + j + 1].objHp > 0 ||
//				//					_map->getTiles()[(i - 1) * MAPTILEY + j + 1].terrain != IMAGEMANAGER->findImage("plaintile")) {
//				//					redtile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j + 1].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j + 1].rc.top, 100);
//				//				}
//				//				else {
//				//					greentile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j +1].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j + 1].rc.top, 100);
//				//				}
//				//				Rectangle(getMemDC(), _map->getTiles()[i*MAPTILEY + j].rc);
//				//				Rectangle(getMemDC(), _map->getTiles()[i*MAPTILEY + j+1].rc);
//				//				Rectangle(getMemDC(), _map->getTiles()[(i-1)*MAPTILEY + j].rc);
//				//				Rectangle(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j+1].rc);
//				//				stop = true;
//				//				break;
//				//			}
//				//		}
//				//		if (stop) break;
//				//	}
//				//	IMAGEMANAGER->alphaRender("용광로",getMemDC(),_ptMouse.x - IMAGEMANAGER->findImage("용광로")->getWidth()/2, _ptMouse.y - IMAGEMANAGER->findImage("용광로")->getHeight() / 2,160);
//				//}
//			}
//			break;
//		}
//	}
//	_targetBox->render(getMemDC());
//	*/
//}
//
//void inGameMenu11::itemRemove()
//{
//
//}
//
//void inGameMenu11::mouse_targetBox()
//{
//	
//	
//	switch (inven_kinds)
//	{
//	case ITEM:
//		for (int i = 0; i < player_inventory.size(); i++) {
//			if (PtInRect(&player_inventory[i]->_rc, _ptMouse)) {
//				_targetBox->SetTarget(player_inventory[i]->_rc, 2, i, 4, false);
//				break;
//			}
//		}
//		break;
//	case EQUIP:
//		for (int i = 0; i < player_equip.size(); i++) {
//			if (PtInRect(&player_equip[i]->_rc, _ptMouse)) {
//				_targetBox->SetTarget(player_equip[i]->_rc, 2, i, 4, false);
//				break;
//			}
//		}
//		break;
//	case ERECTION:
//		RECT temp = RectMake(WINSIZEX - 250, 30, 226, 72);
//		if (PtInRect(&temp, _ptMouse)) {
//			_targetBox->SetTarget(temp, 2, 100, false);
//		}
//		if (PtInRect(&temp, _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON)) {
//			if (iserection) {
//				iserection = false;
//			}
//			else {
//				iserection = true;
//			}
//		}
//
//		if (iserection) {
//			RECT temp1 = RectMake(WINSIZEX - 210, 110, 150, 30);
//			if (PtInRect(&temp1, _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON)) {
//				for (int i = 0; i < player_inventory.size(); i++) {
//					if (player_inventory[i]->item_name != "목재")continue;
//					if (player_inventory[i]->count >= 2) {
//						player_inventory[i]->count -= 2;
//						is_erection_select = true;
//						break;
//					}
//				}
//				
//			}// 건물 선택 재료 검사
//		}
//
//		break;
//	}
//	
//}
//
//
//
//void inGameMenu11::keyDown()
//{
//	if (INPUT->GetKeyDown('I')) {
//		if (isCheck) {
//			isCheck = false;
//			_targetBox->RemoveTarget();
//		}
//		else {
//			isCheck = true;
//		}
//		inventory_setting();
//	}
//
//	if (INPUT->GetKeyDown('Q')) {
//		_targetBox->RemoveTarget();
//		if (inven_kinds == ITEM) {
//			inven_kinds = EQUIP;
//		}
//		else if(inven_kinds == EQUIP){
//			inven_kinds = ERECTION;
//		}
//		else if (inven_kinds == ERECTION) {
//			inven_kinds = ITEM;
//
//		}
//		istargetBox = false;
//		iserection = false;
//	}
//	if (INPUT->GetKeyDown('E')) {
//		_targetBox->RemoveTarget();
//		if (inven_kinds == ITEM) {
//			inven_kinds = ERECTION;
//		}
//		else if (inven_kinds == EQUIP) {
//			inven_kinds = ITEM;
//		}
//		else if (inven_kinds == ERECTION) {
//			inven_kinds = EQUIP;
//
//		}
//		istargetBox = false;
//		iserection = false;
//	}
//} 
//
//
//void inGameMenu11::food_eat()
//{
//	if (inven_kinds == ITEM) {
//		
//		for (int i = 0; i < player_inventory.size(); i++) {
//			if (PtInRect(&player_inventory[i]->_rc,_ptMouse )&& INPUT->GetKeyDown(VK_LBUTTON)) {
//				if (player_inventory[i]->Kinds == ITEM_FOOD) {
//					player_inventory[i]->count--;
//					if (player_inventory[i]->count == 0) {
//						player_inventory[i]->isCheck = false;
//						player_inventory[i]->Kinds = ITEM_NULL;
//						player_inventory[i]->count = 0;
//						player_inventory[i]->item_name = "";
//						player_inventory[i]->img_name = "";
//					}
//					IMAGEMANAGER->findImage("스테미나")->setWidth(-5);
//					if (IMAGEMANAGER->findImage("스테미나")->getWidth() >= StaminaMax) {
//						IMAGEMANAGER->findImage("스테미나")->settingWidth(StaminaMax);
//					}
//					break;
//				}
//
//			}
//
//		}
//
//	}
//
//}
//
//void inGameMenu11::inventory_setting()
//{
//	bool _br = false;;
//	for (int i = 0; i < player_inventory.size(); i++) {
//		if (player_inventory[i]->item_name == "")continue;
//		for (int j = 0; j < player_inventory.size(); j++) {
//			if (player_inventory[j]->item_name == ""|| i==j)continue;
//			if (player_inventory[i]->item_name == player_inventory[j]->item_name) {
//				player_inventory[i]->count += player_inventory[j]->count;
//
//				player_inventory[j]->isCheck = false;
//				player_inventory[j]->Kinds = ITEM_NULL;
//				player_inventory[j]->count = 0;
//				player_inventory[j]->item_name = "";
//				player_inventory[j]->img_name = "";
//				_br = true;
//				break;
//			}
//
//		}
//		if (_br) break;
//	}
//
//}

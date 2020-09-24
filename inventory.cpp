#include "stdafx.h"
#include "inventory.h"
#include "basicmap.h"


HRESULT inventory::init()
{
	IMAGEMANAGER->addImage("Q", "Images/이미지/GUI/Q버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("E", "Images/이미지/GUI/E버튼.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("커서", "Images/이미지/GUI/커서.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory_Kinds", "Images/이미지/GUI/inventory_Kinds.bmp", 383, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_item_icon", "Images/이미지/GUI/img_item_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_icon", "Images/이미지/GUI/img_equip_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Img_UI_EquipmentSlotFilled", "Images/이미지/GUI/Img_UI_EquipmentSlotFilled.bmp", 72, 72, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("img_UI_TargetingBox", "Images/이미지/GUI/img_UI_TargetingBox.bmp", 72, 21,4,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_UI_ItemTooltip", "Images/이미지/GUI/img_UI_ItemTooltip.bmp", 296, 216, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item_slot", "Images/이미지/GUI/img_UI_InventorySlotBoundary.bmp", 88, 88, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_equip_slot", "Images/이미지/GUI/img_equip_slot.bmp", 582, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_erection_icon", "Images/이미지/GUI/img_erection_icon.bmp", 78, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory_background", "Images/이미지/GUI/inventory_background.bmp", 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_industry_icon", "Images/이미지/GUI/img_industry_icon.bmp", 226, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("img_steelwork_icon", "Images/이미지/GUI/img_steelwork_icon.bmp", 205, 59, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("용광로", "Images/이미지/오브젝트/용광로.bmp", 112, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("용광로", "Images/이미지/오브젝트/용광로.bmp", 112/2, 160/2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("pick", "Images/이미지/아이템/곡괭이.bmp", 56, 56, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("0", "Images/이미지/GUI/0.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1", "Images/이미지/GUI/1.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "Images/이미지/GUI/2.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3", "Images/이미지/GUI/3.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "Images/이미지/GUI/4.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5", "Images/이미지/GUI/5.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6", "Images/이미지/GUI/6.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7", "Images/이미지/GUI/7.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "Images/이미지/GUI/8.bmp", 15, 19, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("9", "Images/이미지/GUI/9.bmp", 15, 19, true, RGB(255, 0, 255));

	greentile = IMAGEMANAGER->addImage("greentile", "Images/이미지/타일/img_tile_green.bmp", 56, 56);
	redtile = IMAGEMANAGER->addImage("redtile", "Images/이미지/타일/img_tile_red.bmp", 56, 56);

	_targetBox = new targetingBox;
	_targetBox->init();
	targetBox[0].img_num = 0;
	targetBox[1].img_num = 1;
	targetBox[2].img_num = 2;
	targetBox[3].img_num = 3;

	inven_kinds = ITEM;
	for (int i = 1; i < 10; i++) {
		item_count[i-1] = i;
	}
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 8; j++) {

			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEM_NULL;
			inven->x = 80 + j * 95;
			inven->y = 150 + i * 95;
			inven->count = 0;
			inven->item_name = "";
			inven->img_name = "";
			inven->_rc = RectMake( inven->x, inven->y, 88, 88);
			player_inventory.push_back(inven);
		}
	}

	for (int i = 0; i < 7; i++) {
		inventory_slot* inven = new inventory_slot;
		inven->isCheck = false;
		inven->Kinds = ITEM_NULL;
		inven->x = 364+ i * 80;
		inven->y = WINSIZEY/2+15 ;
		inven->count = 0;
		inven->img_name = "";
		inven->_rc = RectMake(inven->x, inven->y, 72, 72);
		player_equip.push_back(inven);
	}
	player_equip[0]->Kinds = ITEM_EQUIP;
	player_equip[0]->img_name = "pick";
	istargetBox = false;
	isCheck = false;
	iserection - false;
	is_erection_select = false;
	return S_OK;
}

void inventory::release()
{
	player_inventory.clear();
	player_equip.clear();
	_targetBox = NULL;
}

void inventory::update()
{
	_targetBox->update();
	keyDown();
	if (isCheck) {
		mouse_targetBox();
	}
	item_check();

	if (INPUT->GetKeyDown(VK_RBUTTON)) {
		if (is_erection_select) {
			for (int i = 0; i < player_inventory.size(); i++) {
				if (player_inventory[i]->item_name != "목재")continue;
				player_inventory[i]->count += 2;
				break;
			}
			is_erection_select = false;
		}
	}// 건물 선택 후 건설을 하지 않고 취소 하였을 경우 
}

void inventory::render()
{

	for (int i = 0; i < player_equip.size();i++) {

		if (player_equip[i]->Kinds != ITEM_EQUIP) continue;
			player_Quick_slot.push_back(player_equip[i]);
		
		
	}
	if (isCheck) {
		if (inven_kinds != ERECTION) {

			IMAGEMANAGER->alphaRender("inventory_background", getMemDC(),0,0,180);
		}
		else {
			IMAGEMANAGER->alphaRender("inventory_background", getMemDC(), WINSIZEX-300, 0, 180);
		}
		IMAGEMANAGER->render("inventory_Kinds", getMemDC(), WINSIZEX/2-180, 15);
		IMAGEMANAGER->render("Q", getMemDC(), 400, 70);
		IMAGEMANAGER->render("E", getMemDC(), 850, 70);
		switch (inven_kinds)
		{
		case ITEM:

			IMAGEMANAGER->render("img_item_icon", getMemDC(), 562, 30);
			for (int i = 0; i < player_inventory.size(); i++) {
				//Rectangle(getMemDC(), player_inventory[i]->_rc);
				IMAGEMANAGER->render("item_slot", getMemDC(), player_inventory[i]->_rc.left, player_inventory[i]->_rc.top);
				if (player_inventory[i]->img_name != "") {
					IMAGEMANAGER->render(player_inventory[i]->img_name, getMemDC(), player_inventory[i]->_rc.left + 15, player_inventory[i]->_rc.top + 15);
				}
				int item_count = player_inventory[i]->count;
				int c = 0;
				while (item_count != NULL) {
					switch (item_count % 10)
					{
					case 0:
						IMAGEMANAGER->render(to_string(0), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 1:
						IMAGEMANAGER->render(to_string(1), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 2:
						IMAGEMANAGER->render(to_string(2), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 3:
						IMAGEMANAGER->render(to_string(3), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 4:
						IMAGEMANAGER->render(to_string(4), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 5:
						IMAGEMANAGER->render(to_string(5), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 6:
						IMAGEMANAGER->render(to_string(6), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 7:
						IMAGEMANAGER->render(to_string(7), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 8:
						IMAGEMANAGER->render(to_string(8), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					case 9:
						IMAGEMANAGER->render(to_string(9), getMemDC(), player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
						break;
					}
					c++;
					item_count /= 10;

				}
				if (player_inventory[i]->count > 0) {
					IMAGEMANAGER->render(to_string(player_inventory[i]->count), getMemDC(), player_inventory[i]->_rc.left + 55, player_inventory[i]->_rc.top + 55);
				}
			}

			if (istargetBox) {
				for (int i = 0; i < 4; i++) {
					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
				}
				IMAGEMANAGER->render("img_UI_ItemTooltip", getMemDC(), 900, 150);

			}
			break;
		case EQUIP:
			IMAGEMANAGER->render("img_equip_icon", getMemDC(), 470, 30);

			IMAGEMANAGER->render("img_equip_slot", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("img_equip_slot")->getWidth() / 2), WINSIZEY / 2);

			for (int i = 0; i < player_equip.size(); i++) {
				if (player_equip[i]->Kinds == ITEM_NULL)continue;
				IMAGEMANAGER->render("Img_UI_EquipmentSlotFilled", getMemDC(), player_equip[i]->_rc.left, player_equip[i]->_rc.top);
				IMAGEMANAGER->render(player_equip[i]->img_name, getMemDC(), player_equip[i]->_rc.left + 15, player_equip[i]->_rc.top);
			}
			if (istargetBox) {
				for (int i = 0; i < 4; i++) {
					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
				}
			}
			break;

		case ERECTION:
			IMAGEMANAGER->render("img_erection_icon", getMemDC(), 660, 30);
			IMAGEMANAGER->render("img_industry_icon", getMemDC(), WINSIZEX - 250, 30);

			if (istargetBox) {
				for (int i = 0; i < 4; i++) {
					IMAGEMANAGER->frameRender("img_UI_TargetingBox", getMemDC(), targetBox[i].x, targetBox[i].y, targetBox[i].img_num, 0);
				}
			}
			if (iserection) {

				IMAGEMANAGER->render("img_steelwork_icon", getMemDC(), WINSIZEX - 240, 100);

			}
			if (is_erection_select) {
				//건설 가능 타일 렌더
				if (PtInRect(&_map->tileMouseTarget().rc, CAMERA->GetMouseRelativePos(_ptMouse))) {
					if (_map->tileMouseTarget().objHp > 0 ||
						_map->tileMouseTarget().terrKey != ("plaintile")) {
						redtile->alphaRender(getMemDC(), CAMERA->GetRelativeX(_map->tileMouseTarget().rc.left), CAMERA->GetRelativeY(_map->tileMouseTarget().rc.top), 100);
					}
					else {
						greentile->alphaRender(getMemDC(), CAMERA->GetRelativeX(_map->tileMouseTarget().rc.left), CAMERA->GetRelativeY(_map->tileMouseTarget().rc.top), 100);
					}
					IMAGEMANAGER->alphaRender("용광로", getMemDC(), CAMERA->GetRelativeX(CAMERA->GetMouseRelativePos(_ptMouse).x - IMAGEMANAGER->findImage("용광로")->getWidth() / 2)  , CAMERA->GetRelativeY(CAMERA->GetMouseRelativePos(_ptMouse).y - IMAGEMANAGER->findImage("용광로")->getHeight() / 2), 160);
				}
				//POINT _ptBuilding = { _ptMouse.x - 1, _ptMouse.y + IMAGEMANAGER->findImage("용광로")->getHeight() / 2 };
				//	for (int i = 0; i < TILEY*MAPY; i++) {
				//		bool stop = false;
				//		for (int j = 0; j < MAPTILEX; j++) {
				//			if (PtInRect(&_map->getTiles()[i*MAPTILEY + j].rc, _ptMouse)) {
				//				if (_map->getTiles()[i*MAPTILEY + j].objHp > 0 ||
				//					_map->getTiles()[i*MAPTILEY + j].terrain != IMAGEMANAGER->findImage("plaintile")) {
				//					redtile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
				//				}
				//				else {
				//					greentile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
				//				}
				//				if (_map->getTiles()[i*MAPTILEY + j+1].objHp > 0 ||
				//					_map->getTiles()[i*MAPTILEY + j + 1].terrain != IMAGEMANAGER->findImage("plaintile")) {
				//					redtile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j+1].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
				//				}
				//				else {
				//					greentile->alphaRender(getMemDC(), _map->getTiles()[i*MAPTILEY + j+1].rc.left, _map->getTiles()[i*MAPTILEY + j].rc.top, 100);
				//				}
				//				if (_map->getTiles()[(i - 1)*MAPTILEY + j].objHp > 0 ||
				//					_map->getTiles()[(i - 1) *MAPTILEY + j].terrain != IMAGEMANAGER->findImage("plaintile")) {
				//					redtile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j].rc.top, 100);
				//				}
				//				else {
				//					greentile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j].rc.top, 100);
				//				}
				//				if (_map->getTiles()[(i - 1)*MAPTILEY + j + 1].objHp > 0 ||
				//					_map->getTiles()[(i - 1) * MAPTILEY + j + 1].terrain != IMAGEMANAGER->findImage("plaintile")) {
				//					redtile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j + 1].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j + 1].rc.top, 100);
				//				}
				//				else {
				//					greentile->alphaRender(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j +1].rc.left, _map->getTiles()[(i - 1)*MAPTILEY + j + 1].rc.top, 100);
				//				}
				//				Rectangle(getMemDC(), _map->getTiles()[i*MAPTILEY + j].rc);
				//				Rectangle(getMemDC(), _map->getTiles()[i*MAPTILEY + j+1].rc);
				//				Rectangle(getMemDC(), _map->getTiles()[(i-1)*MAPTILEY + j].rc);
				//				Rectangle(getMemDC(), _map->getTiles()[(i - 1)*MAPTILEY + j+1].rc);
				//				stop = true;
				//				break;
				//			}
				//		}
				//		if (stop) break;
				//	}
				//	IMAGEMANAGER->alphaRender("용광로",getMemDC(),_ptMouse.x - IMAGEMANAGER->findImage("용광로")->getWidth()/2, _ptMouse.y - IMAGEMANAGER->findImage("용광로")->getHeight() / 2,160);
				//}
			}
			break;
		}
	}
	_targetBox->render(getMemDC());

}

void inventory::itemRemove()
{

}

void inventory::mouse_targetBox()
{
	
	
	switch (inven_kinds)
	{
	case ITEM:
		for (int i = 0; i < player_inventory.size(); i++) {
			if (PtInRect(&player_inventory[i]->_rc, _ptMouse)) {
				_targetBox->SetTarget(player_inventory[i]->_rc, 2, i, 4, false);
				//mouse_setingRc(player_inventory[i]->_rc);
				//istargetBox = true;
				break;
			}
		}
		break;
	case EQUIP:
		for (int i = 0; i < player_equip.size(); i++) {
			if (PtInRect(&player_equip[i]->_rc, _ptMouse)) {
				_targetBox->SetTarget(player_equip[i]->_rc, 2, i, 4, false);
				//mouse_setingRc(player_equip[i]->_rc);
				//istargetBox = true;
				break;
			}
		}
		break;
	case ERECTION:
		RECT temp = RectMake(WINSIZEX - 250, 30, 226, 72);
		if (PtInRect(&temp, _ptMouse)) {
			//mouse_setingRc(temp);
			//istargetBox = true;
			_targetBox->SetTarget(temp, 2, 100, false);
		}
		if (PtInRect(&temp, _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON)) {
			if (iserection) {
				iserection = false;
			}
			else {
				iserection = true;
			}
		}

		if (iserection) {
			RECT temp1 = RectMake(WINSIZEX - 210, 110, 150, 30);
			if (PtInRect(&temp1, _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON)) {
				for (int i = 0; i < player_inventory.size(); i++) {
					if (player_inventory[i]->item_name != "목재")continue;
					if (player_inventory[i]->count >= 2) {
						player_inventory[i]->count -= 2;
						is_erection_select = true;
						break;
					}
				}
				
			}// 건물 선택 재료 검사
		}

		break;
	}
	
}

void inventory::mouse_setingRc(RECT rc )
{
	targetBox[0].x = rc.left-5;
	targetBox[0].y = rc.top-5;

	targetBox[1].x = rc.right-15;
	targetBox[1].y = rc.top-5;

	targetBox[2].x = rc.right-15;
	targetBox[2].y = rc.bottom - 15;

	targetBox[3].x = rc.left-5;
	targetBox[3].y = rc.bottom-15;
}

void inventory::keyDown()
{
	if (INPUT->GetKeyDown('I')) {
		if (isCheck) {
			isCheck = false;
			_targetBox->RemoveTarget();
		}
		else {
			isCheck = true;
		}
	}

	if (INPUT->GetKeyDown('Q')) {
		_targetBox->RemoveTarget();
		if (inven_kinds == ITEM) {
			inven_kinds = EQUIP;
		}
		else if(inven_kinds == EQUIP){
			inven_kinds = ERECTION;
		}
		else if (inven_kinds == ERECTION) {
			inven_kinds = ITEM;

		}
		istargetBox = false;
		iserection = false;
	}
	if (INPUT->GetKeyDown('E')) {
		_targetBox->RemoveTarget();
		if (inven_kinds == ITEM) {
			inven_kinds = ERECTION;
		}
		else if (inven_kinds == EQUIP) {
			inven_kinds = ITEM;
		}
		else if (inven_kinds == ERECTION) {
			inven_kinds = EQUIP;

		}
		istargetBox = false;
		iserection = false;
	}
} 

void inventory::item_check()
{
	if (INPUT->GetKeyDown('C')) {
		for (int i = 0; i < player_inventory.size(); i++) {

			if (player_inventory[i]->item_name != "목재")continue;
			if (player_inventory[i]->count > 2) {
				player_inventory[i]->count -= 2;
			}
		}
	}
}
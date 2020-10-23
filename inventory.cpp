#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_targetBox = new targetingBox;
	_targetBox->init();
	money = new int;
	*money = 9999;
	StaminaMax = IMAGEMANAGER->findImage("½ºÅ×¹Ì³ª")->getWidth();
	for (int i = 1; i < 10; i++) {
		item_count[i - 1] = i;
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {

			inventory_slot* inven = new inventory_slot;
			inven->isCheck = false;
			inven->Kinds = ITEM_NULL;
			inven->x = 80 + j * 95;
			inven->y = 150 + i * 95;
			inven->count = 0;
			inven->item_name = "";
			inven->img_name = "";
			inven->_rc = RectMake(inven->x, inven->y, 88, 88);
			player_inventory.push_back(inven);
		}
	}

	//====================================================
	//Å×½ºÆ®¿ë
	/*
	ITEM_NULL,
	ITEM_FOOD,
	ITEM_EQUIP,
	ITEM_MATERIAL,*/

	/*
	berryDrop
	rockDrop
	treeDrop
	*/
	//====================================================
	isCheck = false;

	return S_OK;
}

void inventory::release()
{
	player_inventory.clear();
}

void inventory::update()
{
	if (INPUT->GetKeyDown(VK_F5)) {
		player_inventory[0]->count = 999;
		player_inventory[0]->Kinds = ITEM_MATERIAL;
		player_inventory[0]->img_name = "treeDrop";
		player_inventory[0]->item_name = "treeDrop";

		player_inventory[1]->count = 999;
		player_inventory[1]->Kinds = ITEM_MATERIAL;
		player_inventory[1]->img_name = "rockDrop";
		player_inventory[1]->item_name = "rockDrop";

		player_inventory[2]->count = 999;
		player_inventory[2]->Kinds = ITEM_FOOD;
		player_inventory[2]->img_name = "berryDrop";
		player_inventory[2]->item_name = "berryDrop";

		player_inventory[3]->count = 999;
		player_inventory[3]->Kinds = ITEM_MATERIAL;
		player_inventory[3]->img_name = "±Ý±¤¼®";
		player_inventory[3]->item_name = "±Ý±¤¼®";

		player_inventory[4]->count = 999;
		player_inventory[4]->Kinds = ITEM_MATERIAL;
		player_inventory[4]->img_name = "coal";
		player_inventory[4]->item_name = "coal";

		player_inventory[5]->count = 999;
		player_inventory[5]->Kinds = ITEM_MATERIAL;
		player_inventory[5]->img_name = "Iron_ore";
		player_inventory[5]->item_name = "Iron_ore";

		player_inventory[6]->count = 999;
		player_inventory[6]->Kinds = ITEM_MATERIAL;
		player_inventory[6]->img_name = "±«Ã¶";
		player_inventory[6]->item_name = "±«Ã¶";

		player_inventory[7]->count = 999;
		player_inventory[7]->Kinds = ITEM_MATERIAL;
		player_inventory[7]->img_name = "±Ý±«";
		player_inventory[7]->item_name = "±Ý±«";

		ITEMMANAGER->setMoney(9999);
	}
	_targetBox->update();
	mouse_targetBox();
	food_eat();

}

void inventory::render(HDC hdc)
{

	IMAGEMANAGER->alphaRender("inventory_background", hdc, 180);
	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q",hdc, 320, 70);
	IMAGEMANAGER->render("E",hdc, 890, 70);
	IMAGEMANAGER->render("img_item_icon",hdc, 502, 30);
	for (int i = 0; i < player_inventory.size(); i++) {
		//Rectangle(getMemDC(), player_inventory[i]->_rc);
		IMAGEMANAGER->render("item_slot",hdc, player_inventory[i]->_rc.left, player_inventory[i]->_rc.top);
		if (player_inventory[i]->img_name != "") {
			IMAGEMANAGER->render(player_inventory[i]->img_name,hdc, player_inventory[i]->_rc.left + 15, player_inventory[i]->_rc.top + 15);
		}
		int item_count = player_inventory[i]->count;
		int c = 0;
		while (item_count != NULL) {
			switch (item_count % 10)
			{
			case 0:
				IMAGEMANAGER->render(to_string(0),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 1:
				IMAGEMANAGER->render(to_string(1),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 2:
				IMAGEMANAGER->render(to_string(2),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 3:
				IMAGEMANAGER->render(to_string(3),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 4:
				IMAGEMANAGER->render(to_string(4),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 5:
				IMAGEMANAGER->render(to_string(5),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 6:
				IMAGEMANAGER->render(to_string(6),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 7:
				IMAGEMANAGER->render(to_string(7),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 8:
				IMAGEMANAGER->render(to_string(8),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			case 9:
				IMAGEMANAGER->render(to_string(9),hdc, player_inventory[i]->_rc.left + 55 - c * 10, player_inventory[i]->_rc.top + 55);
				break;
			}
			c++;
			item_count /= 10;

		}
		if (player_inventory[i]->count > 0) {
			IMAGEMANAGER->render(to_string(player_inventory[i]->count),hdc, player_inventory[i]->_rc.left + 55, player_inventory[i]->_rc.top + 55);
		}
	}
	
	if (isCheck) {
		item_info_print(hdc);
		_targetBox->render(hdc);
	}
	
}

void inventory::mouse_targetBox()
{
	for (int i = 0; i < player_inventory.size(); i++) {
		if (PtInRect(&player_inventory[i]->_rc, _ptMouse)) {
			_targetBox->SetTarget(player_inventory[i]->_rc, 2, i, 4, false);
			isCheck = true;
			
			break;
		}
	}
}

void inventory::food_eat()
{
	for (int i = 0; i < player_inventory.size(); i++) {
		if (PtInRect(&player_inventory[i]->_rc, _ptMouse) && player_inventory[i]->Kinds == ITEM_FOOD && INPUT->GetKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("°Ç¼³ÅÇÅ¬¸¯");
			player_inventory[i]->count--;
			STATMANAGER->setRight(-5);
			//IMAGEMANAGER->findImage("½ºÅ×¹Ì³ª")->setWidth(-5);
			//
			//if (IMAGEMANAGER->findImage("½ºÅ×¹Ì³ª")->getWidth() >= StaminaMax) {
			//	IMAGEMANAGER->findImage("½ºÅ×¹Ì³ª")->settingWidth(StaminaMax);
			//}

			ITEMMANAGER->vItem_count_zoro();
		}
	}
}

void inventory::item_info_print(HDC hdc)
{
	for (int i = 0; i < player_inventory.size(); i++) {
		if (PtInRect(&player_inventory[i]->_rc, _ptMouse)) {
			_item_info->render(hdc, player_inventory[i]->img_name);
		}
	}
}

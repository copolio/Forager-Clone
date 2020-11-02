#include "stdafx.h"
#include "stone_statue.h"

void stone_statue::render(string item_key, HDC hdc)
{
	
	string _item_info = item_key + to_string(UNITMANAGER->is_Building_level(item_key)+1);
	tagItemInfo item_make = DATABASE->GetItem_Make(_item_info);
	if (item_key == "tombCenter") {
		IMAGEMANAGER->render("산신령의 묘석", hdc, WINSIZEX / 2 -150 , WINSIZEY / 2-150);
	}
	else if (item_key == "goddess") {
		IMAGEMANAGER->render("여신의 우물", hdc, WINSIZEX / 2 - 150, WINSIZEY / 2 - 150);
	}
	else if (item_key == "elvenstatue") {
		IMAGEMANAGER->render("요정의 나무", hdc, WINSIZEX / 2 - 150, WINSIZEY / 2 - 150);
	}
	IMAGEMANAGER->render(item_make.materials_one, hdc, WINSIZEX / 2 - 120, WINSIZEY / 2 - 70);
	POINT pos;
	pos.x = WINSIZEX / 2 - 20;
	pos.y = WINSIZEY / 2 - 50;
	TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(item_make.materials_one)), pos, 25, 0);
	pos.x = WINSIZEX / 2 +20;
	pos.y = WINSIZEY / 2 - 50;
	TEXTMANAGER->ShowText(hdc, false, "  / "+to_string(item_make.one), pos, 25, 0);

	IMAGEMANAGER->render(item_make.materials_two, hdc, WINSIZEX / 2 - 120, WINSIZEY / 2 - 10);
	pos;
	pos.x = WINSIZEX / 2 - 20;
	pos.y = WINSIZEY / 2 ;
	TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(item_make.materials_two)), pos, 25, 0);
	pos.x = WINSIZEX / 2 + 20;
	pos.y = WINSIZEY / 2 ;
	TEXTMANAGER->ShowText(hdc, false, "  / " + to_string(item_make.two), pos, 25, 0);

	IMAGEMANAGER->render(item_make.materials_Three, hdc, WINSIZEX / 2 - 120, WINSIZEY / 2 +50);
	pos;
	pos.x = WINSIZEX / 2 - 20;
	pos.y = WINSIZEY / 2 + 50;
	TEXTMANAGER->ShowText(hdc, false, to_string(ITEMMANAGER->item_count(item_make.materials_Three)), pos, 25, 0);
	pos.x = WINSIZEX / 2 + 20;
	pos.y = WINSIZEY / 2 + 50;
	TEXTMANAGER->ShowText(hdc, false, "  / " + to_string(item_make.three), pos, 25, 0);


	RECT temp = RectMake(WINSIZEX / 2 - 60, WINSIZEY / 2 + 105, 165, 45);
	if (PtInRect(&temp, _ptMouse)&& cilck()) {
		click_item_event(_item_info, item_key);
	}

}
bool stone_statue::cilck()
{
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		SOUNDMANAGER->play("생산시작");
		return true;
	}
	return false;
}
void stone_statue::click_item_event(string item_key, string item_key2)
{
	tagItemInfo item = DATABASE->GetItem_Make(item_key);

	if (PRODUCTIONMANAGER->is_Item_Cilck(item.itemKey)) {
		if (ITEMMANAGER->Item_count_Minus(item.materials_one, item.one, item.materials_two, item.two, item.materials_Three, item.three)) {
			UNITMANAGER->is_Building_level_Up(item_key2);
			if (item_key2 == "tombCenter") {
				
			}
			else if (item_key2 == "goddess") {
				
			}
			else if (item_key2 == "elvenstatue") {
				
			}
		}
	}
	
}
#include "stdafx.h"
#include "item_info.h"

void item_info::render(HDC hdc,string item_name)
{
	/*berryDrop
		rockDrop
		treeDrop*/
	if (item_name == "berryDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 950, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "열매", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(소모품)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "가치 : 1", pos, 30, 0);
		pos.x = 990;
		pos.y = 320;
		TEXTMANAGER->ShowText(hdc, false, "+5 에너지", pos, 30, 0,RGB(0,255,0));
	}
	else if (item_name == "rockDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "돌", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "가치 : 1", pos, 30, 0);
	}
	else if (item_name == "treeDrop") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "목재", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 1);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "가치 : 1", pos, 30, 0);
	}
	else if (item_name == "금괴") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "금괴", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "가치 : 8", pos, 30, 0);
	}
	else if (item_name == "괴철") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "괴철", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "가치 : 8", pos, 30, 0);
	}
	else if (item_name == "금광석") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "금광석", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "가치 : 8", pos, 30, 0);
	}
	else if (item_name == "Iron_ore") {
		IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
		IMAGEMANAGER->render("bag", hdc, 1000, 450);
		IMAGEMANAGER->render(item_name, hdc, 920, 180);
		POINT pos;
		pos.x = 1030;
		pos.y = 195;
		TEXTMANAGER->ShowText(hdc, false, "철광석", pos, 30, 0);
		pos.x = 1000;
		pos.y = 250;
		TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 0);
		pos.x = 1000;
		pos.y = 280;
		TEXTMANAGER->ShowText(hdc, false, "가치 : 5", pos, 30, 0);
	}
	else if (item_name == "coal") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 920, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, false, "석탄", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, false, "가치 : 5", pos, 30, 0);
	}
	else if (item_name == "skullHeadDrop") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 920, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, false, "스컬머리", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, false, "가치 : 3", pos, 30, 0);
	}
	else if (item_name == "물고기") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 950, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, false, "물고기", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, false, "(소모품)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, false, "가치 : 1", pos, 30, 0);
	pos.x = 990;
	pos.y = 320;
	TEXTMANAGER->ShowText(hdc, false, "+5 에너지", pos, 30, 0, RGB(0, 255, 0));
	}
	else if (item_name == "milkDrop") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 950, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, false, "우유", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, false, "(소모품)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, false, "가치 : 3", pos, 30, 0);
	pos.x = 990;
	pos.y = 320;
	TEXTMANAGER->ShowText(hdc, false, "+5 에너지", pos, 30, 0, RGB(0, 255, 0));
	}
	else if (item_name == "leather") {
	IMAGEMANAGER->render("img_UI_ItemTooltip", hdc, 900, 150);
	IMAGEMANAGER->render("bag", hdc, 1000, 450);
	IMAGEMANAGER->render(item_name, hdc, 950, 180);
	POINT pos;
	pos.x = 1030;
	pos.y = 195;
	TEXTMANAGER->ShowText(hdc, false, "가죽", pos, 30, 0);
	pos.x = 1000;
	pos.y = 250;
	TEXTMANAGER->ShowText(hdc, false, "(재료)", pos, 30, 0);
	pos.x = 1000;
	pos.y = 280;
	TEXTMANAGER->ShowText(hdc, false, "가치 : 3", pos, 30, 0);

	}




}

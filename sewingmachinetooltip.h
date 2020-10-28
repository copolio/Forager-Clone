#pragma once
#include "item.h"
class sewingmachinetooltip
{
public:
	void render(HDC hdc, int num, RECT rc, string item_name);

	void click_item_event(string item_key);

	bool cilck();
private:
	tagItemInfo _item;
};


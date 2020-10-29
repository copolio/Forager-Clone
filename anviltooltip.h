#pragma once
#include "item.h"

class anviltooltip
{
public:
	void render(HDC hdc, int num, RECT rc, string item_name);
	void click_item_event(string item_key);

	bool cilck();
	void WeaponeUpgrad();
private:
	tagItemInfo _item;
	tagItem _item_Kind;
};


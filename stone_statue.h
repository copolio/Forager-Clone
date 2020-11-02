#pragma once
#include "item.h"
class stone_statue
{
private:



public:
	void render(string item_key, HDC hdc);
	bool cilck();
	void click_item_event(string item_key, string item_key2);
};


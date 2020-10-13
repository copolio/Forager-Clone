#pragma once
class anviltooltip
{

public:
	void render(HDC hdc, int num, RECT rc);
	void click_item_event(int num);

	bool cilck();
};


#pragma once
class steelworktooltip
{		
private:

public:
	void render(HDC hdc, int num, RECT rc,string item_name);
	void click_item_event(string item_key);

	bool cilck();
};


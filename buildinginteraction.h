#pragma once
#include "steelworktooltip.h"
#include "sewingmachinetooltip.h"
#include "anviltooltip.h"


struct targetMenu {
	RECT rc;
	bool intouch;
	string item_name;
};

class buildinginteraction
{
private:
	vector<targetMenu*> _anvil_menu;
	vector<targetMenu*> steelwork_menu;
	vector<targetMenu*> sewingmachine_menu;

	anviltooltip _anviltooltip;
	sewingmachinetooltip _sewingmachinetooltip;
	steelworktooltip _steelworktooltip;
public:
	HRESULT init();
	void release();
	void targertrender(HDC hdc,string key);


};


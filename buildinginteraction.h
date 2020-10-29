#pragma once
#include "steelworktooltip.h"
#include "sewingmachinetooltip.h"
#include "anviltooltip.h"
#include "singletonBase.h"

struct targetMenu{
	RECT rc;
	bool intouch;
	string item_name;
};

class buildinginteraction : public singletonBase<buildinginteraction>
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

	void SetWeaponeBowName(string name) { _anvil_menu[6]->item_name = name;};
	void SetWeaponeSwordName(string name) {  _anvil_menu[5]->item_name = name; };
	void SetWeaponePickaxName(string name) { _anvil_menu[3]->item_name = name; };
	void SetFlagName(string name) { sewingmachine_menu[6]->item_name = name; };

};


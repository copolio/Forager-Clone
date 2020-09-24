#pragma once
#include "inventory_slot.h"
#include "targetingBox.h"
#include "gameNode.h"

class basicmap;
struct mouse_rc
{
	float x, y;
	int img_num;

};
enum Kinds
{
	ITEM,
	EQUIP,
	ERECTION
};

//class basicmap;
class inventory : public gameNode
{
private:
	basicmap* _map;
	image* greentile;
	image* redtile;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void itemRemove();
	void mouse_targetBox();
	void mouse_setingRc(RECT rc);
	void keyDown();
	bool isCheck;
	string item_count[9];
	void item_check();

	vector<inventory_slot*> getPlayerInventory() { return player_inventory; }
	void setPlayerInven(vector<inventory_slot*> playerInven) { player_inventory = playerInven; }
private:
	vector<inventory_slot*> player_inventory;  
	vector<inventory_slot*> player_equip;
	vector<inventory_slot*> player_Quick_slot;
	mouse_rc targetBox[4];
	Kinds inven_kinds;

	targetingBox* _targetBox;
	bool istargetBox;
	bool iserection;
	bool is_erection_select;		//용광로 선택 건축 많아지면 enum값으로 변경


	int StaminaMax;
public:
	void setIMLink(basicmap* map) { _map = map; };
	bool getBuildingStatus() { return is_erection_select; };
	void setBuildingStatus(bool status) { is_erection_select = status; };
	void food_eat();
	void inventory_setting();
	bool inventory_alreadyopen() {
		return isCheck;
	}
};


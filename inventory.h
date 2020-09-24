#pragma once
#include "inventory_slot.h"
#include "gameNode.h"

struct mouse_rc
{
	float x, y;
	int img_num;

};
enum Kinds
{
	ITEM,
	EQUIP,
};

//class basicmap;
class inventory : public gameNode
{

private:
	//basicmap _map;

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
	bool istargetBox;


};


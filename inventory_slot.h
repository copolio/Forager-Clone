#pragma once
enum ItemKinds
{
	ITEM_NULL,
	ITEM_FPPD,
	ITEM_EQUIP,
	ITEM_MATERIAL

};

class inventory_slot
{
public:
	float x, y;
	RECT _rc;
	bool isCheck;
	int count;
	string img_name;
	ItemKinds Kinds;
	string item_name;
	string item_Info;
private:

};

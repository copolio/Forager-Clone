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
	ItemKinds Kinds;

private:

};

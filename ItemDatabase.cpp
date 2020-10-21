#include "stdafx.h"
#include "ItemDatabase.h"

#define ITEM_MAX 14

void ItemDatabase::init()
{
	_itemDictionary.clear();

	// ÀÓ½Ã·Î 10°³
	tagItem items[ITEM_MAX];
	items[0] = tagItem("berryDrop", "¿­¸Å", CONSUMABLE, 1, 5);
	items[1] = tagItem("¹°°í±â", "¹°°í±â", CONSUMABLE, 1, 5);
	items[2] = tagItem("milkDrop", "¿ìÀ¯", CONSUMABLE, 3, 5);
	items[3] = tagItem("rockDrop", "µ¹", INGREDIANT, 1, 0);
	items[4] = tagItem("treeDrop", "¸ñÀç", INGREDIANT, 1, 0);
	items[5] = tagItem("±Ý±«", "±Ý±«", INGREDIANT, 1, 0);
	items[6] = tagItem("±«Ã¶", "±«Ã¶", INGREDIANT, 1, 0);
	items[7] = tagItem("±Ý±¤¼®", "±Ý±¤¼®", INGREDIANT, 1, 0);
	items[8] = tagItem("Iron_ore", "Ã¶±¤¼®", INGREDIANT, 1, 0);
	items[9] = tagItem("coal", "¼®Åº", INGREDIANT, 1, 0);
	items[10] = tagItem("skullHeadDrop", "½ºÄÃ¸Ó¸®", INGREDIANT, 1, 0);
	items[11] = tagItem("leather", "°¡Á×", INGREDIANT, 1, 0);
	items[12] = tagItem("slot_Bow", "È°", EQUIPMENT, 1, 0);
	items[13] = tagItem("sword", "Ä®", EQUIPMENT, 1, 0);

	for (int i = 0; i < ITEM_MAX; i++) {
		_itemDictionary.insert(make_pair(items[i].itemKey, items[i]));
	}


}

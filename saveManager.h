#pragma once
#include "singletonBase.h"
#include "inventory_slot.h"

#define ITEMSIZE 20
#define	EQUIPSIZE 7
class qucik_slot;
class saveManager : public singletonBase<saveManager>
{
private:
	

	quick_slot* _quick_slot;
	inventory_slot My_Item[ITEMSIZE];
	inventory_slot My_equip[EQUIPSIZE];
public:
	void set_quick_slot_info(quick_slot* _q) {
		_quick_slot = _q;
	}
	void save();
	bool load();
	bool DoesFileExist(LPCSTR pszFilename);
	LPCSTR My_Game_save_file_tiem;
	LPCSTR My_Game_save_file_equip;

	void Item_transform();
	void equip_transform();
};


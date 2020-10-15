#pragma once
#include "singletonBase.h"
#include "inventory_slot.h"
#include "tile.h"
#define ITEMSIZE 20
#define	EQUIPSIZE 7
#define TILEMAXSIZE 7056
class qucik_slot;
class earth;
class saveManager : public singletonBase<saveManager>
{
private:
	earth* _map;
	tile My_Tile[TILEMAXSIZE];
	quick_slot* _quick_slot;
	inventory_slot My_Item[ITEMSIZE];
	inventory_slot My_equip[EQUIPSIZE];
	vector<tile> *_game_tile;
public:
	void set_quick_slot_info(quick_slot* _q) {
		_quick_slot = _q;
	}
	void set_Tile_info(earth* _m) {
		_map = _m;

	}
	vector<tile> get_Tile_info() {
		return *_game_tile;
	}

	void save();
	bool load();
	LPCSTR My_Game_save_file_item;
	LPCSTR My_Game_save_file_equip;
	LPCSTR My_Game_save_file_tile;

	void Tile_transform();
	void Item_transform();
	void equip_transform();

};


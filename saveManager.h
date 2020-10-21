#pragma once
#include "singletonBase.h"
#include "inventory_slot.h"
#include "tile.h"
#include "npc.h"
#define ITEMSIZE 20
#define	EQUIPSIZE 7
#define TILEMAXSIZE 7056
#define UNITMAXSIZE 1000
#define NPCMAXSIZE 1			//NPC °³¼ö
class qucik_slot;	
class earth;
class saveManager : public singletonBase<saveManager>
{
private:/*
		std::vector<double> v;
double* a = &v[0];
		*/
	vector<unit*> _Unit;
	unit My_unit[UNITMAXSIZE];

	int unit_vecter_size;

	earth* _map;
	tile My_Tile[TILEMAXSIZE];
	quick_slot* _quick_slot;
	inventory_slot My_Item[ITEMSIZE];
	inventory_slot My_equip[EQUIPSIZE];
	npc quest[NPCMAXSIZE];
	vector<tile> *_game_tile;
public:
	void set_quick_slot_info(quick_slot* _q) {
		_quick_slot = _q;
	}
	void set_Tile_info(earth* _m) {
		_map = _m;
		_game_tile = _map->PGetTiles();
	}
	vector<tile> get_Tile_info() {
		return *_game_tile;
	}

	void save();
	bool load();
	LPCSTR My_Game_save_file_item;
	LPCSTR My_Game_save_file_equip;
	LPCSTR My_Game_save_file_tile;
	LPCSTR My_Game_save_file_unit;
	LPCSTR My_Game_save_file_player;
	LPCSTR My_Game_save_file_npc;

	void Tile_transform();
	void Item_transform();
	void equip_transform();
	void Unit_transform();
	void Player_transform();
	void npc_transform();

};


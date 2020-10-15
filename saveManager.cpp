#include "stdafx.h"
#include "saveManager.h"
#include "quick_slot.h"
#include "earth.h"
void saveManager::save()
{
	this->Item_transform();
	this->equip_transform();
	this->Tile_transform();
	this->Unit_transform();
	HANDLE file;
	DWORD write;

	file = CreateFile(My_Game_save_file_item, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, My_Item, sizeof(inventory_slot) * ITEMSIZE, &write, NULL);
	CloseHandle(file);

	file = CreateFile(My_Game_save_file_equip, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, My_equip, sizeof(inventory_slot) * EQUIPSIZE, &write, NULL);
	CloseHandle(file);

	file = CreateFile(My_Game_save_file_tile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, My_Tile, sizeof(tile) * TILEMAXSIZE, &write, NULL);
	CloseHandle(file);

	file = CreateFile(My_Game_save_file_unit, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, My_unit, sizeof(unit) * _Unit.size(), &write, NULL);
	CloseHandle(file);

}

bool saveManager::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(My_Game_save_file_item, GENERIC_READ, 0, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, My_Item, sizeof(inventory_slot) *ITEMSIZE, &read, NULL);
	CloseHandle(file);
	if (file != INVALID_HANDLE_VALUE) { // 파일의 존재 여부 확인
		for (int i = 0; i < ITEMMANAGER->getvInventory_info().size(); i++) {
			ITEMMANAGER->getvInventory_info()[i]->count = My_Item[i].count;
			ITEMMANAGER->getvInventory_info()[i]->img_name = My_Item[i].img_name;
			ITEMMANAGER->getvInventory_info()[i]->isCheck = My_Item[i].isCheck;
			ITEMMANAGER->getvInventory_info()[i]->item_Info = My_Item[i].item_Info;
			ITEMMANAGER->getvInventory_info()[i]->item_name = My_Item[i].item_name;
			ITEMMANAGER->getvInventory_info()[i]->Kinds = My_Item[i].Kinds;
			ITEMMANAGER->getvInventory_info()[i]->x = My_Item[i].x;
			ITEMMANAGER->getvInventory_info()[i]->y = My_Item[i].y;
			ITEMMANAGER->getvInventory_info()[i]->_rc = My_Item[i]._rc;
		}
	}

	file = CreateFile(My_Game_save_file_equip, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, My_equip, sizeof(inventory_slot) *EQUIPSIZE, &read, NULL);
	CloseHandle(file);


	if (file != INVALID_HANDLE_VALUE) { // 파일의 존재 여부 확인
		for (int i = 0; i < ITEMMANAGER->get_equip_info().size(); i++) {
			ITEMMANAGER->get_equip_info()[i]->count = My_equip[i].count;
			ITEMMANAGER->get_equip_info()[i]->img_name = My_equip[i].img_name;
			ITEMMANAGER->get_equip_info()[i]->isCheck = My_equip[i].isCheck;
			ITEMMANAGER->get_equip_info()[i]->item_Info = My_equip[i].item_Info;
			ITEMMANAGER->get_equip_info()[i]->item_name = My_equip[i].item_name;
			ITEMMANAGER->get_equip_info()[i]->Kinds = My_equip[i].Kinds;
			ITEMMANAGER->get_equip_info()[i]->x = My_equip[i].x;
			ITEMMANAGER->get_equip_info()[i]->y = My_equip[i].y;
			ITEMMANAGER->get_equip_info()[i]->_rc = My_equip[i]._rc;
		}
		_quick_slot->quick_slot_update();
	}

	file = CreateFile(My_Game_save_file_tile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, My_Tile, sizeof(tile) *TILEMAXSIZE, &read, NULL);
	CloseHandle(file);


	if (file != INVALID_HANDLE_VALUE) {
		for (int i = 0; i < TILEMAXSIZE; i++) {
			(*_game_tile)[i].terrKey = My_Tile[i].terrKey ;
			(*_game_tile)[i].terrainFrameX = My_Tile[i].terrainFrameX ;
			(*_game_tile)[i].terrainFrameY = My_Tile[i].terrainFrameY;
			(*_game_tile)[i].hasUnit = My_Tile[i].hasUnit;
			(*_game_tile)[i].canPass = My_Tile[i].canPass;
			(*_game_tile)[i].layer = My_Tile[i].layer;
			(*_game_tile)[i].rc = My_Tile[i].rc;
			(*_game_tile)[i].tag = My_Tile[i].tag;
			(*_game_tile)[i].x = My_Tile[i].x;
			(*_game_tile)[i].y = My_Tile[i].y;
		}
	}
	My_unit = new unit[num];
	file = CreateFile(My_Game_save_file_unit, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, My_unit, sizeof(unit) * UNITMAXSIZE, &read, NULL);
	CloseHandle(file);

	if (file != INVALID_HANDLE_VALUE) {

		for (int i = 0; i < UNITMAXSIZE ; i++) {
			cout << My_unit[i].tileIndex << endl;
			tile* ptile;
			if(My_unit[i].tileIndex >= 0)
				ptile = _map->GetTileP(My_unit[i].tileIndex);

			switch (My_unit[i].tag) {
			case TAG::ITEM:
				UNITMANAGER->AddProduction(My_unit[i].objKey, { My_unit[i].rc.left, My_unit[i].rc.top });
				break;
			case TAG::ENEMY:
				UNITMANAGER->AddUnits(My_unit[i].objKey, { My_unit[i].rc.left, My_unit[i].rc.top }, true);
				break;
			case TAG::PLAYER:
				break;
			case TAG::OBJECT:
				UNITMANAGER->AddResource(My_unit[i].objKey, ptile, My_unit[i].tileIndex);
				break;
			case TAG::NPC:
				
				break;
			case TAG::BUILDING:
				UNITMANAGER->AddBuilding(My_unit[i].objKey, _map->GetTileP(0));
				break;
			}
		}
	}
	return true;
}

void saveManager::Item_transform()
{
	for (int i = 0; i < ITEMMANAGER->getvInventory_info().size(); i++) {
		My_Item[i].count =ITEMMANAGER->getvInventory_info()[i]->count;
		My_Item[i].img_name =ITEMMANAGER->getvInventory_info()[i]->img_name;
		My_Item[i].isCheck =ITEMMANAGER->getvInventory_info()[i]->isCheck;
		My_Item[i].item_Info =ITEMMANAGER->getvInventory_info()[i]->item_Info;
		My_Item[i].item_name =ITEMMANAGER->getvInventory_info()[i]->item_name;
		My_Item[i].Kinds =ITEMMANAGER->getvInventory_info()[i]->Kinds;
		My_Item[i].x =ITEMMANAGER->getvInventory_info()[i]->x;
		My_Item[i].y =ITEMMANAGER->getvInventory_info()[i]->y;
		My_Item[i]._rc =ITEMMANAGER->getvInventory_info()[i]->_rc;
	}

}

void saveManager::equip_transform()
{
	for (int i = 0; i < ITEMMANAGER->get_equip_info().size(); i++) {
		 My_equip[i].count = ITEMMANAGER->get_equip_info()[i]->count;
		 My_equip[i].img_name = ITEMMANAGER->get_equip_info()[i]->img_name;
		 My_equip[i].isCheck = ITEMMANAGER->get_equip_info()[i]->isCheck;
		 My_equip[i].item_Info = ITEMMANAGER->get_equip_info()[i]->item_Info;
		 My_equip[i].item_name = ITEMMANAGER->get_equip_info()[i]->item_name;
		 My_equip[i].Kinds = ITEMMANAGER->get_equip_info()[i]->Kinds;
		 My_equip[i].x = ITEMMANAGER->get_equip_info()[i]->x;
		 My_equip[i].y = ITEMMANAGER->get_equip_info()[i]->y;
		 My_equip[i]._rc = ITEMMANAGER->get_equip_info()[i]->_rc;
	}
}

void saveManager::Unit_transform()
{
	_Unit = UNITMANAGER->GetUnits();

	for (int i = 0; i < UNITMAXSIZE; i++) {
		My_unit[i].tileIndex = 1;
		if (i < _Unit.size()) {
			My_unit[i].objKey = _Unit[i]->objKey;
			My_unit[i].tag = _Unit[i]->tag;
			My_unit[i].rc = _Unit[i]->rc;
			My_unit[i].tileIndex = _Unit[i]->tileIndex;
		}
		else {
			My_unit[i].tag = TAG::NONE;

		}
	}
}

void saveManager::Tile_transform()
{

	for (int i = 0; i <(*_game_tile).size(); i++) {
		My_Tile[i].terrKey = (*_game_tile)[i].terrKey;
		My_Tile[i].terrainFrameX =(*_game_tile)[i].terrainFrameX;
		My_Tile[i].terrainFrameY =(*_game_tile)[i].terrainFrameY;
		My_Tile[i].hasUnit =(*_game_tile)[i].hasUnit;
		My_Tile[i].canPass =(*_game_tile)[i].canPass;
		My_Tile[i].layer =(*_game_tile)[i].layer;
		My_Tile[i].rc =(*_game_tile)[i].rc;
		My_Tile[i].tag =(*_game_tile)[i].tag;
		My_Tile[i].x =(*_game_tile)[i].x;
		My_Tile[i].y =(*_game_tile)[i].y;
	}
}


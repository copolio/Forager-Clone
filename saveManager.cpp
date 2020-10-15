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

	int num = _Unit.size();
	string str = to_string(num);

	INIDATA->addData("UnitCount", "0", str.c_str());
	INIDATA->saveINI("Unit");
}

bool saveManager::load()
{
	int num = INIDATA->loadDataInteger("Unit", "UnitCount", "0");
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
	ReadFile(file, My_unit, sizeof(unit) * num, &read, NULL);
	CloseHandle(file);

	if (file != INVALID_HANDLE_VALUE) {
		for (int i = 0; i < num ; i++) {
			cout << i << endl;
			switch (My_unit[i].tag) {
			case TAG::TERRAIN:

				break;
			case TAG::ITEM:

				break;
			case TAG::ENEMY:

				break;
			case TAG::PLAYER:
				for (int i = 0; i < UNITMANAGER->GetUnits().size(); i++) {
					if (UNITMANAGER->GetUnits()[i]->tag == TAG::PLAYER) {
						UNITMANAGER->GetUnits()[i]->currentCount = My_unit[i].currentCount;
						UNITMANAGER->GetUnits()[i]->currentHp = My_unit[i].currentHp;
						UNITMANAGER->GetUnits()[i]->isHit = My_unit[i].isHit;
						UNITMANAGER->GetUnits()[i]->maxHp = My_unit[i].maxHp;
						UNITMANAGER->GetUnits()[i]->nextCount = My_unit[i].nextCount;
						UNITMANAGER->GetUnits()[i]->rc = My_unit[i].rc;
						UNITMANAGER->GetUnits()[i]->x = My_unit[i].x;
						UNITMANAGER->GetUnits()[i]->y = My_unit[i].y;
						break;
					}
				}
				break;
			case TAG::OBJECT:
				
				break;
			case TAG::NPC:
				
				break;
			case TAG::BUILDING:

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
	My_unit = &(*_Unit[0]);

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


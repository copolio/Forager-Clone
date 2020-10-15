#include "stdafx.h"
#include "saveManager.h"
#include "quick_slot.h"
void saveManager::save()
{
	this->Item_transform();
	this->equip_transform();
	HANDLE file;
	DWORD write;

	file = CreateFile(My_Game_save_file_tiem, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, My_Item, sizeof(inventory_slot) * ITEMSIZE, &write, NULL);
	CloseHandle(file);

	file = CreateFile(My_Game_save_file_equip, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, My_equip, sizeof(inventory_slot) * EQUIPSIZE, &write, NULL);
	CloseHandle(file);
}

bool saveManager::load()
{
	
	
		HANDLE file;
		DWORD read;
		file = CreateFile(My_Game_save_file_tiem, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, My_Item, sizeof(inventory_slot) *ITEMSIZE, &read, NULL);
		CloseHandle(file);

		file = CreateFile(My_Game_save_file_equip, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, My_equip, sizeof(inventory_slot) *EQUIPSIZE, &read, NULL);
		CloseHandle(file);
	

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
	

	return true;
}

bool saveManager::DoesFileExist(LPCSTR pszFilename)
{
	DWORD dwAttrib = GetFileAttributes(pszFilename);
	if (!(dwAttrib & FILE_ATTRIBUTE_DEVICE) &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		return true;
	}
	return false;
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


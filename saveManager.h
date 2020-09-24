#pragma once
#include "singletonBase.h"
#include "tile.h"
#define SAVEFILE 7056

class saveManager :public singletonBase<saveManager>
{

public:
	tile _tiles[SAVEFILE];
	//LPCSTR slotName;
	string slotName;





	void save();
	void load();

	void exchangeToArray(vector<tile> _vTiles);
	void getSaveTile() { return save(); }
	void getLoadTile() { return load(); }

	int arraySize();
	//void g
};


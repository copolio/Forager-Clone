#pragma once
#include "singletonBase.h"
#include "tile.h"
#define SAVEFILE 8000

class saveManager :public singletonBase<saveManager>
{

public:
	tile _tiles[SAVEFILE];
	LPCSTR slotName;





	void save();
	void load();

	void exchangeToArray(vector<tile> _vTiles);
	void getSaveTile() { return save(); }
	void getLoadTile() { return load(); }

	

	int arraySize();
	//void g
};


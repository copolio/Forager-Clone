#pragma once
#include "tile.h"
class gamemap
{
protected:
	vector<tile> _vTile;
public:
	vector<tile> GetTiles() { return _vTile; }
	vector<tile>* PGetTiles() { return &_vTile; }

	tile GetTile(int index) { return _vTile[index]; };
	tile* GetTileP(int index) { return &_vTile[index]; };
	RECT GetTileRc(int index) { return _vTile[index].rc; }
};


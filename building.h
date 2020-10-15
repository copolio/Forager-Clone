#pragma once
#include "unit.h"
#include "tile.h"
#define BUILDINGHP 500

class building : public unit
{
public:
	vector<tile*> _tiles;
	RECT interactionRc;

public:
	void setBuilding(string buildingName, tile* _tile, int tileindex);
	void setBuilding(string buildingName, vector<tile*> tiles, int tileindex);
	void dead() override;
	void hurt(int damage) override;
	void render(HDC hdc) override;
};


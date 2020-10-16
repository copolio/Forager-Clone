#pragma once
#include "unit.h"
#include "tile.h"

#define NUMRES 3
#define RESHP 50
#define BERRYHP RESHP
#define TREEHP RESHP
#define ROCKHP RESHP

class inGameResource : public unit
{
public:
	tile* _tile;

public:
	void setRandomRes(tile* tile, int ptileIndex);
	void setResource(string key, tile* p_tile, int p_tileIndex);
	void dead() override;
	void render(HDC hdc) override;

	void hurt(int damage) override;
};


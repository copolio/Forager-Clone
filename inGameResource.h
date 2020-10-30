#pragma once
#include "unit.h"
#include "tile.h"

#define NUMRES 3
#define BERRYHP 30
#define TREEHP 120
#define ROCKHP 150

class inGameResource : public unit
{
public:
	tile* _tile;

public:
	void setRandomRes(tile* tile, int ptileIndex);
	void setResource(string key, tile* p_tile, int p_tileIndex);
	void dead() override;
	void render(HDC hdc) override;

	void hurt(int damage,bool onlyEffect = false) override;
};


#pragma once
#include "unit.h"
#include "tile.h"

#define NUMRES 3
#define RESHP 50
#define BERRYHP RESHP
#define TREEHP RESHP
#define ROCKHP RESHP

class resource : public unit
{
public:
	tile* _tile;

public:
	void setRandomRes(tile* tile);
	void dead() override;
	void render(HDC hdc) override;
	
};


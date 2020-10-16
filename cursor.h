#pragma once

#include "earth.h"
#include "unit.h"
#include "targetingBox.h"
#include "buildinginteraction.h"

#define MAXTOUCHDISTANCE TILESIZE*2

class earth;
class cursor
{

private:
	buildinginteraction* _buildinginteraction;
	earth* _map;
	unit* _unit;
	targetingBox _targetingBox;
	bool isbuilding;
	int number;
	bool interaction;
	vector<unit*> vUnit;
private:
	void CheckObject();

public:
	void init();
	void update();
	void render(HDC hdc);
	void LinkMap(earth* map) { _map = map; };
	bool InteractionOpen()
	{
		return interaction;
	};
	unit* GetTargetUnit() { return _unit; };
};


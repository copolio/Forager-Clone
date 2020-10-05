#pragma once

#include "earth.h"
#include "unit.h"
#include "targetingBox.h"

class earth;

class cursor
{

private:
	earth* _map;
	unit* _unit;
	targetingBox _targetingBox;

private:
	void CheckObject();


public:
	void init();
	void update();
	void render(HDC hdc);
	void LinkMap(earth* map) { _map = map; };

	unit* GetTargetUnit() { return _unit; };
};


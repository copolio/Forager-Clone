#pragma once
#include "singletonBase.h"
#include "building.h"
#include "enemy.h"
#include "fieldItem.h"
#include "resource.h"
#include "unit.h"

class UnitManager : public singletonBase<UnitManager>
{
private:
	vector<unit*> _vUnits;

private:
	void Sorting();
	void CheckRemoveUnit();

public:
	void init();
	void update();
	void render(HDC hdc);

	void AddUnits(tile* p_tile);
	void AddUnits(string p_itemKey, POINT p_pos);


public:
	vector<unit*> GetUnits() { return _vUnits; };
};


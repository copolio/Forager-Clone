#pragma once
#include "building.h"
class fishTrap : public building
{
private:
	int _cntfishWait;
	int _fishWait;
	bool _isCatch;


public:
	void setFishTrap(string buildingName, tile* _tile, int tileindex);

	void update() override;
	void render(HDC hdc) override;

};


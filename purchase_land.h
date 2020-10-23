#pragma once
#include "targetingBox.h"
#define LANDPRICE 10
class earth;

class purchase_land 
{
private:
	bool isCheck;
	earth* _map;
	targetingBox *_targetBox;
	int _tileIndex;
	int _islandIndex;
	RECT _targetIslandrc;
	int* balance;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void renderBuildableTile(HDC hdc);
	void setIsCheck(bool check) {
		isCheck = check;
	}
	void setMapLink(earth* map) { _map = map; };
};


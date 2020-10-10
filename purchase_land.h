#pragma once
#include "targetingBox.h"

class earth;

class purchase_land 
{
private:
	bool isCheck;
	earth* _map;
	targetingBox *_targetBox;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void setIsCheck(bool check) {
		isCheck = check;
	}
	void setMapLink(earth* map) { _map = map; };
};


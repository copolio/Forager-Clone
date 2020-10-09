#pragma once
#include "targetingBox.h"

class purchase_land 
{
private:
	bool isCheck;
	targetingBox *_targetBox;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void setIsCheck(bool check) {
		isCheck = check;
	}
};


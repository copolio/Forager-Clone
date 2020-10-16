#pragma once
#include "unit.h"
class fieldItem : public unit
{

private:
	bool isUp;
	int maxY;
	int minY;
	int _disappearCount;

public:

	void animation() override;
	void setFieldItem(POINT ptPos, string itemKey);
	void collision() override;
	void render(HDC hdc) override;
};


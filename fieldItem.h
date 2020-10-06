#pragma once
#include "unit.h"
class fieldItem : public unit
{

public:

	void setFieldItem(POINT ptPos, string itemKey);
	void collision() override;
};


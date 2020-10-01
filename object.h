#pragma once
#include "unit.h"
enum class OBJECTSTATUS {
	IDLE,
	ATTACKED
};
class object : public unit
{
public:
	string objKey;
	int objHp;
	int objFrameX;
	int objFrameY;
	OBJECTSTATUS objStatus;
};


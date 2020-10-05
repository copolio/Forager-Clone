#pragma once
#include "unit.h"
#define NUMRES 3
#define RESHP 50
#define BERRYHP RESHP
#define TREEHP RESHP
#define ROCKHP RESHP

class resource : public unit
{
public:
	void setRandomRes(RECT _rc);
};


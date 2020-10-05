#include "stdafx.h"
#include "resource.h"

void resource::setRandomRes(RECT _rc)
{
	this->rc = _rc;
	this->layer = LAYER::OBJECT;
	this->tag = TAG::OBJECT;
	switch (RANDOM->range(NUMRES)) {
	case 0:
		this->objKey = "berry";
		this->objFrameX = 0;
		this->objFrameY = 0;
		this->hp = BERRYHP;
		break;
	case 1:
		this->objKey = "rock";
		this->objFrameX = 0;
		this->objFrameY = 0;
		this->hp = ROCKHP;
		break;
	case 2:
		this->objKey = "tree";
		this->objFrameX = 0;
		this->objFrameY = 0;
		this->hp = TREEHP;
		break;
	}
}

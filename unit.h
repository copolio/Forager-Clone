#pragma once
#include "gameObject.h"
#define NUMUNIT 5 //빌딩 2개 + 자원 3개
struct dropItem {
	RECT rc;
	string itemKey;
	string imgName;
	float dropItemX;
	float dropItemY;
};
class unit : public gameObject
{
public:
	int hp;
	int exp;
	string objKey;
	int objFrameX;
	int objFrameY;
public:
	void setDropItem();
	void setMapTile();
};


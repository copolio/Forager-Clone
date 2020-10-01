#pragma once
#include "gameObject.h"
struct dropItem {
	RECT rc;
	//image* dropItems;
	string itemKey;
	string imgName;
	float dropItemX;
	float dropItemY;

};
class unit :
	public gameObject
{
private:

	int hp;
	int exp;

public:
	void setDropItem();
	void setMapTile();
	void setHp(int _hp) { hp = _hp; };
};


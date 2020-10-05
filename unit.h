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
class unit : public gameObject
{
protected:
	int hp;
	int currentHp;
	int exp;

public:
	void setDropItem();
	void setMapTile();
	void setHp(int _hp) { hp = _hp; };
	void setCurrentHp(int _currentHp) { currentHp = _currentHp; };
};


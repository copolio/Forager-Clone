#pragma once
#include "gameObject.h"
#define NUMUNIT 5 //빌딩 2개 + 자원 3개
class dropItem{
public:
	string itemKey;
};

class unit : public gameObject
{
public:
	int hp;
	int currentHp;
	int exp;
	dropItem dropItem;
	string objKey;
	int objFrameX;
	int objFrameY;
public:
	void setDropItem();
	void setMapTile();


	void hurt(int damage) {
		currentHp -= damage;
		if (currentHp <= 0)
			dead();
	};
	virtual void getItem() { ; };
	virtual void dead() { ; };


	bool isDead() { if (currentHp <= 0) return true; else return false; }
};


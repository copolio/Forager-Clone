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
	int maxHp;
	int currentHp;
	int exp;
	dropItem dropItem;
	string objKey;
	int objFrameX;
	int objFrameY;
public:

	void hurt(int damage);
	virtual void collision() { ; };
	virtual void dead() { ; };
	virtual void update();
	virtual void render(HDC hdc) override;

	bool isDead();
};


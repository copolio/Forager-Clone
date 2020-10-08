#pragma once
#include "gameObject.h"
#define NUMUNIT 5 //빌딩 2개 + 자원 3개
class dropItem{
public:
	string itemKey;
};

class unit : public gameObject
{

private:

	

public:
	int maxHp;
	int currentHp;
	int exp;
	dropItem dropItem;
	string objKey;
	int objFrameX;
	int objFrameY;
	POINT dir;
public:

	void hurt(int damage);
	virtual void collision() { ; };
	virtual void dead() { ; };
	virtual void update();
	virtual void render(HDC hdc) override;


	//tile GetTile(int index) { return _vTile[index]; };
	//RECT GetTileRc(int index) { return _vTile[index].rc; }

	
	bool isDead();
};


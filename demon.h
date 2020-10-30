#pragma once
#include "enemy.h"
#define MOVERANGE 2
#define MOVESPEED 1
enum DEMONSTATE
{
	DWALK,
	DIDLE,
	DYELL

};
class demon :public enemy
{
private :
	DEMONSTATE _state4;

	int demonWaitCount;
	int demonBrassCount;
	int demonHitCount;
	int searchCount;
	int demonAttackRange;
	int skillFireCount;

	bool tryAttack;
	POINT _destination;
	bool isattacking;

public:
	HRESULT init();
	void update() override;
	void render(HDC hdc) override;

	void demonMove();
	void demonAttack();
	void demonAnimation();
	void demonLookDirection();
	void demonBrassFire();
	

};


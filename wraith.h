#pragma once
#include "enemy.h"

enum WRAITHSTATE
{
	FLY,
	SHOOT
};

class wraith :public enemy
{

private:
	WRAITHSTATE _state3;

	int wraithWaitCount;
	int wraithHitCount;
	int wraithShootCount;
	int searchCount;
	int wraithAttackRange;
	int skillFireCount;
	int skill1coolTime;
	int skillAngle;
	bool tryAttack;

	int Atk;
public:
	HRESULT init();
	void update() override;
	void render(HDC hdc) override;

	void wraithMove();
	void wraithAttack();
	void wraithAnimation();
	void wraithLookDirection();
	void wraithFire();
	
	float shootToTarget();
	void dead() override;
};


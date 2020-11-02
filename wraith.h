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
	int skillAngle;

	int _hitCount;
	bool tryAttack;

	int _difficultyLevel;
public:
	HRESULT init(int p_level);
	void update() override;
	void render(HDC hdc) override;

	void wraithMove();
	void wraithAttack();
	void wraithAnimation();
	void wraithLookDirection();
	void wraithFire();
	void wraithHitAttack();

	//float shootToTarget();
	void dead() override;
};


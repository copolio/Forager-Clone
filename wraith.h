#pragma once
#include "enemy.h"
class wraith :public enemy
{

private:
	int wraithWaitCount;
	int wraithHitCount;
	int wraithShootCount;
	int searchCount;
	int wraithAttackRange;
	
	int skillFireCount;


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
	
};


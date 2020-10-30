#pragma once
#include "enemy.h"

enum SMALLMUSTATE
{
	IDLE6,
	CRY2
};
class smallMu : public enemy
{
private:
	SMALLMUSTATE _state6;


	int searchCount;
	int ShootCount;
	bool isattacking;

public: 

	HRESULT init();
	void update();
	void render(HDC hdc) override;
	void smallMuAnimation();
	void smallMuMove();
	void smallMuFire();
};


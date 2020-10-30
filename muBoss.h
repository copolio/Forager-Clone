#pragma once
#include "unit.h"
enum MUSTATE
{
	MIDLE,
	CRY,
	MUSHOOT
};

class muBoss : public enemy
{
private:
	MUSTATE _state5;
	int fireCount;
	int crashCount;
	int crashPointCount;
	int searchCount;

	bool _canFire;
	bool _readyToCrash;

public:

	HRESULT init();
	void update() override;
	void render(HDC hdc) override;
	
	void muuAnimation();
	void hurt(int damage, bool onlyEffect = false) override;
	void dead() override;

	void muFire();
	void muBossExplode();


	
};


#pragma once
#include "unit.h"
enum MUSTATE
{
	MIDLE,
	CRY
};

class muBoss : public enemy
{
private:
	MUSTATE _state5;
public:

	HRESULT init();
	void update() override;
	void render(HDC hdc) override;
	
	void muuAnimation();
	void hurt(int damage, bool onlyEffect = false) override;
	void dead() override;


	
};


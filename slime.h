#pragma once
#include "enemy.h"
enum SLIMESTATE
{


};
class slime : public enemy
{
private:
	int slimejumpRange;

public:
	HRESULT init();
	void update();
	void render(HDC hdc) override;

	void slimeAnimation();
	void slimeMove();
	void slimeJump();


};


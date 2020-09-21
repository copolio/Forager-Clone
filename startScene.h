#pragma once
#include "gameNode.h"
#include "targetingBox.h"
#include "reactImage.h"


#define BUTTON_MAX 6

class startScene : public gameNode
{
private:
	enum BTN {
		SETTING,
		CREDIT,
		EXIT,
		SLOT1,
		SLOT2,
		SLOT3,
	};

private:
	reactImage _button[BUTTON_MAX];

	targetingBox *_targetingBox;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void CheckCursorOnButton();
	void CheckButtonClick();
};


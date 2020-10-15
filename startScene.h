#pragma once
#include "gameNode.h"
#include "targetingBox.h"
#include "reactImage.h"
#include "gamesetting.h"
#include "earth.h"

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

	//saveManager* _saveManager;
	
	int testWalkEffectCount = 0;
	int testWalkEffectInterval = 10;

	bool gameSlotCheck;
	bool gameOptionCheck;
	bool _gameslotOne;
	bool _gameslotTwo;
	bool _gameslotThree;

	gamesetting *_game_setting;

	RECT saveRc; 

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void CheckGameFile();
	void CheckCursorOnButton();
	void CheckButtonClick();
};


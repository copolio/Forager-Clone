#pragma once

#include "reactImage.h"

class gamesetting
{
private:
	const int BGM = 0;
	const int SFX = 1;
	float _sfxVolumn;
	float _bgmVolumn;
	int _lang;
	int _choiceOptionNum;
	bool _camShake;
	bool _peaceMode;
	bool _cursorOn;

	int max;
	int min;

	RECT _rcWindow;
	RECT _rcOptions[6];
	RECT _rcArrow[10];
	RECT _rcSound[2];
	RECT _rcSoundBack[2];

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void CheckCursorOn();
	void CheckClick();
	void VolumnSetting();
};


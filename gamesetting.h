#pragma once
class gamesetting
{

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};


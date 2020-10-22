#pragma once
#include "building.h"
#include "cursor.h"

class fishTrap : public building
{
private:

	// Fish 정보
	int _cntfishWait;
	int _fishWait;
	bool _isCatch;

	// 텍스트 스케일 조절
	int sizeMin;
	int sizeCurrent;
	int sizeMax;
	bool sizeUp;

	// 커서 정보
	cursor *_cursor;


public:
	void setFishTrap(string buildingName, tile* _tile, int tileindex);

	void update() override;
	void animation();
	void fish();
	
	void render(HDC hdc) override;

};


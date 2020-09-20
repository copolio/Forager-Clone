#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY]; //인게임화면(왼쪽화면)에 사용되는 타일 총 400개
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY]; //샘플타일 총 160개
	tagCurrentTile _currentTile; //현재타일

	RECT _rcSave;		//세이브
	RECT _rcLoad;		//로드
	RECT _rcTerrain;	//지형
	RECT _rcObject;		//오브젝트
	RECT _rcEraser;		//지우개 (오브젝트만 지운다, 지형은 덮어씌운다)

	bool test; // 왜 반영이 안 되냐.ㅁㅁㄴㅇㅁㄴㅇㅁㄴㅇ

	CTRL _ctrlSelect;	//현재 어떤 컨트롤 상태인지

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//맵툴세팅
	void maptoolSetup();
	void setMap();
	void save();
	void load();

	//지형, 오브젝트 선택하기
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

};


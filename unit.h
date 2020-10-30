#pragma once
#include "gameObject.h"
#include "progressBar.h"

#define NUMUNIT 5 //빌딩 2개 + 자원 3개
class dropItem{
public:
	string itemKey;
};

class unit : public gameObject
{

protected:
	progressBar _hpBar;
	

public:
	// 이미지 키값
	string objKey;

	// 상태값
	int maxHp;
	int currentHp;
	bool isHit = false;	// 맞는 순간 타격 애니메이션 재생
	
	int atk;
	// 드롭
	int exp;
	dropItem dropItem;
	int tileIndex; // 저장 로드용

	// 애니메이션 관련
	int objFrameX;
	int objFrameY;
	int objMaxFrameX;
	int objMaxFrameY;

	// 애니메이션 재생 속도 관련
	int currentCount;
	int nextCount;
	int frameX;
	int count;

	bool waveUp;
	

public:
	virtual void update();
	void render(HDC hdc) override;
	
public:
	virtual void hurt(int damage, bool onlyEffect = false);			// 체력 닳음
	virtual void animation();		// 애니메이션 연출
	virtual void collision() { ; };	// 충돌시 연출 (필드 아이템)
	virtual void dead();		// 사망시 연출
	bool isDead();
};


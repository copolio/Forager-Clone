#pragma once
#include "enemy.h"
#define MOVERANGE 2
#define MOVESPEED 1
enum SKULLSTATE
{
	STAY,	//걸어다니는 이미지랑 
	ATTACK,
	APPEAR,
	IDLE2,
	GOTHIT
};

class skull :public enemy
{
private : 
private : 
	//int skullMoveCount;
	//int skullIdleCount;
	SKULLSTATE _state;

	int skullAttackRange;
	int searchCount;
	int skullHitCount;
	int skullHitWaitCount;
	//bool hitPlayer;
	bool tryAttack;
	POINT _destination;

	int nonAttacktime;
	bool isattacking;

	int Atk;

public :
	HRESULT init();
	 void update() override;
	 void render(HDC hdc) override;
	 void skullMove();
	 //void move(vector<int> vDestTileIndex) override;
	 void canAttackCheck();
	 void skullAnimation();
	 void skullLookDirection();
	
	 /*int FindSkullTilePos();
	 bool CanCheckMove(int index);
	 void CheckSkullTile();
	 void CheckCollision();*/

};


#include "stdafx.h"
#include "UnitManager.h"
#include "productionManager.h"
void UnitManager::init()
{
	//자원 1 (나무, 돌, 열매)
	IMAGEMANAGER->addFrameImage("berry", "Images/이미지/오브젝트/resource/img_object_berry.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rock", "Images/이미지/오브젝트/resource/img_object_rock.bmp", 112, 56, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tree", "Images/이미지/오브젝트/resource/img_object_tree.bmp", 280, 168, 5, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("berryDrop", "Images/이미지/아이템/berry.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("carry_berry", "Images/이미지/아이템/berry.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rockDrop", "Images/이미지/아이템/돌.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("treeDrop", "Images/이미지/아이템/wood.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fish", "Images/이미지/아이템/물고기.bmp", 56, 56, true, RGB(255, 0, 255));


	
	//자원 2 ('해골, 소'의 드랍아이템)
	IMAGEMANAGER->addImage("skullHeadDrop", "Images/이미지/아이템/skullHead.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("milkDrop", "Images/이미지/아이템/milk.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("carry_milk", "Images/이미지/아이템/milk.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pooDrop", "Images/이미지/아이템/poo.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("leatherDrop", "Images/이미지/아이템/leather.bmp", 56, 56, true, RGB(255, 0, 255));


	

	//에너미 - (해골, 소, 레이스)
	IMAGEMANAGER->addFrameImage("skull", "Images/이미지/NPC/해골idle2.bmp", 280, 112, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullAppear", "Images/이미지/NPC/해골Appear.bmp", 224, 56, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullAttack", "Images/이미지/NPC/해골attack.bmp", 393, 112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullIdle", "Images/이미지/NPC/해골stay.bmp",224 ,112 , 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skullappa", "Images/이미지/NPC/skullitai.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("cow", "Images/이미지/NPC/황소IDLE.bmp", 400, 100, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cowWalk", "Images/이미지/NPC/황소WALK.bmp", 560, 100, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cowDash", "Images/이미지/NPC/cowDash.bmp", 320, 100, 4, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("wraithAttack", "Images/이미지/NPC/레이스2.bmp", 1710, 400, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wraithIdle", "Images/이미지/NPC/레이스IDLE2.bmp", 2280, 400, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wraithBullet", "Images/이미지/NPC/레이스무기발사.bmp", 80, 600, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("demonYell", "Images/이미지/NPC/small_demon_yell.bmp", 576, 128, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("demonIdle", "Images/이미지/NPC/small_demon_idle.bmp", 256, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("demonWalk", "Images/이미지/NPC/small_demon_walk.bmp", 576, 102, 9, 2, true, RGB(255, 0, 255));
	
	// NPC
	IMAGEMANAGER->addFrameImage("David", "Images/이미지/NPC/img_npc_David.bmp", 444, 88, 4, 1, true, RGB(255, 0, 255));

	// 보물 상자
	IMAGEMANAGER->addImage("treasureBox", "Images/이미지/오브젝트/treasureBox.bmp", 140, 132, true, RGB(255, 0, 255));

	// 체력바
	IMAGEMANAGER->addImage("hpBarBG", "Images/이미지/NPC/NPC체력(뒤).bmp", 50, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpBar", "Images/이미지/NPC/NPC체력(앞).bmp", 40, 10, true, RGB(255, 0, 255));

	// 투사체 매니저 생성
	_projectileManager = new ProjectileManager;
	_projectileManager->init();
	_pProjectiles = _projectileManager->GetProjectile();

	// 스폰 매니저 생성
	//_spawnManager = new SpawnManager;
	//_spawnManager->init();
	SPAWNMANAGER->init();
}

void UnitManager::release()
{
	for(int i = 0 ; i < _vUnits.size(); i++)
		SAFE_DELETE(_vUnits[i]);
	_vUnits.clear();
	_vEnemy.clear();
	_vNpc.clear();
}


void UnitManager::update()
{
	Sorting();
	CheckRemoveUnit();

	// 유닛 업데이트
	for (int i = 0; i < _vUnits.size(); i++) {
		if (_vUnits[i]->tag != TAG::PLAYER ) {
			_vUnits[i]->update();
		}

		// 카메라 외곽과 NPC, 필드 아이템은 충돌처리 무시
		RECT temp;
		if (_vUnits[i]->tag == TAG::ITEM) continue;
		if (_vUnits[i]->tag == TAG::NPC) continue;
		if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &_vUnits[i]->rc)) continue;

		// 투사체와 유닛간의 충돌처리
		checkCollision(_vUnits[i]);
	}

	//_spawnManager->update();
	SPAWNMANAGER->update();
	_projectileManager->update();
}

void UnitManager::checkCollision(unit * p_unit)
{
	for (int k = 0; k < PROJECTILE_MAX; k++) {
		RECT temp;
		if (!_pProjectiles[k].isAppear) continue; 	// 발사 안 된 투사체는 무시

		// 유닛과 충돌한 투사체가 있다면
		if (IntersectRect(&temp, &p_unit->rc, &RectMake(_pProjectiles[k].x, 
			_pProjectiles[k].y, _pProjectiles[k].width, _pProjectiles[k].height)))
		{
			// Enemy 투사체는 플레이어에게만 데미지 적용
			if (_pProjectiles[k].isEnemyProjectTile)
			{
				if (p_unit->tag == TAG::PLAYER)
				{
					//SOUNDMANAGER->play("유령무기맞는소리", 0.4f);
					//IMAGEMANAGER->findImage("스테미나")->setWidth(5);
					_player->hurt(_pProjectiles[k].damage);
				}
				if (p_unit->tag != TAG::ENEMY && p_unit->tag != TAG::OBJECT) {
					if(!_pProjectiles[k].isBrassing)
						_pProjectiles[k].isAppear = false;
				}

			}
			// Player 투사체는 모든 유닛에게 데미지 적용
			else {
				if (p_unit->tag != TAG::PLAYER) {
					p_unit->hurt(_pProjectiles[k].damage);
					_pProjectiles[k].isAppear = false;
					if (p_unit->isDead())
					{
						if (p_unit->objKey == "skull")
							SOUNDMANAGER->play("해골사망소리");
						else if (p_unit->objKey == "cow")
							SOUNDMANAGER->play("황소사망소리");

						//스태니마 감소
						STATMANAGER->setRight(5);

						//그 유닛의 경험치 획득.
						int t_exp = p_unit->exp;
						if (t_exp > 0) {
							t_exp = RANDOM->range(t_exp - 2, t_exp + 3);
							POINT pt = { p_unit->rc.left, p_unit->rc.top };
							string str = std::to_string(t_exp);
							str.insert(0, "EXP ");
							TEXTMANAGER->ShowFloatingText(str, pt, RGB(100, 255, 100), RGB(0, 0, 0));
							STATMANAGER->IncreaseExp(t_exp);

						}
						// 타격 줌인 연출
						CAMERA->forceZoomIn(0.04f, 0.008f);
					}
					else {
						CAMERA->forceZoomIn(0.008f, 0.002f);
					}
				}
				
			}
		}
	}
}


void UnitManager::render(HDC hdc)
{
	// 레이어 : Terrain
	for (int i = 0; i < _vUnits.size(); i++) {
		if ((*_vUnits[i]).layer == LAYER::TERRAIN) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &(*_vUnits[i]).rc)) continue;
			(*_vUnits[i]).render(hdc);
		}
	}

	// 레이어 : Object
	for (int i = 0; i < _vUnits.size(); i++) {
		if ((*_vUnits[i]).layer == LAYER::OBJECT) {
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &(*_vUnits[i]).rc)) continue;
			(*_vUnits[i]).render(hdc);
		}
	}

	_projectileManager->render(hdc);
}



bool compare(unit* i, unit* j) {
	return (*i).GetCenterY() < (*j).GetCenterY();
}


// y축 정렬
void UnitManager::Sorting()
{
	sort(_vUnits.begin(), _vUnits.end(), compare);
}

// 죽거나 제거해야될 객체는 삭제
void UnitManager::CheckRemoveUnit()
{
	if (_vUnits.size() > 0) {
		for (auto iter = _vUnits.begin(); iter != _vUnits.end();) {
			if ((*iter)->isDead()) {
				if ((*iter)->tag == TAG::BUILDING) {
					PRODUCTIONMANAGER->removeBuildingRc((*iter)->rc);
				}
				SAFE_DELETE((*iter));
				iter = _vUnits.erase(iter);
			}
			else
				++iter;
		}
	}

	if (_vEnemy.size() > 0) {
		for (auto iter = _vEnemy.begin(); iter != _vEnemy.end();) {
			if ((*iter)->isDead()) {
				iter = _vEnemy.erase(iter);
			}
			else
				++iter;
		}
	}
}


void UnitManager::AddUnits(ForagerPlayer* p_unit)
{
	_player = p_unit;
	_vUnits.push_back(p_unit);

	// NPC 세팅
	AddUnits("David", { WINSIZEX / 2 + 100, WINSIZEY / 2 + 100 }, false);
}

void UnitManager::AddUnits(skull* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(wraith* p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(cow * p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}

void UnitManager::AddUnits(demon * p_unit, bool test)
{
	_vUnits.push_back(p_unit);
}



void UnitManager::AddUnits(string p_unitName, POINT p_pos, bool enemyCheck)
{

	// 에너미 생성
	if (enemyCheck) {
		//해골
		if (p_unitName == "skull")
		{
			skull* _skull = new skull;
			_skull->setLinkMap(_map);
			_skull->setEnemy(p_unitName, "skullHeadDrop", _player, p_pos);
			_skull->init();

			_vUnits.push_back(_skull);
			_vEnemy.push_back(_skull);
		}

		//소
		if (p_unitName == "cow")
		{
			cow* _cow = new cow;
			_cow->setLinkMap(_map);
			_cow->setEnemy(p_unitName, "milkDrop", _player, p_pos);
			_cow->init();
			_vUnits.push_back(_cow);
			_vEnemy.push_back(_cow);
		}

		//레이스
		if (p_unitName == "wraithIdle")
		{
			wraith* _wraith = new wraith;
			_wraith->setLinkMap(_map);
			_wraith->setEnemy(p_unitName, "leatherDrop", _player, p_pos);
			_wraith->init();
			_vUnits.push_back(_wraith);
			_vEnemy.push_back(_wraith);
		}

		//데몬
		if (p_unitName == "demonIdle")
		{
			demon* _demon = new demon;
			_demon->setLinkMap(_map);
			_demon->setEnemy(p_unitName, "img_game_money_icon", _player, p_pos);
			_demon->init();
			_vUnits.push_back(_demon);
			_vEnemy.push_back(_demon);
		}
	}
	
	// NPC 생성
	else {
		if (p_unitName == "David")
		{
			npc* t_npc = new npc;
			t_npc->setNpc(p_unitName, p_pos, &_player->rc);
			_vUnits.push_back(t_npc);
			_vNpc.push_back(t_npc);
		}
	}
}

// 유닛 추가
void UnitManager::AddUnits(string p_itemKey, POINT p_pos)
{
	for (int i = 0; i < 3; i++) {
		fieldItem* t_fieldItem = new fieldItem;
		t_fieldItem->setFieldItem(p_pos, p_itemKey);
		_vUnits.push_back(t_fieldItem);
	}
	if (p_itemKey == "rockDrop") {
		if (RANDOM->range(3, 10) > 5) {
			for (int i = 0; i < RANDOM->range(2) + 1; i++) {
				fieldItem* t_fieldItem = new fieldItem;
				t_fieldItem->setFieldItem(p_pos, "Iron_ore");
				_vUnits.push_back(t_fieldItem);
			}
		}
		if (RANDOM->range(0, 5) < 3) {
			for (int i = 0; i < RANDOM->range(2) + 1; i++) {
				fieldItem* t_fieldItem = new fieldItem;
				t_fieldItem->setFieldItem(p_pos, "금광석");
				_vUnits.push_back(t_fieldItem);
			}
		}
	}
}

void UnitManager::AddProduction(string p_itemKey, POINT p_pos)
{
	fieldItem* t_fieldItem = new fieldItem;

	t_fieldItem->setFieldItem(p_pos, p_itemKey);
	_vUnits.push_back(t_fieldItem);
}



int UnitManager::GetMonsterCount()
{
	int t_monsterCount = 0;
	for (int i = 0; i < _vUnits.size(); i++) {
		if (_vUnits[i]->tag == TAG::ENEMY) {
			t_monsterCount++;
		}
	}
	return t_monsterCount;
}

void UnitManager::setLinkMap(earth * p_map)
{
	_map = p_map;
	//_spawnManager->setLinkMap(_map);
	SPAWNMANAGER->setLinkMap(_map);
}

POINT UnitManager::GetPlayerFootPt()
{
	return { CAMERA->GetRelativeX(_player->GetCenterX()) , CAMERA->GetRelativeY(_player->rc.bottom + 25) };
}


void UnitManager::AddBuilding(string buildkey, tile * _tile, int tileindex)
{
	if (buildkey == "fishtrap") {
		fishTrap *t_fishTrap = new fishTrap;
		t_fishTrap->setFishTrap(buildkey, _tile, tileindex);
		_vUnits.push_back(t_fishTrap);

	}
	else {
		building* _building = new building;
		_building->setBuilding(buildkey, _tile, tileindex);
		_vUnits.push_back(_building);

	}
}

void UnitManager::AddBuilding(string buildkey, vector<tile*> tiles, int tileindex)
{
	building* _building = new building;
	_building->setBuilding(buildkey, tiles, tileindex);
	_vUnits.push_back(_building);
	PRODUCTIONMANAGER->settion(_building->rc);
	//_production->settion(_building->rc);ㅈ
}

void UnitManager::AddResource(tile* p_tile, int p_tileIndex)
{
	inGameResource* _res = new inGameResource;
	_res->setRandomRes(p_tile, p_tileIndex);
	_vUnits.push_back(_res);
}

void UnitManager::AddResource(string key, tile * _tile, int p_tileIndex)
{
	inGameResource* _res = new inGameResource;
	_res->setResource(key, _tile, p_tileIndex);
	_vUnits.push_back(_res);
}

void UnitManager::AddTreasure(string p_key, string p_itemRewardKey, POINT p_ptPos)
{
	treasureBox *t_tBox = new treasureBox;
	t_tBox->setTreasureBox(p_key, p_itemRewardKey, p_ptPos, &_player->rc);
	_vUnits.push_back(t_tBox);
}






#include "stdafx.h"
#include "ProjectileManager.h"

void ProjectileManager::init()
{
	IMAGEMANAGER->addImage("BowArrow", "Images/이미지/아이템/img_UI_bowArrow.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("BowArrow")->initForRotateImage(false);
	IMAGEMANAGER->addFrameImage("wratihMissile", "Images/이미지/NPC/wratihMissile.bmp", 990, 90, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("demonBrass", "Images/이미지/NPC/firebrass.bmp", 2560, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slimeMissile", "Images/이미지/NPC/slime_bullet.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slimeBossMissile", "Images/이미지/NPC/red_bullet.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("smallMuMissile", "Images/이미지/NPC/seed.bmp", 30, 30, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("muMissile", "Images/이미지/NPC/baby_mu.bmp", 198, 45, 6, 1, true, RGB(255, 0, 255));


	for (int i = 0; i < PROJECTILE_MAX; i++) {
		_projectiles[i].imgKey = "temp";
		_projectiles[i].x = 0;
		_projectiles[i].y = 0;
		_projectiles[i].angle = 0.0f;
		_projectiles[i].damage = 0;
		_projectiles[i].frameX = 0;
		_projectiles[i].frameY = 0;
		_projectiles[i].isAppear = false;
		_projectiles[i].isEnemyProjectTile = false;
		_projectiles[i].isStretch = false;
		_projectiles[i].isBrassing = false;
		_projectiles[i].speed = 0;
		_projectiles[i].count = 0;
		_projectiles[i].brassCount = 0;
		_projectiles[i]._playerTargetRc = nullptr;
		_projectiles[i].isFollowing = false;
	}
}

void ProjectileManager::release()
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		_projectiles[i].isAppear = false;
	}
}

void ProjectileManager::update()
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		if (_projectiles[i].isAppear) 
		{
			//해당 투사체가 isFollowing인 경우,
			if (_projectiles[i].isFollowing) {
				float targetAngle = shootToTarget(i);
				float destAngle = (targetAngle + _projectiles[i].angle) * 0.5f;
				_projectiles[i].angle = destAngle;

				if (_projectiles[i].brassCount++ > 240) {
					_projectiles[i].isAppear = false;
				}
			}

			// 이미지 출력 안 하는, 투사체겸 장판 데미지용
			if (_projectiles[i].imgKey == _strDamageBoundary) {
				if (_projectiles[i].count++ > 3) {
					_projectiles[i].isAppear = false;
				}
			}

			// 이미지 출력하는 일반 투사체
			else 
			{
				// 일반 화살같은
				if (!_projectiles[i].isBrassing)
				{
					_projectiles[i].x += cosf(_projectiles[i].angle * PI / 180.0f) * _projectiles[i].speed;
					_projectiles[i].y -= sinf(_projectiles[i].angle * PI / 180.0f) * _projectiles[i].speed;

					// 프레임이 필요한 투사체의 경우-
					if (_projectiles[i].isFrame)
					{
						if (_projectiles[i].count++ % 10 == 0)
						{
							_projectiles[i].frameX++;
							if (_projectiles[i].frameX > 10)
							{
								_projectiles[i].frameX = 11;
								_projectiles[i].frameY = 0;
							}
						}
					}
				}
				// 브레스같은
				else
				{
					if (_projectiles[i].count++ % 12 == 0)
					{
						_projectiles[i].frameX += _projectiles[i].isPingPong ? 1 : -1;
						if (_projectiles[i].frameX > 8)
							_projectiles[i].isPingPong = false;
						if (_projectiles[i].isPingPong == false && _projectiles[i].frameX == 0)
							_projectiles[i].isAppear = false;
					}
				}
			}

			
			
			// 카메라 바깥으로 나가면 삭제
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &RectMakeCenter(_projectiles[i].x, _projectiles[i].y, 20, 20)))
				_projectiles[i].isAppear = false;
		}
	}
}

void ProjectileManager::render(HDC hdc)
{
	if (CAMERA->movelimit) {
		for (int i = 0; i < PROJECTILE_MAX; i++)
		{
			if (_projectiles[i].isAppear) {

				if (_projectiles[i].imgKey == _strDamageBoundary)
					continue;
				// 일반 렌더
				if (!_projectiles[i].isFrame)
					IMAGEMANAGER->findImage(_projectiles[i].imgKey)->rotateRender(hdc, CAMERA->GetRelativeX(_projectiles[i].x), CAMERA->GetRelativeY(_projectiles[i].y), _projectiles[i].angle * PI / 180.0f);
				// 프레임 렌더
				else {
					IMAGEMANAGER->frameRender(_projectiles[i].imgKey, hdc, CAMERA->GetRelativeX(_projectiles[i].x), CAMERA->GetRelativeY(_projectiles[i].y), _projectiles[i].frameX, _projectiles[i].frameY, CAMERA->GetZoom());
				}
			}
		}
	}

}

void ProjectileManager::CreateProjectile(string imgKey, int x, int y, int damage, float angle, float speed, int size, bool isEnemy, bool isFrame, bool isStretch)
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		if (!_projectiles[i].isAppear) {
			_projectiles[i].imgKey = imgKey;
			_projectiles[i].x = x;
			_projectiles[i].y = y;
			_projectiles[i].damage = damage;
			_projectiles[i].angle = angle;
			_projectiles[i].speed = speed;
			_projectiles[i].isEnemyProjectTile = isEnemy;
			_projectiles[i].isStretch = isStretch;
			_projectiles[i].count = 0;
			_projectiles[i].isAppear = true;
			_projectiles[i].width = size;
			_projectiles[i].height = size;
			_projectiles[i].isFrame = isFrame;
			_projectiles[i].frameX = 0;
			_projectiles[i].frameY = 0;

			_projectiles[i].isBrassing = false;
			_projectiles[i].brassCount = 0;
			_projectiles[i].isPingPong = false;
			_projectiles[i].isFollowing = false;

			_projectiles[i]._playerTargetRc = nullptr;
			break;
		}
	}
}

void ProjectileManager::CreateProjectile(string imgKey, RECT * playerTargetRc, int x, int y, int damage, float angle, float speed, int size, bool isEnemy, bool isFrame, bool isFollowing)
{
	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		if (!_projectiles[i].isAppear) {
			_projectiles[i].imgKey = imgKey;
			_projectiles[i].x = x;
			_projectiles[i].y = y;
			_projectiles[i].damage = damage;
			_projectiles[i].angle = angle;
			_projectiles[i].speed = speed;
			_projectiles[i].width = size;
			_projectiles[i].height = size;
			_projectiles[i].isEnemyProjectTile = isEnemy;
			_projectiles[i].isFrame = isFrame;
			_projectiles[i].isFollowing = isFollowing;
			_projectiles[i].frameX = 0;
			_projectiles[i].frameY = 0;
			_projectiles[i].count = 0;
			_projectiles[i]._playerTargetRc = playerTargetRc;

			_projectiles[i].isBrassing = false;
			_projectiles[i].brassCount = 0;
			_projectiles[i].isPingPong = false;
			_projectiles[i].isAppear = true;

			break;
		}
	}


}

float ProjectileManager::shootToTarget(int index)
{	
	int cX = _projectiles[index].x;
	int cY = _projectiles[index].y;

	int pL = _projectiles[index]._playerTargetRc->left;
	int pR = _projectiles[index]._playerTargetRc->right;
	int pT = _projectiles[index]._playerTargetRc->top;
	int pB = _projectiles[index]._playerTargetRc->bottom;

	int cPx = pL + (pR - pL) / 2;
	int cPy = pT + (pB - pT) / 2;

	return atan2(-(cPy - cY), (cPx - cX)) / PI * 180;
	
	
}

void ProjectileManager::CreateProjectile(string imgKey, int x, int y, int damage, int width, int height, bool isLeft)
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		if (!_projectiles[i].isAppear) {
			_projectiles[i].imgKey = imgKey;
			_projectiles[i].x = x;
			_projectiles[i].y = y;
			_projectiles[i].damage = damage;
			_projectiles[i].angle = 0;
			_projectiles[i].speed = 0;
			_projectiles[i].isEnemyProjectTile = true;
			_projectiles[i].isStretch = false;
			_projectiles[i].count = 0;
			_projectiles[i].isAppear = true;
			_projectiles[i].width = width;
			_projectiles[i].height = height;
			_projectiles[i].isFrame = true;

			_projectiles[i].isBrassing = true;
			_projectiles[i].brassCount = 0;
			_projectiles[i].isPingPong = true;

			_projectiles[i].frameX = 0;
			_projectiles[i].frameY = isLeft ? 1 : 0;

			_projectiles[i].isFollowing = false;
			_projectiles[i]._playerTargetRc = nullptr;

			break;
		}
	}

}

void ProjectileManager::CreateProjectile(int x, int y, int damage, int width, int height)
{
	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		if (!_projectiles[i].isAppear) {
			_projectiles[i].imgKey = _strDamageBoundary;
			_projectiles[i].x = x;
			_projectiles[i].y = y;
			_projectiles[i].damage = damage;
			_projectiles[i].width = width;
			_projectiles[i].height = height;
			_projectiles[i].isStretch = false;
			_projectiles[i].isEnemyProjectTile = true;
			_projectiles[i].speed = 0;
			_projectiles[i].count = 0;
			_projectiles[i].angle = 0.0f;
			_projectiles[i].isBrassing = false;
			_projectiles[i].brassCount = 0;
			_projectiles[i].isPingPong = false;
			_projectiles[i].isAppear = true;
			_projectiles[i].isFollowing = false;

			_projectiles[i]._playerTargetRc = nullptr;
			break;
		}
	}
	

}



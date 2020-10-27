#include "stdafx.h"
#include "ProjectileManager.h"

void ProjectileManager::init()
{
	IMAGEMANAGER->addFrameImage("BowArrow", "Images/이미지/아이템/img_UI_bowArrow.bmp", 448, 56, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wratihMissile", "Images/이미지/NPC/wratihMissile.bmp", 990, 90, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("demonBrass", "Images/이미지/NPC/firebrass.bmp", 2560, 180, 8, 2, true, RGB(255, 0, 255));
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
	}
}

void ProjectileManager::update()
{
	for (int i = 0; i < PROJECTILE_MAX; i++) {
		if (_projectiles[i].isAppear) 
		{
			if (!_projectiles[i].isBrassing)
			{
				_projectiles[i].x += cosf(_projectiles[i].angle * PI / 180.0f) * _projectiles[i].speed;
				_projectiles[i].y -= sinf(_projectiles[i].angle * PI / 180.0f) * _projectiles[i].speed;
				if (_projectiles[i].isStretch)
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
			
			// 카메라 바깥으로 나가면 삭제
			RECT temp;
			if (!IntersectRect(&temp, &CAMERA->GetCameraRect(), &RectMakeCenter(_projectiles[i].x, _projectiles[i].y, 20, 20)))
				_projectiles[i].isAppear = false;
		}
	}
}

void ProjectileManager::render(HDC hdc)
{
	for (int i = 0; i < PROJECTILE_MAX; i++) 
	{
		
		if (_projectiles[i].isAppear) {
			//RectMakeCenter(_projectiles[i].x, _projectiles[i].y, 20, 20);
			if(!_projectiles[i].isStretch)
				IMAGEMANAGER->frameRender(_projectiles[i].imgKey, hdc, 
									 CAMERA->GetRelativeX(_projectiles[i].x), CAMERA->GetRelativeY(_projectiles[i].y), _projectiles[i].frameX, _projectiles[i].frameY, CAMERA->GetZoom());
			else
				IMAGEMANAGER->frameRender(_projectiles[i].imgKey, hdc,
									 CAMERA->GetRelativeX(_projectiles[i].x), CAMERA->GetRelativeY(_projectiles[i].y), _projectiles[i].frameX, _projectiles[i].frameY, CAMERA->GetZoom());
		}
	}
}

void ProjectileManager::CreateProjectile(string imgKey, int x, int y, int damage, float angle, float speed, int size, bool isEnemy, bool isStretch)
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

			_projectiles[i].isBrassing = false;
			_projectiles[i].brassCount = 0;
			_projectiles[i].isPingPong = false;

			//cout << angle << endl;
			if (isStretch == false)
			{
				float minAngle = -22.5f;
				float maxAngle = 22.5f;
				float addAngle = 45.0f;
				int count = 0;
				for (int x = 0; x < 8; x++)
				{
					if (minAngle + (count * addAngle) <= angle && angle <= maxAngle + (count * addAngle)) {
						_projectiles[i].frameX = x % 8;
						_projectiles[i].frameY = 0;
						break;
					}
					count++;
				}
			}
			else
			{
				_projectiles[i].frameX = 0;
				_projectiles[i].frameY = 0;
			}
			break;
		}
	}
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

			_projectiles[i].isBrassing = true;
			_projectiles[i].brassCount = 0;
			_projectiles[i].isPingPong = true;

			_projectiles[i].frameX = 0;
			_projectiles[i].frameY = isLeft ? 1 : 0;

			break;
		}
	}

}

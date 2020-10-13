#pragma once

#define PROJECTILE_MAX 10


struct tagProjectile {
		string imgKey;
		float x, y;
		float angle;
		float speed;
		int frameX;
		int frameY;
		int damage;
		bool isStretch;
		bool isEnemyProjectTile;
		bool isAppear;
};

class ProjectileManager{


	tagProjectile _projectiles[PROJECTILE_MAX];

public:
	void init();
	void update();
	void render(HDC hdc);
	void CreateProjectile(string imgKey, int x, int y, int damage = 10, float angle = 0.0f, float speed = 0.5f, bool isEnemy = false, bool isStretch = false);
	tagProjectile* GetProjectile() { return _projectiles; }
};


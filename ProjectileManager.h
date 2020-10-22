#pragma once

#define PROJECTILE_MAX 20


struct tagProjectile {
		string imgKey;
		float x, y;
		float angle;
		float speed;
		int width;
		int height;
		int frameX;
		int frameY;
		int damage;
		int count;
		int brassCount;
		bool isStretch;
		bool isEnemyProjectTile;
		bool isAppear;
		bool isBrassing;
		bool isPingPong;

};

class ProjectileManager{


	tagProjectile _projectiles[PROJECTILE_MAX];

public:
	
	void init();
	void update();
	void render(HDC hdc);
	void CreateProjectile(string imgKey, int x, int y, int damage = 10, float angle = 0.0f,
		float speed = 0.5f, int size = 20, bool isEnemy = false, bool isStretch = false);

	void CreateProjectile(string imgKey, int x, int y, int damage = 1, int width = 100, int height = 20, bool isLeft = false);
	tagProjectile* GetProjectile() { return _projectiles; }
};


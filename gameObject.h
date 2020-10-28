#pragma once
enum class LAYER
{
	TERRAIN,
	OBJECT
};
enum class TAG
{
	TERRAIN,
	ITEM,
	ENEMY,
	PLAYER,
	OBJECT,
	NPC,
	BUILDING,
	NONE,
};
class gameObject
{
public:
	float x, y;
	RECT rc;
	LAYER layer;
	TAG tag;	
	


public:
	int GetCenterX() { return rc.left + (rc.right - rc.left) / 2; };
	int GetCenterY() { return rc.top + (rc.bottom - rc.top) / 2; };
	void setCenterX(int _x) { x = _x; };
	void setCenterY(int _y) { y = _y; };
	POINT GetCenterPoint() { return { GetCenterX(), GetCenterY() }; };

	virtual void render(HDC hdc) = 0;
};


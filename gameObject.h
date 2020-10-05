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
	BUILDING
};
class gameObject
{
public:
	int x, y;
	RECT rc;
	LAYER layer;
	TAG tag;	


public:
	int GetCenterX() { return rc.left + (rc.right - rc.left) / 2; };
	int GetCenterY() { return rc.top + (rc.bottom - rc.top) / 2; };

};


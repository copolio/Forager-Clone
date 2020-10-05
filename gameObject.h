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
	int getX() { return x; };
	int getY() { return y; };
	RECT getRect() { return rc; };
};


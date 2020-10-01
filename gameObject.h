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
	RECT rc;
	LAYER layer;
	TAG tag;	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
public:
	LAYER getLayer() { return layer; };
	string getTag() { return tag; };
	RECT getRect() { return rc; };
};


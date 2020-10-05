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
protected:

	int x, y;
	int layer;
	string tag;
	RECT rc;
	LAYER layer;
	TAG tag;	
//public:
//	virtual HRESULT init();
//	virtual void release();
//	virtual void update();
//	virtual void render(HDC hdc);

public:
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render(HDC hdc) = 0;

public:
	int getX() { return x; };
	int getY() { return y; };
	int getLayer() { return layer; };
	string getTag() { return tag; };
	RECT getRect() { return rc; };
};


#pragma once
enum class LAYER
{
	WATER,
	LAND,
	SKY
};
class gameObject
{
protected:

	int x, y;
	int layer;
	string tag;
	RECT rc;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

public:
	int getX() { return x; };
	int getY() { return y; };
	int getLayer() { return layer; };
	string getTag() { return tag; };
	RECT getRect() { return rc; };
};


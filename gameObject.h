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
};


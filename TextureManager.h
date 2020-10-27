#pragma once
#include "singletonBase.h"
class TextureManager : public singletonBase<TextureManager>
{
private:
	struct tagRender {
		string imgKey;
		LAYER layer;
		RECT *rc;
		int* frameX;
		int* frameY;
		BYTE* alpha;
		bool isFrameImage;
		bool isAlaphImage;
	};

private:
	list<tagRender> _lRenderObject;

public:
	void render(HDC hdc);
	void release();
	void AddRender(string p_imgKey, RECT *rc, LAYER p_layer = LAYER::TERRAIN, int* p_frameX = nullptr, int* p_frameY = nullptr, BYTE* p_alpha = nullptr, bool isFrameImage = false);
	void CheckRemoveRenderObject();

private:
	void Sorting();
	bool Compare(tagRender* a, tagRender* b);
};


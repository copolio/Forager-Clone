#pragma once
#include "singletonBase.h"
#include <list>

#define MAX_EFFECT 20

class EffectManager : public singletonBase<EffectManager>
{
private:
	struct tagEffect {
		string imgKey;
		POINT ptPos;
		int interval;
		int count;
		int maxFrameX;
		int frameX;
		int currentAlpha;
		int toAlpha;
		float currentSize;
		float destSize;
		bool isFrameImage;
		bool isReset;
		bool isAppear;
		int width;
		int height;
	};

private:
	tagEffect* _effects[MAX_EFFECT];
	list<tagEffect*> _listEffect;
	list<tagEffect*>::iterator iter;

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);

	void ShowEffectFrame(string _imgKey, POINT ptPos);
	void ShowEffectFrame(string _imgKey, POINT ptPos, int frameInterval);
	void ShowEffectFrame(string _imgKey, POINT ptPos, int frameInterval, float size);
	// size example : 0.5f -> 1.0f
	void ShowEffectAlphaSize(string _imgKey, POINT ptPos, float fromSizeA, float toSizeB, int fromAlphaA, int toAlphaB);
	void ShowEffectAlphaSize(string _imgKey, POINT ptPos, float fromSizeA, float toSizeB, int fromAlphaA, int toAlphaB, int waitCount);

};


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
		bool isRelative;
	};

private:
	tagEffect* _effects[MAX_EFFECT];
	list<tagEffect*> _listEffect;
	list<tagEffect*>::iterator iter;

public:
	const string smokeEff = "DigSmoke";
	const string walkEff = "Walk1";

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);

	void ShowEffectFrame(string _imgKey, POINT ptPos, bool isRelative = false);
	void ShowEffectFrame(string _imgKey, POINT ptPos, int frameInterval, bool isRelative = false);
	void ShowEffectFrame(string _imgKey, POINT ptPos, int frameInterval, float size, bool isRelative = false);
	// size example : 0.5f -> 1.0f
	void ShowEffectAlphaSize(string _imgKey, POINT ptPos, float fromSizeA, float toSizeB, int fromAlphaA, int toAlphaB, bool isRelative = false);
	void ShowEffectAlphaSize(string _imgKey, POINT ptPos, float fromSizeA, float toSizeB, int fromAlphaA, int toAlphaB, int waitCount, bool isRelative = false);

};


#pragma once
//=============================================================
//	## progressBar ## (프로그래스바 = 체력바 = 로딩바 등등)
//=============================================================

class progressBar 
{
private:
	image* _progressBarFront;		//체력바 앞 이미지(렉트변경됨)
	image* _progressBarBack;		//체력바 뒤 이미지(변경안함)
	float _x, _y;					//체력바 위치좌표
	int _width;					//체력바 가로길이
	float _height;					//체력바 세로길이

public:
	void init(const char* frontImg, const char* backImg);
	void render(HDC hdc);

	//체력바 게이지 세팅하기
	void setGauge(float maxHp, float currentHp, int x, int y);

};


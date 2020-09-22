#pragma once
class reactImage
{

private:
	RECT _rc;
	string _imgKey1;
	string _imgKey2;

	int _currentSize;
	int _zoomSize;
	int _zoomSpeed;
	int _width;
	int _height;

	bool _isCursorOn;

	BYTE _alpha;

public:
	HRESULT init(RECT rc, int zoomSize, int zoomSpeed, string imgKey, string imgKey2 = "", BYTE alpha = 255);
	void update();
	void render(HDC hdc);

	void CursorIn();
	void CursorOut();



public:
	RECT GetRect() { return _rc; }
};


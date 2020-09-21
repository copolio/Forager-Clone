#include "stdafx.h"
#include "ForagerPlayer.h"

HRESULT ForagerPlayer::init()
{
	_rcForager = RectMakeCenter(100, 615, 30, 41);
	
	IMAGEMANAGER->addFrameImage("playerStop", "Images/이미지/플레이어/player_idle_frame.bmp", 120,112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRUN", "Images/이미지/플레이어/player_run_frame.bmp", 160, 112, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRotate", "Images/이미지/플레이어/player_rotate_frame.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRotateLeft", "Images/이미지/플레이어/player_rotate_frame_left.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));


	_foragerIdle = IMAGEMANAGER->findImage("playerStop");
	_foragerRun = IMAGEMANAGER->findImage("playerRUN");
	_foragerRotate = IMAGEMANAGER->findImage("playerRotate");

	for(int i = 1 ; i < 12; i++){
		image *left = IMAGEMANAGER->findImage("playerRotateLeft");
		image *right = IMAGEMANAGER->findImage("playerRotate");

		Rotate(left, left->getFrameWidth(), left->getFrameHeight(), i, true);
		Rotate(right, right->getFrameWidth(), right->getFrameHeight(), i, false);
	}

	//프레임이미지 애니메이션 관련 변수 초기화 
	_count = 0;
	_index = 0;

	//회전관련 변수 초기화 
	_Acount = 0;
	_spinCount = 0;
	_spinSpeed = 0;

	//플레이어 상태 불값 초기화 
	_isLeft = false;
	_isUp = false;
	_isMoveHorizon = false;
	_isMoveVertical = false;
	_isMoveRotate = false;
	_isRun = false;

	return S_OK;
}

void ForagerPlayer::release()
{

}

void ForagerPlayer::update()
{
	animation();
	PlayerControll();
	playerMove();
	playerLookingDirection();
	
}

void ForagerPlayer::render()
{
	switch (_state)
	{
	case IDLE:
		IMAGEMANAGER->frameRender("playerStop", getMemDC(), _rcForager.left, _rcForager.top);
		break;
	case RUN:
		IMAGEMANAGER->frameRender("playerRUN", getMemDC(), _rcForager.left, _rcForager.top);
		break;
	case ROTATE: 
		if (_isLeft) {
			IMAGEMANAGER->frameRender("playerRotateLeft", getMemDC(), _rcForager.left, _rcForager.top);
		}
		else {
			IMAGEMANAGER->frameRender("playerRotate", getMemDC(), _rcForager.left, _rcForager.top);
		}
		break;
	}
}

void ForagerPlayer::animation()
{
	switch (_state)
	{
	case IDLE:
		if (_isLeft)
		{
			_count++;
			_foragerIdle->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 3;
				}
				_foragerIdle->setFrameX(_index);
			}
		}
		else
		{
			_count++;
			_foragerIdle->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 3)
				{
					_index = 0;
				}
				_foragerIdle->setFrameX(_index);
			}
		}
		break;

	case RUN:
		if (_isLeft)
		{
			_count++;
			_foragerRun->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 3;
				}
				_foragerRun->setFrameX(_index);
			}
		}
		else
		{
			_count++;
			_foragerRun->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 3)
				{
					_index = 0;
				}
				_foragerRun->setFrameX(_index);
			}
		}
		break;

	case ROTATE:
		if (_isLeft)
		{
			_count++;
			
			if (_count % 1 == 0)
			{
				_index++;
				if (_index > 11)
				{
					_index = 0;
					_state = STATE::IDLE;
					_isMoveRotate = false;
				}
				IMAGEMANAGER->findImage("playerRotateLeft")->setFrameX(_index);
			}
		}
		else
		{
			_count++;
			_foragerRotate->setFrameY(0);
			if (_count % 1 == 0)
			{
				_index++;
				if (_index >11)
				{
					_index = 0;
					_state = STATE::IDLE;
					_isMoveRotate = false;
				}
				_foragerRotate->setFrameX(_index);
			}
		}
		break;
	}
}

void ForagerPlayer::PlayerControll()
{

	if (_state != STATE::ROTATE) {
		//가만히 있는 상태
		if (!INPUT->GetKey(VK_LEFT) || !INPUT->GetKey(VK_RIGHT))
		{
			_state = IDLE;
			_isMoveHorizon = false;
			_isMoveVertical = false;
		}
		//뛰어다니는 상태 (좌우 움직임)
		if (INPUT->GetKey(VK_LEFT) || INPUT->GetKey(VK_RIGHT))
		{
			_isMoveHorizon = true;
			_state = RUN;
			_isLeft = (INPUT->GetKey(VK_LEFT)) ? true : false;	//방향설정
		}
		//뛰어다니는 상태 (상하 움직임)
		if (INPUT->GetKey(VK_UP) || INPUT->GetKey(VK_DOWN))
		{
			_isMoveVertical = true;
			_state = RUN;
			_isUp = (INPUT->GetKey(VK_UP)) ? true : false;	//방향 설정
		}

		// 움직일 떄만 굴러갈 수 있게
		if (_state != STATE::IDLE)
		{
			//굴러다니는 상태 
			if (INPUT->GetKeyDown(VK_SPACE))
			{
				_state = ROTATE;
				_isMoveRotate = true;
				//_isLeft = (INPUT->GetKey(VK_LEFT)) ? true : false;
			}
		}
	}
}

void ForagerPlayer::playerMove()
{
	//플레이어 좌우 움직임 처리 
	if (_isMoveHorizon)
	{
		int applySpeed = (_isLeft) ? -3 : 3;

		//int applySpeed = (_isUp) ? -3 : 3;
		_spinSpeed = applySpeed * 2;
		
		if (_rcForager.left >= 0)
		{
			OffsetRect(&_rcForager, applySpeed, 0);
			//플레이어가 움직이다가, 스페이스바 누르면 회전하면서 가속
			if (_state == STATE::ROTATE)
			{
				OffsetRect(&_rcForager, _spinSpeed, 0);
			}
		}

		//플레이어가 화면 왼쪽으로 안나가게끔 처리 
		else
		{
			_rcForager.left = 0;
			_rcForager.right = 80;
		}
		//플레이어가 화면 오른쪽으로 안나가게끔 처리 
		if (_rcForager.right >= 1300)
		{
			_rcForager.right = 1300;
			_rcForager.left = 1260;
		}
	}

	//플레이어 상하 움직임 처리 
	if (_isMoveVertical)
	{
		int applySpeed = (_isUp) ? -3 : 3;

		_spinSpeed = applySpeed * 2;

		if (_rcForager.top >= 0)
		{
			OffsetRect(&_rcForager, 0, applySpeed);
			//플레이어가 움직이다가, 스페이스바 누르면 회전하면서 가속
			if (_state == STATE::ROTATE)
			{
				OffsetRect(&_rcForager, 0, _spinSpeed);
				_isMoveRotate = false;
			}
		}

		//플레이어가 화면 위쪽으로 안나가게끔 처리 
		else
		{
			_rcForager.top = 0;
			_rcForager.bottom = 40;
		}
		//플레이어가 화면 아래쪽으로 안나가게끔 처리
		if (_rcForager.bottom >= 640)
		{
			_rcForager.top = 600;
			_rcForager.bottom = 640;
		}
	}
}

//플레이어가 보는 시선이 마우스 위치에 따라 변경 
void ForagerPlayer::playerLookingDirection()
{
	int forgaerCenter = (_rcForager.left + _rcForager.right) / 2;


	if (_state != STATE::ROTATE) {
		if (forgaerCenter < _ptMouse.x)
			_isLeft = false;
		else
			_isLeft = true;
	}
}

void ForagerPlayer::RotateImage(image* img)
{
	if (_spinCount++ >= 12)
		_spinCount = 1;

	Rotate(img, img->getFrameWidth(), img->getFrameHeight(), _spinCount, _isLeft);
}

void ForagerPlayer::Rotate(image* img, int sizeX, int sizeY, int frameX, bool left)
{
	int x, y;
	int orig_x, orig_y;
	int pixel;

	double radian = 0;

	if (left)
		radian = (frameX * 30 * PI / 180.0);
	else
		radian = (frameX * -30 * PI / 180.0);

	double cc = cos(radian), ss = sin(-radian);
	double xcenter = (double)sizeX / 2.0, ycenter = (double)sizeY / 2.0; // (2)
	for (y = 0; y < sizeY; y++)
	{
		for (x = 0; x < sizeX; x++)
		{
			orig_x = (int)(xcenter + ((double)y - ycenter)*ss + ((double)x - xcenter)*cc);
			orig_y = (int)(ycenter + ((double)y - ycenter)*cc - ((double)x - xcenter)*ss);
			pixel = 0; // (3)

			if ((orig_y >= 0 && orig_y < sizeY) && (orig_x >= 0 && orig_x < sizeX)) // (4)
				SetPixel(img->getMemDC(), frameX * sizeX + x, y, GetPixel(img->getMemDC(), orig_x, orig_y));

		}
	}
}


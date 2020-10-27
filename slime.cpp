#include "stdafx.h"
#include "slime.h"

HRESULT slime::init()
{
	
	slimejumpRange = 100;
	return S_OK;
}

void slime::update()
{
	slimeJump();
	


}

void slime::render(HDC hdc)
{
	Rectangle(hdc, rc);
}

void slime::slimeAnimation()
{

}

void slime::slimeMove()
{

}

void slime::slimeJump()
{
	POINT originCenter = { GetCenterX(),GetCenterY() };
	POINT currentCenter = { GetCenterX(), GetCenterY() };
	POINT lastCenter = { _target->GetCenterX(), _target->GetCenterY() };

	



}

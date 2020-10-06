#include "stdafx.h"

void tile::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(terrKey, hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), terrainFrameX, terrainFrameY);
}

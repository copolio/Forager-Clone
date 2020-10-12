#include "stdafx.h"

void tile::render(HDC hdc)
{
	img->frameRender(hdc, CAMERA->GetRelativeX(rc.left), CAMERA->GetRelativeY(rc.top), terrainFrameX, terrainFrameY, CAMERA->GetZoom());
}

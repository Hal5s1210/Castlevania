#include "Tilemap.h"
#include "..\..\Framework\Viewport.h"

RECT Tilemap::GetAreaRect()
{
	RECT r;

	r.left = 0;
	r.top = 0;
	r.right = r.left + tileW * width;
	r.bottom = r.top + tileH * height;

	return r;
}


void Tilemap::Render(float sx, float sy)
{
	Viewport* view = Viewport::GetInstance();

	float cam_x, cam_y;
	view->GetPosition(cam_x, cam_y);
	int cam_w, cam_h;
	view->GetSize(cam_w, cam_h);

	int X = max(cam_x / tileW, 0);
	int Y = max(cam_y / tileH, 0);
	int XW = min(ceil((cam_x + cam_w) / tileW), width);
	int YH = min(ceil((cam_y + cam_h) / tileH), height);


	for (int i = Y; i < YH; i++)
	{
		for (int j = X; j < XW; j++)
		{
			int id = matrix->at(i)[j];
			tileset->Draw(id - 1, j * tileW + sx, i * tileH + sy);
		}
	}
}

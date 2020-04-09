#include "Tilemap.h"
#include "..\..\Framework\Viewport.h"

void Tilemap::Render(float sx, float sy)
{
	Viewport* view = Viewport::GetInstance();

	float cam_x, cam_y;
	view->GetPosition(cam_x, cam_y);
	int cam_w, cam_h;
	view->GetSize(cam_w, cam_h);

	int X = max(cam_x / tileW, 0);
	int Y = max(cam_y / tileH, 0);
	int XW = min((cam_x + cam_w) / tileW + 1, width);
	int YH = min((cam_y + cam_h) / tileH + 1, height);


	for (int i = Y; i < YH; i++)
	{
		for (int j = X; j < XW; j++)
		{
			int id = matrix[i][j];
			tileset->Draw(id - 1, j * tileW + sx, i * tileH + sy);
		}
	}
}

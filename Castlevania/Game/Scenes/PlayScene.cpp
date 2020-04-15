#include "PlayScene.h"


void PlayScene::Load()
{
	Scene::Load();
	board = Board::GetInstance();
	board->LoadTexture();
}

void PlayScene::Unload()
{
	Scene::Unload();
}

void PlayScene::Update(DWORD dt)
{
	grid->GetObjectlist(&objects);

	for (int i = 0; i < items.size(); i++)
	{
		if (!items[i]->IsClaimed())
		{
			items[i]->Update(dt, &objects);
			if (items[i]->IsTimeOut())
			{
				delete items[i];
				items.erase(items.begin() + i);
				--i;
				continue;
			}
		}
		else
		{
			delete items[i];
			items.erase(items.begin() + i);
			--i;
			continue;
		}

		objects.push_back(items[i]);
	}

	player->Update(dt, &objects);

	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->IsDone())
		{
			delete effects[i];
			effects.erase(effects.begin() + i);
			--i;
		}
	}

	AdjustView();

	board->Update(dt);
}

void PlayScene::Render()
{
	tilemap->Render(x, y);
	board->Render();

	for (LPGAMEOBJECT obj : objects)
	{
		obj->Render(x, y);
	}

	for (LPITEM i : items)
	{
		i->Render(x, y);
	}

	player->Render(x, y);

	for (LPEFFECT e: effects)
	{
		e->Render(x, y);
	}
}

void PlayScene::AdjustView()
{
	float player_x, player_y;

	player->GetPosition(player_x, player_y);
	Viewport::GetInstance()->SetPosition(player_x - 112, player_y - 80);

	float cam_x, cam_y;
	int cam_w, cam_h;

	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	Viewport::GetInstance()->GetSize(cam_w, cam_h);

	RECT area = tilemap->GetAreaRect();

	//if (cam_x < area.left) cam_x = area.left;
	//if (cam_x > area.right - cam_w) cam_x = area.right - 32;

	Viewport::GetInstance()->SetPosition(cam_x, 0);
}




void PlaySceneKeyHandler::KeyState(BYTE* state)
{
	Input* input = Input::GetInstance();

	Simon* player = scene->GetPlayer();

	if (player)
	{
		if (input->IsKeyDown(PAD_DOWN))
		{
			player->SetState(Simon::Crounch);
		}
		else if (input->IsKeyDown(PAD_LEFT))
		{
			player->SetState(Simon::WalkL);
		}
		else if (input->IsKeyDown(PAD_RIGHT))
		{
			player->SetState(Simon::WalkR);
		}
		else
		{
			player->SetState(Simon::Idle);
		}
	}

}

void  PlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	NSDebug::DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Simon* player = scene->GetPlayer();

	if (player)
	{
		switch (KeyCode)
		{
		case BUTTON_A:
			if (Input::GetInstance()->IsKeyDown(PAD_UP))
			{
				player->SetState(Simon::SubAttack);
			}
			else
			{
				player->SetState(Simon::Attack);
			}
			break;

		case BUTTON_B:
			player->SetState(Simon::Jump);
			break;

		}
	}

}

void  PlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
	NSDebug::DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
#include "PlayScene.h"
#include "..\Objects\Weapons\Stopwatch.h"


void PlayScene::Load()
{
	Scene::Load();
	board = Board::GetInstance();
	board->LoadTexture();
	AdjustView();
}

void PlayScene::Unload()
{
	Scene::Unload();
}

void PlayScene::Update(DWORD dt)
{
	Viewport* view = Viewport::GetInstance();

	grid->GetObjectlist(&objects);

	objects.push_back(player);

	if (player->IsHitDoor())
	{
		player->Update(dt, &objects);
		for (LPGAMEOBJECT o : objects)
		{
			if (dynamic_cast<Simon*>(o)) continue;
			o->Update(dt);
		}
		view->Update(dt);
		board->Update(dt);

		if (view->IsSwitchView())
		{
			if (view->IsReachAutoDest())
			{
				player->GainControl();
				view->SetSwitchView(false);
			}
		}

		return;
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(dt, &objects);

		if (!enemies[i]->IsInCell() && (enemies[i]->IsOutView() || !enemies[i]->IsAlive()))
		{
			enemies[i]->Unactive();
			enemies.erase(enemies.begin() + i);
			--i;
		}
		else
		{
			enemies[i]->InCell(false);
			if (enemies[i]->IsAlive() && !enemies[i]->IsOutView())
				objects.push_back(enemies[i]);
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt, &objects);

		if (bullets[i]->IsHitSomething() || bullets[i]->IsOutOfView())
		{
			if (dynamic_cast<Simon*>(bullets[i]->GetShooter()))
				player->GetSubWeapon()->Count(-1);

			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
		}
		else objects.push_back(bullets[i]);
	}

	player->Update(dt, &objects);

	for (LPGAMEOBJECT o : objects)
	{
		if (dynamic_cast<Simon*>(o) ||
			dynamic_cast<Enemy*>(o) ||
			dynamic_cast<Bullet*>(o))
			continue;
		o->Update(dt);
	}

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

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Update(dt);
		if (effects[i]->IsOutOfView() || (effects[i]->IsOneTimeEffect() && effects[i]->IsDone()))
		{
			delete effects[i];
			effects.erase(effects.begin() + i);
			--i;
			continue;
		}
		objects.push_back(effects[i]);
	}

	AdjustView();

	board->Update(dt);

	view->Update(dt);
}

void PlayScene::Render()
{
	Effect::RenderBackgroundEffect();

	tilemap->Render(x, y);
	board->Render();

	for (LPGAMEOBJECT obj : objects)
	{
		obj->Render(x, y);
	}

	board->RenderGameover();
}

void PlayScene::Reset()
{
	Scene::Reset();
	AdjustView();
}

void PlayScene::AdjustView()
{
	if (Viewport::GetInstance()->IsAuto()) return;

	float player_x, player_y;

	player->GetPosition(player_x, player_y);
	Viewport::GetInstance()->SetPosition(player_x - 120, player_y - 64);

	float cam_x, cam_y;
	int cam_w, cam_h;

	Viewport::GetInstance()->GetPosition(cam_x, cam_y);
	Viewport::GetInstance()->GetSize(cam_w, cam_h);

	RECT area = tilemap->GetAreaRect();

	if (cam_x < area.left) cam_x = area.left;
	if (cam_x > area.right - cam_w) cam_x = area.right - cam_w;
	cam_y = area.top;

	Viewport::GetInstance()->SetPosition(cam_x, cam_y);
}




void PlaySceneKeyHandler::KeyState(BYTE* state)
{
	Input* input = Input::GetInstance();

	Simon* player = scene->GetPlayer();

	if (player)
	{
		if (player->IsInputEnable())
		{
			if (input->IsKeyDown(PAD_DOWN))
			{
				player->SetState(Simon::StairDown);
				player->SetState(Simon::Crouch);
			}
			else if (input->IsKeyDown(PAD_UP))
			{
				player->SetState(Simon::StairUp);
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
		else
		{
			player->SetState(Simon::Idle);
		}
	}

}

void  PlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	Simon* player = scene->GetPlayer();

	if (player)
	{
		if (player->IsInputEnable())
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

	if (Board::GetInstance()->IsGameOver())
	{
		switch (KeyCode)
		{
		case BUTTON_START:
			Board::GetInstance()->ConfirmSelection();
			break;

		case BUTTON_SELECT:
			Board::GetInstance()->ChangeSelection();
			break;

		default:
			break;
		}
	}

	switch (KeyCode)
	{
	case DIK_F1:
		Scenes::GetInstance()->NextScene(SCENE1_ID);
		break;

	case DIK_F2:
		Scenes::GetInstance()->NextScene(SCENE2_ID);
		break;

	case DIK_F3:
		Scenes::GetInstance()->NextScene(SCENE3_ID);
		break;

	case DIK_F4:
		Scenes::GetInstance()->NextScene(SCENE4_ID);
		break;

	case DIK_F5:
		Debug::EnableDebugging();
		break;

	default:
		break;
	}

}

void  PlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
}
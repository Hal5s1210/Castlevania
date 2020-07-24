#include "IntroScene.h"

void IntroScene::Load()
{
	Scene::Load();
	board = Board::GetInstance();
	board->LoadTexture();
	Viewport::GetInstance()->SetPosition(0, 0);
	scenestart = 0; 
	board->Update(0);
}

void IntroScene::Unload()
{
	Scene::Unload();
}

void IntroScene::Update(DWORD dt)
{
	grid->GetObjectlist(&objects);

	if (scenestart == 0)
	{
		scenestart = GetTickCount();
		for (LPGAMEOBJECT o : objects)
		{
			SimpleObject* s = dynamic_cast<SimpleObject*>(o);
		}
	}

	for (LPGAMEOBJECT o : objects)
	{
		o->Update(dt);
		SimpleObject* s = dynamic_cast<SimpleObject*>(o);
		if (s->GetName() == "Simon")
		{
			float simon_x, simon_y;
			s->GetPosition(simon_x, simon_y);
			if (simon_x < 120)
			{
				s->SetPosition(120, simon_y);
				s->SetSpeed(0, 0);
				s->SetAnimation(1);
			}
		}
	}

	if (scenestart != 0 && GetTickCount() - scenestart >= scenetime)
	{
		Scenes::GetInstance()->NextScene(SCENE1_ID);
	}
}

void IntroScene::Render()
{
	for (LPGAMEOBJECT o : objects)
	{
		o->Render(x, y);
	}

	board->Render();
}
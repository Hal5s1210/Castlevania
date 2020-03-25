#pragma once

#define DIO_TEX_ID -10
#define DIO_TEX_DIR L"Resources\\Textures\\Dio.png"
#define DIO_ANIMATION 0

#include "Scene.h"

class Dio : public GameObject
{
public:
	Dio()
	{
		LPTEXTURE texture = Textures::GetInstance()->Get(DIO_TEX_ID);

		LPANIMATION s = new Animation(texture);
		s->AddFrame(0, 0, 256, 240);
		AddAnimation(s);

		SetAnimation(DIO_ANIMATION);
	}
	~Dio()
	{
		animations.clear();
	}
	void Update(DWORD dt) {};
	void Render()
	{
		animations[currentAnimation]->Draw(x, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

class KonoDioDa : public Scene
{
	Dio* dio;

public:
	void LoadScene()
	{
		Textures::GetInstance()->Add(DIO_TEX_ID, DIO_TEX_DIR, D3DCOLOR_XRGB(116, 116, 116));

		dio = new Dio;
		dio->SetPosition(0, 0);

		OutputDebugString(L"[INFO] Dio loaded OK\n");
		sceneStart = true;
	}
	void EndScene()
	{
		delete dio;

		Textures* textures = Textures::GetInstance();
		textures->Remove(DIO_TEX_ID);

		OutputDebugString(L"[INFO] Dio ended OK\n");
	}
	void Update(DWORD dt) {}
	void Render()
	{
		dio->Render();
	}
	void ButtonDown(int keyCode) {}
	void ButtonUp(int keyCode) {}
};


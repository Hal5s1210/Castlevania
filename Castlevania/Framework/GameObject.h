#pragma once

#include <vector>
#include "Sprite.h"

class GameObject;
typedef GameObject* LPGAMEOBJECT;

struct CoEvent;
typedef CoEvent* LPCOEVENT;



struct CoEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	CoEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOEVENT& a, LPCOEVENT& b)
	{
		return a->t < b->t;
	}
};



class GameObject
{
protected:
	float x, y;
	float vx, vy;
	float dx, dy;

	DWORD dt;

	bool flip;

	std::vector<LPANIMATION> animations;
	int currentAnimation;


	LPCOEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(std::vector<LPGAMEOBJECT>* coObjects, std::vector<LPCOEVENT>& coEvents);
	void FilterCollision(
		std::vector<LPCOEVENT>& coEvents,
		std::vector<LPCOEVENT>& coEventsResult,
		float& min_tx, float& min_ty,
		float& nx, float& ny);

public:
	GameObject();
	~GameObject();

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }

	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	void AddAnimation(LPANIMATION animation) { animations.push_back(animation); }
	void SetAnimation(int animation) { currentAnimation = animation; animations[currentAnimation]->Reset(); }
	void PauseAnimation() { animations[currentAnimation]->Pause(); }
	void PlayAnimtion() { animations[currentAnimation]->Play(); }

	virtual void Update(DWORD dt);
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;

};



class Generator
{
public:
	virtual LPGAMEOBJECT ObjectCreate(int id) = 0;
	virtual LPGAMEOBJECT MapCreate(int id) = 0;
	virtual LPGAMEOBJECT EnemyCreate(int id) = 0;
};


class Platform :public GameObject
{
public:
	Platform()
	{
		LPTEXTURE texture = Textures::GetInstance()->Get(-100);

		LPANIMATION s = new Animation(texture);
		s->AddFrame(0, 0, 16, 16);
		AddAnimation(s);

		SetAnimation(0);
	}

	~Platform()
	{
		animations.clear();
	}

	void Render() 
	{
		animations[currentAnimation]->Draw(x, y);
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x;
		t = y;
		r = l + 16;
		b = t + 16;
	}
};
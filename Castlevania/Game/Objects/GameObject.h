#pragma once

#include <unordered_map>
#include "..\..\Framework\Sprite.h"

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

	std::unordered_map<const char*, LPANIMATION> animations;
	LPANIMATION currentAnimation;


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

	void AddAnimation(const char* id, LPANIMATION animation) { animations[id] = animation; }
	void SetAnimation(const char* id) { currentAnimation = animations[id]; }
	void PauseAnimation() { currentAnimation->Pause(); }
	void PlayAnimtion() { currentAnimation->Play(); }

	virtual void Update(DWORD dt);
	virtual void Render(float x = 0, float y = 0) = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;

};
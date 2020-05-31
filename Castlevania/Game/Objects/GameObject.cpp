#include "GameObject.h"
#include <algorithm>
#include <locale>
#include <codecvt>
#include "..\..\Framework\Collision.h"
#include "..\..\Dependencies\pugixml\src\pugixml.hpp"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	dx = dy = 0;
	dt = 0;
	flip = false;
}

GameObject::~GameObject()
{
}

void GameObject::AddAnimation(LPANIMATION animation)
{
	ANIMATION* ani = new ANIMATION;
	ani->first = animation;
	ani->second = -1;
	animations.push_back(ani);
}


void GameObject::Update(DWORD dt)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

LPCOEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	Collision::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CoEvent* e = new CoEvent(t, nx, ny, coO);
	return e;
}

void GameObject::CalcPotentialCollisions(std::vector<LPGAMEOBJECT>* coObjects, std::vector<LPCOEVENT>& coEvents)
{
	if (coObjects == NULL) return;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i) == this) continue;

		LPCOEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CoEvent::compare);
}

void GameObject::FilterCollision(
	std::vector<LPCOEVENT>& coEvents,
	std::vector<LPCOEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0;
	ny = 0;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


void GameObject::CheckSweptCollision(std::vector<LPGAMEOBJECT>* coObjects)
{
	if (coObjects == NULL) return;

	std::vector<LPCOEVENT> coEvents;

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.empty())
	{
		x += dx;
		y += dy;
	}
	else
	{
		std::vector<LPCOEVENT> coEventResults;
		float min_tx, min_ty, nx, ny;

		FilterCollision(coEvents, coEventResults, min_tx, min_ty, nx, ny);

		float ddx, ddy;

		ddx = dx;
		ddy = dy;

		ProcessCollision(&coEventResults, min_tx, min_ty, nx, ny, ddx, ddy);

		x += ddx;
		y += ddy;
	}
}

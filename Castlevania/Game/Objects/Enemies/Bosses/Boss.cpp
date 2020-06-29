#include "Boss.h"
#include "..\..\Effect.h"
#include "..\..\..\Board.h"

void Boss::TakeDamage(int damage, LPGAMEOBJECT hitter)
{
	if (IsHit()) return;

	invulnerableTimeStart = GetTickCount();
	hit = true;

	Effect::AddHitEffect(hitter, this);
	Board::GetInstance()->BossHit(damage);
	hp = Board::GetInstance()->GetBossHp();


	if (hp <= 0)
	{
		hp = 0;
		alive = false;

		LPSPRITE sprite = currentAnimation->first->GetFrame(currentAnimation->second);
		RECT r = sprite->GetRect();

		Effect::AddBossDeathEffect(r, x, y);

		Board::GetInstance()->AddScore(score);
	}
}
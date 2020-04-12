#pragma once
class Collision
{
public:
	static bool AABB(
		float l1, float t1, float r1, float b1,
		float l2, float t2, float r2, float b2);

	static void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny);
};


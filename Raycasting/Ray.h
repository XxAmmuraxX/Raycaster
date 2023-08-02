#pragma once
#include "Wall.h"
#include "raymath.h"
#include<vector>

typedef Vector2 Vec2;

struct HitInfo
{
	Vec2 pos;
	Color color;
	float hit_ratio = 0;
	Texture2D texture;
	HitInfo(Vector2 pos, Color color, float hit_ratio, Texture2D texture) : pos(pos), color(color),hit_ratio(hit_ratio), texture(texture){}
};

class Ray2D
{
	Vec2 pos;
	float angle;
	std::vector<HitInfo> hits;
	HitInfo closest_hit{ { INT_MAX / 1.f,INT_MAX / 1.f }, BLACK,0,Texture2D()};
	Vector2 dir;
	friend class RayScene;
public:
	Ray2D(Vec2 pos, float angle);
	HitInfo GetHitStats() { return closest_hit; }
	float GetDistance();
	void ClearHits();
	inline float GetAngle() { return angle; }
	void UpdateDir(float& reference_angle);
	inline void SetPos(Vector2& pos) { this->pos = pos; }
	bool FindClosestHit();
	bool Cast(Wall& wall);
	void Draw();

};


Vector2 operator+(Vector2 a, Vector2 b);

Vector2 operator-(Vector2 a, Vector2 b);

Vector2 operator*(float a, Vector2 b);

Vector2 operator*(Vector2 b, float a);

Vector2 operator/(Vector2 a, float b);

Vector2 operator+=(Vector2& a, Vector2 b);

Vector2 operator-=(Vector2& a, Vector2 b);

Vector2 operator*=(Vector2& b, float a);

Vector2 operator/=(Vector2& a, float b);

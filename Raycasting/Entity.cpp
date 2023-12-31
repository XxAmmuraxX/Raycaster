#include "Entity.h"

Entity::Entity(float FOV, int ray_count) :
	pos({ 400,400 }), FOV(FOV), ray_count(ray_count)
{
	for (float a = -FOV / 2; a <= FOV / 2; a += FOV / ray_count)
	{
		rays.push_back(Ray2D(pos, a));
	}
}

void Entity::Update(std::vector<Wall>& walls)
{

	Move(100);

	//ChangeRayCount(); crashes the app

	for (auto& ray : rays)
	{
		ray.ClearHits();
		ray.SetPos(pos);
		ray.UpdateDir(orientation.x);
		for (auto& wall : walls)
		{
			ray.Cast(wall);
		}
		ray.FindClosestHit();
	}
}

void Entity::WallCollision(std::vector<Wall>& walls)
{
	for (auto& wall : walls)
	{

	}
}

void Entity::Draw()
{
	DrawCircle(pos.x, pos.y, 15, GRAY);

	for (auto& ray : rays)
	{
		ray.Draw();
	}

	//DrawText(TextFormat("%.2lf", orientation.y), 100, 100, 40, RED);
	const char* ray_count = TextFormat("Emitted Ray count: %d", rays.size());
	DrawText(ray_count, 10, 100, 20, DARKBLUE.transparent(140));
}

void Entity::PointToMouse()
{
	Vector2 vec = GetMousePosition() - pos;
	orientation.x = RAD2DEG*atan2(vec.y, vec.x);
}

void Entity::ChangeRayCount()
{
	bool is_change = false;
	if (IsKeyDown(KEY_RIGHT))
	{
		if (FOV < 120)
			FOV += GetFrameTime() * 10;
		is_change = true;
	}
	if (IsKeyDown(KEY_LEFT))
	{
		if (FOV > 45)
			FOV -= GetFrameTime() * 10;
		is_change = true;
	}
	if (IsKeyDown(KEY_UP))
	{
		if (ray_count < 1000)
			ray_count += GetFrameTime() * 100;
		is_change = true;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		if (ray_count > 5)
			ray_count -= GetFrameTime() * 100;
		is_change = true;
	}

	if (is_change)
	{
		rays.clear();

		for (float a = -FOV / 2; a <= FOV / 2; a += int(FOV / ray_count))
		{
			rays.push_back(Ray2D(pos, a));
		}
	}
}

void Entity::Move(float speed)
{
	if (IsKeyDown(KEY_A))
	{
		pos += Vector2{cosf(orientation.x * DEG2RAD - PI / 2), sinf(orientation.x * DEG2RAD - PI / 2) } *speed* GetFrameTime();
		//orientation.x -= GetFrameTime() * 150;
	}

	if (IsKeyDown(KEY_D))
	{
		pos += Vector2{cosf(orientation.x * DEG2RAD + PI/2), sinf(orientation.x * DEG2RAD + PI/2) } *speed* GetFrameTime();
		//orientation.x += GetFrameTime() * 150;
	}

	if (IsKeyDown(KEY_W))
	{
		pos += Vector2{cosf(orientation.x*DEG2RAD),sinf(orientation.x*DEG2RAD) } * speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_S))
	{
		pos -= Vector2{cosf(orientation.x* DEG2RAD), sinf(orientation.x* DEG2RAD) } *speed* GetFrameTime();
	}

	//look up and down
	Vector2 look_dir = Vector2Normalize(GetMouseDelta()) * Vector2Length(GetMouseDelta()) / 10;
	orientation.y -= look_dir.y  * GetFrameTime() * 100;
	if (orientation.y > 90) orientation.y = 90;
	if (orientation.y < -90) orientation.y = -90;
	orientation.x += look_dir.x  * GetFrameTime() * 100;
	if (orientation.x > 360) orientation.x = 0;
	if (orientation.x < 0) orientation.x = 360;
	SetMousePosition(GetScreenWidth() / 2.f, GetScreenHeight() / 2.f);
}

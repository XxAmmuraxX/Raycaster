#pragma once
#include"Ray.h"

class Entity
{
	Vector2 pos;
	float z_pos = 0;
	Vector2 orientation = { 0,0 };
	std::vector<Ray2D> rays; 
	float FOV;
	float ray_count;
	friend class Scene3D;
public:
	float GetRadAngle() { return orientation.x * DEG2RAD; }
	Entity(float FOV, int ray_count);
	void Update(std::vector<Wall>& walls);
	void WallCollision(std::vector<Wall>& walls);
	void Draw();
	void PointToMouse();
	void ChangeRayCount();
	void Move(float speed);
};
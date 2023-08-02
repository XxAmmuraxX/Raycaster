#pragma once
#include "Entity.h"

class Scene
{
public:
	Scene(Vector2 pos, float width, float height);
	virtual void Draw() = 0;
protected:
	Vector2 pos;
	float width, height;
};
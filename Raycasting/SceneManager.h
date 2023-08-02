#pragma once
#include "Scene3D.h"
#include "RayScene.h"

class SceneManager
{
public:
	void Run();
	void Update();
	void Render();
	SceneManager(float width, float height, int fps);
private:
	RayScene* ray_scene;
	Scene3D* scene_3d;
};
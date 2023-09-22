#include "SceneManager.h"

void SceneManager::Run()
{
	while (!WindowShouldClose())
	{
		Update();
		Render();
	}
}

void SceneManager::Update()
{
	ray_scene->Update();
	scene_3d->Update(ray_scene->entity);
}

void SceneManager::Render()
{
	BeginDrawing();

	ClearBackground(LIGHTGRAY);

	ray_scene->Draw();
	scene_3d->Draw(ray_scene->entity);
	DrawFPS(10, 10);

	EndDrawing();
}

SceneManager::SceneManager(float width, float height, int fps)
{
	InitWindow(width, height, "Raycaster");
	SetTargetFPS(fps);
	//ToggleFullscreen();
	ray_scene = new RayScene({ { 0, 0 }, GetScreenWidth() / 2.f, GetScreenHeight() / 1.f });
	scene_3d = new Scene3D({ GetScreenWidth()/2.f,0}, GetScreenWidth() / 1.f, GetScreenHeight() / 1.f, ray_scene->entity);
	HideCursor();
	//******* SCENES *******//
	//scenes.push_back(RayScene({ GetScreenWidth() / 2.f,0 }, GetScreenWidth() / 2.f, GetScreenHeight()));
}

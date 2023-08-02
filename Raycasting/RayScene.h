#pragma once
#include "Scene.h"
#include<iostream>

class RayScene : public Scene
{
public:
	RayScene(Vector2 pos, float width, float height);
	void Update();
	void Draw();
private:
	friend class Scene3D;
	friend class SceneManager;
	void GenRandMap(float density,float spaciness);
	void ResetMap();
	void GenBoxes(Color color);
	void GenBoxes(Texture2D& texture);
	void AddTexture();
	std::vector<Wall> walls;
	Entity entity{ 90,1000 };
	static const size_t x_tiles = 10, y_tiles = 10;
	Texture2D wooden_box_texture = LoadTexture("wooden_box.png");
	Texture2D white_wall_texture = LoadTexture("white_wall.png");
	int map[x_tiles * y_tiles] ={1,1,1,1,1,0,0,0,1,1,
								 1,0,0,0,0,0,1,0,0,1,
								 1,0,1,1,1,0,1,1,1,1,
								 1,0,0,0,1,0,0,0,0,0,
								 1,0,1,1,1,1,1,0,1,0,
								 0,0,0,1,0,0,0,0,1,0,
								 0,1,0,1,0,1,1,0,1,0,
								 0,1,0,1,1,1,0,0,0,0,
								 0,0,0,0,0,0,0,1,1,0,
								 1,1,0,1,1,1,0,0,0,0};
};
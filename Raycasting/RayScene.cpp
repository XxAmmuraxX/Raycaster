#include "RayScene.h"
#include<random>
#include <string>

RayScene::RayScene(Vector2 pos, float width, float height) :
	Scene(pos,width,height)
{
	//walls.push_back(Wall({ 100,100 }, { 200,200 }));
	walls.push_back(Wall({ 0,0 }, { width,0 },GRAY));
	walls.push_back(Wall({ 0,height }, { width,height }, GRAY));
	walls.push_back(Wall({ 0,0 }, { 0,height }, GRAY));
	walls.push_back(Wall({ width,0 }, { width,height }, GRAY));
	//walls.push_back(Wall({ 100,300 }, { 300,100 }));
	//walls.push_back(Wall({ 200,300 }, { 400,300 }));
	GenRandMap(0.5,0.5);
	GenBoxes(wooden_box_texture);
	//AddTexture();
	//GenRandWalls(1);
}

void RayScene::Update()
{
	entity.Update(walls);
}

void RayScene::Draw()
{
	DrawRectangleLines(pos.x, pos.y, width, height, BLACK);

	for (auto& wall : walls)
		wall.Draw();

	entity.Draw();
}

void RayScene::GenRandMap(float density,float spaciness)
{
	float spawn_chance = density * 100;
	float touch_chance = spaciness * 100;
	ResetMap();
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			if (GetRandomValue(0, 100) < spawn_chance)
			{
				if (GetRandomValue(0, 100) < touch_chance)
				{
					map[y * x_tiles + x] = 1;
				}
				else
				{
					float neighbor = false;
					int max_x = 2, max_y = 2;
					int i = -1, j = -1;
					if (x == 0) j++;
					if (y == 0) i++;
					if (x == x_tiles - 1) max_x--;
					if (y == y_tiles - 1) max_y--;
					for (i; i < max_y; i++)
					{
						for (j; j < max_x; j++)
						{
							if (map[(y + i) * x_tiles + x + j] == 1)
							{
								neighbor = true;
							}
						}
					}
					if (!neighbor)
					{
						map[y * x_tiles + x] = 1;
					}
				}
			}
		}
	}
}

void RayScene::ResetMap()
{
	for (auto& block : map)
	{
		block = 0;
	}
}

void RayScene::GenBoxes(Color color)
{
	Vector2 size = { width / x_tiles,height / y_tiles };
	for (int j = 0; j < y_tiles; j++)
	{
		for (int i = 0; i < x_tiles; i++)
		{
			if (map[j*x_tiles + i] == 1)
			{
				Box box(i, j, size,color);
				box.Push(walls);
			}
		}
	}
}

void RayScene::GenBoxes(Texture2D& texture)
{
	Vector2 size = { width / x_tiles,height / y_tiles };
	for (int j = 0; j < y_tiles; j++)
	{
		for (int i = 0; i < x_tiles; i++)
		{
			if (map[j * x_tiles + i] == 1)
			{
				Box box(i, j, size, texture);
				box.Push(walls);
			}
		}
	}
}

void RayScene::AddTexture()
{
	for (auto& wall : walls)
	{
		wall.texture = wooden_box_texture;
	}
}

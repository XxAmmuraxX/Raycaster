#pragma once
#include<vector>
#include "raylib.h"

struct Wall
{ 
	Vector2 pos1;
	Vector2 pos2;
	Color color;
	Texture2D texture;
	Wall(Vector2 pos1, Vector2 pos2, Color color) : pos1(pos1), pos2(pos2), color(color) {}
	Wall(Vector2 pos1, Vector2 pos2, Color color, Texture2D& t2d) : pos1(pos1), pos2(pos2), color(color), texture(t2d) {}
	void Draw();
};

struct Box
{
	Wall *left, *right, *top, *bottom;
	Vector2 size;
	int index;
	Color color;
	Box(int i,int j, Vector2 size,Color color);
	Box(int i,int j, Vector2 size,Texture& texture);
	void Push(std::vector<Wall>& walls);
	void Draw();
};
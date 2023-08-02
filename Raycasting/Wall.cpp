#include "Wall.h"

void Wall::Draw()
{
	DrawLineEx(pos1, pos2, 2, color);
}

Box::Box(int i, int j, Vector2 size, Color color) : color(color)
{
	Vector2 pos = { i * size.x, j * size.y };
	Vector2 p1 = { pos.x, pos.y };
	Vector2 p2 = { pos.x + size.x, pos.y };
	Vector2 p3 = { pos.x, pos.y + size.y };
	Vector2 p4 = { pos.x + size.x, pos.y + size.y};
	top = new Wall(p1, p2, color);
	left = new Wall(p1, p3, color);
	right = new Wall(p2, p4, color);
	bottom = new Wall(p3, p4, color);
}

Box::Box(int i, int j, Vector2 size, Texture& texture)
{
	Vector2 pos = { i * size.x, j * size.y };
	Vector2 p1 = { pos.x, pos.y };
	Vector2 p2 = { pos.x + size.x, pos.y };
	Vector2 p3 = { pos.x, pos.y + size.y };
	Vector2 p4 = { pos.x + size.x, pos.y + size.y };
	top = new Wall(p1, p2, WHITE, texture);
	left = new Wall(p1, p3, WHITE, texture);
	right = new Wall(p2, p4, WHITE, texture);
	bottom = new Wall(p3, p4, WHITE, texture);
}

void Box::Push(std::vector<Wall>& walls)
{
	walls.push_back(*top);
	walls.push_back(*left);
	walls.push_back(*right);
	walls.push_back(*bottom);
}

void Box::Draw()
{
	top->Draw();
	left->Draw();
	right->Draw();
	bottom->Draw();
}

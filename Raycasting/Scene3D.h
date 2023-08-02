#pragma once
#include "Scene.h"

struct strip {
	Vector2 pos;
	float width, height, brightness;
	void Update(float height, float brightness) { this->height = height; this->brightness = brightness; }
	//void Draw() {DrawRectangle() }
};

class Scene3D : public Scene
{
	std::vector<float> brightness;
	std::vector<float> rec_height;
	std::vector<Color> rec_color;
	std::vector<float> ratios;
	std::vector<Texture2D> textures;
	float rec_width;
	bool is_fullscreen = false;
public:
	Scene3D(Vector2 pos, float width, float height,Entity& entity);
	void ToggleFullsceen();
	void Update(Entity& entity);
	void Draw() { ; }
	void Draw(Entity& entity);
};
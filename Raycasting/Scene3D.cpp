#include "Scene3D.h"
#include<cmath>
#include<algorithm>

float BrightnessFromDistance(float distance,float max_distance)
{
	float brightness = std::exp(-distance / max_distance);

	return std::max(0.0f, std::min(1.0f, brightness));
}

float HeightFromDistance(float distance, float max_distance, float angle, Entity& entity)
{
	float height;
	if (IsKeyDown(KEY_SPACE))
		height = max_distance / distance;
	else
		height = max_distance / distance / cosf(angle * DEG2RAD);
	return height;
	return std::max(0.0f, std::min(1.0f, height));
}

Scene3D::Scene3D(Vector2 pos, float width, float height, Entity& entity) :
	Scene(pos,width,height)
{
	rec_width = width / entity.rays.size();
}

void Scene3D::ToggleFullsceen()
{
	if (IsKeyPressed(KEY_F11))
	{
		if (is_fullscreen)
		{
			width = GetScreenWidth();
			pos.x = 0;
			is_fullscreen = false;
		}
		else
		{
			width = GetScreenWidth() / 2.f;
			pos.x = GetScreenWidth() / 2.f;
			is_fullscreen = true;
		}
	}
}

void Scene3D::Update(Entity& entity)
{
	Scene3D::ToggleFullsceen();

	brightness.clear();
	rec_height.clear();
	rec_color.clear();
	ratios.clear();
	textures.clear();

	for (auto& ray : entity.rays)
	{
		brightness.push_back(BrightnessFromDistance(ray.GetDistance(), 400));
		rec_height.push_back(HeightFromDistance(ray.GetDistance(), 100000,ray.GetAngle(),entity));
		rec_color.push_back(ray.GetHitStats().color);
		ratios.push_back(ray.GetHitStats().hit_ratio);
		textures.push_back(ray.GetHitStats().texture);
	}
}

void Scene3D::Draw(Entity& entity)
{
	float y_offset = height * sinf(entity.orientation.y * DEG2RAD);
	DrawRectangle(pos.x, pos.y + y_offset + height/2 - height * 2, width, height * 2, SKYBLUE);
	DrawRectangleGradientV(pos.x, pos.y + y_offset + height/2, width, height / 2, BLACK, DARKGREEN);
	DrawRectangle(pos.x,pos.y + height + y_offset, width, height * 1.5f, DARKGREEN);
	for (int i = 0; i < brightness.size(); i++)
	{
		Vector2 rec_pos = { pos.x + i * rec_width, pos.y + height / 2 - (rec_height[i]) / 2 };
		rec_pos += {0, y_offset + entity.z_pos * rec_height[i]};

		float texture_x_dest = textures[i].width * ratios[i];
		if(IsTextureReady(textures[i]))
			DrawTexturePro(textures[i], { texture_x_dest,0,rec_width + 1,textures[i].height / 1.f }, { rec_pos.x,rec_pos.y, rec_width + 1, rec_height[i] }, { 0,0 }, 0, ColorBrightness(WHITE, -1.0f + brightness[i]));
		else
			DrawRectangleGradientV(rec_pos.x,rec_pos.y, rec_width+1, rec_height[i],ColorTint(rec_color[i],WHITE), ColorBrightness(rec_color[i], -1.0f + brightness[i]));
		//DrawRectangleGradientV(rec_pos.x,rec_pos.y, rec_width+1, rec_height[i], ColorBrightness(WHITE, -1.0f + brightness[i]).transparent(200),BLACK.transparent(200));
	}
}

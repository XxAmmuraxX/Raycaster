#include "Ray.h"
#include<iostream>

Ray2D::Ray2D(Vec2 pos, float angle) :
	pos(pos),
    angle(angle)
{

}

float Ray2D::GetDistance()
{
    if (closest_hit.pos.x < INT_MAX && closest_hit.pos.y < INT_MAX)
        return Vector2Distance(pos, closest_hit.pos);
    else
        return INT_MAX;
}

void Ray2D::Draw()
{
    if (hits.size())
        DrawLine(pos.x, pos.y, closest_hit.pos.x, closest_hit.pos.y, closest_hit.color);
}

bool Ray2D::FindClosestHit()
{
    if (hits.size())
    {
        HitInfo Closest = { Vector2{INT_MAX/1.f,INT_MAX/1.f},BLACK,0,Texture2D()};
        for (auto& hit : hits)
        {
            if (Vector2Distance(hit.pos, pos) < Vector2Distance(Closest.pos, pos))
            {
                Closest = hit;
            }
        }
        closest_hit = Closest;
        return true;
    }
    closest_hit.pos = { INT_MAX/1.f,INT_MAX/1.f };
    return false;
}

void Ray2D::ClearHits()
{
    hits.clear();
}

void Ray2D::UpdateDir(float& reference_angle)
{
    float new_angle = (reference_angle + angle) * DEG2RAD;
    dir = { cosf(new_angle),sinf(new_angle) };
}

bool Ray2D::Cast(Wall& wall)
{
    float x1 = wall.pos1.x;
    float y1 = wall.pos1.y;
    float x2 = wall.pos2.x;
    float y2 = wall.pos2.y;
    
    float x3 = this->pos.x;
    float y3 = this->pos.y;
    float x4 = this->pos.x + this->dir.x;
    float y4 = this->pos.y + this->dir.y;

    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (denominator == 0)
    {
        return false;
    }

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;

    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

    if (t > 0 && t < 1 && u > 0)
    {
        Vector2 intersection = { x1 + t * (x2 - x1), y1 + t * (y2 - y1) };
        float hit_ratio = Vector2Distance(wall.pos1, intersection) / Vector2Distance(wall.pos1, wall.pos2);
        hits.push_back(HitInfo(intersection,wall.color,hit_ratio,wall.texture));
        return true;
    }

    return false;
}

Vector2 operator+(Vector2 a, Vector2 b)
{
    return Vector2Add(a, b);
}

Vector2 operator-(Vector2 a, Vector2 b)
{
    return Vector2Subtract(a, b);
}

Vector2 operator*(float a, Vector2 b)
{
    return Vector2Scale(b, a);
}

Vector2 operator*(Vector2 b, float a)
{
    return Vector2Scale(b, a);
}

Vector2 operator/(Vector2 a, float b)
{
    return Vector2Scale(a, 1 / b);
}

Vector2 operator+=(Vector2& a, Vector2 b)
{
    return a = Vector2Add(a, b);
}

Vector2 operator-=(Vector2& a, Vector2 b)
{
    return a = Vector2Subtract(a, b);
}

Vector2 operator*=(Vector2& b, float a)
{
    return b = Vector2Scale(b, a);
}

Vector2 operator/=(Vector2& a, float b)
{
    return a = Vector2Scale(a, 1 / b);
}
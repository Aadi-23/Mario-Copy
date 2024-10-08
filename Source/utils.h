//Adarsh Kumar

#pragma once
#include "raylib.h"
#include "Level.h"

bool AABBVsAABB(const Vector2 pos1, const Vector2 pos2, const Vector2 size1, const Vector2 size2);

bool SweptRayvsAABB(const Vector2 rayorigin, const Vector2 rayvector, const Vector2 rec_pos, const Vector2 rec_size,Collision* collision);

bool SweptAABBvsAABB(const Vector2 pos1, const Vector2 size1, const Vector2 vel1, const Vector2 pos2,const Vector2 size2, Collision* collision);
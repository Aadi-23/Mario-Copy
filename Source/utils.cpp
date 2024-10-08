//Adarsh Kumar

#include "utils.h"
#include <cmath>
#include "myMath.h"


bool AABBVsAABB(const Vector2 pos1, const Vector2 pos2, const Vector2 size1, const Vector2 size2)
{
	bool CollisionX = pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x;

	bool CollisionY = pos1.y + size1.y >= pos2.y && pos2.y + size2.y >= pos1.y;

	return CollisionX && CollisionY;
}


bool SweptRayvsAABB(const Vector2 rayorigin, const Vector2 rayvector, const Vector2 rec_pos, const Vector2 rec_size, Collision* collision)
{
	Vector2 t_near = (rec_pos - rayorigin) / rayvector;   // Gives the near point on rectangle
	Vector2 t_far = (rec_pos + rec_size - rayorigin) / rayvector;  // Gives the far point on rectangle

	

	if (t_near.x > t_far.x)
	{
		std::swap(t_near.x, t_far.x);
	}
	if (t_near.y > t_far.y)
	{
		std::swap(t_near.y, t_far.y);
	}


	if (t_near.x > t_far.y || t_near.y > t_far.x)
	{
		return false;
	}

	 

	if (t_near.x > t_near.y)
	{
		if (rayvector.x < 0)
		{
			collision->contact_normal = { 1,0 };
		}
		else
		{
			collision->contact_normal = {-1, 0 };
		}
	}
	else if (t_near.x < t_near.y)
	{
		if (rayvector.y < 0)
		{
			collision->contact_normal = { 0,1 };
		}
		else
		{
			collision->contact_normal = { 0,-1 };
		}
	}

    collision->collision_t = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0)
	{
		return false;
	}

	if (collision->collision_t > 1.0f)
	{
		return false;
	}

	
	

	return true;

}

bool SweptAABBvsAABB(const Vector2 pos1, const Vector2 size1, const Vector2 vel1, const Vector2 pos2, const Vector2 size2, Collision* collision)
{
	// Increasing size of static box

	Vector2 Expandedrec_pos = pos2 - (size1 / 2);
	Vector2 Expandedrec_size = size2 + size1;


	if (SweptRayvsAABB(pos1 + (size1/2), vel1, Expandedrec_pos, Expandedrec_size, &(*collision)))
	{
		if (collision->collision_t < 1.0f && collision->collision_t >= 0)
		{
			return true;
		}
	}

	return false;
}
//Adarsh Kumar, Aayush Sarcar

#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Level.h"
#include "utils.h"
#include "ResourceManager.h"
#include "myMath.h"


Enemy::Enemy(const Vector2 pos)
{
	position = pos;
	size = ENEMYSIZE;
	velocity = { -1,0 };
	type = Entity_Type::Mushroom;
	color = BLUE;
	dead = false;
};

void Enemy::add_entity(Level* level)
{
	level->tempenemies.push_back(*this);
}

void Enemy::render()
{
	DrawTexture(ResourceManager::textures.Mushroom,(int) position.x, (int)position.y, WHITE);
}

void Enemy::update(Level* level)
{
	for (Entity* e_wall : level->all_entities)
	{
		if (e_wall->type == Entity_Type::Wall)
		{
			Vector2 temp_displacment = velocity * ENEMYMOVEMENTSPEED * GetFrameTime();
			Collision temp_collision;

			// Collision with the wall So the enemy goes back in reverse.
			if (SweptAABBvsAABB(position, size, temp_displacment, e_wall->position, e_wall->size, &temp_collision))
			{
				velocity.x *= -1;
			}

		}

	}

	// Movement Update
	position.x += velocity.x * (ENEMYMOVEMENTSPEED * GetFrameTime());
	

}


Wall::Wall(const Vector2 pos)
{
	position = pos;
	size = WALLSIZE;
	color = BROWN;
	dead = false;
	type = Entity_Type::Wall;
	velocity = { 0,0 };
}


void Wall::add_entity(Level* level)
{
	level->tempwalls.push_back(*this);
}

void Wall::update(Level* level)
{
	level;
}

void Wall::render()
{
	DrawTexture(ResourceManager::textures.Wall, (int)position.x, (int)position.y, WHITE);
}


Ground::Ground(const Vector2 pos)
{
	position = pos;
	size = { GROUNDWIDTH, GROUNDHEIGHT };
	type = Entity_Type::Ground;
	color = GRAY;
	velocity = { 0,0 };
	dead = false;
}

void Ground::add_entity(Level* level)
{
	level->tempground.push_back(*this);
};

void Ground::update(Level* level)
{
	level;
}

void Ground::render()
{
	DrawTexture(ResourceManager::textures.Ground, (int)position.x, (int)position.y, WHITE);
}

Coin::Coin(const Vector2 coin_pos)
{
	position = coin_pos;
	size = COIN_SIZE;
	type = Entity_Type::Coin;
	color = YELLOW;
	velocity = { 0,0 };
	dead = false;
}
void Coin::add_entity(Level*level)
{
	level->tempcoins.push_back(*this);
}

void Coin::update(Level*level)
{
	level;
}

void Coin::render()
{
	DrawRectangleV(position, size, color);
}

VictoryFlag::VictoryFlag()
{
	pos = {0,0};
	size = FLAG_SIZE;
	color = RED;
}


void Parallax::ParallaxHandling()
{
	float BGwidth = (float)ResourceManager::textures.Background.width;
	float FGwidth = (float)ResourceManager::textures.Foreground.width;


	if (PlayerController::player.canMove == true) 
	{
		if (PlayerController::player.velocity.x < 0)
		{
			BGScrollSpeed += 0.5f;
			FGScrollSpeed += 1.0f;
		}

		if (PlayerController::player.velocity.x > 0)
		{
			BGScrollSpeed -= 0.5f;
			FGScrollSpeed -= 1.0f;
		}
		
	}
	 
	//For Wrapping
	DrawTextureEx(ResourceManager::textures.Background, { BGScrollSpeed, 0 }, 0.0f, 1.0f, WHITE);
	DrawTextureEx(ResourceManager::textures.Background, { BGwidth + BGScrollSpeed, 0 }, 0.0f, 1.0f, WHITE);

	DrawTextureEx(ResourceManager::textures.Foreground, { FGScrollSpeed , 0 }, 0.0f, 1.0f, WHITE);
	DrawTextureEx(ResourceManager::textures.Foreground, { FGwidth + FGScrollSpeed, 0 }, 0.0f, 1.0f, WHITE);

	if (BGScrollSpeed <= -BGwidth) 
	{
		BGScrollSpeed += BGwidth;
	}
	if (BGScrollSpeed >= 0)
	{
		BGScrollSpeed -= BGwidth;
	}

	if (FGScrollSpeed <= -FGwidth)
	{
		FGScrollSpeed += FGwidth;
	}
	if (FGScrollSpeed >= 0) 
	{
		FGScrollSpeed -= FGwidth;
	}
}

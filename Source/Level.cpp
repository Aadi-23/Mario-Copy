//Adarsh Kumar, Aayush Sarcar

#pragma once
#include "raylib.h"
#include "myMath.h"
#include "Level.h"
#include "utils.h"
#include "ResourceManager.h"
#include "raymath.h"
#include "HighscoreManager.h"



Vector2 Level::PositionTransformationInGrid( const float x, const float y)
{
	Vector2 transformed_position;

	transformed_position.x = x * GRIDCELLSIZE.x;
	transformed_position.y = y * GRIDCELLSIZE.y;

	return transformed_position;
}

void Level::CameraSpawn()
{
	player_camera.zoom = 1.5f;
	player_camera.offset = {  PlayerController::player.position.x + 30, (float)GetRenderHeight() / 2 + PlayerController::player.position.y };
	player_camera.target = PlayerController::player.position;

	uiCamera.zoom = 1.0f;
	uiCamera.target = { 0, 0 };
	uiCamera.offset = { 0, 0 };
	uiCamera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

}

void Level::CameraPosUpdate(const Player& player)
{
		player_camera.target.x = player.position.x;
	if (player.position.x > (float) GetRenderWidth() / 4)
	{
	}
}



void Level::EnemySpawner(const Vector2 pos)
{
	Enemy enemy{ pos };

	enemy.add_entity(this);

}


void Level::SpawnGround(const Vector2 pos)
{
	Ground t_ground{ pos };

	t_ground.add_entity(this);
}

void Level::SpawnWall(const Vector2 pos)
{
	Wall wall{ pos };


	wall.add_entity(this);
}

void Level::SpawnCoin(const Vector2 coin_pos)
{
	Coin coin{ coin_pos };

	coin.add_entity(this);
}

void Level::Reset()
{
	score = 0;

	gameOver = false;

	walls.clear();
	enemies.clear();
	ground.clear();
	coins.clear();
	all_entities.clear();
}

void Level::LevelRender()
{
	BeginMode2D(player_camera);
	playercontroller.playerRender();
	
	for (Entity* e : all_entities)
	{
		e->render();
	}

	const Vector2 flagPos{flag.pos.x, flag.pos.y + 10};

	DrawTextureV(ResourceManager::textures.Flag,flagPos,WHITE);

	EndMode2D();


	BeginMode2D(uiCamera);
	
	for (int i = 0; i < playercontroller.player.health; i++)
	{
		Vector2 heartPos = { (float)400 + i * (ResourceManager::textures.Health.width + 10), (float)350 };

		DrawTextureEx(ResourceManager::textures.Health, heartPos, 0.0f, 0.6f, WHITE);
	}

	char scoreText[20];
	sprintf_s(scoreText, "Score: %d", score);
	DrawText(scoreText, 10, 350, 50, BLACK);

	EndMode2D();
}

void Level::EntitiesCollision()
{

	Vector2 player_displacement = PlayerController::player.velocity * GetFrameTime();


	for (int i = 0; i < 5; i++)
	{
		Entity* closest_entity = nullptr;
		Collision closest_collision = { 1,{0,0} };

		for (Entity* e : all_entities)
		{
			Collision temp_collision = { 1,{0,0} };

			if (SweptAABBvsAABB(PlayerController::player.position, PlayerController::player.size, player_displacement, e->position, e->size, &temp_collision))
			{
				if (temp_collision.collision_t < closest_collision.collision_t)
				{
					closest_collision = temp_collision;
					closest_entity = &(*e);
				}
			}
		}

		float t_epsilon = 0.001f;
		PlayerController::player.position += player_displacement * (closest_collision.collision_t - t_epsilon);
		player_displacement = player_displacement * (1 - closest_collision.collision_t);
		player_displacement -= closest_collision.contact_normal * Vector2DotProduct(player_displacement, closest_collision.contact_normal);

		if (closest_entity != nullptr)
		{
			PlayerController::player.velocity -= closest_collision.contact_normal * Vector2DotProduct(PlayerController::player.velocity, closest_collision.contact_normal);
			playercontroller.canJump = true;

			if (closest_collision.contact_normal.y < 0)
			{
				playercontroller.onGround = true;
			}
			
			if (closest_entity->type == Entity_Type::Wall)
			{
				PlayerController::player.canMove = false;
			}
			else
			{
				PlayerController::player.canMove = true;
			}

			if (closest_entity->type == Entity_Type::Coin)
			{
				score += COIN_VALUE;
				closest_entity->dead = true;
			}

			//Vertical Collision
			if (closest_entity->type == Entity_Type::Mushroom && closest_collision.contact_normal.y < 0)
			{
				SpawnCoin(closest_entity->position);
				EnemySpawner(RandomEnemyPositionGenerator());
				closest_entity->dead = true;
				score += 100;
			}

			//Horizontal collision
			for (Entity* e : all_entities)
			{
				if (e->type == Entity_Type::Mushroom)
				{
					float playerHalfWidth = PlayerController::player.size.x / 2; //useful for calculating the center of the player character.
					float playerHalfHeight = PlayerController::player.size.y / 2; //useful for calculating the center of the player character.

					Vector2 playerCenter = { PlayerController::player.position.x + playerHalfWidth, PlayerController::player.position.y + playerHalfHeight };

					Vector2 mushroomCenter = { e->position.x + e->size.x / 2, e->position.y + e->size.y / 2 }; 

					float minDistanceX = playerHalfWidth + e->size.x / 2;  //minimum distance needed for a collision to occur
					float minDistanceY = playerHalfHeight + e->size.y / 2;

					float distanceX = fabs(playerCenter.x - mushroomCenter.x); // Calculate the horizontal distance between the center of the player and the center of the mushroom.
					float distanceY = fabs(playerCenter.y - mushroomCenter.y); // Calculate the vertical distance between the center of the player and the center of the mushroom.

					if (distanceX <= minDistanceX && distanceY <= minDistanceY) // If both conditions are met, it means the player character and the mushroom are colliding within their bounding boxes.
					{
						if (!playercontroller.player.isHurt)
						{
							playercontroller.player.health--;
							playercontroller.player.isHurt = true;
							playercontroller.player.hurtStartTime = GetTime();
						}
						if (playercontroller.player.health <= 0)
						{
							playercontroller.player.dead = true;
							gameOver = true;
							
						}
						else if (playercontroller.player.isHurt && (GetTime() - playercontroller.player.hurtStartTime) >= 1.0)
						{
							playercontroller.player.isHurt = false;
						}
					}
				}
			}

			
		}
		
	
	}

}


Vector2 Level::RandomEnemyPositionGenerator()
{
	Vector2 Spawn_pos;

	Spawn_pos.x = (float) GetRandomValue((int)PlayerController::player.position.x,(int)FINISH_POINT.x);

	for (const Entity* e : all_entities)
	{
		if(e->type == Entity_Type::Wall)
		{
			if (e->position.x == Spawn_pos.x)
			{
				Spawn_pos.x = (float) GetRandomValue((int)PlayerController::player.position.x, (int)FINISH_POINT.x);
			}
		}

		if (e->type == Entity_Type::Mushroom)
		{
			Spawn_pos.y = e->position.y;
		}
		
	}

	return Spawn_pos;
}



void Level::refreshEntities()
{
	auto last_entity = std::remove_if(all_entities.begin(), all_entities.end(), [](const Entity* e)->bool {return e->dead; });

	all_entities.erase(last_entity, all_entities.end());

	enemies.remove_if([](const Enemy& e)->bool {return e.dead; });
	walls.remove_if([](const Wall& e)->bool {return e.dead; });
	ground.remove_if([](const Ground& e)->bool {return e.dead; });
	coins.remove_if([](const Coin& e)->bool {return e.dead; });

	while (tempenemies.size() != 0)
	{
		enemies.push_back(tempenemies.back());
		all_entities.push_back(&enemies.back());
		tempenemies.pop_back();
	}

	while (tempwalls.size() != 0)
	{
		walls.push_back(tempwalls.back());
		all_entities.push_back(&walls.back());
		tempwalls.pop_back();
	}
	while (tempground.size() != 0)
	{
		ground.push_back(tempground.back());
		all_entities.push_back(&ground.back());
		tempground.pop_back();
	}
	while (tempcoins.size() != 0)
	{
		coins.push_back(tempcoins.back());
		all_entities.push_back(&coins.back());
		tempcoins.pop_back();
	}
}


void Level::Animation_Assigner()
{
	for (AnimationData& data : ResourceManager::aniamtionsdata)
	{
		switch (data.AnimationID[0])
		{
		case('P'):
		{
			if (data.AnimationID[1] == 'R')
			{
				playercontroller.player_run_animation.Frames = data.frames;
				playercontroller.player_run_animation.sprite_sheet = &ResourceManager::textures.player_run_sheet;
				playercontroller.player_run_animation.animation_loop = { data.animation_bool == 0 ? true : false };
			}
			else if (data.AnimationID[1] == 'J')
			{
				playercontroller.player_jump_animation.Frames = data.frames;
				playercontroller.player_jump_animation.sprite_sheet = &ResourceManager::textures.player_jump_sheet;
				playercontroller.player_jump_animation.animation_loop = { data.animation_bool == 0 ? true : false };
			}

		}
		break;
		default:
			break;
		}
	}
}

void Level::Update()
{
	refreshEntities();
	
	for (Entity* e : all_entities)
	{
		e->update(this);
	}

	if (CheckCollisionPointRec(flag.pos,{playercontroller.player.position.x, playercontroller.player.position.y, playercontroller.player.size.x,playercontroller.player.size.y }))
	{
		WaitTime(1.5);
		score += 50;
		gameWon = true;
	}

	if (playercontroller.player.position.y >= GetScreenHeight() + 5)
	{
		playercontroller.player.health = 0;
		gameOver = true;
	}


	CameraPosUpdate(PlayerController::player);
	playercontroller.playerUpdate();
	EntitiesCollision();
	PL.ParallaxHandling();
}
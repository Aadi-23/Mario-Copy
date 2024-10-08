//Adarsh Kumar

#pragma once
#include "raylib.h"
#include <vector>
#include <list>
#include "Entity.h"
#include "PlayerController.h"


struct Collision
{
	float collision_t = 1.0f;
	Vector2 contact_normal = { 0,0 };
};

class Level
{
	Camera2D player_camera = { 0 };
	Camera2D uiCamera = { 0 };

	std::list<Enemy>enemies;
	std::list<Wall>walls;
	std::list<Ground> ground;
	std::list<Coin>coins;


public:
	std::vector<Entity*> all_entities{};
	
	

	// Temporary vectors
	std::vector<Enemy>tempenemies;
	std::vector<Wall>tempwalls;
	std::vector<Ground> tempground;
	std::vector<Coin> tempcoins;

	PlayerController playercontroller;
	Parallax PL;

	Vector2 FINISH_POINT = { 0,0 };
	VictoryFlag flag;

	int score = 0;
	bool gameOver = false;
	bool gameWon = false;

	void CameraSpawn();
	void CameraPosUpdate(const Player &player);

	Vector2 PositionTransformationInGrid(const float x, const float y);

	Vector2 RandomEnemyPositionGenerator();// Generates the random position for enemy in game
	
	void EnemySpawner(const Vector2 pos);
	void SpawnGround(const Vector2 pos);
	void SpawnWall(const Vector2 pos);
	void SpawnCoin(const Vector2 coin_pos);

	void EntitiesCollision();

	// Assigns the animation data to respectable entity
	void Animation_Assigner();
	
	void refreshEntities();

	void Reset();
	void Update();
	void LevelRender();
	
};

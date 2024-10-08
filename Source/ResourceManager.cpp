//Adarsh Kumar, Aayush Sarcar

#pragma once
#include "raylib.h"
#include "ResourceManager.h"
#include <string>
#include <fstream>

Textures ResourceManager::textures;
std::vector<AnimationData> ResourceManager::aniamtionsdata;

constexpr const char* LevelTextFile = "./Assets/level.txt";

void ResourceManager::LoadResources()
{
	textures.Background = LoadTexture("./Assets/background.png");
	textures.Foreground = LoadTexture("./Assets/foreground.png");
	textures.player_texture = LoadTexture("./Assets/Character.png");
	textures.Mushroom = LoadTexture("./Assets/Mushroom.png");
	textures.Ground = LoadTexture("./Assets/Ground.png");
	textures.Wall = LoadTexture("./Assets/Wall.png");

	textures.Health = LoadTexture("./Assets/health.png");

	textures.Flag = LoadTexture("./Assets/flag.png");
	


	// Animations 
	for (AnimationData& data : aniamtionsdata)
	{
		// Here i load texture accroding to the path i get from txt. It is easier to add multiple animation this way. As i am using two char as ID of animations.
		switch(data.AnimationID[0])
		{
		case('P'):
		{
			if (data.AnimationID[1] == 'R')
			{
				textures.player_run_sheet = LoadTexture(data.animation_path.c_str());

			}
			else if (data.AnimationID[1] == 'J')
			{
				textures.player_jump_sheet = LoadTexture(data.animation_path.c_str());
			}
			
		}
		break;
		default:
			break;
		}
	}
}




void ResourceManager::LoadEntityFromTxt()
{
	std::string leveltxt = LoadFileText(LevelTextFile);

	float x_pos = 0;
	float y_pos = 0;

	for (char& c : leveltxt)
	{
		
		switch (c)
		{
		case('0'):
		{
			x_pos++;
		}
		break;

		case('e'):
		{
			GameManager::level.EnemySpawner( GameManager::level.PositionTransformationInGrid(x_pos, y_pos));
			x_pos++;
		}
		break;
		case('g'):
		{
			GameManager::level.SpawnGround( GameManager::level.PositionTransformationInGrid(x_pos, y_pos) );
			x_pos++;
		}
		break;
		case('w'):
		{
			GameManager::level.SpawnWall(GameManager::level.PositionTransformationInGrid(x_pos, y_pos));
			x_pos++;
		}
		break;

		case('f'):
		{
			GameManager::level.flag.pos = (GameManager::level.PositionTransformationInGrid(x_pos, y_pos));
		}
		break;
		case('\n'):
		{
			y_pos++;
			x_pos = 0;
		}
		break;
		default:
		{
			x_pos++;
		}
		break;
		}


	}
}

void ResourceManager::AnimationFileReader()
{
	std::ifstream Animation_file("./Assets/Animation.txt");

	std::string temp_string;
	AnimationData temp_animation_data = {};

	// Reading the animation data from file 
	if (Animation_file.is_open())
	{
		while (Animation_file>>temp_animation_data.AnimationID)
		{
			Animation_file >>temp_animation_data.animation_path>> temp_animation_data.frames >> temp_animation_data.animation_bool;

			aniamtionsdata.push_back(temp_animation_data);
		}
	}
}




void ResourceManager::UnloadResources()
{
	UnloadTexture(textures.Background);
	UnloadTexture(textures.Foreground);
	UnloadTexture(textures.player_texture);
	UnloadTexture(textures.Mushroom);
	UnloadTexture(textures.Ground);
	UnloadTexture(textures.Wall);
	UnloadTexture(textures.Health);

	UnloadTexture(textures.Flag);

	UnloadTexture(textures.player_run_sheet);
	UnloadTexture(textures.player_jump_sheet);
}
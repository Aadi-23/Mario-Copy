//Aayush Sarcar, Adarsh Kumar

#pragma once
#include "raylib.h"
#include "GameManager.h"

struct Textures
{
	Texture2D Background;
	Texture2D Foreground;
	
	Texture2D Mushroom;
	Texture2D Ground;
	Texture2D Wall;
	Texture2D CharDMG;
	Texture2D Health;
	Texture2D CharSpeak;
	Texture2D CharSweat;
	Texture2D Flag;


	// Animation
	Texture2D player_texture;
	Texture2D player_run_sheet;
	Texture2D player_jump_sheet;
};

struct ResourceManager
{
	static Textures textures;
	
    static std::vector<AnimationData>aniamtionsdata;

	static void AnimationFileReader();

	 

	static void LoadEntityFromTxt();
	static void LoadResources();
	static void UnloadResources();
};


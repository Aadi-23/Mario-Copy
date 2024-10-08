//Adarsh Kumar

#pragma once
#include "raylib.h"
#include<string>

 
// Note: This code i took from my personal project (Adarsh Kumar). I did wrote all the things by myself but i am reusing it here in my pair game because it is good prototype code for animation
// Same for the animation.cpp

enum AnimationState
{
	IDLE, WALK, JUMP,
};

struct AnimationData
{
	std::string AnimationID;
	std::string animation_path;
	int frames = 0;
	int animation_bool = 0;
};

struct Animation
{
	Texture2D* sprite_sheet = {};
	int Frames = 0;
	// I made this bool So I can pass to animation player if i want the animation to loop or not. This loop exist in animation as i load this data from file.
	bool animation_loop = false;
	
};

class AnimationPlayer
{
private:
	const Animation* current_animation = {};
	int frame_counter = 0;
	float framerate = 0;

	
	

public:
	AnimationState animation_state = IDLE;

	int current_frame = 0;
	Rectangle animation_rec{};       // This is source rectangle from sprite sheet helps rendering texture

	void StartAmination(const Animation* anim);
	void animation_update();
	void animation_render(const Vector2 & anim_pos);
};

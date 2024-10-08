//Aayush Sarcar, Adarsh Kumar

#pragma once
#include "raylib.h"

constexpr Vector2 GRIDCELLSIZE = { 40,40 };

// Player
constexpr int PLAYERSPEED = 300;
constexpr int PLAYERXPOS = 120;
constexpr int PLAYERYPOS = 200;
constexpr float FRICTION = 0.8f;
constexpr Vector2 PLAYERSIZE = { 50.0f, 50.0f }; 
constexpr int JUMPMAXHEIGHT = 250;

// Ground
constexpr Vector2 GRAVITY = { 0,500};

constexpr int GROUNDWIDTH = 40;  
constexpr int GROUNDHEIGHT = 40;   

// Enemy
constexpr Vector2 ENEMYSIZE = { 40,40 };
constexpr float ENEMYMOVEMENTSPEED = 150.0f;

// Wall
constexpr Vector2 WALLSIZE = { 40,40 };

//Coin
constexpr Vector2 COIN_SIZE = { 20, 20 };
constexpr int COIN_VALUE = 100;

//Flag
constexpr Vector2 FLAG_SIZE = {30, 30};



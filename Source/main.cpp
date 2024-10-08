//Aayush Sarcar, Adarsh Kumar

#pragma once
#include "raylib.h"
#include "GameManager.h"
#include "ResourceManager.h"




int main(void)
{   
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);              

    ResourceManager::AnimationFileReader();
    ResourceManager::LoadResources();
    GameManager manager;

    manager.level.playercontroller.PlayerSpawner(PlayerController::player);
    manager.level.CameraSpawn();
    manager.GS = GameStates::MAIN_MENU;

    manager.level.Animation_Assigner();
 
    ResourceManager::LoadEntityFromTxt();
    
   
    while (!WindowShouldClose())   
    {
        manager.RunGame();
    }

    ResourceManager::UnloadResources();
    
    CloseWindow();       

    return 0;
}
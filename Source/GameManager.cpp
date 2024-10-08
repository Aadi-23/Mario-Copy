//Aayush Sarcar

#pragma once
#include "raylib.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include <vector>
#include <iostream>


Level GameManager::level;

GameManager::GameManager() : GS(GameStates::MAIN_MENU)
{
    level = Level(); 
    playerController = PlayerController(); 
    HS = HighScore(); 
}

/*Took help from ChatGPT to reorganize the code; initially I was doing the logic in the switch cases themselves, but then GPT advised to 
make different functions and put them in the switch cases to make it more organized*/

void GameManager::RunGame()
{
    
    switch (GS)
    {
    case GameStates::MAIN_MENU:
        UpdateMainMenu();
        break;
    case GameStates::NAME_SCREEN:
        UpdateNameScreen();
        break;
    case GameStates::GAME:
        UpdateGame();
        break;
    case GameStates::PAUSE:
        UpdatePause();
        break;
    case GameStates::GAME_OVER:
        UpdateGameOver();
        break;
    case GameStates::WIN_SCREEN:
        UpdateWinScreen();
        break;
    case GameStates::HIGH_SCORE:
        UpdateHighScore();
        break;
    default:
        break;
    }
}

void GameManager::UpdateMainMenu()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawText("START = ENTER\nEXIT GAME = ESCAPE", 300, 400, 50, WHITE);
    
    EndDrawing();

    if (IsKeyPressed(KEY_ENTER))
    {
        GS = GameStates::NAME_SCREEN;
    }
}

void GameManager::UpdateNameScreen()
{
    HS.AssignPlayerName(playerController);

    playerName = playerController.GetPlayerName();

    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawText(TextFormat("Your Name: %s", playerName.c_str()), 300, 200, 50, BLACK);

    DrawText("PLAY GAME = ENTER", 300, 400, 50, WHITE);


    EndDrawing();

    if (IsKeyPressed(KEY_ENTER))
    {
        GS = GameStates::GAME;
    }
}

void GameManager::UpdateGame()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);

    level.Update();
    level.LevelRender();
    DrawText("PAUSE = P", 2, 2, 30, WHITE);

    EndDrawing();

    if (IsKeyDown(KEY_P))
    {
        GS = GameStates::PAUSE;
    }
    if (level.gameOver)
    {
        GS = GameStates::GAME_OVER;
    }
    if (level.gameWon)
    {
        GS = GameStates::WIN_SCREEN;
    }
}

void GameManager::UpdatePause()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawText("MAIN MENU = BACKSPACE", 250, 400, 50, WHITE);


    EndDrawing();

    if (IsKeyDown(KEY_BACKSPACE))
    {
        GS = GameStates::MAIN_MENU;
    }
   
}

void GameManager::UpdateGameOver()
{
    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawText("Game Over", 400, 40, 60, RED);

    playerName = playerController.GetPlayerName();
    playerScore = level.score;

    DrawText(TextFormat("%s's Score: %d", playerName.c_str(), playerScore), 300, 250, 50, WHITE);    
    
    DrawText("Press H to View High Scores", 300, 350, 50, WHITE);

    EndDrawing();

    if (IsKeyDown(KEY_H))
    {
        HS.AddHighScore(playerName,playerScore);

        GS = GameStates::HIGH_SCORE;
    }

}

void GameManager::UpdateWinScreen()
{

    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawText("You Win!!!", 400, 40, 60, PINK);

    playerName = playerController.GetPlayerName();
    playerScore = level.score;

    DrawText(TextFormat("%s's Score: %d", playerName.c_str(), playerScore), 300, 250, 50, WHITE);

    DrawText("Press H to View High Scores", 300, 350, 50, WHITE);

    EndDrawing();

    if (IsKeyDown(KEY_H))
    {
        HS.AddHighScore(playerName, playerScore);

        GS = GameStates::HIGH_SCORE;
    }
}

void GameManager::UpdateHighScore()
{ 
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("Press Esc to Exit", 320, 600, 40, WHITE);

    DrawText("Top 5 High Scores:", 320, 100, 40, WHITE);

    DrawText("Press C to clear High Scores", 320, 500, 40, WHITE);

    std::vector<HighScoreEntry> topScores = HS.GetTopHighScores(5);

    int yPos = 150;
    int rank = 1;

    for (const HighScoreEntry& entry : topScores)
    {
        DrawText(TextFormat("%d. %s - %d", rank, entry.playerName, entry.score), 320, yPos, 40, WHITE);
        yPos += 50;
        rank++;
    }

    EndDrawing();

    if (IsKeyPressed(KEY_C))
    {
        HS.ClearHighScores();
    }

}

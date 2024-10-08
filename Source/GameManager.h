//Aayush Sarcar

#pragma once
#include "raylib.h"
#include "Level.h"
#include "HighscoreManager.h"
#include "PlayerController.h"

//Took help from ChatGPT to reorganize the code
enum class GameStates
{
    MAIN_MENU, NAME_SCREEN, GAME, PAUSE, GAME_OVER, WIN_SCREEN , HIGH_SCORE
};

struct GameManager
{

    GameManager();

    GameStates GS;
    HighScore HS;
    PlayerController playerController;

    static Level level;

    std::string playerName;
    int playerScore;

    void RunGame();
    void UpdateMainMenu();
    void UpdateNameScreen();
    void UpdateGame();
    void UpdatePause();
    void UpdateGameOver();
    void UpdateWinScreen();
    void UpdateHighScore();
};

//Aayush Sarcar

#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include "PlayerController.h"


struct HighScoreEntry
{
	char playerName[4]; //Player's name, limited to 3 characters.
	int score;
};

// Class to manage high scores.
class HighScore
{
public:
	HighScore();

	void LoadHighScores(); // Load high scores from a file.

	void AddHighScore(const std::string& playername,int score); // Add a new high score entry.

	void SaveHighScore(); // Save high scores to a file.

	void ClearHighScores();

	void AssignPlayerName(PlayerController& playerController);

	std::vector<HighScoreEntry> GetTopHighScores(int count); // Get the top high scores
	

private:
	std::vector<HighScoreEntry> highScores; // Collection of high score entries.

	const char* highscoresFile = "highscores.data"; // File name for storing high scores.

	char GenerateRandomName();

	std::string GenerateRandomPlayerName();

	std::string playerName;
};
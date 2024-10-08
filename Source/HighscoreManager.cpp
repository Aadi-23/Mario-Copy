//Aayush Sarcar

#include "raylib.h"
#include "HighscoreManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

//I(Aayush Sarcar) took help from ChatGPT to write this code because I had no idea how to implement highscore system

	HighScore::HighScore()
	{
		LoadHighScores(); // Load high scores from the file when an instance is created.
	}

	void HighScore::LoadHighScores()
	{
		std::ifstream inputFile("highscores.dat", std::ios::binary);//Open the binary file for reading

		if (inputFile.is_open())
		{
			// Read highscores from the binary file.
			while (!inputFile.eof())
			{
				HighScoreEntry entry;
				inputFile.read(reinterpret_cast<char*>(&entry), sizeof(entry));

				if (!inputFile.eof())
				{
					highScores.push_back(entry);
				}
			}

			inputFile.close();
		}
	}

	void HighScore::AddHighScore(const std::string& playername,int score)
	{
		//Create new highscore entry
		HighScoreEntry entry;
		entry.score = score;

		// Generate a random player name.
		strncpy_s(entry.playerName, playername.c_str(), sizeof(entry.playerName));

		//Add entry to the highscore
		highScores.push_back(entry);

		//Sort the highscores by score (highest to lowest)
		std::sort(highScores.begin(), highScores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b)
		{
				return a.score > b.score;
		});

		// Limit the highscores to the top 5 entries.
		if (highScores.size() > 5)
		{
			highScores.resize(5);
		}

		//Save the updated highscores
		SaveHighScore();
	}

	void HighScore::SaveHighScore()
	{
		// Open a binary output file for writing highscore entries.
		std::ofstream outputFile("highscores.dat", std::ios::binary);

		if (outputFile.is_open())
		{
			// Write all the highscore entries to the file.
			for (const HighScoreEntry& entry : highScores)
			{
				outputFile.write(reinterpret_cast<const char*>(&entry), sizeof(entry));
			}

			outputFile.close();
		}
	}

	void HighScore::ClearHighScores()
	{
		highScores.clear();
		SaveHighScore();
	}

	std::vector<HighScoreEntry> HighScore::GetTopHighScores(int count)
	{
		// Ensure that we don't request more highscores than are available.	
		count = std::min(count, static_cast<int>(highScores.size()));

		// Return a vector containing the top 'count' highscore entries.
		return std::vector<HighScoreEntry>(highScores.begin(), highScores.begin() + count);
	}

	char HighScore::GenerateRandomName()
	{
		// Generates and returns a random uppercase letter between 'A' and 'Z'.
		return static_cast<char>('A' + rand() % 26);
	}

	std::string HighScore::GenerateRandomPlayerName()
	{
		if(playerName.empty())
		{
			// If playerName is empty, generate a random player name.
			playerName += GenerateRandomName();
			playerName += GenerateRandomName();
			playerName += GenerateRandomName();
		}
		
		return playerName;
	}

	void HighScore::AssignPlayerName(PlayerController& playerController)
	{
		if (playerName.empty())
		{
			// If playerName is empty, generate a random player name and assign it to the player controller.
			playerName = GenerateRandomPlayerName();

			playerController.SetPlayerName(playerName);
		}
	}

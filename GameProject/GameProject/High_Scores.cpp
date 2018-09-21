#pragma once
#include "High_Scores.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
using namespace sf;

High_Scores::High_Scores(void)
{
	//Alphas for colour manipulation
	alpha_max = 3 * 255;
	alpha_div = 3;
}

//Holds the names and scores of users
struct HighScore
{
	string name;
	int score;
};

//Set up for sort
bool sortByScore(const HighScore &lhs, const HighScore &rhs) { return lhs.score > rhs.score; }

int High_Scores::Run(sf::RenderWindow & App)
{
	//Variables
	Event event;
	bool Running = true;
	int alpha = 0;

	//Text set up
	Font GameFont;
	Text Title;
	Text Exit;
	Text Score;
	Text Name;
	vector<Text> HighScoreSorted;
	vector<Text> NamesSorted;

	//Highscore set up
	HighScore playerNS;
	vector<HighScore> HighScores;

	//Map background set up
	ifstream BaseLayer("BaseLayer.txt");
	ifstream SecondLayer("SecondLayer.txt");
	Texture TileTexture;
	Sprite Tiles;
	Sprite TilesSec;
	vector<vector<Vector2i>> map;
	vector<vector<Vector2i>> mapSec;

	LoadMapCounter("BaseLayer.txt", map);
	LoadMapCounter("SecondLayer.txt", mapSec);

	SetTextureFile("TileSetProject.png", TileTexture, Tiles);
	SetTextureFile("TileSetProject.png", TileTexture, TilesSec);

	if (!GameFont.loadFromFile("GameText.ttf"))
	{
		cerr << "Error loading GameText.ttf" << endl;
		return -1;
	}

	//Highscore file initialised
	string line;
	ifstream HighScoreFile("HighScores.txt");

	//Read the file into struct objects
	while (!HighScoreFile.eof())
	{
		HighScoreFile >> playerNS.score >> playerNS.name;
		HighScores.push_back(playerNS);
	}
	HighScoreFile.close();

	//Sort the struct vector into descending order
	sort(HighScores.begin(), HighScores.end(), sortByScore);

	//Set the names and scores to text for display
	for (HighScore &n : HighScores)
	{
		Score.setString(to_string(n.score));
		Name.setString(n.name);

		HighScoreSorted.push_back(Score);
		NamesSorted.push_back(Name);
	}

	//Set text for title and exit
	Title.setFont(GameFont);
	Title.setCharacterSize(40);
	Title.setString("High Scores");
	Title.setPosition(App.getSize().x / 4, App.getSize().y / 9);
	Title.setFillColor(Color());

	Exit.setFont(GameFont);
	Exit.setCharacterSize(30);
	Exit.setString("Exit");
	Exit.setPosition(App.getSize().x / 2.3, App.getSize().y / 1.2);
	Title.setFillColor(Color());

	//Position variables for use in loops to set Highscore names and score to screen
	float y = (App.getSize().y / 3);
	float x = (App.getSize().y / 3);

	//Highscores reduced to just top 5
	HighScores.resize(5);

	//Setup for text from the score and name into sorted vectors
	for (size_t i = 0; i < HighScores.size(); i++)
	{
		Name.setString(HighScores[i].name);
		Score.setString(to_string(HighScores[i].score));

		NamesSorted.push_back(Name);
		HighScoreSorted.push_back(Score);
	}
	
	//Setup text for Score
	for (size_t i = 0; i < HighScoreSorted.size(); i++)
	{
		HighScoreSorted[i].setFont(GameFont);
		HighScoreSorted[i].setCharacterSize(24);
		HighScoreSorted[i].setPosition(App.getSize().x / 1.33, x);
		HighScoreSorted[i].setFillColor(Color(255, 0, 0, 255));
		x += 34;
	}

	//Setup text for name
	for (size_t i = 0; i < NamesSorted.size(); i++)
	{
		NamesSorted[i].setFont(GameFont);
		NamesSorted[i].setCharacterSize(24);
		NamesSorted[i].setPosition(App.getSize().x / 7, y);
		NamesSorted[i].setFillColor(Color(255, 0, 0, 255));
		y += 34;
	}

	//Screen running
	while (Running)
	{
		while (App.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					return 0;
				}
			}

			//Mouse click exit check
			Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));
			if (Exit.getGlobalBounds().contains(mousePos))
			{
				Exit.setFillColor(Color(255, 0, 0, 255));
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					return 0;
				}
			}
			else
			{
				Exit.setFillColor(Color());
			}
		}

	//Alpha manipulation for fade in and out
	if (alpha < alpha_max)
	{
		alpha++;
	}

	//Draw everything to screen
	DrawMapTiles(map, Tiles, App);
	DrawMapTiles(mapSec, TilesSec, App);
	App.draw(Title);
	App.draw(Exit);

	for (int i = 0; i < 5; i++)
	{
		App.draw(HighScoreSorted[i]);
		App.draw(NamesSorted[i]);
	}

	App.display();
		
	}

	return (-1);
}

#include "Game_Over.h"

Game_Over::Game_Over(void)
{
	//Alphas for colour manipulation
	alpha_max = 255 * 3;
	alpha_div = 3;
}

int Game_Over::Run(sf::RenderWindow & App)
{
	//Variables
	Event event;
	bool Running = true;
	int alpha = 0;

	//Font and Text
	Font GameFont;
	Text GameOver;
	Text Exit;
	Text Name;
	Text AskEntry;
	Text HS;
	Text CurHighScore;
	string NameEntry;

	//High Score File
	ofstream HighScoreFile;

	//Background
	ifstream BaseLayer("BaseLayer.txt");
	ifstream SecondLayer("SecondLayer.txt");
	Texture TileTexture;
	Sprite Tiles;
	Sprite TilesSec;
	vector<vector<Vector2i>> map;
	vector<vector<Vector2i>> mapSec;

	Clock GameOverC;
	Time GameOverT;

	//Background load
	LoadMapCounter("BaseLayer.txt", map);
	LoadMapCounter("SecondLayer.txt", mapSec);

	SetTextureFile("TileSetProject.png", TileTexture, Tiles);
	SetTextureFile("TileSetProject.png", TileTexture, TilesSec);

	//Font Load
	if (!GameFont.loadFromFile("GameText.ttf"))
	{
		cerr << "Error loading GameText.ttf" << endl;
		return -1;
	}

	//Text setup
	GameOver.setFont(GameFont);
	GameOver.setCharacterSize(40);
	GameOver.setString("Game Over");
	GameOver.setPosition(App.getSize().x / 3.8, App.getSize().y / 9);
	GameOver.setFillColor(Color(255,0,0,255));

	Exit.setFont(GameFont);
	Exit.setCharacterSize(30);
	Exit.setString("Exit");
	Exit.setPosition(App.getSize().x / 2.3, App.getSize().y / 1.2);
	Exit.setFillColor(Color());

	HS.setPosition(App.getSize().x / 40, App.getSize().y / 4);
	HS.setCharacterSize(40);
	HS.setString("Your Score:");
	HS.setFont(GameFont);
	HS.setFillColor(Color(0, 0, 255, 255));

	CurHighScore.setPosition(App.getSize().x / 1.5, App.getSize().y / 4);
	CurHighScore.setCharacterSize(40);
	CurHighScore.setString(to_string(GameHighScore));
	CurHighScore.setFont(GameFont);
	CurHighScore.setFillColor(Color(0, 0, 255, 255));

	AskEntry.setFont(GameFont);
	AskEntry.setCharacterSize(18);
	AskEntry.setString("Please type in your name and press enter:");
	AskEntry.setPosition(App.getSize().x / 40, App.getSize().y / 1.8);
	AskEntry.setFillColor(Color());
	
	Name.setFont(GameFont);
	Name.setCharacterSize(40);
	Name.setPosition(App.getSize().x / 3.8, App.getSize().y / 1.6);
	Name.setFillColor(Color(0,0,255,255));

	//Screen running
	while (Running)
	{
		while (App.pollEvent(event))
		{
			// Window closed
			if (event.type == Event::Closed)
			{
				return (-1);
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				return 0;
			}
			//Key pressed for entry of name
			if (GameHighScore > 0)
			{
				if (event.type == Event::KeyPressed)
				{
					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						if (NameEntry.length() > 0)
						{
							HighScoreFile.open("HighScores.txt", ios::app);
							HighScoreFile << "\n" << GameHighScore << " " << NameEntry;
							HighScoreFile.close();

							return 0;
						}
					}
				}
				//SFML special event check for entering text to screen
				if (event.type == Event::TextEntered)
				{
					if (event.text.unicode >= 32 && event.text.unicode <= 128)
					{
						if (NameEntry.size() < 6)
						{
							NameEntry += ((char)event.text.unicode);
							Name.setString(NameEntry);
						}
					}
					else if (event.text.unicode == 8 && NameEntry.length() > 0)
					{
						NameEntry.erase(NameEntry.length() - 1, NameEntry.length());
						Name.setString(NameEntry);
					}
				}
			}
		}
	//Checking for exit mouse click
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

	//Alpha for colour setting, fade in and out
	if (alpha < alpha_max)
	{
		alpha++;
	}

	Tiles.setColor(Color(255, 255, 255, alpha));

	DrawMapTiles(map, Tiles, App);
	DrawMapTiles(mapSec, TilesSec, App);

	App.draw(GameOver);

	GameOverT = GameOverC.getElapsedTime();

	//Timer to delay entry appearing
	if (GameOverT.asSeconds() > 3)
	{
		if (GameHighScore > 0)
		{
			App.draw(AskEntry);
			App.draw(Name);
			App.draw(HS);
			App.draw(CurHighScore);
			App.draw(Exit);
		}
		else
		{
			App.draw(HS);
			App.draw(CurHighScore);
			App.draw(Exit);
		}
	}

	App.display();

	}
	return -1;
}

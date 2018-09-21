#include "Main_Menu.h"
#include "Map.h"

using namespace std;
using namespace sf;

Main_Menu::Main_Menu(void)
{
	//For Colour alpha calculations
	alpha_max = 3 * 255;
	alpha_div = 3;
}

int Main_Menu::Run(sf::RenderWindow &App)
{
	//Variables
	Event event;
	bool Running = true;
	int alpha = 0;

	//Text
	Font GameFont;
	Text Title;
	Text Menu1;
	Text Menu2;
	Text Menu3;

	//Timers
	Clock Menu;
	Time MenuPop;

	//Set map for background
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

	//Set up the text display for the screen
	Title.setFont(GameFont);
	Title.setCharacterSize(40);
	Title.setString("It's Hign Noon!");
	Title.setPosition(App.getSize().x / 5, App.getSize().y / 8);
	Title.setFillColor(Color());

	Menu1.setFont(GameFont);
	Menu1.setCharacterSize(30);
	Menu1.setString("Start Game");
	Menu1.setPosition(App.getSize().x / 3.2, App.getSize().y / 2.5);
	
	Menu2.setFont(GameFont);
	Menu2.setCharacterSize(30);
	Menu2.setString("High Scores");
	Menu2.setPosition(App.getSize().x / 3.3, App.getSize().y / 1.8);

	Menu3.setFont(GameFont);
	Menu3.setCharacterSize(30);
	Menu3.setString("Exit");
	Menu3.setPosition(App.getSize().x / 2.3, App.getSize().y / 1.1);

	//While main menu screen is running
	while (Running)
	{
		//adjust alpha value for fade in / fade out screens
		if (alpha < alpha_max)
		{
			alpha++;
		}

		Tiles.setColor(Color(255, 255, 255, alpha));

		DrawMapTiles(map, Tiles, App);
		DrawMapTiles(mapSec, TilesSec, App);

		App.draw(Title);

		MenuPop = Menu.getElapsedTime();

		//Menu appears after 2 seconds
		if (MenuPop.asSeconds() > 2)
		{
			App.draw(Menu1);
			App.draw(Menu2);
			App.draw(Menu3);
		}
		
		App.display();

		while (App.pollEvent(event))
		{
			//Window closed
			if (event.type == sf::Event::Closed)
			{
				return -1;
			}
			//Exit application
			if (Keyboard::isKeyPressed(Keyboard::Escape) && MenuPop.asSeconds() > 1)
			{
				return -1;
			}
			//Mouse click menu
			Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));
			if (Menu1.getGlobalBounds().contains(mousePos))
			{
				Menu1.setFillColor(Color(255, 0, 0, 255));
			}
			else
			{
				Menu1.setFillColor(Color());
			}

			if (Menu2.getGlobalBounds().contains(mousePos))
			{
				Menu2.setFillColor(Color(255, 0, 0, 255));
			}
			else
			{
				Menu2.setFillColor(Color());
			}

			if (Menu3.getGlobalBounds().contains(mousePos))
			{
				Menu3.setFillColor(Color(255, 0, 0, 255));
			}
			else
			{
				Menu3.setFillColor(Color());
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (Menu1.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
				{
					GameHighScore = 0;
					return 1;
				}
				else if (Menu2.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
				{
					return 2;
				}
				else if (Menu3.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left))
				{
					return -1;
				}
			}
		}	
	}
	
	return (-1);
}


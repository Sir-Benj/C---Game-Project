#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <cmath>
#include <sstream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include "Player.h"
#include "Enemy.h"

# define PI           3.14159265358979323846  /* pi */

using namespace std;
using namespace sf;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	//Variables
	//Map
	ifstream BaseLayer("BaseLayer.txt");
	ifstream SecondLayer("SecondLayer.txt");
	Texture TileTexture;
	Sprite Tiles;
	Sprite TilesSec;
	//Calculations
	Vector2f mousePos;
	Vector2f aimAngle;
	Vector2f aimAngleNorm;
	//Clocks for timing
	Clock clockOne;
	Clock clockTwo;
	Clock clockThree;
	Clock clockFour;
	//Enemy spawn counter
	int spawnCount = 0;
	//Highscore counter
	int highScore = 0;

	//Map set up

	vector<vector<Vector2i>> map;
	vector<vector<Vector2i>> mapSec;
	vector<CollisionTile> CTiles;

	LoadMapCounter("BaseLayer.txt", map);
	LoadMapCounter("SecondLayer.txt", mapSec);

	SetTextureFile("TileSetProject.png", TileTexture, Tiles);
	SetTextureFile("TileSetProject.png", TileTexture, TilesSec);

	CreateColTiles(mapSec, CTiles);

	//Sets up game screen to map size (for 16*16 tiles)

	Vector2f ScreenSize((map.size()*16), (map.size()*16));
	RenderWindow GameScreen(VideoMode(ScreenSize.x, ScreenSize.y, 16), "It's High Noon");
	GameScreen.setFramerateLimit(60);

	//Player set up

	Player player(Vector2f((ScreenSize.x / 2), (ScreenSize.y / 3)), Vector2f(24,32));
	player.SetPlayerTexture("PlayerSpriteSheet.png", player);

	//Enemy set up

	Enemy enemy(GameScreen, "Enemy.png");
	vector<Enemy> enemies;

	//Bullet set up

	Bullet bulletOne(player, "Bullet.png");
	vector<Bullet> bullets;

	while (GameScreen.isOpen())
	{
		//Set times and events

		Time sinceStart = clockOne.getElapsedTime();
		Time sinceFrameStart = clockTwo.restart();
		Time sinceShot = clockThree.getElapsedTime();
		Time sinceDmg = clockFour.getElapsedTime();

		Event event;
		GameScreen.pollEvent(event);
		
		if (event.type == Event::Closed)
		{
			GameScreen.close();
		}
		
		//Update all actions and movements
		
		player.PlayerAction(player, ScreenSize, CTiles);
		player.ColEnemy(player, enemies, clockFour, sinceDmg);
		if (player.playerHP < 1)
		{
			break;
		}
		
		enemy.SpawnEnemy(spawnCount, enemy, enemies, GameScreen);
		enemy.EnemyMove(enemy, enemies, player);
	
		bulletOne.CalShot(bulletOne, clockThree, sinceShot, bullets, GameScreen, player);
		bulletOne.CheckOnScreen(bullets, GameScreen);
		bulletOne.CheckMapCol(bullets, CTiles);
		bulletOne.CheckEnemyCol(spawnCount, bullets, enemies, highScore);

		//Draw the frame

		GameScreen.clear();

		DrawMapTiles(map, Tiles, GameScreen);
		DrawMapTiles(mapSec, TilesSec, GameScreen);

		GameScreen.draw(player.playerRect);

		for (size_t i = 0; i < bullets.size(); i++)
		{
			GameScreen.draw(bullets[i].bulletRect);
		}

		for (size_t i = 0; i < enemies.size(); i++)
		{
			GameScreen.draw(enemies[i].enemyRect);
		}

		GameScreen.display();
	}

	cout << "GAME OVER" << endl;
	cout << "Your Score = " << highScore << endl;
	cout << "Press any key to exit" << endl;
	getchar();

	return 0;
}
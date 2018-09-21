#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//Empty constructor
Enemy::Enemy()
{
}

//Full Contructor for program needs
Enemy::Enemy(RenderWindow &gamescreen, string ProjTextureFile)
{
	enemyRect.setPosition(0,0);
	enemyRect.setSize(Vector2f(34, 42));
	enemyTexture.loadFromFile(ProjTextureFile);
	enemyCurVelo = Vector2f(0, 0);
	enemyHP = 3;
	enemySpeed = 0.05;

	//Texture loaded within the construction
	if (!enemyTexture.loadFromFile(ProjTextureFile))
	{
		cout << ProjTextureFile << "is not present, cannot run program." << endl;;
	}
	enemyRect.setTexture(&enemyTexture);
}

//Destructor
Enemy::~Enemy()
{
}

//Enemy movement calculations for all enemies
void Enemy::EnemyMove(Enemy &enemy, vector<Enemy> &enemies, Player &player, Clock &frameclock, Time &frametime)
{
	Vector2f playerPos = Vector2f(player.playerRect.getPosition());
	
	for (size_t i = 0; i < enemies.size(); i++)
	{
		Vector2f aimAngle = playerPos - Vector2f(enemies[i].enemyRect.getPosition());
		Vector2f aimAngleNorm = aimAngle / (sqrt(pow(aimAngle.x, 2) + pow(aimAngle.y, 2)));

		frametime = frameclock.getElapsedTime();

		enemies[i].enemyCurVelo = aimAngleNorm * (enemies[i].enemySpeed * frametime.asMilliseconds());

		enemies[i].enemyRect.move(enemies[i].enemyCurVelo);
	}
}


//Enemy collision detection and resolve (NYI)
void Enemy::EnemyMapCol(vector<Enemy> &enemies, vector<CollisionTile> &ColTiles)
{
	
	for (size_t k = 0; k < ColTiles.size(); k++)
	{
		if (ColTiles[k].Collision == true)
		{
			for (size_t i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].enemyRect.getGlobalBounds().intersects(ColTiles[k].CTile.getGlobalBounds()))
				{
						//A* alogrithm could be used
				}
			}
		}
	}
}

//Enemy random spawn location control
void Enemy::SpawnEnemy(int &spawnCount, int &spawnMax, Enemy &enemy, vector<Enemy> &enemies, RenderWindow &gamescreen)
{
	if (spawnCount < spawnMax)
	{
		Vector2f topSpawn((rand() % 188 + 129), -42);
		Vector2f botSpawn((rand() % 188 + 129), gamescreen.getSize().y + 42);
		Vector2f leftSpawn(-34, (rand() % 180 + 129));
		Vector2f rightSpawn(gamescreen.getSize().x + 34, (rand() % 180 + 129));

		int randomSpawn = rand() % 4 + 1;

		switch (randomSpawn)
		{
		case 1: enemy.enemyRect.setPosition(Vector2f(topSpawn));
			break;
		case 2: enemy.enemyRect.setPosition(Vector2f(botSpawn));
			break;
		case 3: enemy.enemyRect.setPosition(Vector2f(leftSpawn));
			break;
		case 4: enemy.enemyRect.setPosition(Vector2f(rightSpawn));
			break;
		}

		enemies.push_back(Enemy(enemy));
		spawnCount++;
	}
}
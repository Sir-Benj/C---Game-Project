#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

void Player::PlayerAction(Player& playerobject, Vector2f screenSize, vector<CollisionTile> &ColTiles, Clock &frameclock, Time &frametime)
//function to check for keyboard inputs controlling the player object, sets direction and velocity and collision boundaries for the screen
//also checks for collision with map tiles and if so acts accordingly 
{
	{
		//Frame timer to have framerate independent gameplay
		frametime = frameclock.getElapsedTime();

		//Get the initial position of the player before the move is done and save it to variables
		float PrevPosX = playerobject.playerRect.getPosition().x, PrevPosY = playerobject.playerRect.getPosition().y;

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			//Check screen boundary
			playerobject.playerRect.move(0, -maxSpeed * frametime.asMilliseconds());
			if (playerobject.playerRect.getPosition().y <= 0)
			{
				playerobject.playerRect.setPosition(playerobject.playerRect.getPosition().x, 0);
			}

			playerobject.CheckPlayerPos();

			//check to see if map collided with 
			for (int i = 0; i < ColTiles.size(); i++)
			{
				ColTiles[i].CheckTilePos();
				//Check if tile has collision
				if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
				{
					//Set previous position (no movement)
					playerobject.playerRect.setPosition(PrevPosX,PrevPosY);
					//Checking for diagonal (two key press)
					if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left))
					{
						//player moves slowly along to the left
						playerobject.playerRect.move(-minSpeed * frametime.asMilliseconds(), 0);
						playerobject.CheckPlayerPos();
						for (int i = 0; i < ColTiles.size(); i++)
						{
							ColTiles[i].CheckTilePos();
							if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
							{
								//If tile moving into is collision on that side, set previous position (no movement)
								playerobject.playerRect.setPosition(PrevPosX, PrevPosY);
							}
						}
						
					}

					if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right))
					{
						playerobject.playerRect.move(minSpeed * frametime.asMilliseconds(), 0);
						playerobject.CheckPlayerPos();
						for (int i = 0; i < ColTiles.size(); i++)
						{
							ColTiles[i].CheckTilePos();
							if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
							{
								playerobject.playerRect.setPosition(PrevPosX, PrevPosY);
							}
						}
					}
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			playerobject.playerRect.move(-maxSpeed * frametime.asMilliseconds(), 0);
			if (playerobject.playerRect.getPosition().x <= 0)
			{
				playerobject.playerRect.setPosition(0, playerobject.playerRect.getPosition().y);
			}

			playerobject.CheckPlayerPos();

			for (int i = 0; i < ColTiles.size(); i++)
			{
				ColTiles[i].CheckTilePos();
				if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
				{
					playerobject.playerRect.setPosition(PrevPosX, PrevPosY);
					if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
					{
						playerobject.playerRect.move(0, -minSpeed * frametime.asMilliseconds());
					}
					if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down))
					{
						playerobject.playerRect.move(0, minSpeed * frametime.asMilliseconds());
					}
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			playerobject.playerRect.move(0, maxSpeed * frametime.asMilliseconds());
			if (playerobject.playerRect.getPosition().y >= (screenSize.y - playerobject.playerRect.getSize().y))
			{
				playerobject.playerRect.setPosition(playerobject.playerRect.getPosition().x, (screenSize.y - playerobject.playerRect.getSize().y));
			}

			playerobject.CheckPlayerPos();

			for (int i = 0; i < ColTiles.size(); i++)
			{
				ColTiles[i].CheckTilePos();
				if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
				{
					playerobject.playerRect.setPosition(PrevPosX, PrevPosY);
					if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left))
					{
						playerobject.playerRect.move(-minSpeed * frametime.asMilliseconds(), 0);
						playerobject.CheckPlayerPos();
						for (int i = 0; i < ColTiles.size(); i++)
						{
							ColTiles[i].CheckTilePos();
							if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
							{
								playerobject.playerRect.setPosition(PrevPosX, PrevPosY);
							}
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right))
					{
						playerobject.playerRect.move(minSpeed * frametime.asMilliseconds(), 0);
						playerobject.CheckPlayerPos();
						for (int i = 0; i < ColTiles.size(); i++)
						{
							ColTiles[i].CheckTilePos();
							if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
							{
								playerobject.playerRect.setPosition(PrevPosX, PrevPosY);
							}
						}
					}
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			playerobject.playerRect.move(maxSpeed * frametime.asMilliseconds(), 0);
			if (playerobject.playerRect.getPosition().x >= (screenSize.x - playerobject.playerRect.getSize().x))
			{
				playerobject.playerRect.setPosition((screenSize.x - playerobject.playerRect.getSize().x), playerobject.playerRect.getPosition().y);
			}

			playerobject.CheckPlayerPos();

			for (int i = 0; i < ColTiles.size(); i++)
			{
				ColTiles[i].CheckTilePos();
				if (playerobject.ColMap(ColTiles[i]) && ColTiles[i].Collision == true)
				{
					playerobject.playerRect.setPosition(PrevPosX, PrevPosY);
					if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))
					{
						playerobject.playerRect.move(0, -minSpeed * frametime.asMilliseconds());
					}
					if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down))
					{
						playerobject.playerRect.move(0, minSpeed * frametime.asMilliseconds());
					}
				}
			}
		}
	}
}

Player::Player()
{
	//default constructor
}

Player::Player(Vector2f position, Vector2f size)
{
	playerRect.setPosition(position);
	playerRect.setSize(size);
	playerHP = 5;
	maxSpeed = 0.5;
	minSpeed = 0.2;
}

Player::~Player()
{
	//destructor
}

//for bounding box collision checks
void Player::CheckPlayerPos()
{
	//sets points for each corner of the rectangle
	top = playerRect.getPosition().y;
	bottom = playerRect.getPosition().y + playerRect.getSize().y;
	left = playerRect.getPosition().x;
	right = playerRect.getPosition().x + playerRect.getSize().x;
}

//sets player texture file
void Player::SetPlayerTexture(string TextureFile, Player &player)
{
	player.playerTexture.loadFromFile(TextureFile);
	if (!player.playerTexture.loadFromFile(TextureFile))
	{
		cout << TextureFile << "is not present, cannot run program." << endl;;
	}
	player.playerRect.setTexture(&player.playerTexture);
	player.playerRect.setTextureRect(IntRect(1*24, 3*32, 24, 32));
}

//bounding box collision check
bool Player::ColMap(CollisionTile tile)
{
	//checks for no overlap of collision tiles, and returns false, if however there is overlap, it returns true
	if (top > tile.bottom || bottom < tile.top || left > tile.right || right < tile.left)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Check for collision with enemy, set damage clock so damage can only occur once a second
void Player::ColEnemy(Player &player, vector<Enemy> &enemies, Clock &dmgclock, Time &sincedmg)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		sincedmg = dmgclock.getElapsedTime();

		if (enemies[i].enemyRect.getGlobalBounds().intersects(player.playerRect.getGlobalBounds()) && sincedmg.asSeconds() > 1)
		{
			player.playerHP--;
			dmgclock.restart();
		}
	}
	
}

//Projectile empty constructor
Bullet::Bullet()
{
}

//Projectile deconstructor
Bullet::~Bullet()
{
}

//Calculate projectile direction and velocity, amount of shots per click limited by timer
void Bullet::CalShot(Bullet &bullet, Clock &shotclock, Time &sinceshot, vector<Bullet> &bullets, RenderWindow &gamescreen, Player &player)
{
	Vector2f mousePos = gamescreen.mapPixelToCoords(Mouse::getPosition(gamescreen));
	Vector2f aimAngle = mousePos - Vector2f(player.playerRect.getPosition().x + (player.playerRect.getSize().x / 2), player.playerRect.getPosition().y + player.playerRect.getSize().y);
	Vector2f aimAngleNorm = aimAngle / (sqrt(pow(aimAngle.x, 2) + pow(aimAngle.y, 2)));

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		sinceshot = shotclock.getElapsedTime();

		if (sinceshot.asSeconds() > 0.2)
		{
			bullet.bulletRect.setPosition(player.playerRect.getPosition().x + (player.playerRect.getSize().x / 2), player.playerRect.getPosition().y + player.playerRect.getSize().y);

			bullet.currentVelo = aimAngleNorm * bullet.maxSpeed;

			bullets.push_back(Bullet(bullet));
			shotclock.restart();
		}
	}
}

//Code for calculation for bullet direction and velocity by Headturna
//Source: https://github.com/Headturna/SFML/blob/master/Example10.cpp
//Accessed 4/4/18
//Code used as follows:
//playerCenter = Vector2f(player.getPosition());
//mousePosWindow = Vector2f(Mouse::getPosition(window));
//aimDir = mousePosWindow - playerCenter;
//aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

//Check projectile is still on the screen, if not remove it from the vector and destroy it
void Bullet::CheckOnScreen(vector<Bullet> &bullets, RenderWindow &gamescreen, Clock &frameclock, Time &frametime)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		frametime = frameclock.getElapsedTime();

		bullets[i].bulletRect.move((bullets[i].currentVelo.x * frametime.asMilliseconds()), (bullets[i].currentVelo.y * frametime.asMilliseconds()));

		if (bullets[i].bulletRect.getPosition().x < 0 || bullets[i].bulletRect.getPosition().x > gamescreen.getSize().x
			|| bullets[i].bulletRect.getPosition().y <0 || bullets[i].bulletRect.getPosition().y > gamescreen.getSize().y)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

//Check for projectile collision with map collision tiles and remove from the vector if they do
void Bullet::CheckMapCol(vector<Bullet> &bullets, vector<CollisionTile> &coltiles)
{
	for (size_t k = 0; k < coltiles.size(); k++)
	{
		if (coltiles[k].Collision == true)
		{
			for (size_t i = 0; i < bullets.size(); i++)
			{
				if (bullets[i].bulletRect.getGlobalBounds().intersects(coltiles[k].CTile.getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
				}
			}
		}
	}
}

//Check for projectile collision with enemy, if so remove from vector
void Bullet::CheckEnemyCol(int &spawnCount, vector<Bullet> &bullets, vector<Enemy> &enemies, int &highscore)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		for (size_t k = 0; k < enemies.size(); k++)
		{
			if (bullets[i].bulletRect.getGlobalBounds().intersects(enemies[k].enemyRect.getGlobalBounds()))
			{
				//If enemy hp is above 1 remove hp
				if (enemies[k].enemyHP > 1)
				{
					bullets.erase(bullets.begin() + i);
					enemies[k].enemyHP--;
					break;
				}
				//if enemy hp is equal to 1 or less and a projectile hits, erase the enemy
				else if (enemies[k].enemyHP <= 1)
				{
					bullets.erase(bullets.begin() + i);
					enemies.erase(enemies.begin() + k);
					highscore += 100;
					spawnCount--;
					break;
				}
            }
		}

	}
}

//Projectile constructor for use in game
Bullet::Bullet(Player &player, string ProjTextureFile)
{
	bulletRect.setPosition(player.playerRect.getPosition().x + (player.playerRect.getSize().x / 2), player.playerRect.getPosition().y + player.playerRect.getSize().y);
	bulletRect.setSize(Vector2f(5, 5));
	BulTexture.loadFromFile(ProjTextureFile);
	currentVelo = Vector2f(0, 0);
	maxSpeed = 0.4;
	if (!BulTexture.loadFromFile(ProjTextureFile))
	{
		cout << ProjTextureFile << "is not present, cannot run program." << endl;;
	}
	bulletRect.setTexture(&BulTexture);
}

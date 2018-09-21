#pragma once
#include "Map.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

//Forward Declaration
class Enemy;

//Player class contains all info and functions for the Player object.
class Player
{
public:
	Player();
	Player(Vector2f position, Vector2f size);
	~Player();
	void PlayerAction(Player &player, Vector2f screensize, vector<CollisionTile> &ColTiles, Clock &frameclock, Time &frametime);
	void CheckPlayerPos();
	void SetPlayerTexture(string TextureFile , Player &player);
	bool ColMap(CollisionTile tile);
	void ColEnemy(Player &player, vector<Enemy> &enemies, Clock &dmgclock, Time &sincedmg);
	int playerHP;
	RectangleShape playerRect;
	Texture playerTexture;

private:
	float top, bottom, left, right;
	float maxSpeed;
	float minSpeed;
};

//Bullet class contains all info and functions for the projectiles.
class Bullet
{
public:
	Bullet();
	Bullet(Player &player, string ProjTextureFile);
	~Bullet();
	void CalShot(Bullet &bullet, Clock &shotclock, Time &sinceshot, vector<Bullet>& bullets, RenderWindow &gamescreen, Player &player);
	void CheckOnScreen(vector<Bullet> &bullets, RenderWindow &gamescreen, Clock &frameclock, Time &frametime);
	void CheckMapCol(vector<Bullet> &bullets, vector<CollisionTile> &coltiles);
	void CheckEnemyCol(int &spawnCount, vector<Bullet>& bullets, vector<Enemy>& enemies, int &highscore);
	RectangleShape bulletRect;

private:
	Vector2f currentVelo;
	float maxSpeed;
	Texture BulTexture;
};
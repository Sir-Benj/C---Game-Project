#pragma once
#include "Map.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

//forward declaration, breaks circular dependency of header files.
class Player;
class Bullet;

//Enemy class contains all information and functions needed for the players opponents.
class Enemy
{
public:
	Enemy();
	Enemy(RenderWindow &gamescreen, string ProjTextureFile);
	~Enemy();
	void EnemyMove(Enemy &enemy, vector<Enemy> &enemies, Player &player, Clock &frameclock, Time &frametime);
	void EnemyMapCol(vector<Enemy> &enemies, vector<CollisionTile> &ColTiles);
	void SpawnEnemy(int &spawnCount, int &spawnMax, Enemy &enemy, vector<Enemy> &enemies, RenderWindow &gamescreen);
	float enemySpeed;
	int enemyHP;
	Vector2f enemyCurVelo;
	RectangleShape enemyRect;
	Texture enemyTexture;
};
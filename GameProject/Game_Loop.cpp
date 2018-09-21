#include "Game_Loop.h"

using namespace std;
using namespace sf;

int Game_Loop::Run(RenderWindow &App)
{
	//Event for checking screen closure.
	Event event;
	//File streams for the map texts
	ifstream BaseLayer("BaseLayer.txt");
	ifstream SecondLayer("SecondLayer.txt");
	//Texture and sprite initialisation
	Texture TileTexture;
	Sprite Tiles;
	Sprite TilesSec;
	Vector2f PlayTextureS(24, 32);
	//vectors for map tiles
	vector<vector<Vector2i>> map;
	vector<vector<Vector2i>> mapSec;
	vector<CollisionTile> CTiles;

	//Map contents loaded to vectors
	LoadMapCounter("BaseLayer.txt", map);
	LoadMapCounter("SecondLayer.txt", mapSec);

	//Textures loaded to map files
	SetTextureFile("TileSetProject.png", TileTexture, Tiles);
	SetTextureFile("TileSetProject.png", TileTexture, TilesSec);

	//Seed random
	srand(time(NULL));

	//Calculations
	Vector2f mousePos;
	Vector2f aimAngle;
	Vector2f aimAngleNorm;

	//Clocks for timing
	Clock clockOne;
	Clock clockTwo;
	Clock clockThree;
	Clock clockFour;
	Clock clockFive;

	//Enemy spawn counter
	int spawnCount = 0;
	int spawnMax = 2;

	//HighScore text set up
	Font GameFont;
	if (!GameFont.loadFromFile("GameText.ttf"))
	{
		cerr << "Error loading GameText.ttf" << endl;
		return -1;
	}

	//Screen text
	Text HighScore;
	HighScore.setPosition(0, 0);
	HighScore.setCharacterSize(18);
	HighScore.setFont(GameFont);

	//Set PlayerHP Screen Text
	Text PlayerHP;
	PlayerHP.setPosition(0, App.getSize().y - PlayerHP.getCharacterSize());
	PlayerHP.setCharacterSize(18);
	PlayerHP.setFont(GameFont);

	//Map set up
	CreateColTiles(mapSec, CTiles);

	//Player set up
	Player player(Vector2f((App.getSize().x / 2), (App.getSize().y / 3)), PlayTextureS);
	player.SetPlayerTexture("PlayerSpriteSheet.png", player);

	//Enemy set up
	Enemy enemy(App, "Enemy.png");
	vector<Enemy> enemies;

	//Bullet set up
	Bullet bulletOne(player, "Bullet.png");
	vector<Bullet> bullets;

	while (App.isOpen())
	{
		//Set times and events
		Time sinceStart;
		Time sinceFrameStart;
		Time sinceShot;
		Time sinceDmg;
		Time sinceSpawn;

		//Event poll for screen closure
		App.pollEvent(event);

		if (event.type == Event::Closed)
		{
			App.close();
		}
		
		//Check for escaoe press and exit
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			return 0;
		}

		//Update all actions and movements

		//Player actions

		player.PlayerAction(player, Vector2f(App.getSize().x, App.getSize().y), CTiles, clockTwo, sinceFrameStart);
		player.ColEnemy(player, enemies, clockFour, sinceDmg);
		PlayerHP.setString("Health: " + to_string(player.playerHP));
		//check player hp to determine game over
		if (player.playerHP < 1)
		{
			return 3;
		}

		//Enemy actions

		sinceSpawn = clockFive.getElapsedTime();

		if (sinceSpawn.asSeconds() > 15 && spawnMax < 20)
		{
			spawnMax++;
			clockFive.restart();
		}
		enemy.SpawnEnemy(spawnCount, spawnMax, enemy, enemies, App);
		enemy.EnemyMove(enemy, enemies, player, clockTwo, sinceFrameStart);

		//Bullet actions
		bulletOne.CalShot(bulletOne, clockThree, sinceShot, bullets, App, player);
		bulletOne.CheckOnScreen(bullets, App, clockTwo, sinceFrameStart);
		bulletOne.CheckMapCol(bullets, CTiles);
		bulletOne.CheckEnemyCol(spawnCount, bullets, enemies, GameHighScore);

		//Highscore for display
		HighScore.setString(to_string(GameHighScore));
		//Frameclock restarted so that movement can be calculated depending on the length of frame draw time, after all previous calculations are complete
		clockTwo.restart().asMilliseconds();

		//Draw frame to screen
		App.clear();

		DrawMapTiles(map, Tiles, App);
		DrawMapTiles(mapSec, TilesSec, App);

		App.draw(player.playerRect);

		for (size_t i = 0; i < bullets.size(); i++)
		{
			App.draw(bullets[i].bulletRect);
		}

		for (size_t i = 0; i < enemies.size(); i++)
		{
			App.draw(enemies[i].enemyRect);
		}

		App.draw(PlayerHP);
		App.draw(HighScore);

		App.display();
	}
	//Exits app if it ever reaches this point
	return -1;
}


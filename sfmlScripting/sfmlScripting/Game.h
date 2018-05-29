#ifndef GAME_H
#define GAME_H
#include "Includes.h"
#include "Character.h"
#include "Monster.h"
#include "Tile.h"
//#include "Wall.h"

class Game
{
private:
	Character character;
	Monster monster;
	Tile * list[120];
	Tile * smallList[120];
	Tile * selectList[8];
	int amountOfWalls;
	Tile * walls[120];
	int score;
	sf::Font font;
	sf::Text scoreDisplay;
	string map;
	string mapTile;

	//venne
	bool nextTo;
public:
	Game();
	Game(sf::Texture * texture, sf::Texture * playerTexture);
	~Game();

	void setupMap(sf::Texture * texture);
	void setupSelectionList(sf::Texture * texture);
	void update(float sec, lua_State * L, lua_State * LU);
	void draw(sf::RenderWindow& window);
	void drawMap(sf::RenderWindow& window);
	void drawSmallMap(sf::RenderWindow& window);
	void drawSelectList(sf::RenderWindow& window);
	void checkCollision();
	string getMap();
	void setMap(string m);
	void setTile(int i, int tile, sf::Texture * texture);
	int getScore();
};

#endif // !
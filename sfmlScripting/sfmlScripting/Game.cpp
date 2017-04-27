#include "Game.h"

Game::Game()
{
	this->character = Character();
	this->monster = Monster();
}

Game::Game(sf::Texture * texture)
{
	this->character = Character();
	this->monster = Monster();
	//120 lång, en för varje tile på banan
	
	string map = "";//1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890ab
	string mapTile = "";
	ifstream myfile("../Maps/map1.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, map))
		{
			cout << map << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	//map tiles
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			mapTile = map.substr((i * 15) + j, 1);
			this->list[(i * 15) + j] = Tile(texture, mapTile, j * 128, i * 128);
		}
	}
	
}

Game::~Game()
{

}

void Game::update(float sec)
{
	bool moved = false;

	this->character.update(sec);
	this->monster.update(this->character);
	this->checkCollision();
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 15; j++)
		{
			window.draw(list[(i * 15) + j]);
		}
	}

	window.draw(character);

	window.draw(monster);

	window.display();
}

void Game::checkCollision()
{
	if (this->character.getBoundingBox().intersects(this->monster.getBoundingBox()))
	{
		//this->character.getCharacter().setFillColor(sf::Color::Black);
	}

	//if (this->character.getHitbox().intersect(this->monster.getHitbox()))
	//{
	////	this->character
	//	//this->character.getCharacter().setFillColor(sf::Color::Black);
	//}
}
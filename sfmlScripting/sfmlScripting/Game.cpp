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
	string map = "1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890abcdefgh1234567890ab";
	string mapTile = "";

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
	this->character.update(sec);
	this->monster.update(sec);
}

void Game::draw(sf::RenderWindow& window)
{

	window.clear(sf::Color::Yellow);

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
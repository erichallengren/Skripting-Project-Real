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


	//map tiles
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->list[(i * 8) + j] = Tile(texture, i * 128, j * 128);
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

	for (int i = 0; i < 15; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			window.draw(list[(i * 8) + j]);
		}
	}

	window.draw(character);

	window.draw(monster);

	window.display();
}
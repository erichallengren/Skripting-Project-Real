#include "Game.h"

Game::Game()
{
	this->character = Character();
	this->monster = Monster();
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

	window.draw(character);

	window.draw(monster);



	window.display();
}
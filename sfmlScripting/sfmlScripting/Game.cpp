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
	this->checkCollision();
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	window.draw(character);

	window.draw(monster);



	window.display();
}

void Game::checkCollision()
{
	if (this->character.getHitbox().intersect(this->monster.getHitbox()) || this->monster.getHitbox().intersect(this->character.getHitbox()))
	{
		this->character.getCharacter().setFillColor(sf::Color::Black);
	}
}
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
	bool moved = false;

	this->character.update(sec);
	this->monster.update(this->character);
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
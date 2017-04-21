#include "Game.h"

Game::Game()
{
	character = new Character();
}

Game::~Game()
{

}

void Game::update(float sec)
{
	this->character->update(sec);
	//this->monster->update(sec);
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Yellow);

	window.draw(this->character->getCharacter());

	//window.draw(this->monster->getMonster());



	window.display();
}
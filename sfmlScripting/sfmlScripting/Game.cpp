#include "Game.h"

Game::Game()
{
	character = new Character();
}

Game::~Game()
{

}

void Game::update(float deltaTime)
{
	this->character->update(deltaTime);
}

void Game::draw(sf::RenderWindow* window)
{
	window->clear(sf::Color::Yellow);

	window->draw(this->character->getCharacter());




	window->display();
}
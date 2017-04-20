#include "Game.h"

Game::Game()
{
	character = new Character();
}

Game::~Game()
{

}

void Game::update()
{
	this->character->update();
}

void Game::draw(sf::RenderWindow* window)
{
	window->clear(sf::Color::Yellow);

	window->draw(this->character->getCharacter());




	window->display();
}
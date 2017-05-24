#pragma once
#include "Includes.h"
#include "Game.h"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 3
class Menu
{
public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int Select(Game &g);
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

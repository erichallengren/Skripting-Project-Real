#ifndef GAME_H#ifndef GAME_H
#define GAME_H
#include "Includes.h"
#include "Character.h"

class Game
{
private:
	Character* character;

public:
	Game();
	~Game();

	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
};

#endif // !
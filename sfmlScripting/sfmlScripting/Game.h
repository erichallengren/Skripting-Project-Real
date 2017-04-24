#ifndef GAME_H
#define GAME_H
#include "Includes.h"
#include "Character.h"
#include "Monster.h"

class Game
{
private:
	Character character;
	Monster monster;
public:
	Game();
	~Game();

	void update(float sec);
	void draw(sf::RenderWindow& window);
};

#endif // !
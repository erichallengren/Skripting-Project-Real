#ifndef CHARACTER_H
#define CHARACTER_H
#include "Includes.h"

class Character
{
private:
	sf::CircleShape character;
	sf::Vector2f velocity;

	bool goingUp;
public:
	Character();
	~Character();

	void update();
	void move();

	sf::CircleShape getCharacter();
};

#endif // !
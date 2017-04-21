#ifndef CHARACTER_H
#define CHARACTER_H
#include "Includes.h"

class Character
{
private:
	sf::CircleShape character;
	sf::Vector2f velocity;

	int tileSize;
	float moveCD;
public:
	Character();
	~Character();

	void update(float sec);
	void move(float sec);

	sf::CircleShape getCharacter();
};

#endif // !
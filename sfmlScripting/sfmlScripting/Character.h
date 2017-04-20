#ifndef CHARACTER_H
#define CHARACTER_H
#include "Includes.h"

class Character
{
private:
	//time
	float deltaTime;

	sf::CircleShape character;
	sf::Vector2f velocity;

	//jumping
	float jumpPower;
	float gravity;
	float mass;
public:
	Character();
	~Character();

	void update(float deltaTime);
	void move();
	void jump();

	sf::CircleShape getCharacter();
};

#endif // !
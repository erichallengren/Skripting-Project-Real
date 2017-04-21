#ifndef MONSTER_H
#define MONSTER_H
#include "Includes.h"

class Monster
{
private:
	sf::RectangleShape monster;
	sf::Vector2f monsterSize;
	sf::Vector2f velocity;

	float moveCD;
public:
	Monster();
	~Monster();

	void update(float sec);
	void move(float sec);

	sf::RectangleShape getMonster();
};


#endif // !
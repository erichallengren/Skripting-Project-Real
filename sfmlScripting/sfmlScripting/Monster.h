#ifndef MONSTER_H
#define MONSTER_H
#include "Includes.h"

class Monster : public sf::Drawable
{
private:
	//sf::RectangleShape monster;
	sf::RectangleShape monster;
	sf::Vector2f monsterSize;
	sf::Vector2f velocity;

	float moveCD;
public:
	Monster();
	~Monster();

	void update(float sec);
	void move(float sec);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

	//sf::RectangleShape getMonster();
	sf::RectangleShape getMonster();
};


#endif // !
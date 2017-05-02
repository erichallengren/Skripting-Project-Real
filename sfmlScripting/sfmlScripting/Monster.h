#ifndef MONSTER_H
#define MONSTER_H
#include "Includes.h"
#include "Hitbox.h"
#include "Character.h"

class Monster : public sf::Drawable
{
private:
	//sf::RectangleShape monster;
	sf::RectangleShape monster;
	sf::Vector2f monsterSize;
	sf::Vector2f middlePoint;
	sf::Vector2f velocity;
	sf::CircleShape debugMidPoint;

	Hitbox hitbox;
public:
	Monster();
	Monster(sf::Texture * texture, int x = 0, int y = 0);
	~Monster(); 

	void update(Character& character);
	void move(Character& character);
	void checkIfCanAttack();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void updateMiddlePoint();

	//sf::RectangleShape getMonster();
	sf::RectangleShape getMonster();
	Hitbox getHitbox();
	sf::FloatRect getBoundingBox();

	//bool monsterCollision(const Character &other);
};


#endif // !
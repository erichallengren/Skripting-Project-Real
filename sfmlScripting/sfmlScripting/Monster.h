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
	Hitbox hurtbox;
	bool hasAttacked;
public:
	Monster();
	Monster(sf::Texture * texture, int x = 0, int y = 0);
	~Monster(); 

	void update(Character& character, bool nextTo, lua_State * L);
	void move(Character& character, bool nextTo, lua_State * L);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void updateMiddlePoint();

	//sf::RectangleShape getMonster();
	sf::RectangleShape getMonster();
	Hitbox getHitbox();
	Hitbox getHurtbox();
	sf::FloatRect getBoundingBox();
	sf::FloatRect getHurtboxBoundingBox();
	sf::Vector2f getMiddlePoint();
	bool getHasAttacked();

	void setMove(float x, float y);
	void setHasAttacked(bool state);

	//bool monsterCollision(const Character &other);
};


#endif // !
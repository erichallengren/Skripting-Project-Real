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

	bool hasAttacked;

	//attack logick
	bool nextTo;
	bool inside;

public:
	Monster();
	Monster(sf::Texture * texture);
	~Monster();

	void update(Character& character, bool nextTo, lua_State * L, int & score);
	void move(Character& character, bool nextTo, lua_State * L);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	void updateMiddlePoint();
	void newMonster(int score);

	sf::RectangleShape getMonster();
	sf::Vector2f getMiddlePoint();
	bool getHasAttacked();

	void setMove(float x, float y);
	void setHasAttacked(bool state);

	void checkSides(Character& character, int & score);

	//bool monsterCollision(const Character &other);
};


#endif // !
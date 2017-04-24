#ifndef HITBOX_H
#define HITBOX_H
#include "Includes.h"

class Hitbox
{
private:
	sf::FloatRect box;
	sf::Vector2f origin;
	sf::Vector2f position;
public:
	Hitbox();
	~Hitbox();
	void setOrigin(sf::Vector2f origin);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);

	bool intersect(const Hitbox &other);
	void move(sf::Vector2f velocity);
};

#endif // !HITBOX_H
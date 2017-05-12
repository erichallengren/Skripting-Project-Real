#pragma once
#include <SFML\Graphics.hpp>
#include <map>

class AnimatedSprite : public sf::Drawable
{
public:
	AnimatedSprite();
	AnimatedSprite(sf::Texture & spriteSheet, sf::Vector2i frameSize, float frameDuration);
	virtual ~AnimatedSprite();

	void addAnimation(std::string name, sf::Vector2i frames);
	void setAnimation(std::string name);
	void playAnimation(std::string first, std::string then);

	void move(const sf::Vector2f & offset);
	void setPosition(const sf::Vector2f & position);

	void update(float delta);
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite sprite;
	sf::Vector2i frameSize;
	sf::Vector2i sheetSize;
	sf::Vector2i currentAnimation;
	std::string nextAnimation;
	
	int activeFrame;
	float frameDuration;
	float currentFrameDuration;

	std::map<std::string, sf::Vector2i> animations;

};


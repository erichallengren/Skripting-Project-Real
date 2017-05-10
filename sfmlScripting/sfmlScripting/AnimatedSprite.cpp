#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite()
{
	this->frameSize = frameSize;

	sf::Vector2u textureSize = { 0, 0 };
	sheetSize.x = textureSize.x;
	sheetSize.y = textureSize.y;

	this->currentAnimation = { 0, 0 };

	this->activeFrame = 0;
	this->frameDuration = 0;
	this->currentFrameDuration = 0;
}

AnimatedSprite::AnimatedSprite(sf::Texture & spriteSheet, sf::Vector2i frameSize, float frameDuration)
{
	this->sprite.setTexture(spriteSheet, true);
	this->sprite.setScale({4, 4});
	this->frameSize = frameSize;

	sf::Vector2u textureSize = spriteSheet.getSize();
	sheetSize.x = textureSize.x / frameSize.x;
	sheetSize.y = textureSize.y / frameSize.y;

	this->currentAnimation = { 0, 0 };

	this->activeFrame = 0;
	this->frameDuration = frameDuration;
	this->currentFrameDuration = 0;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::addAnimation(std::string name, sf::Vector2i frames)
{
	if (frames.y < frames.x)
		throw "what are you doing?";

	animations.insert_or_assign(name, frames);
}

void AnimatedSprite::setAnimation(std::string name)
{
	auto it = animations.find(name);
	if (it == animations.end())
		throw "animation does not exist";

	currentAnimation = it->second;
}

void AnimatedSprite::playAnimation(std::string first, std::string then)
{
	setAnimation(first);
	nextAnimation = then;
}

void AnimatedSprite::move(const sf::Vector2f & offset)
{
	sprite.move(offset);
}

void AnimatedSprite::setPosition(const sf::Vector2f & position)
{
	this->sprite.setPosition(position);
}

void AnimatedSprite::update(float delta)
{
	currentFrameDuration += delta;
	if (currentFrameDuration > frameDuration)
	{
		currentFrameDuration -= frameDuration;
		activeFrame++;

		if (activeFrame > currentAnimation.y)
		{
			if (nextAnimation != "")
			{
				setAnimation(nextAnimation);
				nextAnimation = "";
			}

			activeFrame = currentAnimation.x;				
		}

		sf::Vector2i framePosition;
		framePosition.x = (activeFrame % sheetSize.x) * frameSize.x;
		framePosition.y = (activeFrame % sheetSize.y) * frameSize.y;

		sprite.setTextureRect(sf::IntRect(framePosition,frameSize));	
	}
}

void AnimatedSprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

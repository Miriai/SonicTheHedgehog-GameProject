#pragma once
#include <box2d/box2d.h>
#include "Animation.h"

class Move
{
public:
	Move() = default;
	Move(b2Body* body, sf::Sprite* sprite, Animation* animation);
	virtual void move(sf::Time deltaTime) = 0;

protected:
	sf::Sprite* m_sprite;
	b2Body* m_body;
	Animation* m_animation;
	sf::Time m_elapsed = {};
	sf::Vector2f m_moveDirection;

private:
};
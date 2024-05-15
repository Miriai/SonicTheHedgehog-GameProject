#pragma once
#include "Characters.h"

class Enemy : public Characters
{
public:
	Enemy(const AnimationData& data, Direction dir, b2World *world, float height, float width);
	void move(sf::Time deltaTime)override;
protected:
	sf::Vector2f m_moveDirection;
private:
};


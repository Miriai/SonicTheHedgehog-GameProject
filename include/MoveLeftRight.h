#pragma once
#include "Move.h"

class MoveLeftRight : public Move
{
public:
	MoveLeftRight(b2Body* body, sf::Sprite* sprite, Animation* animation);
	void move(sf::Time deltaTime) override;

private:
};
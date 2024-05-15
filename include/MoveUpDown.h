#pragma once
#include "Move.h"

class MoveUpDown : public Move
{
public:
	MoveUpDown(b2Body* body, sf::Sprite* sprite, Animation* animation);
	void move(sf::Time deltaTime) override;

private:
};
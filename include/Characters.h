#pragma once
#include "MovingObject.h"

class Characters : public MovingObject
{
public:
	Characters(const AnimationData& data, Direction dir, b2World* world,
		int typeTaxture, float height, float width);

private:
};
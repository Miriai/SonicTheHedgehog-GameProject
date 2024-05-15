#pragma once
#include "MovingObject.h"

template <class T>
class Factory;

class MovingGround : public MovingObject
{

public:
	MovingGround(float height, float width, b2World* world); 
	void move(sf::Time deltaTime)override;

private:
	static bool m_registerit;

};
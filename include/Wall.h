#pragma once
#include "NonAnimationObject.h"

//forward declaration
template <class T>
class Factory;

class Wall : public NonAnimationObject
{
public:
	Wall(float height, float width , b2World* world, char type);
	void update(sf::Time delta) override {};
private:
	static bool m_registerit;

};
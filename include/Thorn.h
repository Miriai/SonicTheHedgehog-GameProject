#pragma once
#include "NonAnimationObject.h"

//forward declaration
template <class T>
class Factory;

class Thorn : public NonAnimationObject
{
public:
	Thorn(float height, float width, b2World* world, char type);
	void update(sf::Time delta) override {};
private:
	static bool m_registerit;

};
#pragma once
#include "StaticObject.h"


//forward declaration
template <class T>
class Factory;

class Ring : public StaticObject
{
public:
	Ring(float height, float width, b2World* world);
private:
	static bool m_registerit;

};
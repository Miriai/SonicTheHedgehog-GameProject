#pragma once
#include "StaticObject.h"

//forward declaration
template <class T>
class Factory;

class Shield : public StaticObject
{
public:
	Shield(float height, float width, b2World* world);
private:
	static bool m_registerit;
};
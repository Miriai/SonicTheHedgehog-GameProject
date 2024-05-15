#pragma once
#include "StaticObject.h"

//forward declaration
template <class T>
class Factory;

class Dimond : public StaticObject
{
public:
	Dimond(float height, float width, b2World* world);

private:
	static bool m_registerit;

};
#pragma once
#include "StaticObject.h"

template <class T>
class Factory;

class Springboard : public StaticObject
{
public:
	Springboard(float height, float width, b2World* world);
	void setIsJump();
private:
	static bool m_registerit;
};
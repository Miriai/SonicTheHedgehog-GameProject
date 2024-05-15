#pragma once
#include "StaticObject.h"

//forward declaration
template <class T>
class Factory;

class Door : public StaticObject
{
public:
	Door(float height, float width, b2World* world);
	void setIsOpenAnimation();
private:
	static bool m_registerit;

};
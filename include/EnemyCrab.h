#pragma once
#include "Enemy.h"
#include "Constant.h"

template <class T>
class Factory;

class EnemyCrab : public Enemy
{
public:
	EnemyCrab( float height, float width, b2World* world );
private:
	static bool m_registerit;
};
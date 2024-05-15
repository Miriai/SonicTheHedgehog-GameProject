#pragma once
#include "Enemy.h"

template <class T>
class Factory;

class EnemyFish : public Enemy
{
public:
	EnemyFish( float height, float width, b2World* world);
private:
	static bool m_registerit;
};
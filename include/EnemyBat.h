#pragma once
#include "Enemy.h"
#include "Constant.h"

template <class T>
class Factory;

class EnemyBat : public Enemy
{
public:
	EnemyBat(float height, float width, b2World* world);
private:
	static bool m_registerit;
};
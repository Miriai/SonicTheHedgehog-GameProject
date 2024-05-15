#include "Enemy.h"

Enemy::Enemy(const AnimationData& data, Direction dir, b2World* world, float height, float width)
	:Characters(data, dir, world, ResourcesAnimation::typeAnimationTexture::a_general,  height, width)
{}
//-----------------------------------------------------------------------------
void Enemy::move(sf::Time deltaTime)
{
	m_elapsed += deltaTime;

	if (m_isFirst)
		m_move = setMove();

	m_move->move(deltaTime);
}
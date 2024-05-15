#include "Move.h"

Move::Move(b2Body* body, sf::Sprite* sprite, Animation* animation)
{
	m_body = body;
	m_animation = animation;
	m_sprite = sprite;
}
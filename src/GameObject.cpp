#include "GameObject.h"
//-----------------------------------------------------------------------------
void GameObject::setLocation(float height, float width)
{
	m_sprite.setPosition(width, height);
}
//-----------------------------------------------------------------------------
bool GameObject::isDisposed() const
{
	return m_isDisposed;
}
//-----------------------------------------------------------------------------
b2Body* GameObject::getBody()
{
	 return m_body;
}
//-----------------------------------------------------------------------------
sf::Sprite GameObject::getSprite()
{
	return m_sprite;
}
//-----------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void GameObject::setDisposed()
{
	m_isDisposed = true;
}
//-----------------------------------------------------------------------------
void GameObject::syncBoxAndSpriteLoc()
{
	b2Vec2 position = m_body->GetPosition();
	auto angle = m_body->GetAngle();

	position *= BOX2D_SCALE;

	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(angle * 56.66f);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f, 
		m_sprite.getTextureRect().height / 2.f);
}
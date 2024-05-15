#include "Animation.h"
#include <iostream>

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite, int typeOfAnimation)
    : m_data(data), m_dir(dir), m_sprite(sprite)
{
    m_animationTime = sf::seconds(0.3f);
    m_sprite.setTexture(ResourcesAnimation::instance().texture(typeOfAnimation));
    update();
}
//-----------------------------------------------------------------------------
void Animation::direction(Direction dir)
{
    if (m_dir == dir )
    {
        return;
    }

    m_index = 0;
    m_dir = dir;
    update();
}
//-----------------------------------------------------------------------------
void Animation::update(sf::Time delta)
{
    m_elapsed += delta;
    if (m_elapsed >= m_animationTime)
    {
        m_elapsed -= m_animationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}
//-----------------------------------------------------------------------------
void Animation::setAnimationSpeed(float speed)
{
    m_animationTime = sf::seconds(speed);
}

//-----------------------------------------------------------------------------
void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
    m_sprite.setOrigin( m_sprite.getTextureRect().width / 2.f, m_sprite.getTextureRect().height / 2.f);
}

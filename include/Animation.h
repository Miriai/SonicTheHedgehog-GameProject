#pragma once
#include <SFML/Graphics.hpp>

#include "Direction.h"
#include "AnimationData.h"
#include "ResourcesAnimation.h"

#include <SFML/Graphics.hpp>

class Animation
{
public:

    Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite, int typeOfAnimation);
    void direction(Direction dir);
    void update(sf::Time delta);
    void setAnimationSpeed(float speed);

private:
    void update();

    int m_index = 0;
    const AnimationData& m_data;
    Direction m_dir = Direction::Up;
    sf::Sprite& m_sprite;
    sf::Time m_animationTime;
    sf::Time m_elapsed = {};
};

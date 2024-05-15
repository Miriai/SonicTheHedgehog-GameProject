#pragma once
#include "AnimationData.h"

class ResourcesAnimation
{
public:
    enum Objects
    {
        Sonic,
        Crab,
        Fish,
        Ring,
        Springboard,
        MovingGround,
        Shield,
        Door,
        Dimond,
        Bat,
        Max,
    };

    enum typeAnimationTexture
    {
        a_sonic,
        a_general
    };

    static ResourcesAnimation& instance();

    ResourcesAnimation(const ResourcesAnimation&) = delete;
    ResourcesAnimation& operator=(const ResourcesAnimation&) = delete;

    const sf::Texture& texture(int index) const;
    const AnimationData& animationData(ResourcesAnimation::Objects object);
  
private:
    ResourcesAnimation();
    std::vector <sf::Texture> m_texture;
    std::vector<AnimationData> m_data;
};

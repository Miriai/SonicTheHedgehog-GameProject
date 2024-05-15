#pragma once

#include <SFML/Graphics.hpp>

enum class Direction
{
    Up,
    Right,
    Left,
    Down,
    Stay,
    Roll,
    Jump,
    Max,
};

enum class MoveType
{
    m_LeftRight,
    m_UpDown,
    None
};

sf::Vector2f toVector(Direction dir);

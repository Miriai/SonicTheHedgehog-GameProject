#pragma once
#include <typeinfo>
#include <map>
#include <typeinfo>
#include <typeindex>
#include "Ring.h"
#include "Enemy.h"
#include "SonicPlayer.h"
#include "Wall.h"
#include "EnemyCrab.h"
#include "EnemyFish.h"
#include "Springboard.h"
#include "Shield.h"
#include "Door.h"
#include "WoodBox.h"
#include "MovingGround.h"
#include "Dimond.h"
#include "Thorn.h"
#include "EnemyBat.h"
#include "ResourcesSounds.h"


// Sample struct for exception throwing
struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(std::string("Unknown collision of ") 
            + typeid(a).name() + " and " + typeid(b).name()) {}
};
void processCollision(GameObject* objectA, GameObject* objectB);

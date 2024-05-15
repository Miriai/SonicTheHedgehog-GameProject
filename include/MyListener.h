#pragma once
#include"CollisionHandling.h"
#include "SonicPlayer.h"

class MyListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
private:
};

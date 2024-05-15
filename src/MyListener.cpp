#include "MyListener.h"


void MyListener::BeginContact(b2Contact* contact)
{
    GameObject* objectA = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
    GameObject* objectB = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (objectA && objectB)
    {
       // std::cout << "CollisionListener::BeginContact " << objectA << " " << objectB << std::endl;
        processCollision(objectA, objectB);
    }

}

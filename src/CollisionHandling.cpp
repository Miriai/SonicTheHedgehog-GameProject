#include "CollisionHandling.h"

namespace // anonymous namespace — the standard way to make function "static"
{
    // primary collision-processing functions
    void playerWall(GameObject* player, GameObject* wall)
    {}
    
    void playerRing(GameObject* player, GameObject* ring)
    {
        // To get the actual types and use them:
        SonicPlayer& r_player = dynamic_cast<SonicPlayer&>(*player);
        Ring& r_ring = static_cast<Ring&>(*ring);

        ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::Ring);
        r_player.increaseRings();
        r_ring.setDisposed();
    }

    void playerEnemy(GameObject* player, GameObject* enemy)
    {
        SonicPlayer& r_player = dynamic_cast<SonicPlayer&>(*player);
        Enemy& r_enemy = static_cast<Enemy&>(*enemy);

        if (!r_player.getIsProtected())
        {
            r_player.setSubLive();
            r_player.setDirection();
            r_player.impulseBack();
            ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::Enemy);
        }
        else
            r_enemy.setDisposed();
    }

    void playerSpringboard(GameObject* player, GameObject* springboard)
    {
        SonicPlayer& r_player = dynamic_cast<SonicPlayer&>(*player);
        Springboard& r_springboard = static_cast<Springboard&>(*springboard);

        r_player.impulsSpringJump();
        r_springboard.setIsJump();
        ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::Spring);
    }

    void playerShield(GameObject* player, GameObject* shield)
    {
        SonicPlayer& r_player = dynamic_cast<SonicPlayer&>(*player);
        Shield& r_shield = static_cast<Shield&>(*shield);

        r_player.setIsProtected(true, 10);
        r_shield.setDisposed();

        ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::Shield);
    }

    void playerDoor(GameObject* player, GameObject* door)
    {
        SonicPlayer& r_player = dynamic_cast<SonicPlayer&>(*player);
        Door& r_door = static_cast<Door&>(*door);

        r_player.setIsFinishLevel(true);
        r_door.setIsOpenAnimation();
    }

    void playerWoodBox(GameObject* player, GameObject* woodBox)
    {}

    void playermovingGround(GameObject* player, GameObject* movingGround)
    {}

    void playerDimond(GameObject* player, GameObject* dimond)
    {
        SonicPlayer& r_player = dynamic_cast<SonicPlayer&>(*player);
        Dimond& r_dimond = static_cast<Dimond&>(*dimond);

        r_player.increaseDimond();
        r_dimond.setDisposed();

        ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::Dimond);
    }

    void playerThorn(GameObject* player, GameObject* thorn)
    {
        SonicPlayer& r_player = dynamic_cast<SonicPlayer&>(*player);
        Thorn& r_thorn = static_cast<Thorn&>(*thorn);

        r_player.setSubLive();
        r_player.setDirection();
        r_player.impulseBack();

        ResourcesSounds::getInstance().playSound(ResourcesSounds::soundType::Enemy);
    }

    // secondary collision-processing functions that just
    // implement symmetry: swap the parameters and call a
    // primary function
    void wallPlayer(GameObject* wall, GameObject* player)
    {
        playerWall(player, wall);
    }

    void ringPlayer(GameObject* ring, GameObject* player)
    {
        playerRing(player, ring);
    }

    void enemyPlayer(GameObject* enemyCrab, GameObject* player)
    {
        playerEnemy(player, enemyCrab);
    }

    void springboardPlayer(GameObject* springboard, GameObject* player)
    {
        playerSpringboard(player, springboard);
    }

    void shieldPlayer(GameObject* shield, GameObject* player)
    {
        playerShield(player, shield);
    }

    void doorPlayer(GameObject* door, GameObject* player)
    {
        playerDoor(player, door);
    }
    void woodBoxPlayer(GameObject* woodBox, GameObject* player)
    {
        playerWoodBox(player, woodBox);
    }

    void movingGroundPlayer(GameObject* movingGroun, GameObject* player)
    {
        playerWoodBox(player, movingGroun);
    }

    void dimondPlayer(GameObject* dimond, GameObject* player)
    {
        playerDimond(player, dimond);
    }

    void thornPlayer(GameObject* thorn, GameObject* player)
    {
        playerThorn(player, thorn);
    }

    using HitFunctionPtr = void (*)(GameObject*, GameObject*);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(SonicPlayer ), typeid(Wall        ))] = &playerWall;
        phm[Key(typeid(Wall        ), typeid(SonicPlayer ))] = &wallPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(Ring        ))] = &playerRing;
        phm[Key(typeid(Ring        ), typeid(SonicPlayer ))] = &ringPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(EnemyCrab   ))] = &playerEnemy;
        phm[Key(typeid(EnemyCrab   ), typeid(SonicPlayer ))] = &enemyPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(EnemyFish   ))] = &playerEnemy;
        phm[Key(typeid(EnemyFish   ), typeid(SonicPlayer ))] = &enemyPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(Springboard ))] = &playerSpringboard;
        phm[Key(typeid(Springboard ), typeid(SonicPlayer ))] = &springboardPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(Shield      ))] = &playerShield;
        phm[Key(typeid(Shield      ), typeid(SonicPlayer ))] = &shieldPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(Door        ))] = &playerDoor;
        phm[Key(typeid(Door        ), typeid(SonicPlayer ))] = &doorPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(WoodBox     ))] = &playerWoodBox;
        phm[Key(typeid(WoodBox     ), typeid(SonicPlayer ))] = &woodBoxPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(MovingGround))] = &playermovingGround;
        phm[Key(typeid(MovingGround), typeid(SonicPlayer ))] = &movingGroundPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(Dimond      ))] = &playerDimond;
        phm[Key(typeid(Dimond      ), typeid(SonicPlayer ))] = &dimondPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(Thorn       ))] = &playerThorn;
        phm[Key(typeid(Thorn       ), typeid(SonicPlayer ))] = &thornPlayer;
        phm[Key(typeid(SonicPlayer ), typeid(EnemyBat    ))] = &playerEnemy;
        phm[Key(typeid(EnemyBat   ), typeid(SonicPlayer  ))] = &enemyPlayer;
 
        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace

void processCollision(GameObject* object1, GameObject* object2)
{
    auto phf = lookup(typeid(*object1), typeid(*object2));

    if (!phf)
    {
        return;
        // throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <experimental/vector>

#include "NonAnimationObject.h"
#include "StaticObject.h"
#include "Constant.h"
#include "Factory.h"

//Forward declaration
class GameObject;
class Rod;
class Wall;
class Ring;

class Board
{
public:
	Board();
	Board(const Board& board); //copy constractor
	~Board() = default;
	void readNameLevelFile();
	std::ifstream openFile(int level);
	void scanMap();
	void resetDataBoard(bool fullReset);
	void checkWhichObejectDelete();
	float getHeight()const;
	float getWidth()const;
	char getCharObject(int height, int width)const;
	void drawStaticObjects(sf::RenderWindow& window)const;
	void scanObjectsIconToMap();
	void createObject(char type, float height, float width);
	void setWorld(b2World *world);
	void syncObjectToWorld();

	void updateStaticAnimation(sf::Time delta);
	bool isWall(char type);

private:

	float m_width,
		  m_height;

	std::ifstream m_boardFile;
	std::vector<std::string> m_levelsFileNames;
	std::vector<std::vector<char>> m_map;
	std::vector<std::shared_ptr<NonAnimationObject>> m_staticNonAnimation;
	std::vector<std::shared_ptr<StaticObject>> m_static;
	b2World* m_world;
	int m_currLevel;

};
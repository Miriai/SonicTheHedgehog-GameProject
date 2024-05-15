#include "GameObject.h"
#include "Board.h"


Board::Board() 
	:m_height(0), m_width(0), m_map(NULL), m_currLevel(0)
{
	m_boardFile.open("Levels.txt");

	if (m_boardFile.fail())
		throw std::out_of_range("Cannot find file, please check the file name and try again.\n");
	readNameLevelFile();
	
}
//-----------------------------------------------------------------------------
void Board::readNameLevelFile()
{
	std::string fileName;

	while (!m_boardFile.eof())
	{
		m_boardFile >> fileName;
		m_levelsFileNames.push_back(fileName);
	}

	m_boardFile.close();
}
//-----------------------------------------------------------------------------
std::ifstream Board::openFile(int level)
{
	if (level > m_levelsFileNames.size())
		exit(EXIT_SUCCESS);

	std::ifstream tempFile;
	tempFile.open(m_levelsFileNames[level]);

	if (tempFile.fail())
		throw std::out_of_range("Cannot find file, please check the file name and try again.\n");

	m_currLevel++;

	return tempFile;
}
//-----------------------------------------------------------------------------
Board::Board(const Board& board)
{
	if (board.getHeight() == 0 || board.getWidth() == 0)
		this->~Board();
	{
		this->m_height = board.getHeight();
		this->m_width = board.getWidth();

		this->m_map.resize((int)board.getHeight());
		this->m_boardFile.close();

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width + 1; j++)
			{
				this->m_map[i].push_back(board.getCharObject(i, j));
			}
		}
	}
}
//-----------------------------------------------------------------------------
void Board::scanMap()
{
	char c;

	m_boardFile = openFile(m_currLevel);
	m_boardFile >> m_height;
	m_boardFile >> std::noskipws >> c;

	m_boardFile >> m_width;
	m_boardFile >> std::noskipws >> c;

	m_map.clear();
	m_map.resize((int)m_height);

	for (int row = 0; row < m_height; row++) {
		for (int col = 0; col < m_width + 1; col++) { //+1 for the '\n'
			m_boardFile >> std::noskipws >> c;
			m_map[row].push_back(c);
		}
	}
}
//-----------------------------------------------------------------------------
float Board::getHeight()const { return m_height; }
//-----------------------------------------------------------------------------
float Board::getWidth()const { return m_width; }
//-----------------------------------------------------------------------------
char Board::getCharObject(int height, int width)const
{
	if (height >= m_height || width >= m_width || width < 0 || height < 0)
		return 'x';

	return m_map[height][width];
}
//-----------------------------------------------------------------------------
void Board::setWorld(b2World* world)
{
	m_world = world;
}
//-----------------------------------------------------------------------------
void Board::syncObjectToWorld()
{
	for (auto& staticNonAnimation : m_staticNonAnimation)
		staticNonAnimation->syncBoxAndSpriteLoc();

	for (auto& staticObject : m_static)
		staticObject->syncBoxAndSpriteLoc();
}
//-----------------------------------------------------------------------------
void Board::updateStaticAnimation(sf::Time delta)
{
	for (auto& staticObject : m_static)
		staticObject->update(delta);
}
//-----------------------------------------------------------------------------
void Board::resetDataBoard(bool fullReset)
{
	if(fullReset)
		m_currLevel = 0;

	for (auto staticNonAnimation : m_staticNonAnimation)
		m_world->DestroyBody(staticNonAnimation->getBody());
	for (auto stati : m_static)
		m_world->DestroyBody(stati->getBody());

	m_staticNonAnimation.clear();
	m_static.clear();
}
//-----------------------------------------------------------------------------
void Board::scanObjectsIconToMap()
{
	for (int height = 0; height < m_height; height++) {
		for (int width = 0; width < m_width; width++) {
			createObject(m_map[height][width], (float)(height * OBJECT_SIZE), 
				(float)(width * OBJECT_SIZE));
		}
	}
}
//-----------------------------------------------------------------------------
void Board::createObject(char type, float height, float width)
{
	if (isWall(type))
	{
		const auto typeObject = std::string(STRING_LENGTH, '#');
		auto object = Factory<NonAnimationObject>::create(typeObject, height , width , m_world, type);
		if (object)
			m_staticNonAnimation.push_back(std::move(object));
	}
	else
	{
		const auto typeObject = std::string(STRING_LENGTH, type);
		auto object = Factory<NonAnimationObject>::create(typeObject, height, width, m_world, type);
		if (object)
			m_staticNonAnimation.push_back(std::move(object));
	}

		const auto typeObject = std::string(STRING_LENGTH, type);
		auto object = Factory<StaticObject>::create(typeObject, height , width , m_world);
		if (object)
			m_static.push_back(std::move(object));
	
}

//-----------------------------------------------------------------------------
void Board::checkWhichObejectDelete()
{
	std::experimental::erase_if(m_staticNonAnimation, [](auto& staticNonAnimation)
		{
			return staticNonAnimation->isDisposed();
		});

	for (auto& staticObject : m_static)
	{
		if (staticObject->isDisposed())
			m_world->DestroyBody(staticObject->getBody());
	}

	std::experimental::erase_if(m_static, [](auto& staticObject)
		{
			return staticObject->isDisposed();
		});

}
//-----------------------------------------------------------------------------
void Board::drawStaticObjects(sf::RenderWindow& window)const
{
	for (auto& staticNonAnimation : m_staticNonAnimation)
		staticNonAnimation->draw(window);

	for (auto& staticObject : m_static)
		staticObject->draw(window);
}

//-----------------------------------------------------------------------------
bool Board::isWall(char type)
{
	if (type == '#' || type == '=' || type == '<' || type == '>' || type == '(' ||
		type == ')' || type == 'W' || type == 'S' || type == 'A')
		return true;

	return false;
	
}

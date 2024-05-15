#include "ResourcesAnimation.h"
#include "Direction.h"
#include <stdexcept>

namespace
{
	AnimationData sonicPlayerData()
	{
		const auto size = sf::Vector2i(150, 150);
		const auto initSpace = sf::Vector2i(0, 0);
		const auto middleSpace = sf::Vector2i(0, 150);

		auto sonicPlayer = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			if (currentStart.x >= 1050)
			{
				currentStart += middleSpace;
				currentStart.x = 0;
			}
			else
				currentStart.x += size.x;

			return currentStart;
		};

		for (int i = 0; i < 80; i++) {
			auto temp = nextStart();

			if ((temp.y >= 0 && temp.y <= 450))
				sonicPlayer.m_data[Direction::Stay].emplace_back(temp, size);

			if ((temp.y == 600 && temp.x >= 300) || (temp.y == 750)) {
				sonicPlayer.m_data[Direction::Right].emplace_back(temp, size);
				sonicPlayer.m_data[Direction::Left].emplace_back(temp, size);
			}
			if (temp.y >= 900 && temp.y <= 1200) {
				sonicPlayer.m_data[Direction::Up].emplace_back(temp, size);
				sonicPlayer.m_data[Direction::Down].emplace_back(temp, size);

			}
			if (temp.x >= 450 && temp.y == 1200)
				sonicPlayer.m_data[Direction::Roll].emplace_back(temp, size);

			if(temp.x == 300 && temp.y == 1350)
				sonicPlayer.m_data[Direction::Jump].emplace_back(temp, size);
		}

		return sonicPlayer;
	}

	AnimationData EnemyCrabData()
	{
		const auto size = sf::Vector2i(100, 68);
		const auto initSpace = sf::Vector2i(-84, 686);

		auto EnemyCrabData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 6; i++)
		{
			auto temp = nextStart();

			if (currentStart.x < 320)
				EnemyCrabData.m_data[Direction::Stay].emplace_back(temp, size);
			else if (currentStart.x > 320)
				EnemyCrabData.m_data[Direction::Right].emplace_back(temp, size);

		}
		return EnemyCrabData;
	}

	AnimationData ringData()
	{
		const auto size = sf::Vector2i(33, 33);
		const auto initSpace = sf::Vector2i(-33, 772);

		auto ringData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 10; i++)
		{
			auto temp = nextStart();

			ringData.m_data[Direction::Stay].emplace_back(temp, size);
		}
		return ringData;
	}

	AnimationData EnemyFishData()
	{
		const auto size = sf::Vector2i(64, 68);
		const auto initSpace = sf::Vector2i(-36, 360);

		auto EnemyFishData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 3; i++)
		{
			auto temp = nextStart();

			EnemyFishData.m_data[Direction::Up].emplace_back(temp, size);
			EnemyFishData.m_data[Direction::Stay].emplace_back(temp, size);

		}
		return EnemyFishData;
	}

	AnimationData springboardData()
	{
		const auto size = sf::Vector2i(67, 67);
		const auto initSpace = sf::Vector2i(-67, 1343);

		auto springboardData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 7; i++)
		{
			auto temp = nextStart();
			if(i == 0)
				springboardData.m_data[Direction::Stay].emplace_back(temp, size);

			springboardData.m_data[Direction::Up].emplace_back(temp, size);

		}
		return springboardData;
	}
	AnimationData movingGroundData()
	{
		const auto size = sf::Vector2i(200, 40);
		const auto initSpace = sf::Vector2i(306, 1370);

		auto springboardData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 1; i++)
		{
			auto temp = nextStart();
			springboardData.m_data[Direction::Right].emplace_back(temp, size);
			springboardData.m_data[Direction::Left].emplace_back(temp, size);
			springboardData.m_data[Direction::Stay].emplace_back(temp, size);


		}
		return springboardData;
	}
	AnimationData shieldData()
	{
		const auto size = sf::Vector2i(53, 53);
		const auto initSpace = sf::Vector2i(652, 1096);

		auto shieldData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.y += size.y;
			return currentStart;
		};

		for (int i = 0; i < 4; i++)
		{
			auto temp = nextStart();
			shieldData.m_data[Direction::Stay].emplace_back(temp, size);
		}
		return shieldData;
	}
	AnimationData doorData()
	{
		const auto size = sf::Vector2i(148, 87);
		const auto initSpace = sf::Vector2i(557, 723);

		auto doorData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.y += size.y;
			return currentStart;
		};

		for (int i = 0; i < 3; i++)
		{
			auto temp = nextStart();
			if (i == 0)
				doorData.m_data[Direction::Stay].emplace_back(temp, size);

			doorData.m_data[Direction::Up].emplace_back(temp, size);


		}
		return doorData;
	}
	AnimationData dimongData()
	{
		const auto size = sf::Vector2i(24, 21);
		const auto initSpace = sf::Vector2i(488, 0);

		auto dimongData = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 8; i++)
		{
			auto temp = nextStart();

			dimongData.m_data[Direction::Stay].emplace_back(temp, size);
		}
		return dimongData;
	}
	AnimationData EnemyBatData()
	{
		const auto size = sf::Vector2i(80, 85);
		const auto initSpace = sf::Vector2i(-80, 230);

		auto EnemyBat = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart.x += size.x;
			return currentStart;
		};

		for (int i = 0; i < 9 ; i++)
		{
			auto temp = nextStart();
			if (i < 8)
			{
				EnemyBat.m_data[Direction::Left].emplace_back(temp, size);
				EnemyBat.m_data[Direction::Right].emplace_back(temp, size);
			}
			else
				EnemyBat.m_data[Direction::Stay].emplace_back(temp, size);

		}
		return EnemyBat;
	}
}

ResourcesAnimation& ResourcesAnimation::instance()
{
	static ResourcesAnimation instance;
	return instance;
}

const sf::Texture& ResourcesAnimation::texture(int index) const
{
	return m_texture[index];
}

const AnimationData& ResourcesAnimation::animationData(ResourcesAnimation::Objects object)
{
	return m_data[object];
}

ResourcesAnimation::ResourcesAnimation()
	: m_data(Max)
{
	sf::Texture temp;

	if (!temp.loadFromFile("playerSonic.png"))
	{
		throw std::runtime_error("Can't load file");
	}
	m_texture.push_back(temp);

	if (!temp.loadFromFile("General.png"))
	{
		throw std::runtime_error("Can't load file");
	}
	m_texture.push_back(temp);


	m_data[Sonic] = sonicPlayerData();
	m_data[Crab] = EnemyCrabData();
	m_data[Fish] = EnemyFishData();
	m_data[Ring] = ringData();
	m_data[Springboard] = springboardData();
	m_data[MovingGround] = movingGroundData();
	m_data[Shield] = shieldData();	
	m_data[Door] = doorData();
	m_data[Dimond] = dimongData();
	m_data[Bat] = EnemyBatData();

	


}

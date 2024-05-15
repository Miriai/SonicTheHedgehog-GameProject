#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constant.h"

//Singleton  
class ResourcesSounds
{
public:
	enum soundType
	{
		Ring,
		Enemy,
		Jump,
		BoostRun,
		GameOver,
		Shield,
		Spring,
		Dimond,
		Background1,
		Background2,
		Background3,
		OnButton,
		Max
	};

	~ResourcesSounds() = default;
	static ResourcesSounds& getInstance();
	void playSound(soundType sound);
	void pauseSound(soundType sound);
	void setValume( float valume);
	void setLoopPlay(soundType sound);

private:
	ResourcesSounds();
	ResourcesSounds(const ResourcesSounds&) = default;
	ResourcesSounds& operator=(const ResourcesSounds&) = default;

	std::map < soundType, sf::SoundBuffer> m_mapSoundBuffer;
	std::map < soundType, sf::Sound > m_mapSound;
};

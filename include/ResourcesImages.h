#pragma once
#include <SFML/Graphics.hpp>

//Singleton 
class ResourcesImages
{
public:
	enum class imageType 
	{
		WallMiddleChar,
		WallLeftChar,
		WallRighteChar,
		IslandMiddleChar,
		IslandLeftChar,
		IslandRighteChar, 
		WallClear,
		Water1,
		Water2,
		Open,
		Thorn,
		PlayButton,
		ExitButton,
		InformationButton,
		SoundOnButton,
		SoundOffButton,
		PlayBigButton,
		ExitBigButton,
		InformationScreen,
		BackGroundLevel1,
		BackGroundLevel2,
		BackGroundLevel3,
		BackGroundLevel4,
		PressEnterToPlay,
		WoodBox,
		GameOver,
		PauseButton
	};

	~ResourcesImages() = default;
	static ResourcesImages& getInstance();
	sf::Texture& getTexture(imageType index);

private:
	ResourcesImages();
	ResourcesImages(const ResourcesImages&) = default;
	ResourcesImages& operator=(const ResourcesImages&) = default;

	std::map <imageType,sf::Texture> m_mapTexture;
};

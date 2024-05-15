#include "ResourcesImages.h"

//Singlton
ResourcesImages::ResourcesImages()
{
	//open textures and check if the opening is ok, if not, throw exception
	if(	!m_mapTexture[imageType::WallMiddleChar    ].loadFromFile("wall2.png")               ||
		!m_mapTexture[imageType::WallLeftChar      ].loadFromFile("wall1.png")               ||
		!m_mapTexture[imageType::WallRighteChar    ].loadFromFile("wall3.png")               ||
		!m_mapTexture[imageType::IslandMiddleChar  ].loadFromFile("wall5.png")               ||
		!m_mapTexture[imageType::IslandLeftChar    ].loadFromFile("wall4.png")               ||
		!m_mapTexture[imageType::IslandRighteChar  ].loadFromFile("wall6.png")               ||
		!m_mapTexture[imageType::WallClear         ].loadFromFile("Wall7.png")               ||
		!m_mapTexture[imageType::Thorn             ].loadFromFile("Thorn.png")               ||
		!m_mapTexture[imageType::Water1            ].loadFromFile("Water1.png")              ||
		!m_mapTexture[imageType::Water2            ].loadFromFile("Water2.png")              ||
		!m_mapTexture[imageType::Open              ].loadFromFile("OpenScreen.JPG")          ||
		!m_mapTexture[imageType::ExitButton        ].loadFromFile("ExitButton.png")          ||
		!m_mapTexture[imageType::InformationButton ].loadFromFile("InformationButton.png")   ||
		!m_mapTexture[imageType::SoundOnButton     ].loadFromFile("SoundOnButton.png")       ||
		!m_mapTexture[imageType::SoundOffButton    ].loadFromFile("SoundOffButton.png")      ||
		!m_mapTexture[imageType::PlayButton        ].loadFromFile("PlayButton.png")          ||
		!m_mapTexture[imageType::PlayBigButton     ].loadFromFile("PlayButtonWithFrame.png") ||
		!m_mapTexture[imageType::ExitBigButton     ].loadFromFile("ExitButtonWithFrame.png") ||
		!m_mapTexture[imageType::InformationScreen ].loadFromFile("informationScreen.png")   ||
		!m_mapTexture[imageType::WoodBox           ].loadFromFile("WoodBox.png")             ||
		!m_mapTexture[imageType::GameOver          ].loadFromFile("GameOver.png")            ||
		!m_mapTexture[imageType::BackGroundLevel1  ].loadFromFile("BackGroundLevel1.JPG")	 ||
		!m_mapTexture[imageType::BackGroundLevel2  ].loadFromFile("BackGroundLevel2.JPG")    ||
		!m_mapTexture[imageType::BackGroundLevel3  ].loadFromFile("BackGroundLevel3.JPG")    ||
		!m_mapTexture[imageType::BackGroundLevel4  ].loadFromFile("BackGroundLevel4.JPG")    ||
		!m_mapTexture[imageType::PressEnterToPlay  ].loadFromFile("PressEnterToPlay.PNG")    ||
		!m_mapTexture[imageType::PauseButton       ].loadFromFile("PauseButton.png" ))
		throw  std::runtime_error("Can't load image file...");


	m_mapTexture.find(imageType::BackGroundLevel1)->second.setRepeated(true);
}
//-----------------------------------------------------------------------------
ResourcesImages& ResourcesImages::getInstance()
{
	static ResourcesImages img;
	return img;
}
//-----------------------------------------------------------------------------
sf::Texture& ResourcesImages::getTexture(imageType index)
{
	return m_mapTexture.find(index)->second;
}

#include "ResourcesSounds.h"
#include <iostream>
//Singlton
ResourcesSounds::ResourcesSounds()
{
	if( !m_mapSoundBuffer[soundType::Ring       ].loadFromFile("CollisionWithCoin.wav"  ) || 
	    !m_mapSoundBuffer[soundType::Enemy      ].loadFromFile("CollisionWithEnemy.wav" ) ||
	    !m_mapSoundBuffer[soundType::Jump       ].loadFromFile("Jump.wav"               ) ||              
	    !m_mapSoundBuffer[soundType::BoostRun   ].loadFromFile("BoostRun.wav"           ) ||    
		!m_mapSoundBuffer[soundType::Spring     ].loadFromFile("CollisionWithSpring.wav") ||
	    !m_mapSoundBuffer[soundType::GameOver   ].loadFromFile("GameOver.wav"           ) ||          
	    !m_mapSoundBuffer[soundType::Shield     ].loadFromFile("CollisionWithShield.wav") ||
	    !m_mapSoundBuffer[soundType::Background1].loadFromFile("BackGroundMusic1.ogg"   ) ||   
	    !m_mapSoundBuffer[soundType::Background2].loadFromFile("BackGroundMusic2.ogg"   ) ||  
	    !m_mapSoundBuffer[soundType::Background3].loadFromFile("BackGroundMusic3.ogg"   ) ||
		!m_mapSoundBuffer[soundType::Dimond     ].loadFromFile("CollisionWithDimond.wav") ||
        !m_mapSoundBuffer[soundType::OnButton   ].loadFromFile("OnButton.ogg"           ))
		throw  std::runtime_error("Can't load sound file...");

	for (auto it = m_mapSoundBuffer.begin(); it != m_mapSoundBuffer.end(); ++it)
		m_mapSound[it->first].setBuffer(m_mapSoundBuffer[it->first]);
}
//-----------------------------------------------------------------------------
ResourcesSounds& ResourcesSounds::getInstance()
{
	static ResourcesSounds sound;
	return sound;
}
//-----------------------------------------------------------------------------
void ResourcesSounds::playSound(soundType sound)
{
	if (m_mapSound.find(sound)->second.getStatus() != sf::Sound::Playing)
		m_mapSound.find(sound)->second.play();
}
//-----------------------------------------------------------------------------
void ResourcesSounds::pauseSound(soundType sound)
{
	m_mapSound.find(sound)->second.pause();
}
void ResourcesSounds::setValume(float valume)
{
	for (auto it = m_mapSound.begin(); it != m_mapSound.end(); ++it)
		it->second.setVolume(valume);

}
//-----------------------------------------------------------------------------
void ResourcesSounds::setLoopPlay(soundType sound)
{
	m_mapSound.find(sound)->second.play();
	m_mapSound.find(sound)->second.setLoop(true);
}
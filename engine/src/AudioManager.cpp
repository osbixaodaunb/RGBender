#include "AudioManager.h"
#include "Log.h"

using namespace engine;

bool AudioManager::init(){
	if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
		return false;

	return true;
}

void AudioManager::update(){

}

void AudioManager::clean(){

}

void AudioManager::playMusic(std::string file, int loops, int channel){
	m_music = Mix_LoadMUS(file.c_str());

	Mix_PlayMusic( m_music, channel );
}

void AudioManager::playChunk(std::string file, int loops, int channel){
	m_sound = Mix_LoadWAV(file.c_str());

	Mix_PlayChannel( channel, m_sound, 0); 
}

void AudioManager::stop(int channel){
	 Mix_HaltMusic();
}

void AudioManager::pause(int channel){

}
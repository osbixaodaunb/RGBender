#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SDL2/SDL_mixer.h"
#include <string>


namespace engine{
	class AudioManager{
	public:
		static AudioManager& Instance(){
			static AudioManager instance;

			return instance;
		}

		bool init();
		void update();
		void clean();
		void playMusic(std::string filename, int loops=-1, int channel=-1);
		void playChunk(std::string filename, int loops=-1, int channel=-1);
		void stop(int channel=-1);
		void pause(int channel=-1);

		inline bool is_music() { return m_is_music; }


	private:
		bool m_is_music;

		//AudioState m_audio_state;
    	Mix_Music * m_music;
		Mix_Chunk * m_sound;

		AudioManager() {}
		~AudioManager() {}

	};

	typedef AudioManager AudioManager;

}

#endif

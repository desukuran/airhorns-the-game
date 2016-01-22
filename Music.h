#pragma once

#include <string>
#include "SDL/SDL_mixer.h"
#include <fstream>
#include <map>
#include "Game.h"

class CMusic
{
public:
	CMusic(void);
	~CMusic(void);
	static int PlaySong(string songname, bool loop, bool rand_pitch);
	static int StopSong(void);
	static int LoadSongs();

	static map<string, string> MusicList;

	//static AudioDevicePtr device;
	static Mix_Music *sound;
};

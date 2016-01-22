#pragma once

#include <string>
#include "SDL/SDL_mixer.h"
#include <fstream>
#include <map>
#include "Game.h"

class CSound
{
public:
	CSound(void);
	~CSound(void);
	static int PlaySound(string songname, bool loop/*, bool rand_pitch*/);
	static int StopSound(void);
	static int LoadSounds();

	static map<string, string> MusicList;

	static Mix_Chunk *sound;
};

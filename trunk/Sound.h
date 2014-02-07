#pragma once

#include <string>
#include "audiere.h"
#include <fstream>
#include <map>
#include "Game.h"

using namespace std;
using namespace audiere;

class CSound
{
public:
	CSound(void);
	~CSound(void);
	static int PlaySound(string songname, bool loop/*, bool rand_pitch*/);
	static int StopSound(void);
	static int LoadSounds();

	static map<string, string> MusicList;

	static AudioDevicePtr device;
	static OutputStreamPtr sound;
};

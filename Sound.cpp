#include "Sound.h"
#include <string>
#include "SDL/SDL_Mixer.h"
#include "DebugMessage.h"

map<string, string> CSound::MusicList;

Mix_Chunk* CSound::sound;

CSound::CSound(void)
{
}

CSound::~CSound(void)
{
}

int CSound::LoadSounds( void )
{
	ifstream file;
	file.open("cfg/sounds.cfg");

	if (!file)
		return 0; //Error loading the songs.cfg

	string songname = "";
	string filename = "";

	getline(file, songname);

	while(!file.eof())
	{
		file >> songname;
		file >> filename;

		MusicList[songname] = filename;
	}

	file.close();

	return 1;
}

int CSound::PlaySound(string songname, bool loop/*, bool rand_pitch*/)
{
	string filename = MusicList[songname];
	string songpath = "sound/" + filename;

	//device = OpenDevice();
	sound = Mix_LoadWAV(songpath.c_str());

	if (!sound) {
		CDebugMessage::AddMessage("Sound: Cannot open "+songname);
		return 0;
	}

	/*if (rand_pitch)
		sound->setPitchShift(CGame::IntRand()%5);
	else*/
		//sound->setPitchShift(1.0f);

	Mix_PlayChannel(0, sound, loop);
	//sound->setRepeat(loop);
	//sound->setVolume(1.0f);

	return 1;
}

int CSound::StopSound()
{
	Mix_HaltChannel(0);
	return 1;
}

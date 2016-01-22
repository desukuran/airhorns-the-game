#include "Music.h"
#include <string>
#include "SDL/SDL_mixer.h"
#include "DebugMessage.h"

map<string, string> CMusic::MusicList;
//AudioDevicePtr CMusic::device;

Mix_Music* CMusic::sound;

CMusic::CMusic(void)
{
}

CMusic::~CMusic(void)
{
}

int CMusic::LoadSongs( void )
{
	ifstream file;
	file.open("cfg/songs.cfg");

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

int CMusic::PlaySong(string songname, bool loop, bool rand_pitch)
{
	string filename = MusicList[songname];
	string songpath = "sound/music/" + filename;

	//device = OpenDevice();
	sound = Mix_LoadMUS(songpath.c_str());

	if (!sound) {
		CDebugMessage::AddMessage("Music: Cannot open "+songname);
		return 0;
	}

	/*if (rand_pitch)
		sound->setPitchShift(CGame::IntRand()%5);
	else
		sound->setPitchShift(1.0f);*/

	Mix_PlayMusic(sound, loop);
	//sound->setRepeat(loop);
	//sound->setVolume(1.0f);

	return 1;
}

int CMusic::StopSong()
{
	Mix_HaltMusic();
	return 1;
}

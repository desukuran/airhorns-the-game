#include "Sound.h"
#include <string>
#include "audiere.h"
#include "DebugMessage.h"

map<string, string> CSound::MusicList;
AudioDevicePtr CSound::device;
OutputStreamPtr CSound::sound;

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

	device = OpenDevice();
	sound = OpenSound(device, songpath.c_str(), false);
      
	if (!sound) {
		CDebugMessage::AddMessage("Music: Cannot open "+songname);
		return 0;
	}

	/*if (rand_pitch)
		sound->setPitchShift(CGame::IntRand()%5);
	else*/
		sound->setPitchShift(1.0f);

	sound->play();
	sound->setRepeat(loop);
	sound->setVolume(1.0f);

	return 1;
}

int CSound::StopSound()
{
	sound->stop();
	return 1;
}
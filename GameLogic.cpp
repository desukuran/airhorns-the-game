#include "GameLogic.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "config.h"
#include "DebugMessage.h"

#include "SDL.h"

using namespace std;

//Resolve Extrernal whatever
SDL_Surface* CGameLogic::screen = NULL;
TTF_Font *CGameLogic::font;
int CGameLogic::ScreenHeight;
int CGameLogic::ScreenWidth;


CGameLogic::CGameLogic(void)
: playing(0)
{
}

CGameLogic::~CGameLogic(void)
{
}

int CGameLogic::DrawTitle(void)
{
	cout << "==========================\nDETHKLAN THE GAME -- 2013\n"; //Obsolete
	return 1;
}

SDL_Surface* CGameLogic::load_image(string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	string target = "img/" + CGame::SpriteList[filename];

	loadedImage = IMG_Load(target.c_str());

	 //If nothing went wrong in loading the image
	if( loadedImage != NULL ) { 
		//Create an optimized image 
		optimizedImage = SDL_DisplayFormatAlpha( loadedImage ); 
		//Free the old image 
		SDL_FreeSurface( loadedImage ); 
	}
	else
		CDebugMessage::AddMessage("IMAGE: Cannot load \"" + filename + "\"");

	return optimizedImage;
}

void CGameLogic::Draw(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
 //Make a temporary rectangle to hold the offsets 
	SDL_Rect offset;

	 offset.x = x; 
	 offset.y = y;

	//Blit the surface 
	 SDL_BlitSurface( source, NULL, destination, &offset );
}

void CGameLogic::DrawText(SDL_Surface* screen, string text, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center)
{
	SDL_Color color = {red, green, blue};
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Rect rect;

	if (!center)
		rect.x = x;
	else
		rect.x = ((CGameLogic::ScreenWidth/2)-(surface->w/2));

	rect.y = y;

	SDL_BlitSurface(surface, NULL, screen, &rect);
    SDL_FreeSurface(surface);
}

void CGameLogic::DrawProgressiveText(SDL_Surface* screen, string text, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center)
{
	//Currently Broken. For now, I am gonna make it call DrawText
	//TODO: Fix.

	CGameLogic::DrawText( screen, text, x, y, red, green, blue, center);

	/*string text1;
	string text2 = text;
	size_t goal = text2.length();

		text1 += text2[0];
		text2.erase(1,0);

		SDL_Color color = {red, green, blue};
		SDL_Surface* surface = TTF_RenderText_Blended(font, text1.c_str(), color);
		SDL_Rect rect;

		if (!center)
			rect.x = x;
		else
			rect.x = ((CGameLogic::ScreenWidth/2)-(surface->w/2));

		rect.y = y;

		SDL_BlitSurface(surface, NULL, screen, &rect);
		SDL_FreeSurface(surface);
		SDL_Delay(1000);*/
}

void CGameLogic::DrawBackground(SDL_Surface* screen, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_FillRect(screen,NULL, SDL_MapRGB(SDL_GetVideoSurface()->format,red,green,blue)); 
}

void CGameLogic::MessageBox(SDL_Surface* screen, string name, string msg)
{
	//TODO: Name. Too Lazy.
	CGameLogic::Draw((CGameLogic::ScreenWidth/2)-(CGameLogic::messagebox->w/2), (CGameLogic::ScreenHeight-CGameLogic::messagebox->h)-(CGameLogic::messagebox->h/32), CGameLogic::messagebox, CGameLogic::screen);
	CGameLogic::DrawText(CGameLogic::screen, msg, (CGameLogic::ScreenWidth/2)-(CGameLogic::messagebox->w/2)+(CGameLogic::messagebox->w/32), (CGameLogic::ScreenHeight)-(CGameLogic::messagebox->h)+(CGameLogic::messagebox->h/32), 0xFF, 0xFF, 0xFF, false);
}

int CGameLogic::InitGame(void)
{
	ifstream indata;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		return 667;
	}
	if (TTF_Init() == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());	
		return 666;
	}

	indata.open("cfg/config.cfg");

	if (!indata)
	{
		//TODO: Less hardcode. Just around the write area, mostly.
		ofstream defaults ("cfg/config.cfg", ofstream::binary);
		char defaulted[32] = "";
		sprintf(defaulted, "%i %i 32", CConfig::defaultWidth, CConfig::defaultHeight);
		printf(defaulted);
		defaults.write(defaulted, sizeof(defaulted));
		defaults.close();

		CGameLogic::ScreenWidth = CConfig::defaultWidth;
		CGameLogic::ScreenHeight = CConfig::defaultHeight;

		screen = SDL_SetVideoMode( CGameLogic::ScreenWidth, CGameLogic::ScreenHeight, 32, SDL_SWSURFACE );
	}
	else
	{
		int width, height, bpp;
		int config[3];

		bool malform = false;

		indata >> width >> height >> bpp;

		config[WIDTH] = width;
		config[HEIGHT] = height;
		config[BPP] = bpp;

		if (config[WIDTH] < 0)
		{
			malform = true;
			config[WIDTH] = CConfig::defaultWidth;
		}

		if (config[HEIGHT] < 0)
		{
			malform = true;
			config[HEIGHT] = CConfig::defaultHeight;
		}

		if (config[BPP] < 0)
		{
			malform = true;
			config[BPP] = 32;
		}

		if (malform)
			CDebugMessage::AddMessage("WARNING: Config is malformed. Loading Default Values.");

		CGameLogic::ScreenWidth = config[WIDTH];
		CGameLogic::ScreenHeight = config[HEIGHT];

		screen = SDL_SetVideoMode( config[WIDTH], config[HEIGHT], config[BPP], SDL_SWSURFACE );
		indata.close();
	}

	string time(__TIME__);
	string date(__DATE__);

	char title_char [256];

	//title_char += cGametitle;

	sprintf(title_char, "Omar Staying %d %d", time.c_str(), date.c_str());

	 //Set the window caption 
	SDL_WM_SetCaption( title_char, NULL );

	font = TTF_OpenFont("cfg/font.ttf", 16);

	if (!font)
	{
		printf(SDL_GetError());
		return 0;
	}

	if (!CMusic::LoadSongs())
		return 0;

	if (!CSound::LoadSounds())
		return 0;

	if (!CGame::LoadImages())
		return 0;

	return 1;
}

void CGameLogic::CleanUp(void)
{
	CGame::FreeImages();
	TTF_CloseFont(font);
	SDL_FreeSurface( screen ); 

	//Quit SDL 
	SDL_Quit(); 
}

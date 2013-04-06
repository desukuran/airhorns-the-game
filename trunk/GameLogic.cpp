#include "GameLogic.h"
#include <iostream>
#include <fstream>
#include <ostream>

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

int CGameLogic::InitGame(void)
{
	ifstream indata;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return 0;
	if (TTF_Init() == -1)
		return 0;
	
	indata.open("cfg/config.cfg");

	if (!indata)
	{
		//TODO: Less hardcode. Just around the write area, mostly.
		ofstream defaults ("cfg/config.cfg", ofstream::binary);
		const char *defaulted = "640 480 32";
		defaults.write(defaulted, 10);
		defaults.close();

		ScreenWidth = 640;
		ScreenHeight = 480;

		screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	}
	else
	{
		int width, height, bpp;
		int config[3];

		indata >> width >> height >> bpp;

		config[WIDTH] = width;
		config[HEIGHT] = height;
		config[BPP] = bpp;

		ScreenWidth = width;
		ScreenHeight = height;

		screen = SDL_SetVideoMode( config[WIDTH], config[HEIGHT], config[BPP], SDL_SWSURFACE );
		indata.close();
	}
	 //Set the window caption 
	SDL_WM_SetCaption( "Omar Staying", NULL );

	font = TTF_OpenFont("cfg/font.ttf", 16);

	if (!font)
	{
		printf(SDL_GetError());
		return 0;
	}

	if (!CMusic::LoadSongs())
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

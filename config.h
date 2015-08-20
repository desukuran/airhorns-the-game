//Configuration class, for release and all that.
//Edit this file to flip some flags.
//Make some functions that change em too if you want.

class CConfig
{
public:
//Debug Flags. Could be used to display text or information. Disable on release, Obviousbly.
static int const debugFlag = 1;
static int const skiptitleFlag = false;

//Pre-release flag, show "Demo" or the like.
static int const preRelease = 1;

/////In-Game Options

//Default Screen Resolution
static int const defaultWidth = 1280;
static int const defaultHeight = 720;

};
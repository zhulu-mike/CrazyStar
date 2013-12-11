#ifndef _UTILS_H_
#define _UTILS_H_

static const char* g_sRedStarImage    = "./image/red.png";
static const char* g_sYellowStarImage = "./image/yellow.png";
static const char* g_sGreenStarImage  = "./image/green.png";
static const char* g_sBlueStarImage   = "./image/blue.png";
static const char* g_sPurpleStarImage = "./image/purple.png";
static const char* g_sBombImage       = "./image/bomb.png";
static const char* g_sMagicImage      = "./image/magic.png";
static const char* g_sBackgroundImage = "./image/bg.png";
static const char* g_sTaoxinImage     = "./image/taoxin.png";
static const char* g_sLevelImage      = "./image/level.png";
static const char* g_sSelectedSound   = "./sound/click.mp3";
static const char* g_gameBackGroundSound   = "./sound/bg.mp3";
static const char* g_mainBackGroundSound   = "./sound/mainbg.mp3";

/*��Ŷ*/
static const char* g_waOSound   = "./sound/wao.mp3";

inline int randLimit(int nMin, int nMax)
{
    assert(nMax != nMin);

    //include max value and min value
    return (rand() % (nMax - nMin + 1) + nMin);
}


#endif

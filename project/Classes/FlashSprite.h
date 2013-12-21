#ifndef _FLASH_SPRITE_H_
#define _FLASH_SPRITE_H_

#include "cocos2d.h"

class FlashSprite : public cocos2d::CCSprite
{
public:
	FlashSprite();
	virtual bool init();
	void play(int count);

	int maxFrame;

	CREATE_FUNC(FlashSprite);
private:
	int tcount;
	float delay;
	int ccount;
	bool isPlay;
	int cframe;

	cocos2d::CCSprite *mc;

	void updateTimeDisplay(float dt);
};

#endif

#include "FlashSprite.h"
#include "ResourceConfig.h"


USING_NS_CC;

FlashSprite::FlashSprite()
	: delay(0.05f)
	, ccount(0)
	, maxFrame(0)
	, cframe(0)
	, mc(NULL)
{
	
}


bool FlashSprite::init()
{
    bool bRet = false;
    do
    {
		CC_BREAK_IF (!CCSprite::init());

		schedule(schedule_selector(FlashSprite::updateTimeDisplay), delay);
		bRet = true;
    }while(0);

    return bRet;
}

void FlashSprite::updateTimeDisplay(float dt)
{
	if (isPlay)
	{

		if (tcount > 0 && tcount <= ccount)
		{
			isPlay = false;
			this->removeFromParent();
			return;
		}
		if (maxFrame <= 0)
		{
			isPlay = false;
			this->removeFromParent();
			return;
		}

		if (mc != NULL)
			mc->removeFromParent();

		mc = CCSprite::create(g_sClickEffectImage,CCRectMake(cframe*70,0,70,50));
		this->addChild(mc);
		
		
		cframe++;
		if (cframe > maxFrame)
		{
			cframe = 0;
			if (tcount > 0)
				ccount++;
		}

	}
}


/*
小于0表示循环播放，大于0表示播放多少次
*/
void FlashSprite::play(int count)
{
	this->tcount = count;
	isPlay = true;
	cframe = 0;
	ccount = 0;
}
#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_

#include "cocos2d.h"



class BackgroundLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();

	void setBackGroundImage(const char *fileimage);

	static void setLifeCount(int count);
	static int getLifeCount();

    CREATE_FUNC(BackgroundLayer);

public:
	cocos2d::CCSprite* bgSprite;
	cocos2d::CCLabelTTF *timeLabel;
private: 
	static int m_nLiftCount;
	/*ÉúÃüµ¹¼ÆÊ±*/
	static int lifeTime;
private:
	 void  updateTimeDisplay(float t);
};

#endif
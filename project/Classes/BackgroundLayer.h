#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_

#include "cocos2d.h"



class BackgroundLayer : public cocos2d::CCLayer
{
public:
	 BackgroundLayer();
    virtual bool init();

	void setBackGroundImage(const char *fileimage);

	void setLifeCount(int count);
	static int getLifeCount();

    CREATE_FUNC(BackgroundLayer);

private:
	cocos2d::CCSprite* bgSprite;
	cocos2d::CCLabelTTF *timeLabel;
private: 
	static int m_nLiftCount;
	/*ÉúÃüµ¹¼ÆÊ±*/
	static int lifeTime;
	static int beginTime;
	static bool haveTimer;
private:
	 void  updateTimeDisplay(float t);
};

#endif
#ifndef _LEVEL_OVER_H_
#define _LEVEL_OVER_H_
#include "cocos2d.h"

class LevelOver : public cocos2d::CCLayer
{
public:
	LevelOver();
	virtual bool init();

	void onShow(bool isPass, int leftCount, int awardScore);

	CREATE_FUNC(LevelOver);
private:
	cocos2d::CCSprite* jieGuo;

	
};

#endif
#ifndef _ACHIEVE_VIEW_H
#define _ACHIEVE_VIEW_H

#include "cocos2d.h"
#include "cocos-ext.h"

class AchieveView:public cocos2d::CCLayer
{
public:
	AchieveView();

	virtual bool init();

	CREATE_FUNC(AchieveView);

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

private:
	void onCommandBack(cocos2d::CCObject * pSender);
	cocos2d::extension::CCScrollView *view;

	float beginY;
	float viewBeginY;
	float beginX;
	float gapY;
	float gapX;






};

#endif
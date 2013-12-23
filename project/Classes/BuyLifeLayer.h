#ifndef _BUYLIFE_LAYER_H_
#define _BUYLIFE_LAYER_H_

#include "cocos2d.h"

class BuyLifeLayer : public cocos2d::CCLayer
{
public:
    BuyLifeLayer();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void onCommandBack(cocos2d::CCObject * pSender);
	void onCommandBuy2(cocos2d::CCObject * pSender);
	void onCommandBuy5(cocos2d::CCObject * pSender);
	void onCommandBuy21(cocos2d::CCObject * pSender);
	void onCommandBuy60(cocos2d::CCObject * pSender);
	void onCommandBuy130(cocos2d::CCObject * pSender);
	CREATE_FUNC(BuyLifeLayer);
    virtual bool init();

	void onShow();

private:
	void addLifeCount(int count);

	float beginY;
    
};

#endif
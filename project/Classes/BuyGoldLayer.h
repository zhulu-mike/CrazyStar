#ifndef _BUYGOLD_LAYER_H_
#define _BUYGOLD_LAYER_H_

#include "cocos2d.h"

class BuyGoldLayer : public cocos2d::CCLayer
{
public:
    BuyGoldLayer();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void onCommandBack(cocos2d::CCObject * pSender);
	void onCommandBuy1(cocos2d::CCObject * pSender);
	void onCommandBuy2(cocos2d::CCObject * pSender);
	void onCommandBuy3(cocos2d::CCObject * pSender);
	void onCommandBuy4(cocos2d::CCObject * pSender);
	CREATE_FUNC(BuyGoldLayer);
    virtual bool init();


private:
	void addGoldCount(int count);

	float beginY;
    
};

#endif
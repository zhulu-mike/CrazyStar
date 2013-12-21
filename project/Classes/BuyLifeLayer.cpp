
#include "BuyLifeLayer.h"
#include "ResourceConfig.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;


BuyLifeLayer::BuyLifeLayer()
{

}

bool BuyLifeLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF (!CCLayer::init());
		CCSprite *p = CCSprite::create(g_sPanelBGImage);
		CCSize ps = p->getContentSize();

        
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		CCScale9Sprite * bg = CCScale9Sprite::create(g_sPanelBGImage,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		bg->setPreferredSize(CCSizeMake(s.width,s.height));
		this->setTouchEnabled(true);
		this->setTouchPriority(-999);

		p = CCSprite::create(g_sPanelBGImage2);
		ps = p->getContentSize();
		bg = CCScale9Sprite::create(g_sPanelBGImage2,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		bg->setPreferredSize(CCSizeMake(s.width-20,s.height-20));
		bg->setPositionX(10);
		bg->setPositionY(10);


		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,this->getTouchPriority(),true);
		bRet = true;

    }while(0);

    return bRet;
}

void BuyLifeLayer::onShow()
{
}

bool BuyLifeLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}
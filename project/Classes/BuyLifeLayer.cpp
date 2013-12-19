
#include "BuyLifeLayer.h"
#include "ResourceConfig.h"
USING_NS_CC;


BuyLifeLayer::BuyLifeLayer()
{

}

bool BuyLifeLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF (!CCLayer::init());

        
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		CCSprite * bg = CCSprite::create(g_sBuyLifeBGImage,CCRectMake(0,0,s.width,s.height));
		this->addChild(bg);
		bg->setScaleX(s.width/bg->getTextureRect().size.width);
		bg->setScaleY(s.height/bg->getTextureRect().size.height);
		bg->setAnchorPoint(ccp(0,0));
		
		
		bRet = true;

    }while(0);

    return bRet;
}

void BuyLifeLayer::onShow()
{
}
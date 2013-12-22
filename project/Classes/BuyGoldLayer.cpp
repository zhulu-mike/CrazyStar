
#include "BuyGoldLayer.h"
#include "ResourceConfig.h"
#include "MyCCMenu.h"
#include "GameScene.h"
#include "BackgroundLayer.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;


BuyGoldLayer::BuyGoldLayer()
	: beginY(40.0f)
{

}

bool BuyGoldLayer::init()
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
		bg->setPreferredSize(CCSizeMake(s.width,s.height-beginY));
		this->setTouchEnabled(true);
		this->setTouchPriority(-1999);

		p = CCSprite::create(g_sPanelBGImage2);
		ps = p->getContentSize();
		bg = CCScale9Sprite::create(g_sPanelBGImage2,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		bg->setPreferredSize(CCSizeMake(s.width-20,s.height-20-beginY));
		bg->setPositionX(10);
		bg->setPositionY(10);

		CCMenuItemImage * back = CCMenuItemImage::create(g_sBackButtonUpBGImage,g_sBackButtonDownBGImage,
														this, 
														menu_selector(BuyGoldLayer::onCommandBack));
		back->setAnchorPoint(ccp(0,1));

		MyCCMenu * backMenu = MyCCMenu::create(back,NULL);
		this->addChild(backMenu);
		backMenu->setPositionX(28);
		backMenu->setPositionY(1000-beginY);
		backMenu->setTouchPriority(-2000);

		CCSprite * t2 = CCSprite::create(g_sBuyGoldBGImage);
		t2->setAnchorPoint(ccp(0,1));
		t2->setPosition(ccp(152,913-beginY));
		this->addChild(t2);

		CCMenuItemImage * buy2 = CCMenuItemImage::create(g_sBuyGoldButtonUpBGImage,g_sBuyGoldButtonDownBGImage,
														this, 
														menu_selector(BuyGoldLayer::onCommandBuy1));
		buy2->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy2Menu = MyCCMenu::create(buy2,NULL);
		this->addChild(buy2Menu);
		buy2Menu->setPositionX(172);
		buy2Menu->setPositionY(713-beginY);
		buy2Menu->setTouchPriority(-2000);

		CCSprite * t5 = CCSprite::create(g_sBuyGoldBGImage1);
		t5->setAnchorPoint(ccp(0,1));
		t5->setPosition(ccp(509,913-beginY));
		this->addChild(t5);


		CCMenuItemImage * buy5 = CCMenuItemImage::create(g_sBuyGoldButtonUpBGImage,g_sBuyGoldButtonDownBGImage,
														this, 
														menu_selector(BuyGoldLayer::onCommandBuy2));
		buy5->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy5Menu = MyCCMenu::create(buy5,NULL);
		this->addChild(buy5Menu);
		buy5Menu->setPositionX(539);
		buy5Menu->setPositionY(713-beginY);
		buy5Menu->setTouchPriority(-2000);

		CCSprite * t21 = CCSprite::create(g_sBuyGoldBGImage2);
		t21->setAnchorPoint(ccp(0,1));
		t21->setPosition(ccp(152,458-beginY));
		this->addChild(t21);

		CCMenuItemImage * buy21 = CCMenuItemImage::create(g_sBuyGoldButtonUpBGImage,g_sBuyGoldButtonDownBGImage,
														this, 
														menu_selector(BuyGoldLayer::onCommandBuy3));
		buy21->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy21Menu = MyCCMenu::create(buy21,NULL);
		this->addChild(buy21Menu);
		buy21Menu->setPositionX(172);
		buy21Menu->setPositionY(260-beginY);
		buy21Menu->setTouchPriority(-2000);

		CCSprite * t60 = CCSprite::create(g_sBuyGoldBGImage3);
		t60->setAnchorPoint(ccp(0,1));
		t60->setPosition(ccp(509,458-beginY));
		this->addChild(t60);

		CCMenuItemImage * buy60 = CCMenuItemImage::create(g_sBuyGoldButtonUpBGImage,g_sBuyGoldButtonDownBGImage,
														this, 
														menu_selector(BuyGoldLayer::onCommandBuy4));
		buy60->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy60Menu = MyCCMenu::create(buy60,NULL);
		this->addChild(buy60Menu);
		buy60Menu->setPositionX(539);
		buy60Menu->setPositionY(260-beginY);
		buy60Menu->setTouchPriority(-2000);


		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,this->getTouchPriority(),true);
		bRet = true;

    }while(0);

    return bRet;
}


bool BuyGoldLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void BuyGoldLayer::onCommandBack(CCObject * pSender)
{
	GameScene::sharedGameScene()->hideBuyGoldLayer();
}

void BuyGoldLayer::onCommandBuy1(CCObject * pSender)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
		addGoldCount(20);
}
void BuyGoldLayer::onCommandBuy2(CCObject * pSender)
{	
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
		addGoldCount(60);
}
void BuyGoldLayer::onCommandBuy3(CCObject * pSender)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
		addGoldCount(140);
}
void BuyGoldLayer::onCommandBuy4(CCObject * pSender)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	addGoldCount(300);
}

void BuyGoldLayer::addGoldCount(int count)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	layer->addGoldCount(count);
}
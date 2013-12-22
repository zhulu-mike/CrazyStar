
#include "BuyLifeLayer.h"
#include "ResourceConfig.h"
#include "MyCCMenu.h"
#include "GameScene.h"
#include "BackgroundLayer.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;


BuyLifeLayer::BuyLifeLayer()
	: beginY(40.0f)
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
		bg->setPreferredSize(CCSizeMake(s.width,s.height-beginY));
		this->setTouchEnabled(true);
		this->setTouchPriority(-999);

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
														menu_selector(BuyLifeLayer::onCommandBack));
		back->setAnchorPoint(ccp(0,1));

		MyCCMenu * backMenu = MyCCMenu::create(back,NULL);
		this->addChild(backMenu);
		backMenu->setPositionX(28);
		backMenu->setPositionY(1000-beginY);
		backMenu->setTouchPriority(-1000);

		CCSprite * t2 = CCSprite::create(g_sBigLifeBGImage);
		t2->setAnchorPoint(ccp(0,1));
		t2->setPosition(ccp(82,890-beginY));
		this->addChild(t2);

		CCSprite * price2 = CCSprite::create(g_sBuy2BGImage);
		price2->setAnchorPoint(ccp(0,1));
		price2->setPosition(ccp(157,889-beginY));
		this->addChild(price2);

		CCSprite * coin2 = CCSprite::create(g_sGoldBGImage);
		coin2->setAnchorPoint(ccp(0,1));
		coin2->setPosition(ccp(392,891-beginY));
		this->addChild(coin2);

		CCMenuItemImage * buy2 = CCMenuItemImage::create(g_sOkButtonUpBGImage,g_sOkButtonDownBGImage,
														this, 
														menu_selector(BuyLifeLayer::onCommandBuy2));
		buy2->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy2Menu = MyCCMenu::create(buy2,NULL);
		this->addChild(buy2Menu);
		buy2Menu->setPositionX(534);
		buy2Menu->setPositionY(907-beginY);
		buy2Menu->setTouchPriority(-1000);

		CCSprite * t5 = CCSprite::create(g_sBigLifeBGImage);
		t5->setAnchorPoint(ccp(0,1));
		t5->setPosition(ccp(82,719-beginY));
		this->addChild(t5);

		CCSprite * price5 = CCSprite::create(g_sBuy5BGImage);
		price5->setAnchorPoint(ccp(0,1));
		price5->setPosition(ccp(157,718-beginY));
		this->addChild(price5);

		CCSprite * coin5 = CCSprite::create(g_sGoldBGImage);
		coin5->setAnchorPoint(ccp(0,1));
		coin5->setPosition(ccp(392,723-beginY));
		this->addChild(coin5);

		CCMenuItemImage * buy5 = CCMenuItemImage::create(g_sOkButtonUpBGImage,g_sOkButtonDownBGImage,
														this, 
														menu_selector(BuyLifeLayer::onCommandBuy5));
		buy5->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy5Menu = MyCCMenu::create(buy5,NULL);
		this->addChild(buy5Menu);
		buy5Menu->setPositionX(534);
		buy5Menu->setPositionY(736-beginY);
		buy5Menu->setTouchPriority(-1000);

		CCSprite * t21 = CCSprite::create(g_sBigLifeBGImage);
		t21->setAnchorPoint(ccp(0,1));
		t21->setPosition(ccp(82,550-beginY));
		this->addChild(t21);

		CCSprite * price21 = CCSprite::create(g_sBuy21BGImage);
		price21->setAnchorPoint(ccp(0,1));
		price21->setPosition(ccp(152,550-beginY));
		this->addChild(price21);

		CCSprite * coin21 = CCSprite::create(g_sGoldBGImage);
		coin21->setAnchorPoint(ccp(0,1));
		coin21->setPosition(ccp(439,553-beginY));
		this->addChild(coin21);

		CCMenuItemImage * buy21 = CCMenuItemImage::create(g_sOkButtonUpBGImage,g_sOkButtonDownBGImage,
														this, 
														menu_selector(BuyLifeLayer::onCommandBuy21));
		buy21->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy21Menu = MyCCMenu::create(buy21,NULL);
		this->addChild(buy21Menu);
		buy21Menu->setPositionX(534);
		buy21Menu->setPositionY(569-beginY);
		buy21Menu->setTouchPriority(-1000);

		CCSprite * t60 = CCSprite::create(g_sBigLifeBGImage);
		t60->setAnchorPoint(ccp(0,1));
		t60->setPosition(ccp(82,358-beginY));
		this->addChild(t60);

		CCSprite * price60 = CCSprite::create(g_sBuy60BGImage);
		price60->setAnchorPoint(ccp(0,1));
		price60->setPosition(ccp(163,367-beginY));
		this->addChild(price60);

		CCSprite * coin60 = CCSprite::create(g_sGoldBGImage);
		coin60->setAnchorPoint(ccp(0,1));
		coin60->setPosition(ccp(455,364-beginY));
		this->addChild(coin60);

		CCMenuItemImage * buy60 = CCMenuItemImage::create(g_sOkButtonUpBGImage,g_sOkButtonDownBGImage,
														this, 
														menu_selector(BuyLifeLayer::onCommandBuy60));
		buy60->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy60Menu = MyCCMenu::create(buy60,NULL);
		this->addChild(buy60Menu);
		buy60Menu->setPositionX(534);
		buy60Menu->setPositionY(378-beginY);
		buy60Menu->setTouchPriority(-1000);

		CCSprite * t130 = CCSprite::create(g_sBigLifeBGImage);
		t130->setAnchorPoint(ccp(0,1));
		t130->setPosition(ccp(82,173-beginY));
		this->addChild(t130);

		CCSprite * price130 = CCSprite::create(g_sBuy130BGImage);
		price130->setAnchorPoint(ccp(0,1));
		price130->setPosition(ccp(162,175-beginY));
		this->addChild(price130);

		CCSprite * coin130 = CCSprite::create(g_sGoldBGImage);
		coin130->setAnchorPoint(ccp(0,1));
		coin130->setPosition(ccp(480,177-beginY));
		this->addChild(coin130);

		CCMenuItemImage * buy130 = CCMenuItemImage::create(g_sOkButtonUpBGImage,g_sOkButtonDownBGImage,
														this, 
														menu_selector(BuyLifeLayer::onCommandBuy130));
		buy130->setAnchorPoint(ccp(0,1));
		MyCCMenu * buy130Menu = MyCCMenu::create(buy130,NULL);
		this->addChild(buy130Menu);
		buy130Menu->setPositionX(534);
		buy130Menu->setPositionY(193-beginY);
		buy130Menu->setTouchPriority(-1000);


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

void BuyLifeLayer::onCommandBack(CCObject * pSender)
{
	GameScene::sharedGameScene()->hideBuyLifeLayer();
}

void BuyLifeLayer::onCommandBuy2(CCObject * pSender)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	if (layer->subGoldCount(10))
		addLifeCount(2);
	else
		GameScene::sharedGameScene()->showBuyGoldLayer();
}
void BuyLifeLayer::onCommandBuy5(CCObject * pSender)
{	
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	if (layer->subGoldCount(25))
		addLifeCount(5);
	else
		GameScene::sharedGameScene()->showBuyGoldLayer();
}
void BuyLifeLayer::onCommandBuy21(CCObject * pSender)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	if (layer->subGoldCount(100))
		addLifeCount(21);
	else
		GameScene::sharedGameScene()->showBuyGoldLayer();
}
void BuyLifeLayer::onCommandBuy60(CCObject * pSender)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	if (layer->subGoldCount(250))
		addLifeCount(60);
	else
		GameScene::sharedGameScene()->showBuyGoldLayer();
}
void BuyLifeLayer::onCommandBuy130(CCObject * pSender)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	if (layer->subGoldCount(500))
		addLifeCount(130);
	else
		GameScene::sharedGameScene()->showBuyGoldLayer();
}

void BuyLifeLayer::addLifeCount(int count)
{
	BackgroundLayer* layer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	layer->addLifeCount(count);
}
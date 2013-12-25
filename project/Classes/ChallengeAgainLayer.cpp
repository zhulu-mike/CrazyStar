
#include "ChallengeAgainLayer.h"
#include "ResourceConfig.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "NumberSprite.h"

USING_NS_CC;
using namespace CocosDenshion;


ChallengeAgainLayer::ChallengeAgainLayer()
{

}

bool ChallengeAgainLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF (!CCLayer::init());

        
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		CCSprite * bg = CCSprite::create(g_sAlertBGImage,CCRectMake(0,0,s.width,s.height));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));

		this->setTouchEnabled(true);
		this->setTouchPriority(-999);
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,this->getTouchPriority(),true);
		

		bRet = true;

    }while(0);

    return bRet;
}

bool ChallengeAgainLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}



void ChallengeAgainLayer::onShow(int round, int need)
{
	float totalWidth = 0.0;
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCSprite *app1 = CCSprite::create(g_sRelifeBGImage);
	app1->setAnchorPoint(ccp(0,0));
	app1->setPositionX(30);
	app1->setPositionY(s.height*0.5);
	this->addChild(app1);
	totalWidth += app1->getContentSize().width;

	NumberSprite * roundTip = NumberSprite::create("white72",round);
	roundTip->setAnchorPoint(ccp(0,0));
	roundTip->setPositionX(app1->getPositionX()+app1->getContentSize().width);
	roundTip->setPositionY(app1->getPositionY());
	this->addChild(roundTip);
	totalWidth += roundTip->getContentSize().width;

	CCSprite *app2 = CCSprite::create(g_sGuanBGImage);
	app2->setAnchorPoint(ccp(0,0));
	app2->setPositionX(roundTip->getPositionX()+roundTip->getContentSize().width);
	app2->setPositionY(roundTip->getPositionY());
	this->addChild(app2);
	totalWidth += app2->getContentSize().width;

	float bx = (s.width - totalWidth)*0.5;
	app1->setPositionX(bx);
	roundTip->setPositionX(app1->getPositionX()+app1->getContentSize().width);
	app2->setPositionX(roundTip->getPositionX()+roundTip->getContentSize().width);

	CCSprite *app3 = CCSprite::create(g_sLifeNeedBGImage);
	app3->setAnchorPoint(ccp(0,0));
	app3->setPositionX(app1->getPositionX());
	app3->setPositionY(app2->getPositionY()-app2->getContentSize().height-20);
	this->addChild(app3);

	NumberSprite * needTip = NumberSprite::create("white72",need);
	needTip->setAnchorPoint(ccp(0,0));
	needTip->setPositionX(app3->getPositionX()+app3->getContentSize().width);
	needTip->setPositionY(app3->getPositionY());
	this->addChild(needTip);

	CCSprite *app4 = CCSprite::create(g_sLifeValueBGImage);
	app4->setAnchorPoint(ccp(0,0));
	app4->setPositionX(needTip->getPositionX()+needTip->getContentSize().width);
	app4->setPositionY(needTip->getPositionY());
	this->addChild(app4);

	CCMenuItemImage* pSureMenu = CCMenuItemImage::create(
                                                g_sSureBGImage, 
                                                g_sSureBGImage, 
                                                this, 
                                                menu_selector(ChallengeAgainLayer::onCommandSure));
	pSureMenu->setAnchorPoint(ccp(0,0));
	CCMenu* pMenu = CCMenu::create(pSureMenu, NULL);
    this->addChild(pMenu);
	pMenu->setTouchPriority(-1000);
	pMenu->setAnchorPoint(ccp(0,0));
	pMenu->setPositionY(app4->getPositionY()-app4->getTextureRect().size.height-40);
	pMenu->setPositionX(100);


	CCSprite * img = CCSprite::create(g_sReturnBGImage);
	CCMenuItemImage* pReturnMenu = CCMenuItemImage::create(
                                                g_sReturnBGImage, 
                                                g_sReturnBGImage, 
                                                this, 
                                                menu_selector(ChallengeAgainLayer::onCommandReturn));
	pReturnMenu->setAnchorPoint(ccp(0,0));
	CCMenu* pMenu2 = CCMenu::create(pReturnMenu, NULL);
    this->addChild(pMenu2);
	pMenu2->setTouchPriority(-1000);
	pMenu2->setAnchorPoint(ccp(0,0));
	pMenu2->setPositionY(pMenu->getPositionY());
	pMenu2->setPositionX(s.width-img->getTextureRect().size.width-100);
}

void ChallengeAgainLayer::onCommandSure(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
	GameLayer*app = (GameLayer*)GameScene::sharedGameScene()->getMainGameLayer();
	app->relife();
}

void ChallengeAgainLayer::onCommandReturn(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
	GameLayer*app = (GameLayer*)GameScene::sharedGameScene()->getMainGameLayer();
	app->hideChallengeAgainLayer();
	GameScene::sharedGameScene()->switchToMainMenu();
}
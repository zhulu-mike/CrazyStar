
#include "ChallengeAgainLayer.h"
#include "ResourceConfig.h"
#include "GameScene.h"
#include "GameLayer.h"

USING_NS_CC;


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
		CCSprite * bg = CCSprite::create(g_sAlertBGImage);
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		
		
		bRet = true;

    }while(0);

    return bRet;
}

void ChallengeAgainLayer::onShow(int round, int need)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCSprite *app1 = CCSprite::create(g_sRelifeBGImage);
	app1->setAnchorPoint(ccp(0,0));
	app1->setPositionX(10);
	app1->setPositionY(s.height*0.5);
	this->addChild(app1);


	CCSprite *app2 = CCSprite::create(g_sGuanBGImage);
	app2->setAnchorPoint(ccp(0,0));
	app2->setPositionX(app1->getPositionX()+app1->getTextureRect().size.width);
	app2->setPositionY(app1->getPositionY());
	this->addChild(app2);

	CCSprite *app3 = CCSprite::create(g_sLifeNeedBGImage);
	app3->setAnchorPoint(ccp(0,0));
	app3->setPositionX(app1->getPositionX());
	app3->setPositionY(app2->getPositionY()-app2->getTextureRect().size.height-20);
	this->addChild(app3);

	CCSprite *app4 = CCSprite::create(g_sLifeValueBGImage);
	app4->setAnchorPoint(ccp(0,0));
	app4->setPositionX(app3->getPositionX()+app3->getTextureRect().size.width);
	app4->setPositionY(app3->getPositionY());
	this->addChild(app4);

	CCMenuItemImage* pSureMenu = CCMenuItemImage::create(
                                                g_sSureBGImage, 
                                                g_sSureBGImage, 
                                                this, 
                                                menu_selector(ChallengeAgainLayer::onCommandSure));
	CCMenu* pMenu = CCMenu::create(pSureMenu, NULL);
    pMenu->alignItemsVertically();
    this->addChild(pMenu);
	pMenu->setAnchorPoint(ccp(0,0));
	pMenu->setPositionY(app4->getPositionY()-app4->getTextureRect().size.height-20);
	pMenu->setPositionX(app3->getPositionX());


	CCSprite * img = CCSprite::create(g_sReturnBGImage);
	CCMenuItemImage* pReturnMenu = CCMenuItemImage::create(
                                                g_sReturnBGImage, 
                                                g_sReturnBGImage, 
                                                this, 
                                                menu_selector(ChallengeAgainLayer::onCommandReturn));
	CCMenu* pMenu2 = CCMenu::create(pReturnMenu, NULL);
    pMenu2->alignItemsVertically();
    this->addChild(pMenu2);
	pMenu2->setAnchorPoint(ccp(0,0));
	pMenu2->setPositionY(pMenu->getPositionY());
	pMenu2->setPositionX(s.width-img->getTextureRect().size.width);
}

void ChallengeAgainLayer::onCommandSure(CCObject* pSender)
{

}

void ChallengeAgainLayer::onCommandReturn(CCObject* pSender)
{

	GameLayer*app = (GameLayer*)GameScene::sharedGameScene()->getMainGameLayer();
	app->hideChallengeAgainLayer();
	GameScene::sharedGameScene()->switchToMainMenu();
}
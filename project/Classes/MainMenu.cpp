#include "MainMenu.h"
#include <SimpleAudioEngine.h>
#include "GameScene.h"
#include "ResourceConfig.h"
#include "BackgroundLayer.h"
#include "FlashSprite.h"
#include "MyCCMenu.h"

USING_NS_CC;
using namespace CocosDenshion;

bool MainMenu::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!CCLayer::init());

		CCSize s = CCDirector::sharedDirector()->getWinSize();

        CCMenuItemImage* pStartMenu = CCMenuItemImage::create(
                                                g_sBeginImage, 
                                                g_sBeginImage, 
                                                this, 
                                                menu_selector(MainMenu::onCommandStart));
        CC_BREAK_IF(!pStartMenu);
		CCMenuItemImage* pGoonMenu = CCMenuItemImage::create(
                                                g_sGoonBGImage, 
                                                g_sGoonBGImage, 
                                                this, 
                                                menu_selector(MainMenu::onCommandGoon));
		CC_BREAK_IF(!pGoonMenu);
		CCMenuItemImage* pHelpMenu = CCMenuItemImage::create(
                                                g_sHelpBGImage, 
                                                g_sHelpBGImage, 
                                                this, 
                                                menu_selector(MainMenu::onCommandHelp));
		CC_BREAK_IF(!pHelpMenu);

        MyCCMenu* pMenu = MyCCMenu::create(pStartMenu,pGoonMenu,pHelpMenu, NULL);
        CC_BREAK_IF(!pMenu);
		pMenu->alignItemsVerticallyWithPadding(15);

        this->addChild(pMenu, 0);

		CCMenuItemImage * sign = CCMenuItemImage::create(
                                                g_sSignBGImage, 
                                                g_sSignBGImage, 
                                                this, 
                                                menu_selector(MainMenu::onCommandSign));
		CCMenuItemImage * achiev = CCMenuItemImage::create(
                                                g_sChengJiuBGImage, 
                                                g_sChengJiuBGImage, 
                                                this, 
                                                menu_selector(MainMenu::onCommandAchieve));
		sign->setAnchorPoint(ccp(0,0));
		achiev->setAnchorPoint(ccp(0,0));
		MyCCMenu * buttomMenu = MyCCMenu::create(sign,achiev,NULL);
		this->addChild(buttomMenu);
		buttomMenu->alignItemsHorizontally();
		buttomMenu->setAnchorPoint(ccp(0,0));
		buttomMenu->setPositionY(s.height*0.5-300);
		buttomMenu->setPositionX(100);

        bRet = true;
    }while(0);

    return true;
}

void MainMenu::onEnter()
{
    CCLayer::onEnter();

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(g_sMainBackGroundSound, true);
}

void MainMenu::onExit()
{
    CCLayer::onExit();

    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void MainMenu::onCommandStart(CCObject* pSender)
{
	addClickFlash(pSender);
    GameScene::sharedGameScene()->switchToGameLayer();
}

void MainMenu::onCommandExit(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");

	#else
		CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
#endif
}

void MainMenu::onCommandSign(CCObject* pSender)
{
	addClickFlash(pSender);
}

void MainMenu::onCommandAchieve(CCObject* pSender)
{
	addClickFlash(pSender);
	GameScene::sharedGameScene()->showAchieveViewLayer();
}

void MainMenu::onCommandGoon(CCObject* pSender)
{
	addClickFlash(pSender);
    BackgroundLayer* pBgLayer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
    if (pBgLayer->subLifeCount(1))  
    {
        GameScene::sharedGameScene()->switchToGameLayer();
    }else{
		GameScene::sharedGameScene()->showBuyLifeLayer();
	}
}

void MainMenu::onCommandHelp(CCObject* pSender)
{
	GameScene::sharedGameScene()->showHelpLayer();
}

void MainMenu::addClickFlash(CCObject *pSender)
{
	FlashSprite *p = FlashSprite::create();
	this->getParent()->addChild(p);
	p->maxFrame = 5;
	p->play(1);

	CCMenuItem * ap = (CCMenuItem*)pSender;
	MyCCMenu *app = (MyCCMenu*)ap->getParent();
	p->setPositionX(app->lastTouch.x);
	p->setPositionY(app->lastTouch.y);
}


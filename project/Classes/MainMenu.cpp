#include "MainMenu.h"
#include <SimpleAudioEngine.h>
#include "GameScene.h"
#include "ResourceConfig.h"
#include "BackgroundLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

bool MainMenu::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!CCLayer::init());

        CCMenuItemImage* pStartMenu = CCMenuItemImage::create(
                                                g_sBeginImage, 
                                                g_sBeginImage, 
                                                this, 
                                                menu_selector(MainMenu::onCommandStart));
        CC_BREAK_IF(!pStartMenu);

        CCMenu* pMenu = CCMenu::create(pStartMenu, NULL);
        CC_BREAK_IF(!pMenu);
        pMenu->alignItemsVertically();

        this->addChild(pMenu, 0);

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
    BackgroundLayer* pBgLayer = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
    if (pBgLayer->subLifeCount(1))  
    {
        GameScene::sharedGameScene()->switchToGameLayer();
    }
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

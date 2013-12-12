#include "MainMenu.h"
#include "GameScene.h"
#include "Utils.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"



USING_NS_CC;
using namespace CocosDenshion;

bool MainMenu::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!CCLayer::init());

        CCMenuItemFont::setFontName("Arial");
        CCMenuItemFont::setFontSize(25);

        CCMenuItemFont* pStartMenu = CCMenuItemFont::create("START", this, menu_selector(MainMenu::onCommandStart));
        CC_BREAK_IF(!pStartMenu);
        CCMenuItemFont* pExitMenu = CCMenuItemFont::create("EXIT", this, menu_selector(MainMenu::onCommandExit));
        CC_BREAK_IF(!pExitMenu);

        CCMenu* pMenu = CCMenu::create(pStartMenu, pExitMenu, NULL);
        CC_BREAK_IF(!pMenu);
        pMenu->alignItemsVertically();

        this->addChild(pMenu, 0);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(g_mainBackGroundSound,true);
        bRet = true;
    }while(0);

    return true;
}

void MainMenu::onCommandStart(CCObject* pSender)
{
    //BackgroundLayer::m_nLiftCount -= 1;
	BackgroundLayer::setLifeCount(BackgroundLayer::getLifeCount()-1);
    GameScene::switchToLevelTips();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
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

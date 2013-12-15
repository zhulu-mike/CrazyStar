#include "GameLayer.h"
#include <SimpleAudioEngine.h>
#include "Utils.h"
#include "LevelTips.h"
#include "GameScene.h"
#include "BackgroundLayer.h"
#include "ResourceConfig.h"
#include "StarCanvas.h"

USING_NS_CC;

using namespace CocosDenshion;

GameLayer::GameLayer()
    : m_nSelectedStatus(0)
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF (!CCLayer::init());
        setTouchEnabled( true );

        CCSize s = CCDirector::sharedDirector()->getWinSize();

        /*初始化道具按钮*/
        CCMenuItemImage* pItemButton = CCMenuItemImage::create(
                                            g_sBombImage, 
                                            g_sBombImage, 
                                            this, 
                                            menu_selector(GameLayer::onCommandItem));
        CCMenuItemImage* pMagicButton = CCMenuItemImage::create(
                                            g_sMagicImage, 
                                            g_sMagicImage, 
                                            this, 
                                            menu_selector(GameLayer::onCommandMagic));
        CCMenuItemImage* pBackButton = CCMenuItemImage::create(
                                            g_sBombImage, 
                                            g_sBombImage, 
                                            this, 
                                            menu_selector(GameLayer::onCommandBack));
        CCMenu* pMenu = CCMenu::create(pItemButton, pMagicButton, pBackButton, NULL);
        pMenu->setPosition(ccp(s.width-100, s.height-100));
        pMenu->alignItemsHorizontally();
        
        this->addChild(pMenu);

        m_pStarCanvas = StarCanvas::create();
        CC_BREAK_IF(!m_pStarCanvas);
        m_pStarCanvas->setPosition(ccp(0, 0));
        m_pStarCanvas->setAnchorPoint(ccp(0, 0));

        m_pStarCanvas->retain();

        bRet = true;

    }while(0);

    return bRet;
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(g_sGameBackGroundSound, true);

    this->addChild(m_pStarCanvas);
}

void GameLayer::onExit()
{
    CCLayer::onExit();

    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

    this->removeChild(m_pStarCanvas);
}
		
void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it ++)
    {
        m_pStarCanvas->touchStarCanvas(((CCTouch*)(*it))->getLocation());

        break;
    }
}

void GameLayer::onCommandBack(CCObject* pSender)
{
    GameScene::sharedGameScene()->switchToMainMenu();
}

void GameLayer::onCommandItem(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
}

void GameLayer::onCommandMagic(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
}

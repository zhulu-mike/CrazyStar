#include "GameLayer.h"
#include <SimpleAudioEngine.h>
#include "Utils.h"
#include "LevelTips.h"
#include "GameScene.h"
#include "BackgroundLayer.h"
#include "StarCanvas.h"
#include "ResourceConfig.h"
#include "FlashSprite.h"
#include "MyCCMenu.h"


USING_NS_CC;

using namespace CocosDenshion;

GameLayer::GameLayer()
    : m_nSelectedStatus(0)
	, m_pLevelOverLayer(NULL)
	, m_pChallengeLayer(NULL)
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
        MyCCMenu* pMenu = MyCCMenu::create(pItemButton, pMagicButton, pBackButton, NULL);
        pMenu->setPosition(ccp(s.width-100, s.height-100));
        pMenu->alignItemsHorizontally();
        
        this->addChild(pMenu,0,9999);

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

	this->setTouchEnabled(true);
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
	addClickFlash(pSender);
}

void GameLayer::onCommandMagic(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
	addClickFlash(pSender);
}

void GameLayer::addClickFlash(CCObject *pSender)
{
	FlashSprite *p = FlashSprite::create();
	this->addChild(p);
	p->maxFrame = 5;
	p->play(1);

	CCMenuItem * ap = (CCMenuItem*)pSender;
	MyCCMenu *app = (MyCCMenu*)ap->getParent();
	p->setPositionX(app->lastTouch.x);
	p->setPositionY(app->lastTouch.y);
}

void GameLayer::showLevelOverLayer(bool win, int leftCount, int leftScore)
{
	if (m_pLevelOverLayer == NULL)
	{
		m_pLevelOverLayer = LevelOver::create();
	}
	this->addChild(m_pLevelOverLayer);
	m_pLevelOverLayer->setAnchorPoint(ccp(0,0));
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pLevelOverLayer->setPositionX(s.width);
	m_pLevelOverLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3, ccp(0,0)),
                    NULL)
					);
	m_pLevelOverLayer->onShow(win,leftCount,leftScore);
}

void GameLayer::hideLevelOverLayer()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pLevelOverLayer->runAction(
		CCSequence::create(
		 CCMoveTo::create(0.3, ccp(-s.width,0)),
		 CCCallFunc::create(this, callfunc_selector(GameLayer::removeLevelOverLayer)),
                    NULL)
					);
}

void GameLayer::removeLevelOverLayer()
{
	m_pLevelOverLayer->removeFromParent();
	m_pLevelOverLayer = NULL;
	m_pStarCanvas->doGameOver();
}

void GameLayer::showChallengeAgainLayer(int round, int need)
{
	if (m_pChallengeLayer == NULL)
	{
		m_pChallengeLayer = ChallengeAgainLayer::create();
	}
	this->addChild(m_pChallengeLayer);
	m_pChallengeLayer->onShow(round, need);
	m_pChallengeLayer->setAnchorPoint(ccp(0,0));
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pChallengeLayer->setPositionX(s.width);
	m_pChallengeLayer->setPositionY(0);
	m_pChallengeLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3, ccp(0,0)),
                    NULL)
					);
}

void GameLayer::hideChallengeAgainLayer()
{
	m_pChallengeLayer->removeFromParent();
	m_pChallengeLayer = NULL;
}

void GameLayer::relife()
{
	int need = getRelifeNeed(m_pStarCanvas->getCurrentLevel());
	BackgroundLayer*app = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	if (app->getLifeCount() >= need)
	{
		app->setLifeCount(app->getLifeCount()-need);
		hideChallengeAgainLayer();
		m_pStarCanvas->renewScore();
		GameScene::sharedGameScene()->switchToGameLayer();
	}else{
		GameScene::sharedGameScene()->showBuyLifeLayer();
	}
}

int GameLayer::getRelifeNeed(int lev)
{
	if (lev % 5 != 0)
	{
		return 1;
	}
	return ceil((float)lev/30.0f);
}

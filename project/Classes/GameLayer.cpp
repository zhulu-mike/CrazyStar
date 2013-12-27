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
#include "SelectedEffect.h"


USING_NS_CC;

using namespace CocosDenshion;

GameLayer::GameLayer()
    : m_kSelectedStatus(kSelectedNone)
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
        CCMenuItemImage* pBombButton = CCMenuItemImage::create(
                                            g_sBombNormalImage, 
                                            g_sBombSelectedImage, 
                                            this, 
                                            menu_selector(GameLayer::onCommandBomb));
        CCMenuItemImage* pMagicButton = CCMenuItemImage::create(
                                            g_sMagicNormalImage, 
                                            g_sMagicSelectedImage, 
                                            this, 
                                            menu_selector(GameLayer::onCommandMagic));
        CCMenuItemImage* pBackButton = CCMenuItemImage::create(
                                            g_sBombNormalImage, 
                                            g_sBombNormalImage, 
                                            this, 
                                            menu_selector(GameLayer::onCommandBack));
        MyCCMenu* pMenu = MyCCMenu::create(pBombButton, pMagicButton, pBackButton, NULL);
        pMenu->setPosition(ccp(s.width-100, s.height-90));
        pMenu->setAnchorPoint(ccp(0, 0));
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
        if (m_kSelectedStatus == kSelectedNone)
        {
            m_pStarCanvas->touchStarCanvas(((CCTouch*)(*it))->getLocation());
        }
        else if (m_kSelectedStatus == kSelectedBomb)
        {
            if (m_pStarCanvas->useBomb(((CCTouch*)(*it))->getLocation()))
                m_kSelectedStatus = kSelectedNone;
        }
        else if (m_kSelectedStatus == kSelectedMagic)
        {
            if (m_pStarCanvas->useMagic(((CCTouch*)(*it))->getLocation()))
                m_kSelectedStatus = kSelectedNone;
        }

        break;
    }
}

void GameLayer::onCommandBack(CCObject* pSender)
{
    GameScene::sharedGameScene()->switchToMainMenu();
}

void GameLayer::onCommandBomb(CCObject* pSender)
{
    if (m_kSelectedStatus == kSelectedBomb)
    {
        m_kSelectedStatus = kSelectedNone;
    }
    else
    {
        m_kSelectedStatus = kSelectedBomb;
		//CCMenuItemImage * app = (CCMenuItemImage*)pSender;
		//app->selected();
    }

    SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
	addClickFlash(pSender);
}

void GameLayer::onCommandMagic(CCObject* pSender)
{
    removeSelectedAnimate();
    
    if (m_kSelectedStatus == kSelectedMagic)
    {
        m_kSelectedStatus = kSelectedNone;
    }
    else
    {
        m_kSelectedStatus = kSelectedMagic;
		//CCMenuItemImage * app = (CCMenuItemImage*)pSender;
		//app->selected();
    }

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

void GameLayer::playSelectedAnimate(cocos2d::CCPoint& pos)
{
    SelectedEffect* pEffect = SelectedEffect::create();
    pEffect->setPosition(pos);
    pEffect->setAnchorPoint(ccp(0, 0));

    addChild(pEffect, 0, kSelectedTag);
}

void GameLayer::removeSelectedAnimate()
{
    removeChildByTag(kSelectedTag);
}

void GameLayer::showLevelOverLayer(bool win, int leftCount, int leftScore, int levelScore)
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
					CCMoveTo::create(0.3f, ccp(0,0)),
                    NULL)
					);
	m_pLevelOverLayer->onShow(win,leftCount,leftScore, levelScore);
}

void GameLayer::hideLevelOverLayer()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pLevelOverLayer->runAction(
		CCSequence::create(
		 CCMoveTo::create(0.3f, ccp(-s.width,0)),
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
					CCMoveTo::create(0.3f, ccp(0,0)),
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

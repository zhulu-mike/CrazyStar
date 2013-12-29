#include "GameScene.h"
#include "BackgroundLayer.h"
#include "MainMenu.h"
#include "GameLayer.h"
#include "ImageConfig.h"
#include "ResourceConfig.h"
#include "BuyLifeLayer.h"
#include "BuyGoldLayer.h"
#include "HelpLayer.h"

USING_NS_CC;

GameScene* GameScene::m_pGameScene = NULL;

GameScene* GameScene::sharedGameScene()
{
    if (m_pGameScene == NULL)
    {
        m_pGameScene = GameScene::create();
        m_pGameScene->retain();
    }

    return m_pGameScene;
}

void GameScene::destory()
{
    if (m_pGameScene != NULL)
    {        
        m_pGameScene->getBackgroundLayer()->release();
        m_pGameScene->getMainMenuLayer()->release();
        m_pGameScene->getMainGameLayer()->release();

        m_pGameScene->release();
    }
}

GameScene::GameScene()
    : m_pBackgroundLayer(NULL)
    , m_pMainMenuLayer(NULL)
    , m_pMainGameLayer(NULL)
	, m_pBuyLifeLayer(NULL)
	, m_pBuyGoldLayer(NULL)
	, m_pHelpLayer(NULL)
{

}

GameScene::~GameScene()
{
    if (m_pBackgroundLayer != NULL)
        m_pBackgroundLayer->release();
    if (m_pMainMenuLayer != NULL)
        m_pMainMenuLayer->release();
    if (m_pMainGameLayer != NULL)
        m_pMainGameLayer->release();
	if (m_pBuyLifeLayer != NULL)
		m_pBuyLifeLayer->release();
	if (m_pBuyGoldLayer != NULL)
		m_pBuyGoldLayer->release();
	if (m_pHelpLayer != NULL)
		m_pHelpLayer->release();
}

bool GameScene::init()
{
    bool bRet = false;
    do
    {
        CCDirector * pDirector;
        CC_BREAK_IF( ! (pDirector = CCDirector::sharedDirector()) );
        this->setContentSize(pDirector->getWinSize());

        ImageConfig::sharedImageConfig()->loadImageConfig(g_sArtCharConfig);
		ImageConfig::sharedImageConfig()->loadImageConfig(g_sWhite72Config);
		ImageConfig::sharedImageConfig()->loadImageConfig(g_sWhite60Config);
		ImageConfig::sharedImageConfig()->loadImageConfig(g_sWhite48Config);
		ImageConfig::sharedImageConfig()->loadImageConfig(g_sGreen60Config);
		ImageConfig::sharedImageConfig()->loadImageConfig(g_sYellow48Config);

        m_pBackgroundLayer = BackgroundLayer::create();
        CC_BREAK_IF(!m_pBackgroundLayer);
        m_pBackgroundLayer->retain();

        m_pMainMenuLayer = MainMenu::create();
        CC_BREAK_IF(!m_pMainMenuLayer);
        m_pMainMenuLayer->retain();

        m_pMainGameLayer = GameLayer::create();
        CC_BREAK_IF(!m_pMainGameLayer);
        m_pMainGameLayer->retain();

        this->addChild(m_pBackgroundLayer, 0, kBackgroundLayerTag);
        
        switchToMainMenu();

        bRet = true;

    }while(0);

    return bRet;
}

void GameScene::switchToMainMenu()
{
    this->removeChildByTag(kMainMenuLayerTag);
    this->removeChildByTag(kMainGameLayerTag);
    this->addChild(m_pMainMenuLayer, 0, kMainMenuLayerTag);
}

void GameScene::switchToGameLayer()
{
    this->removeChildByTag(kMainMenuLayerTag);
    this->removeChildByTag(kMainGameLayerTag);
    this->addChild(m_pMainGameLayer, 0, kMainGameLayerTag);
}

void GameScene::showBuyLifeLayer()
{
	if (m_pBuyLifeLayer == NULL)
		m_pBuyLifeLayer = BuyLifeLayer::create();
	this->addChild(m_pBuyLifeLayer,0,kBuyLifeLayerTag);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pBuyLifeLayer->setAnchorPoint(ccp(0,0));
	m_pBuyLifeLayer->setPositionY(s.height*2);
	m_pBuyLifeLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3f, ccp(0,0)),
                    NULL)
		);
}

void GameScene::hideBuyLifeLayer()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pBuyLifeLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3f, ccp(0,s.height*2)),
					CCCallFunc::create(this, callfunc_selector(GameScene::removeBuyLifeLayer)),
                    NULL)
		);
}

void GameScene::removeBuyLifeLayer()
{
	m_pBuyLifeLayer->removeFromParent();
	m_pBuyLifeLayer = NULL;
}

void GameScene::showBuyGoldLayer()
{
	if (m_pBuyGoldLayer == NULL)
		m_pBuyGoldLayer = BuyGoldLayer::create();
	this->addChild(m_pBuyGoldLayer,0,kBuyGoldLayerTag);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pBuyGoldLayer->setAnchorPoint(ccp(0,0));
	m_pBuyGoldLayer->setPositionY(s.height*2);
	m_pBuyGoldLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3f, ccp(0,0)),
                    NULL)
		);
}

void GameScene::hideBuyGoldLayer()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pBuyGoldLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3f, ccp(0,s.height*2)),
					CCCallFunc::create(this, callfunc_selector(GameScene::removeBuyGoldLayer)),
                    NULL)
		);
}

void GameScene::removeBuyGoldLayer()
{
	m_pBuyGoldLayer->removeFromParent();
	m_pBuyGoldLayer = NULL;
}

bool GameScene::subGold(int count)
{
	BackgroundLayer * app = (BackgroundLayer*)m_pBackgroundLayer;
	return app->subGoldCount(count);
}

void GameScene::showHelpLayer()
{
	if (m_pHelpLayer == NULL)
		m_pHelpLayer = HelpLayer::create();
	this->addChild(m_pHelpLayer,0,kHelpLayerTag);
	((HelpLayer*)m_pHelpLayer)->onShow(1);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pHelpLayer->setAnchorPoint(ccp(0,0));
	m_pHelpLayer->setPositionY(s.height*2);
	m_pHelpLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3f, ccp(0,0)),
                    NULL)
		);
}

void GameScene::hideHelpLayer()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pHelpLayer->runAction(
		CCSequence::create(
					CCMoveTo::create(0.3f, ccp(0,s.height*2)),
					CCCallFunc::create(this, callfunc_selector(GameScene::removeHelpLayer)),
                    NULL)
		);
}

void GameScene::removeHelpLayer()
{
	m_pHelpLayer->removeFromParent();
	m_pHelpLayer = NULL;
}

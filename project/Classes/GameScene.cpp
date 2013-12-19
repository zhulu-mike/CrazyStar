#include "GameScene.h"
#include "BackgroundLayer.h"
#include "MainMenu.h"
#include "GameLayer.h"
#include "BuyLifeLayer.h"

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
}

bool GameScene::init()
{
    bool bRet = false;
    do
    {
        CCDirector * pDirector;
        CC_BREAK_IF( ! (pDirector = CCDirector::sharedDirector()) );
        this->setContentSize(pDirector->getWinSize());

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
					CCMoveTo::create(0.3, ccp(0,0)),
                    NULL)
		);
}


#include "GameScene.h"
#include "BackgroundLayer.h"
#include "MainMenu.h"
#include "LevelTips.h"
#include "GameLayer.h"

USING_NS_CC;


GameScene* GameScene::createDefaultScene()
{
    GameScene* pScene = GameScene::create();

    CCLayer* pBgLayer = (CCLayer*)BackgroundLayer::create();
    CCLayer* pMenuLayer = (CCLayer*)MainMenu::create();

    pScene->addChild(pBgLayer);
    pScene->addChild(pMenuLayer);

    return pScene;
}

void GameScene::switchToMainMenu()
{
    GameScene* pScene = GameScene::create();

    CCLayer* pBgLayer = (CCLayer*)BackgroundLayer::create();
    CCLayer* pMenuLayer = (CCLayer*)MainMenu::create();

    pScene->addChild(pBgLayer);
    pScene->addChild(pMenuLayer);

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GameScene::switchToLevelTips()
{
    GameScene* pScene = GameScene::create();

    CCLayer* pBgLayer = (CCLayer*)BackgroundLayer::create();
    CCLayer* pMenuLayer = (CCLayer*)LevelTips::create();

    pScene->addChild(pBgLayer);
    pScene->addChild(pMenuLayer);

    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GameScene::switchToGameLayer()
{
    GameScene* pScene = GameScene::create();

    CCLayer* pBgLayer = (CCLayer*)BackgroundLayer::create();
    CCLayer* pGameLayer = (CCLayer*)GameLayer::create();

    pScene->addChild(pBgLayer);
    pScene->addChild(pGameLayer);

    CCDirector::sharedDirector()->replaceScene(pScene);
}


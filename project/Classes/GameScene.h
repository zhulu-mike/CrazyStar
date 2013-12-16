#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

class GameScene : public cocos2d::CCScene
{
public:
    static GameScene* sharedGameScene();
    static void destory();    
    CREATE_FUNC(GameScene);
private:
    static GameScene* m_pGameScene;

public:
    enum
    {
        kBackgroundLayerTag = 0,
        kMainMenuLayerTag = 1,
        kMainGameLayerTag   = 2
    };

    GameScene();
    ~GameScene();
    bool init();
    void switchToMainMenu();
    void switchToGameLayer();

    cocos2d::CCLayer* getBackgroundLayer() { return m_pBackgroundLayer; }
    cocos2d::CCLayer* getMainMenuLayer()   { return m_pMainMenuLayer;   }
    cocos2d::CCLayer* getMainGameLayer()   { return m_pMainGameLayer;   }

    void setBackgroundLayer(cocos2d::CCLayer* pLayer){ m_pBackgroundLayer = pLayer; }
    void setMainMenuLayer(cocos2d::CCLayer* pLayer)  { m_pMainMenuLayer   = pLayer; }
    void setMainGameLayer(cocos2d::CCLayer* pLayer)  { m_pMainGameLayer   = pLayer; }

private:
    cocos2d::CCLayer* m_pBackgroundLayer;
    cocos2d::CCLayer* m_pMainMenuLayer;
    cocos2d::CCLayer* m_pMainGameLayer;
};

#endif
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "AchieveLayer.h"

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
        kMainGameLayerTag   = 2,
		kBuyLifeLayerTag = 3,
		kBuyGoldLayerTag = 4,
		kHelpLayerTag    = 5,
		kAchieveEffectLayerTag = 6
    };

    GameScene();
    ~GameScene();
    bool init();
    void switchToMainMenu();
    void switchToGameLayer();
	void showBuyLifeLayer();
	void hideBuyLifeLayer();
	void removeBuyLifeLayer();
	void showBuyGoldLayer();
	void hideBuyGoldLayer();
	void removeBuyGoldLayer();
	void hideHelpLayer();
	void showHelpLayer();
	void removeHelpLayer();
	bool subGold(int count);

    cocos2d::CCLayer* getBackgroundLayer() { return m_pBackgroundLayer; }
    cocos2d::CCLayer* getMainMenuLayer()   { return m_pMainMenuLayer;   }
    cocos2d::CCLayer* getMainGameLayer()   { return m_pMainGameLayer;   }
	cocos2d::CCLayer* getBuyLifeLayer()   { return m_pBuyLifeLayer;   }
	cocos2d::CCLayer* getBuyGoldLayer()   { return m_pBuyGoldLayer;   }
	cocos2d::CCLayer* getHelpLayer()   { return m_pHelpLayer;   }
	AchieveLayer* getAchieveEffectLayer() { return m_pAchieveLayer; }

    void setBackgroundLayer(cocos2d::CCLayer* pLayer){ m_pBackgroundLayer = pLayer; }
    void setMainMenuLayer(cocos2d::CCLayer* pLayer)  { m_pMainMenuLayer   = pLayer; }
    void setMainGameLayer(cocos2d::CCLayer* pLayer)  { m_pMainGameLayer   = pLayer; }

private:
    cocos2d::CCLayer* m_pBackgroundLayer;
    cocos2d::CCLayer* m_pMainMenuLayer;
    cocos2d::CCLayer* m_pMainGameLayer;
	cocos2d::CCLayer* m_pBuyLifeLayer;
	cocos2d::CCLayer* m_pBuyGoldLayer;
	cocos2d::CCLayer* m_pHelpLayer;
	AchieveLayer* m_pAchieveLayer;
};

#endif
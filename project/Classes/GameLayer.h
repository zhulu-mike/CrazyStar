#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
#include "StarSprite.h"
#include "LevelOver.h"

#define MAP_SIZE 10

class StarCanvas;
class GameLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(GameLayer);
    
    GameLayer();
    ~GameLayer();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    void onCommandBack(CCObject* pSender);
    void onCommandItem(CCObject* pSender);
    void onCommandMagic(CCObject* pSender);

	void showLevelOverLayer(bool win, int leftCount, int leftScore);
	void hideLevelOverLayer();

    void nextLevel();
    void gameOver();
private:
    int m_nSelectedStatus;

	LevelOver* m_pLevelOverLayer;

    StarCanvas* m_pStarCanvas;
};

#endif
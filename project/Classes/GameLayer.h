#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
#include "StarSprite.h"

#define MAP_SIZE 10

class StarCanvas;
class GameLayer : public cocos2d::CCLayer
{
public:
    enum selectedItem
    {
        kSelectedNone  = 0,
        kSelectedBomb  = 1,
        kSelectedMagic = 2,
        kSelectedTag   = 3,
    };

    CREATE_FUNC(GameLayer);
    
    GameLayer();
    ~GameLayer();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    void onCommandBack(CCObject* pSender);
    void onCommandBomb(CCObject* pSender);
    void onCommandMagic(CCObject* pSender);

    void nextLevel();
    void gameOver();

    void playSelectedAnimate(cocos2d::CCPoint& pos);
    void removeSelectedAnimate();
private:
    int m_kSelectedStatus;

    StarCanvas* m_pStarCanvas;
};

#endif
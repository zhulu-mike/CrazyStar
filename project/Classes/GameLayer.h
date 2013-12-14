#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
#include "StarSprite.h"

#define MAP_SIZE 10

class GameLayer : public cocos2d::CCLayer
{
public:

    enum starColor
    {
        kStarNone   = 0,
        kStarRed    = 1,
        kStarYellow = 2,
        kStarGreen  = 3,
        kStarBlue   = 4,
        kStarPurple = 5,
        kStarMax    = 6
    };

    enum popDirection
    {
        kNorth     = 0,
        kEast      = 1,
        kSouth     = 2,
        kWest      = 3,
    };

    GameLayer();
    ~GameLayer();
    

    virtual bool init();
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    void onCommandBack(CCObject* pSender);
    void onCommandItem(CCObject* pSender);
    void onCommandMagic(CCObject* pSender);
	void onDispose();

    void showTargetScore();
    void showCurrentScore();
    void addCurrentScore(int nScore);

    void showLevelInfo();

    void initStarImage();
    void generateMap();
    void popStar(int x, int y);
    void removeStar();
    void fillHole();
    void nextLevel();

    bool isOver();
    bool isSameColor(int x, int y, int kColor);

    void removeAll();
    void gameOver();
	void showPopEffect(cocos2d::CCPoint point, int type);

    CREATE_FUNC(GameLayer);

private:
    cocos2d::CCLabelTTF* m_pCurrentScore;

    bool m_bIsOver;
    int m_popColor;
    int m_nSelectedStatus;
	float beginX;
	float beginY;

    std::vector<cocos2d::CCPoint> m_popStar;
    cocos2d::CCSpriteBatchNode* m_pStarBatchNode[kStarMax];
    StarSprite* m_starMap[MAP_SIZE][MAP_SIZE];
};

#endif
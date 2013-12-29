#ifndef _STAR_CANVAS_H_
#define _STAR_CANVAS_H_

#include "cocos2d.h"

#define MAP_SIZE 10

class StarSprite;
class ScoreControl;
class StarCanvas : public cocos2d::CCNode
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

    CREATE_FUNC(StarCanvas);

    StarCanvas();
    ~StarCanvas();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    void touchStarCanvas(cocos2d::CCPoint& location);
    void popStar(int x, int y);
    void removeStar();
    void fillHole();
    void clearAllStar();
    void playPopEffect(cocos2d::CCPoint& point, int type);

    bool isHasPopStar();
    bool isSameColor(int x, int y, int kColor);

    bool useBomb(cocos2d::CCPoint& pos);
    bool useMagic(cocos2d::CCPoint& pos);

	void showPopEffect(cocos2d::CCPoint point, int type);
	void showPopEffectBySprite(CCNode *p);
	void showPopEffectBySpriteWithSound(CCNode * p);
	void checkIsOver();
	void moveHorizontalHole();
    void gameOver();
	void doGameOver();
	int getCurrentLevel();

	void renewScore();

private:
    void _generateOneStar(int x, int y, int c);
	void addPingJiaEff(int type);
	void changePopState();
	int getLeftScore(int count);

private:
    float m_fBeginX;
    float m_fBeginY;
    float m_fIntervalX;
    float m_fIntervalY;
    float m_fStarWidth;
    float m_fStarHeight;

	bool popIng;
	bool gameState;

    int m_nPopColor;

    std::vector<cocos2d::CCPoint> m_popStar;
    
    StarSprite* m_pStarMap[MAP_SIZE][MAP_SIZE];
    
    cocos2d::CCSpriteBatchNode* m_pStarBatchNode[kStarMax];

    ScoreControl* m_pScoreControl;
};

#endif
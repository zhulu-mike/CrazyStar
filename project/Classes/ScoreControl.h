#ifndef _SCORE_CONTROL_H_
#define _SCORE_CONTROL_H_

#include "NumberSprite.h"
#include "cocos2d.h"

class ScoreControl : public cocos2d::CCNode
{
public:
    CREATE_FUNC(ScoreControl);

    ScoreControl();
    ~ScoreControl();

    virtual bool init();

    void setCurrentLevel(int nLevel);
    void addCurrentLevel(int nLevel);

    void addCurrentScore(int nScore);
    void setCurrentScore(int nScore);
    void setTargetScore();

    int getCurrentScore() { return m_nCurrentScore; }
    int getCurrentLevel() { return m_nCurrentLevel; }
    int getTargetScore();

    cocos2d::CCPoint getCurrentScorePosition();

    void clearAllScore();
	void addScoreEffect(int score, int count);
	void renewScore();
    bool isUpLevel();
	/*获取本关得分*/
	int getCurrentLevelScore();
private:
    int m_nCurrentLevel;
    int m_nCurrentScore;
	int m_nLastScore;
    int m_nTargetScore;

    cocos2d::CCLabelTTF* m_pTargetScoreLabel;
	cocos2d::CCSprite* m_pGuan;
	cocos2d::CCSprite* m_pMuBiao;
	cocos2d::CCSprite* m_jiaScore;
	NumberSprite* m_pLevelImg;
	NumberSprite* m_pTargetImg;
	NumberSprite* m_pCurrentScoreLabel;

	void updateLevel();
};

#endif


#ifndef _SCORE_CONTROL_H_
#define _SCORE_CONTROL_H_

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

    void clearAllScore();
	void renewScore();
    bool isUpLevel();
private:
    int m_nCurrentLevel;
    int m_nCurrentScore;
	int m_nLastScore;

    cocos2d::CCLabelTTF* m_pCurrentScoreLabel;              
    cocos2d::CCLabelTTF* m_pTargetScoreLabel;
};

#endif


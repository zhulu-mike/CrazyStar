#ifndef _LEVEL_TIPS_H_
#define _LEVEL_TIPS_H_

#include "cocos2d.h"

class LevelTips : public cocos2d::CCLayer
{
public:
    virtual bool init();
    virtual void onEnterTransitionDidFinish();

    void onShowTipsFinish(CCNode* pSender);
    
    static int getLevelTarget();

    CREATE_FUNC(LevelTips);

public:
    static int m_level;
    static int m_currentScore;
};

#endif
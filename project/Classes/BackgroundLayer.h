#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer
{
public:
    BackgroundLayer();
    ~BackgroundLayer();
    
    CREATE_FUNC(BackgroundLayer);
    
    virtual bool init();

    int getLifeCount() { return m_nLifeCount; }
    void setLifeCount(int nCount);
    bool subLifeCount(int nCount);
    bool addLifeCount(int nCount);
    void setBackgroundImage(const char* fileName);
    void updateTimeDisplay(float dt);

private:
    int m_nLifeCount;
    int m_nLeftTime;

	cocos2d::CCSprite*   m_pBgSprite;
	cocos2d::CCLabelTTF* m_pTimeLabel;
    std::vector<cocos2d::CCSprite*> m_lifeVector;
};

#endif
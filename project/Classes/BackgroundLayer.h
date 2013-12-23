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
	int getGoldCount() { return m_nGoldCount; }
    void setGoldCount(int nCount);
    void setBackgroundImage(const char* fileName);
    void updateTimeDisplay(float dt);
	bool addGoldCount(int nCount);
	bool subGoldCount(int nCount);
private:
    int m_nLifeCount;
    int m_nLeftTime;
	int m_nGoldCount;

	void onCommandBuyLife(cocos2d::CCObject * pSender);
	void onCommandBuyGold(cocos2d::CCObject * pSender);
	void addClickFlash(cocos2d::CCObject *pSender);

	cocos2d::CCSprite*   m_pBgSprite;
	cocos2d::CCLabelTTF* m_pTimeLabel;
	cocos2d::CCLabelTTF* m_pGoldLabel;
    std::vector<cocos2d::CCSprite*> m_lifeVector;
	cocos2d::CCSprite* m_pGoldImage;
	cocos2d::CCSprite* chengHaoe;
};

#endif
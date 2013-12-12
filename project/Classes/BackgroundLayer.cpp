#include "BackgroundLayer.h"
#include "Utils.h"
#include "GlobalConstData.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

using namespace CocosDenshion;
using namespace std;

int BackgroundLayer::m_nLiftCount = 5;
int BackgroundLayer::lifeTime = 120;
int BackgroundLayer::beginTime = 0;
bool BackgroundLayer::haveTimer = false;

BackgroundLayer::BackgroundLayer()
	:bgSprite(NULL)
	,timeLabel(NULL)
{}

bool BackgroundLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!CCLayer::init());

        CCSize s = CCDirector::sharedDirector()->getWinSize();

        bgSprite = CCSprite::create(g_sBackgroundImage, CCRectMake(0, 0, s.width, s.height));
        CC_BREAK_IF(!bgSprite);
        this->addChild(bgSprite, 0);
        bgSprite->setAnchorPoint(ccp(0, 0));
        bgSprite->setPosition(ccp(0, 0));

        CCSpriteBatchNode* pSpriteBatch = CCSpriteBatchNode::create(g_sTaoxinImage);
        CC_BREAK_IF(!pSpriteBatch);

        for (int i = 0; i < m_nLiftCount; ++ i)
        {
            CCSprite* pLiftSprite = CCSprite::create();
            pLiftSprite->initWithTexture(pSpriteBatch->getTexture(), CCRectMake(0, 0, 20, 20));
            CC_BREAK_IF(!pLiftSprite);
            this->addChild(pLiftSprite);
            pLiftSprite->setAnchorPoint(ccp(0, 0));
            pLiftSprite->setPosition(ccp(147 + i * 25, s.height-34));
        }
		if (m_nLiftCount < life_full)
		{
			//需要显示倒计时
			string  txt = transTimeStr(lifeTime);
			timeLabel = CCLabelTTF::create(txt.c_str(), "Arial", 25, CCSizeMake(200, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            timeLabel->retain();

			this->addChild(timeLabel);
			timeLabel->setAnchorPoint(ccp(0, 0));
			timeLabel->setPosition(ccp(147+125, s.height - 38));
			haveTimer = true;
			schedule(schedule_selector(BackgroundLayer::updateTimeDisplay),1.0f);
			beginTime = time(NULL);
		}
		
        bRet = true;

    }while(0);

    return bRet;
}


 void BackgroundLayer::updateTimeDisplay(float t)
{
	if (lifeTime > 0)
	{
		lifeTime--;
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		string  txt = transTimeStr(lifeTime);
		timeLabel->setString(txt.c_str());
	}else{
		int now = time(NULL);
		if (now - beginTime > LIFE_CREATE_TIME)
		{
			beginTime = now;
			lifeTime = LIFE_CREATE_TIME;
			string  txt = transTimeStr(lifeTime);
			timeLabel->setString(txt.c_str());
			setLifeCount(m_nLiftCount++);
		}

	}
}

void BackgroundLayer::setBackGroundImage(const char *fileimage)
{
	/*this->removeChild(bgSprite);
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	bgSprite = CCSprite::create(fileimage, CCRectMake(0, 0, s.width, s.height));

    this->addChild(bgSprite, 0);
    bgSprite->setAnchorPoint(ccp(0, 0));
    bgSprite->setPosition(ccp(0, 0));*/
	bgSprite->initWithFile(fileimage);
}

void BackgroundLayer::setLifeCount(int count)
{
	m_nLiftCount = count;
	if (count >= life_full && haveTimer)
	{
		unschedule(schedule_selector(BackgroundLayer::updateTimeDisplay));
	}else if (count < life_full && !haveTimer)
	{
		lifeTime = LIFE_CREATE_TIME;
		string  txt = transTimeStr(lifeTime);
		if (timeLabel == NULL)
		{
			CCSize s = CCDirector::sharedDirector()->getWinSize();
			timeLabel = CCLabelTTF::create(txt.c_str(), "Arial", 25, CCSizeMake(200, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
			this->addChild(timeLabel);
			timeLabel->setAnchorPoint(ccp(0, 0));
			timeLabel->setPosition(ccp(147+125, s.height - 38));
		}else{
			timeLabel->setString(txt.c_str());
		}
		haveTimer = true;
		schedule(schedule_selector(BackgroundLayer::updateTimeDisplay),1.0f);
		beginTime = time(NULL);
	}
}

int BackgroundLayer::getLifeCount()
{
	return m_nLiftCount;
}
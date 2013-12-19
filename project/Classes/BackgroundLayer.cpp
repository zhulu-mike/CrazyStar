#include "BackgroundLayer.h"
#include <SimpleAudioEngine.h>

#include "ResourceConfig.h"
#include "Utils.h"

USING_NS_CC;

using namespace CocosDenshion;

#define MAX_LIFE_COUNT 5
#define LIFT_CREATE_TIME 600

BackgroundLayer::BackgroundLayer()
	: m_nLifeCount(1)
    , m_nLeftTime(0)
    , m_pBgSprite(NULL)
	, m_pTimeLabel(NULL)
{
	
}

BackgroundLayer::~BackgroundLayer()
{

}

bool BackgroundLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());

        CCSize s = CCDirector::sharedDirector()->getWinSize();
        
        //m_pBgSprite = CCSprite::create(g_sBackgroundImage, CCRectMake(0, 0, s.width, s.height));
        //CC_BREAK_IF(!m_pBgSprite);
        //m_pBgSprite->setAnchorPoint(ccp(0, 0));
        //m_pBgSprite->setPosition(ccp(0, 0));
        
        //this->addChild(m_pBgSprite, 0);

        CCSpriteBatchNode* pSpriteBatch = CCSpriteBatchNode::create(g_sTaoxinImage);
        CC_BREAK_IF(!pSpriteBatch);

        for (int i = 0; i < MAX_LIFE_COUNT; ++ i)
        {
            CCSprite* pLifeSprite = CCSprite::create();
            CC_BREAK_IF(!pLifeSprite);
            
            pLifeSprite->initWithTexture(pSpriteBatch->getTexture(), CCRectMake(0, 0, 20, 20));
            pLifeSprite->setVisible(true);
            pLifeSprite->setAnchorPoint(ccp(0, 0));
            pLifeSprite->setPosition(ccp(147 + i * 25, s.height-34));

            this->addChild(pLifeSprite);

			m_lifeVector.push_back(pLifeSprite);
        }

        m_pTimeLabel = CCLabelTTF::create("", "Arial", 25, CCSizeMake(200, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        CC_BREAK_IF(!m_pTimeLabel);
        m_pTimeLabel->setAnchorPoint(ccp(0, 0));
        m_pTimeLabel->setPosition(ccp(147+125, s.height - 38));

        this->addChild(m_pTimeLabel);

        schedule(schedule_selector(BackgroundLayer::updateTimeDisplay), 1.0f);
		
        bRet = true;

    }while(0);

    return bRet;
}


void BackgroundLayer::updateTimeDisplay(float dt)
{
    if (m_nLifeCount >= MAX_LIFE_COUNT)
        return ;

    if (m_nLeftTime > 0)
        m_nLeftTime -- ;

    m_pTimeLabel->setString(StringFormatHelper()("%02d:%02d", m_nLeftTime/60, m_nLeftTime%60));

    if (m_nLeftTime == 0) { addLifeCount(1); }
}

void BackgroundLayer::setBackgroundImage(const char* fileName)
{
    CC_ASSERT(fileName != NULL);

	m_pBgSprite->initWithFile(fileName);
}

void BackgroundLayer::setLifeCount(int nCount)
{
    if (nCount < 0) { return; }

    if ((m_nLifeCount = nCount) > MAX_LIFE_COUNT)
        m_nLifeCount = MAX_LIFE_COUNT;

    for (int i = 0; i < MAX_LIFE_COUNT; ++ i)
        m_lifeVector[i]->setVisible(false);

    for (int i = 0; i < m_nLifeCount; ++ i)
        m_lifeVector[i]->setVisible(true);

    if (m_nLifeCount < MAX_LIFE_COUNT && m_nLeftTime == 0)
        m_nLeftTime = LIFT_CREATE_TIME;

    if (m_nLifeCount == MAX_LIFE_COUNT)
        m_pTimeLabel->setString("");
}

bool BackgroundLayer::subLifeCount(int nCount)
{
    if (m_nLifeCount < nCount)
        return false;

    setLifeCount(m_nLifeCount - nCount);
    
    return true;
}

bool BackgroundLayer::addLifeCount(int nCount)
{
    if ((m_nLifeCount + nCount) > MAX_LIFE_COUNT)
        return false;

    setLifeCount(m_nLifeCount + nCount);

    return true;
}
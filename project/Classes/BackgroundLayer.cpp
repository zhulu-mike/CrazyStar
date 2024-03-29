#include "BackgroundLayer.h"
#include <SimpleAudioEngine.h>

#include "ResourceConfig.h"
#include "Utils.h"
#include "MyCCMenu.h"
#include "GameScene.h"
#include "FlashSprite.h"

USING_NS_CC;

using namespace CocosDenshion;

#define MAX_LIFE_COUNT 5
#define LIFT_CREATE_TIME 600

BackgroundLayer::BackgroundLayer()
	: m_nLifeCount(5)
    , m_nLeftTime(0)
    , m_pBgSprite(NULL)
	, m_pTimeLabel(NULL)
	, m_pGoldImage(NULL)
	, chengHaoe(NULL)
	, m_nGoldCount(0)
	, m_pGoldLabel(NULL)
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

		CCMenuItemImage * jiahao1 = CCMenuItemImage::create(g_sJiaHaoBGImage,g_sJiaHaoBGImage,
														this, 
														menu_selector(BackgroundLayer::onCommandBuyLife));
		jiahao1->setAnchorPoint(ccp(0,0));
		MyCCMenu * jiaMenu1 = MyCCMenu::create(jiahao1, NULL);
		this->addChild(jiaMenu1);
		jiaMenu1->setPositionX(m_pTimeLabel->getPositionX()+80);
		jiaMenu1->setPositionY(s.height-38);


		m_pGoldImage = CCSprite::create(g_sGoldBGImage);
		this->addChild(m_pGoldImage);
		m_pGoldImage->setAnchorPoint(ccp(0,0));
		m_pGoldImage->setPositionY(s.height-48);
		m_pGoldImage->setPositionX(s.width-200);

		m_pGoldLabel = CCLabelTTF::create("", "Arial", 25, CCSizeMake(200, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        CC_BREAK_IF(!m_pGoldLabel);
		this->addChild(m_pGoldLabel);
        m_pGoldLabel->setAnchorPoint(ccp(0, 0));
		m_pGoldLabel->setPosition(ccp(m_pGoldImage->getPositionX()+m_pGoldImage->getContentSize().width+10, s.height - 38));
		setGoldCount(0);


		CCMenuItemImage * jiahao2 = CCMenuItemImage::create(g_sJiaHaoBGImage,g_sJiaHaoBGImage,
														this, 
														menu_selector(BackgroundLayer::onCommandBuyGold));
		jiahao2->setAnchorPoint(ccp(0,0));
		MyCCMenu * jiaMenu2 = MyCCMenu::create(jiahao2, NULL);
		this->addChild(jiaMenu2);
		jiaMenu2->setPositionX(m_pGoldLabel->getPositionX()+100);
		jiaMenu2->setPositionY(s.height-38);

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
	{
		int dis = m_nLifeCount - MAX_LIFE_COUNT;
		char buf[64];
		sprintf(buf,"%d", dis);
		m_pTimeLabel->setString(buf);
	}

    for (int i = 0; i < MAX_LIFE_COUNT; ++ i)
        m_lifeVector[i]->setVisible(false);
	int len = m_nLifeCount;
	len = len > MAX_LIFE_COUNT ? MAX_LIFE_COUNT : len;
    for (int i = 0; i < len; ++ i)
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
    setLifeCount(m_nLifeCount + nCount);

    return true;
}

void BackgroundLayer::setGoldCount(int nCount)
{
    if (nCount < 0) { return; }
	m_nGoldCount = nCount;
	char buf[64];
	sprintf(buf,"%d", m_nGoldCount);
	m_pGoldLabel->setString(buf);
}

bool BackgroundLayer::subGoldCount(int nCount)
{
    if (m_nGoldCount < nCount)
        return false;

    setGoldCount(m_nGoldCount - nCount);
    
    return true;
}

bool BackgroundLayer::addGoldCount(int nCount)
{
    setGoldCount(m_nGoldCount + nCount);

    return true;
}

void BackgroundLayer::onCommandBuyLife(CCObject * pSender)
{
	addClickFlash(pSender);
	GameScene::sharedGameScene()->showBuyLifeLayer();
}

void BackgroundLayer::onCommandBuyGold(CCObject * pSender)
{
	addClickFlash(pSender);
	GameScene::sharedGameScene()->showBuyGoldLayer();
}

void BackgroundLayer::addClickFlash(CCObject *pSender)
{
	FlashSprite *p = FlashSprite::create();
	this->addChild(p);
	p->maxFrame = 5;
	p->play(1);

	CCMenuItem * ap = (CCMenuItem*)pSender;
	MyCCMenu *app = (MyCCMenu*)ap->getParent();
	p->setPositionX(app->lastTouch.x);
	p->setPositionY(app->lastTouch.y);
}
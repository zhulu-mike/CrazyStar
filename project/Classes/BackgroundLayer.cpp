#include "BackgroundLayer.h"
#include "Utils.h"

USING_NS_CC;

int BackgroundLayer::m_nLiftCount = 5;

bool BackgroundLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!CCLayer::init());

        CCSize s = CCDirector::sharedDirector()->getWinSize();

        CCSprite* pSprite = CCSprite::create(g_sBackgroundImage, CCRectMake(0, 0, s.width, s.height));
        CC_BREAK_IF(!pSprite);
        this->addChild(pSprite, 0);
        pSprite->setAnchorPoint(ccp(0, 0));
        pSprite->setPosition(ccp(0, 0));

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

        bRet = true;

    }while(0);

    return bRet;
}
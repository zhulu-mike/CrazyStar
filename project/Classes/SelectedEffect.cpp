#include "SelectedEffect.h"

USING_NS_CC;

SelectedEffect::SelectedEffect()
    : m_pSelectedAnimate(NULL)
{

}

SelectedEffect::~SelectedEffect()
{
    if (m_pSelectedAnimate != NULL)
        m_pSelectedAnimate->release();
}

bool SelectedEffect::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCSprite::init());

        CCAnimation* pAnimation = CCAnimation::create();
        CC_BREAK_IF(!pAnimation);
        for( int i = 1; i < 6; i ++)
        {
            char szName[100] = {0};
            sprintf(szName, "./image/image%02d.png", i);
            pAnimation->addSpriteFrameWithFileName(szName);
        }
        pAnimation->setDelayPerUnit(1.5f / 6.0f);

        m_pSelectedAnimate = CCRepeatForever::create(CCAnimate::create(pAnimation));
        m_pSelectedAnimate->retain();

        this->runAction(m_pSelectedAnimate);

        bRet = true;

    }while(0);

    return bRet;
}
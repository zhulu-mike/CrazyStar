#include "LevelTips.h"
#include "GameScene.h"

USING_NS_CC;

int LevelTips::m_level = 1;
int LevelTips::m_currentScore = 0;

bool LevelTips::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!CCLayer::init());

        bRet = true;
    }while(0);

    return bRet;
}

void LevelTips::onEnterTransitionDidFinish()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    char buf[64] = {0};
    sprintf(buf, "LEVEL %d", m_level);

    CCLabelTTF *pLevel = CCLabelTTF::create(buf, "Arial", 25, CCSizeMake(200, 100), 
        kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    pLevel->setPosition(ccp(s.width, s.height / 2));

    this->addChild(pLevel);

    CCFiniteTimeAction* pMoveAction = CCMoveTo::create(1, ccp(s.width / 2, s.height / 2));
    CCFiniteTimeAction* pMoveDone = CCCallFuncN::create(this, callfuncN_selector(LevelTips::onShowTipsFinish));

    CCSequence* pSequence = CCSequence::create(pMoveAction, pMoveDone, NULL);

    pLevel->runAction(pSequence);
}

void LevelTips::onShowTipsFinish(CCNode* pSender)
{
    GameScene::switchToGameLayer();
}
int LevelTips::getLevelTarget()
{
    if (m_level < 4)
        return 250*m_level*(m_level+3);
    else if (m_level < 54)
        return 4500+2020*(m_level-3)+10*(m_level*m_level-7*m_level+12);
    else
        return 133000+(m_level-54)*3000;
    
    return 0;
}
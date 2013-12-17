#include "StarSprite.h"

USING_NS_CC;

#define MOVE_INTERVAL 0.4f
#define JNMP_INTERVAL 0.1f

void StarSprite::moveToDown(CCPoint& pos, float delayTime)
{
    //float moveTime = (getPosition().y - pos.y) / 53.f * MOVE_SPEED;
    
    CCActionInterval* pActionJump = CCJumpTo::create(JNMP_INTERVAL, getPosition(), 2, 1);
    CCActionInterval* pActionMove = CCMoveTo::create(MOVE_INTERVAL, pos);

    this->runAction(CCSequence::create(CCDelayTime::create(delayTime), pActionJump, pActionMove, NULL));
}

void StarSprite::moveToLeft(CCPoint& pos)
{
    //float moveTime = (getPosition().x - pos.x) / 53.f * MOVE_SPEED;

    CCActionInterval* pActionJump = CCMoveTo::create(JNMP_INTERVAL, ccp(getPosition().x + 2, getPosition().y));
    CCActionInterval* pActionMove = CCMoveTo::create(0.2f, pos);

    this->runAction(CCSequence::create(pActionJump, pActionMove, NULL));
}
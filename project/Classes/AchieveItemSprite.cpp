#include "AchieveItemSprite.h"
#include "ResourceConfig.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

AchieveItemSprite::AchieveItemSprite()
{

}

AchieveItemSprite* AchieveItemSprite::create(AchieveManager::AchieveVO vo)
{
	AchieveItemSprite* ret = new AchieveItemSprite();
	ret->createChildren(vo);
	return ret;
}


void AchieveItemSprite::createChildren(AchieveManager::AchieveVO vo)
{
	CCSprite *p = CCSprite::create(g_sAchieveItemBGImage);
	CCSize ps = p->getContentSize();
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCScale9Sprite* bg = CCScale9Sprite::create(g_sAchieveItemBGImage,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
	this->addChild(bg);
	this->setTouchEnabled(false);
	bg->setPreferredSize(CCSizeMake(350,120));
}

void AchieveItemSprite::playEffect()
{
	this->setScale(0.0f);
	this->runAction(
		CCSequence::create(
		CCScaleTo::create(0.5f,1.0f,1.0f),
		CCDelayTime::create(0.5f),
		CCMoveTo::create(0.5f,ccp(this->getPositionX(), this->getPositionY()+100)),
		CCRemoveSelf::create(true),
		
		NULL)
		);
}


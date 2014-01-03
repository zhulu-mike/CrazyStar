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

	char url[64] = {0};
	sprintf(url,"%s%d%s", "./image/achieve/", vo.id, ".png");

	CCSprite* pic = CCSprite::create(url);
	this->addChild(pic);

	//this->setTouchEnabled(false);
	bg->setPreferredSize(CCSizeMake(350,120));
}

void AchieveItemSprite::playEffect()
{
	
}


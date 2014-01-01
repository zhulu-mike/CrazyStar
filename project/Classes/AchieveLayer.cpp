#include "AchieveLayer.h"
#include "AchieveManager.h"
#include "AchieveItemSprite.h"

USING_NS_CC;

AchieveLayer::AchieveLayer()
{
	this->setTouchEnabled(false);
}

void AchieveLayer::completeAchieveItems(int type, int value)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	std::vector<AchieveManager::AchieveVO> arr = AchieveManager::sharedAchieveManager()->getCanCompleteAchieve(type,value);
	int i = 0;
	int size = arr.size();
	for (;i<size;i++)
	{
		AchieveItemSprite* sp = AchieveItemSprite::create(arr[i]);
		this->addChild(sp);
		sp->setPositionX(s.width*0.5);
		sp->setPositionY(s.height*0.5);
		sp->playEffect();
	}
}
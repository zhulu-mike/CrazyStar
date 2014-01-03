#ifndef _ACHIEVE_ITEM_SPRITE_H
#define _ACHIEVE_ITEM_SPRITE_H


#include "cocos2d.h"
#include "AchieveManager.h"

class AchieveItemSprite : public cocos2d::CCNode
{
public:
	AchieveItemSprite();
	static AchieveItemSprite* create(AchieveManager::AchieveVO vo);
	


public:
	void createChildren(AchieveManager::AchieveVO vo);

	void playEffect();











};

#endif
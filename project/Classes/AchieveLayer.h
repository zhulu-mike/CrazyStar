#ifndef _AHIEVE_LAYER_H
#define _AHIEVE_LAYER_H

#include "cocos2d.h"

class AchieveLayer : public cocos2d::CCLayer
{
public:
	AchieveLayer();

	void completeAchieveItems(int type, int value);

     int totalCount;
private:
	void removeItem();
	void showSocreAddEffect(cocos2d::CCPoint pos,int count);
	void showLifeAddEffect(cocos2d::CCPoint pos,int count);
	void showGoldAddEffect(cocos2d::CCPoint pos,int count);













};

#endif
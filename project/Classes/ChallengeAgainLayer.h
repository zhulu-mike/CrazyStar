#ifndef _CHALLENGE_AGAIN_H_
#define _CHALLENGE_AGAIN_H_
#include "cocos2d.h"

class ChallengeAgainLayer : public cocos2d::CCLayer
{
public:
	ChallengeAgainLayer();
	virtual bool init();

	void onShow(int round, int need);

	CREATE_FUNC(ChallengeAgainLayer);

	
private:
	void onCommandSure(CCObject* pSender);
	void onCommandReturn(CCObject* pSender);
};

#endif
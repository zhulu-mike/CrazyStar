#ifndef _HELP_LAYER_H
#define _HELP_LAYER_H

#include "cocos2d.h"

class HelpLayer : public cocos2d::CCLayer
{
	public:

		HelpLayer();
		virtual bool init();


	CREATE_FUNC(HelpLayer);

private:
	void onCommandBack(cocos2d::CCObject * pSender);

	float beginY;






};

#endif



#ifndef _BUYLIFE_LAYER_H_
#define _BUYLIFE_LAYER_H_

#include "cocos2d.h"

class BuyLifeLayer : public cocos2d::CCLayer
{
public:
    BuyLifeLayer();
    
    CREATE_FUNC(BuyLifeLayer);
    
    virtual bool init();

	void onShow();
    
};

#endif
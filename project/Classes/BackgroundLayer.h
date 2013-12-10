#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();

    CREATE_FUNC(BackgroundLayer);

public:
    static int m_nLiftCount;
};

#endif
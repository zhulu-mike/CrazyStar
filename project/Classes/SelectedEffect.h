#ifndef _SELECTED_EFFECT_H_
#define _SELECTED_EFFECT_H_

#include "cocos2d.h"

class SelectedEffect : public cocos2d::CCSprite
{
public:
    CREATE_FUNC(SelectedEffect);

    SelectedEffect();
    ~SelectedEffect();
    virtual bool init();

private:
    cocos2d::CCAction* m_pSelectedAnimate;
};

#endif
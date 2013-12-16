#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "cocos2d.h"

class MainMenu : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(MainMenu);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();

    void onCommandStart(CCObject* pSender);
    void onCommandExit(CCObject* pSender);
};

#endif
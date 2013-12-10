#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "cocos2d.h"

class MainMenu : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(MainMenu);

    void onCommandStart(CCObject* pSender);
    void onCommandExit(CCObject* pSender);
};

#endif
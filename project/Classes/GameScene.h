#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"

class GameScene : public cocos2d::CCScene
{
public:
    static GameScene* createDefaultScene();

    static void switchToMainMenu();
    static void switchToLevelTips();
    static void switchToGameLayer();

    CREATE_FUNC(GameScene);
};

#endif
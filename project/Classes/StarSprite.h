#ifndef _STAR_SPRITE_H_
#define _STAR_SPRITE_H_

#include "cocos2d.h"

class StarSprite : public cocos2d::CCSprite
{
public:
    void moveToDown(cocos2d::CCPoint& pos, float delayTime = 0.0);
    void moveToLeft(cocos2d::CCPoint& pos);
    
    void setStarColor(int kColor) { m_kStarColor = kColor; }
    int getStarColor() { return m_kStarColor; }

    CREATE_FUNC(StarSprite);

private:
    int m_kStarColor;
};

#endif
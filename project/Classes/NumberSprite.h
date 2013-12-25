#ifndef _NUMBER_SPRITE_H_
#define _NUMBER_SPRITE_H_

#include "cocos2d.h"

class NumberSprite : public cocos2d::CCNode
{
public:
	NumberSprite(std::string ke,int num);

    static NumberSprite* create(std::string ke,int num);

    virtual bool init();

private:
    void _addNumberSprite(cocos2d::CCPoint& off, int n);

private:
    int m_nRealNumber;
	std::string key;
};

#endif
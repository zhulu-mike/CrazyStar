#ifndef _IMAGE_CONFIG_H_
#define _IMAGE_CONFIG_H_

#include "cocos2d.h"

class ImageConfig
{
public:
    static ImageConfig* sharedImageConfig();
    static void destory();
private:
    static ImageConfig* m_pImageConfig;

public:
    ImageConfig();
    ~ImageConfig();
    void loadImageConfig(const char* fileName);
    
    cocos2d::CCTexture2D* getTexture2D();
    cocos2d::CCRect getNumberRect(int n);

private:
    void _parserConfig(const char* name, const cocos2d::CCRect& rect);
private:

    cocos2d::CCSpriteBatchNode*  m_pSpriteBatchNode;

    std::vector<cocos2d::CCRect> m_whiteNumber;
    std::vector<cocos2d::CCRect> m_yellowNumber;
};

#endif
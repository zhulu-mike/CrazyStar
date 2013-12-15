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
    void parserConfig(const char* name, const cocos2d::CCRect& rect);
private:
    std::vector<cocos2d::CCRect> m_whiteNumber;
    std::vector<cocos2d::CCRect> m_yellowNumber;
};

#endif
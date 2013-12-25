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
    
    cocos2d::CCTexture2D* getTexture2D(std::string key);
    cocos2d::CCRect getNumberRect(std::string key,int n);

private:
    void _parserConfig(std::vector<cocos2d::CCRect> &numVector,const char* name, const cocos2d::CCRect& rect);
private:

	std::map<std::string,cocos2d::CCSpriteBatchNode*> m_pictureMap;
	std::map<std::string,std::vector<cocos2d::CCRect>> m_rectMap;

    std::vector<cocos2d::CCRect> m_whiteNumber;
    std::vector<cocos2d::CCRect> m_yellowNumber;
};

#endif
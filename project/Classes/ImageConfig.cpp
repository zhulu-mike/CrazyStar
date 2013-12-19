#include "ImageConfig.h"
#include "support/tinyxml2/tinyxml2.h"
#include "Utils.h"

USING_NS_CC;

ImageConfig* ImageConfig::m_pImageConfig = NULL;

ImageConfig::ImageConfig()
    : m_whiteNumber(10)
    , m_yellowNumber(10)
{

}

ImageConfig::~ImageConfig()
{
    m_pSpriteBatchNode->release();
}

ImageConfig* ImageConfig::sharedImageConfig()
{
    if (m_pImageConfig == NULL)
        m_pImageConfig = new ImageConfig();
    
    return m_pImageConfig;
}

void ImageConfig::destory()
{
    if (m_pImageConfig != NULL)
        delete m_pImageConfig;
}

void ImageConfig::loadImageConfig(const char* fileName)
{
    CCAssert(fileName != NULL, "Load image config faild!");

    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(fileName);
    tinyxml2::XMLElement* pRootElem = xmlDoc.RootElement();

    m_pSpriteBatchNode = CCSpriteBatchNode::create(pRootElem->Attribute("fileName"));
    m_pSpriteBatchNode->retain();

    CCAssert(m_pSpriteBatchNode != NULL, "Load image faild!");

    tinyxml2::XMLElement* pChildElem = pRootElem->FirstChildElement("child");
    while(pChildElem != NULL)
    {
        _parserConfig(pChildElem->Attribute("name"), 
            CCRectMake(pChildElem->FloatAttribute("x"), 
                   pChildElem->FloatAttribute("y"),
                   pChildElem->FloatAttribute("w"),
                   pChildElem->FloatAttribute("h")));

        pChildElem = pChildElem->NextSiblingElement("child");
    }
}

void ImageConfig::_parserConfig(const char* name, const cocos2d::CCRect& rect)
{
    if (!strcmp(name, "white0")) {  
        m_whiteNumber[0] = rect;
    }
    else if (!strcmp(name, "white1")) {
        m_whiteNumber[1] = rect;
    }
    else if (!strcmp(name, "white2")) {
        m_whiteNumber[2] = rect;
    }
    else if (!strcmp(name, "white3")) {
        m_whiteNumber[3] = rect;
    }
    else if (!strcmp(name, "white4")) {
        m_whiteNumber[4] = rect;
    }
    else if (!strcmp(name, "white5")) {
        m_whiteNumber[5] = rect;
    }
    else if (!strcmp(name, "white6")) {
        m_whiteNumber[6] = rect;
    }
    else if (!strcmp(name, "white7")) {
        m_whiteNumber[7] = rect;
    }
    else if (!strcmp(name, "white8")) {
        m_whiteNumber[8] = rect;
    }
    else if (!strcmp(name, "white9")) {
        m_whiteNumber[9] = rect;
    }
}

cocos2d::CCTexture2D* ImageConfig::getTexture2D()
{
    return m_pSpriteBatchNode->getTexture();
}

cocos2d::CCRect ImageConfig::getNumberRect(int n)
{
    RETURN_VALUE_IF(n < 0 || n > 9, CCRectZero);

    return m_whiteNumber[n];
}
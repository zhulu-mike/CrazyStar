#include "ImageConfig.h"
#include "support/tinyxml2/tinyxml2.h"

USING_NS_CC;

ImageConfig* ImageConfig::m_pImageConfig = NULL;

ImageConfig::ImageConfig()
    : m_whiteNumber(10)
    , m_yellowNumber(10)
{

}

ImageConfig::~ImageConfig()
{

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

    tinyxml2::XMLElement* pChildElem = pRootElem->FirstChildElement("child");
    while(pChildElem != NULL)
    {
        parserConfig(pChildElem->Attribute("name"), 
            CCRect(pChildElem->FloatAttribute("x"), 
                   pChildElem->FloatAttribute("y"),
                   pChildElem->FloatAttribute("w"),
                   pChildElem->FloatAttribute("h")));

        pChildElem = pRootElem->NextSiblingElement("child");
    }
}

void ImageConfig::parserConfig(const char* name, const cocos2d::CCRect& rect)
{
    if (name == "white0") {  
        m_whiteNumber[0] = rect;
    }
    else if (name == "white1") {
        m_whiteNumber[1] = rect;
    }
    else if (name == "white2") {
        m_whiteNumber[2] = rect;
    }
    else if (name == "white3") {
        m_whiteNumber[3] = rect;
    }
    else if (name == "white4") {
        m_whiteNumber[4] = rect;
    }
    else if (name == "white5") {
        m_whiteNumber[5] = rect;
    }
    else if (name == "white6") {
        m_whiteNumber[6] = rect;
    }
    else if (name == "white7") {
        m_whiteNumber[7] = rect;
    }
    else if (name == "white8") {
        m_whiteNumber[8] = rect;
    }
    else if (name == "white9") {
        m_whiteNumber[9] = rect;
    }
}
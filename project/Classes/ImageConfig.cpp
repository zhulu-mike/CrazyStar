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
    //m_pSpriteBatchNode->release();
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

	

    CCSpriteBatchNode * m_pSpriteBatchNode = CCSpriteBatchNode::create(pRootElem->Attribute("fileName"));
    m_pSpriteBatchNode->retain();
	const char* key = pRootElem->Attribute("key");
	m_pictureMap[std::string(key)] = m_pSpriteBatchNode;

    CCAssert(m_pSpriteBatchNode != NULL, "Load image faild!");

    tinyxml2::XMLElement* pChildElem = pRootElem->FirstChildElement("child");
	std::vector<cocos2d::CCRect> m_num(10);

    while(pChildElem != NULL)
    {
        _parserConfig(m_num, pChildElem->Attribute("name"), 
            CCRectMake(pChildElem->FloatAttribute("x"), 
                   pChildElem->FloatAttribute("y"),
                   pChildElem->FloatAttribute("w"),
                   pChildElem->FloatAttribute("h")));

        pChildElem = pChildElem->NextSiblingElement("child");
    }
	m_rectMap[key] = m_num;
}

void ImageConfig::_parserConfig(std::vector<cocos2d::CCRect> &numVector, const char* name, const cocos2d::CCRect& rect)
{
    if (!strcmp(name, "0.png")) {  
        numVector[0] = rect;
    }
    else if (!strcmp(name, "1.png")) {
        numVector[1] = rect;
    }
    else if (!strcmp(name, "2.png")) {
        numVector[2] = rect;
    }
    else if (!strcmp(name, "3.png")) {
        numVector[3] = rect;
    }
    else if (!strcmp(name, "4.png")) {
        numVector[4] = rect;
    }
    else if (!strcmp(name, "5.png")) {
        numVector[5] = rect;
    }
    else if (!strcmp(name, "6.png")) {
        numVector[6] = rect;
    }
    else if (!strcmp(name, "7.png")) {
        numVector[7] = rect;
    }
    else if (!strcmp(name, "8.png")) {
        numVector[8] = rect;
    }
    else if (!strcmp(name, "9.png")) {
        numVector[9] = rect;
    }
}

cocos2d::CCTexture2D* ImageConfig::getTexture2D(std::string key)
{
	return m_pictureMap[key]->getTexture();
}

cocos2d::CCRect ImageConfig::getNumberRect(std::string key, int n)
{
    RETURN_VALUE_IF(n < 0 || n > 9, CCRectZero);

    return m_rectMap[key][n];
}
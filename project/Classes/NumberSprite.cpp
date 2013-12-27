#include "NumberSprite.h"
#include "Utils.h"
#include "ImageConfig.h"

USING_NS_CC;

NumberSprite* NumberSprite::create(std::string ke, int num)
{ 
    NumberSprite *pRet = new NumberSprite(ke,num); 
    if (pRet && pRet->init()) 
    {
        pRet->autorelease(); 
        return pRet;
    } 
    else 
    {
        delete pRet;
        pRet = NULL;
        return NULL; 
    } 
}

NumberSprite::NumberSprite(std::string ke,int num)
    : m_nRealNumber(num)
	, key(ke)
	, realWidth(0.0f)
{
}

bool NumberSprite::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCNode::init());

        std::string numStr = StringFormatHelper()("%d", m_nRealNumber);

        CCPoint off = CCPointZero;

        for (std::size_t i = 0; i < numStr.length(); ++ i)
        {
            _addNumberSprite(off, numStr[i] - '0');
        }

        bRet = true;

    }while(0);

    return bRet;
}

void NumberSprite::_addNumberSprite(CCPoint& off, int n)
{
    CCRect rect = ImageConfig::sharedImageConfig()->getNumberRect(key,n);
    CCTexture2D* pTexture2D = ImageConfig::sharedImageConfig()->getTexture2D(key);
    CCSprite* pSprite = CCSprite::createWithTexture(pTexture2D, rect); 

    pSprite->setPosition(off);
    pSprite->setAnchorPoint(ccp(0, 0));

    addChild(pSprite);

	realWidth += rect.size.width;
    off.x += rect.size.width;
}
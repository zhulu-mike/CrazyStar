#include "MyCCMenu.h"

USING_NS_CC;

bool MyCCMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	lastTouch = touch->getLocation();
	return CCMenu::ccTouchBegan(touch,event);
}

MyCCMenu* MyCCMenu::create()
{
    return MyCCMenu::create(NULL, NULL);
}

MyCCMenu * MyCCMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    MyCCMenu *pRet = MyCCMenu::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;
}

MyCCMenu* MyCCMenu::createWithArray(CCArray* pArrayOfItems)
{
    MyCCMenu *pRet = new MyCCMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

MyCCMenu* MyCCMenu::createWithItems(CCMenuItem* item, va_list args)
{
    CCArray* pArray = NULL;
    if( item )
    {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
        }
    }
    
    return MyCCMenu::createWithArray(pArray);
}

MyCCMenu* MyCCMenu::createWithItem(CCMenuItem* item)
{
    return MyCCMenu::create(item, NULL);
}
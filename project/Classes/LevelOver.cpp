
#include "LevelOver.h"
#include "ResourceConfig.h"
USING_NS_CC;


LevelOver::LevelOver()
    : jieGuo(NULL)
{

}

bool LevelOver::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF (!CCLayer::init());

        
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		jieGuo = CCSprite::create(g_sLevelPassImage);
		this->addChild(jieGuo);
		jieGuo->setAnchorPoint(ccp(0, 0));
		jieGuo->setPositionX((s.width-jieGuo->getTextureRect().size.width)*0.5);
		jieGuo->setPositionY(s.height*0.5);

		CCSprite *shengYU = CCSprite::create(g_sLevelLeftImage);
		this->addChild(shengYU);
		shengYU->setAnchorPoint(ccp(0, 0));
		shengYU->setPositionX((s.width-shengYU->getTextureRect().size.width)*0.5);
		shengYU->setPositionY(jieGuo->getPositionY()-jieGuo->getTextureRect().size.height*0.5-40);

		CCSprite *jiangLi = CCSprite::create(g_sLevelAwardImage);
		this->addChild(jiangLi);
		jiangLi->setAnchorPoint(ccp(0, 0));
		jiangLi->setPositionX((s.width-jiangLi->getTextureRect().size.width)*0.5);
		jiangLi->setPositionY(shengYU->getPositionY()-shengYU->getTextureRect().size.height*0.5-60);

		CCSprite *totalSoce = CCSprite::create(g_sLevelScoreImage);
		this->addChild(totalSoce);
		totalSoce->setAnchorPoint(ccp(0, 0));
		totalSoce->setPositionX((s.width-totalSoce->getTextureRect().size.width)*0.5);
		totalSoce->setPositionY(jiangLi->getPositionY()-jiangLi->getTextureRect().size.height*0.5-80);
		
		bRet = true;

    }while(0);

    return bRet;
}

void LevelOver::onShow(bool isPass, int leftCount, int awardScore)
{
	CCTexture2D * p ;

	if (!isPass)
	{
		p = CCSprite::create(g_sLevelLoseImage)->getTexture();
	}else{
		p = CCSprite::create(g_sLevelPassImage)->getTexture();
	}
	jieGuo->setTexture(p);
}
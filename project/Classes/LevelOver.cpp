
#include "LevelOver.h"
#include "ResourceConfig.h"
#include "NumberSprite.h"
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
		jieGuo->setPositionY(s.height*0.5+200);

		totalSoce = CCSprite::create(g_sLevelScoreImage);
		this->addChild(totalSoce);
		totalSoce->setAnchorPoint(ccp(0, 0));
		totalSoce->setPositionX((s.width-totalSoce->getTextureRect().size.width)*0.5-60);
		totalSoce->setPositionY(jieGuo->getPositionY()-jieGuo->getTextureRect().size.height-100);

		shengYU = CCSprite::create(g_sLevelLeftImage);
		this->addChild(shengYU);
		shengYU->setAnchorPoint(ccp(0, 0));
		shengYU->setPositionX((s.width-shengYU->getTextureRect().size.width)*0.5-60);
		shengYU->setPositionY(totalSoce->getPositionY()-totalSoce->getTextureRect().size.height-50);

		jiangLi = CCSprite::create(g_sLevelAwardImage);
		this->addChild(jiangLi);
		jiangLi->setAnchorPoint(ccp(0, 0));
		jiangLi->setPositionX((s.width-jiangLi->getTextureRect().size.width)*0.5-60);
		jiangLi->setPositionY(shengYU->getPositionY()-shengYU->getTextureRect().size.height-50);

		
		
		bRet = true;

    }while(0);

    return bRet;
}

void LevelOver::onShow(bool isPass, int leftCount, int awardScore, int levelScore)
{
	CCTexture2D * p ;

	if (!isPass)
	{
		p = CCSprite::create(g_sLevelLoseImage)->getTexture();
	}else{
		p = CCSprite::create(g_sLevelPassImage)->getTexture();
	}
	jieGuo->setTexture(p);

	NumberSprite * leftTip = NumberSprite::create("white60",leftCount);
	this->addChild(leftTip);
	leftTip->setAnchorPoint(ccp(0,0));
	leftTip->setPositionX(shengYU->getPositionX()+shengYU->getContentSize().width + 20);
	leftTip->setPositionY(shengYU->getPositionY());

	NumberSprite * awardTip = NumberSprite::create("white60",awardScore);
	this->addChild(awardTip);
	awardTip->setAnchorPoint(ccp(0,0));
	awardTip->setPositionX(jiangLi->getPositionX()+jiangLi->getContentSize().width + 20);
	awardTip->setPositionY(jiangLi->getPositionY());

	NumberSprite * levelScoreTip = NumberSprite::create("white60",levelScore);
	this->addChild(levelScoreTip);
	levelScoreTip->setAnchorPoint(ccp(0,0));
	levelScoreTip->setPositionX(totalSoce->getPositionX()+totalSoce->getContentSize().width + 20);
	levelScoreTip->setPositionY(totalSoce->getPositionY());
}
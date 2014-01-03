#include "AchieveLayer.h"
#include "AchieveManager.h"
#include "AchieveItemSprite.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "StarCanvas.h"
#include "ScoreControl.h"
#include "ResourceConfig.h"
#include "NumberSprite.h"
#include "BackgroundLayer.h"

USING_NS_CC;

AchieveLayer::AchieveLayer()
	: totalCount(0)
{
	this->setTouchEnabled(false);
}

void AchieveLayer::completeAchieveItems(int type, int value)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	std::vector<AchieveManager::AchieveVO> arr = AchieveManager::sharedAchieveManager()->getCanCompleteAchieve(type,value);
	int i = 0;
	int size = arr.size();
	float totalHeight = size * 130 - 10;
	float beginY = s.height-(s.height - totalHeight) * 0.5;
	for (;i<size;i++)
	{
		AchieveItemSprite* sp = AchieveItemSprite::create(arr[i]);
		this->addChild(sp);
		sp->setPositionX(s.width*0.5);
		sp->setPositionY(beginY-60);
		sp->playEffect();
		sp->setScale(0.0f);
		sp->runAction(
			CCSequence::create(
			CCScaleTo::create(0.5f,1.0f,1.0f),
			CCDelayTime::create(2.0f),
			CCCallFunc::create(this, callfunc_selector(AchieveLayer::removeItem)),
			CCRemoveSelf::create(),
			NULL)
			);
		if (arr[i].score > 0)
			showSocreAddEffect(sp->getPosition(),arr[i].score);
		if (arr[i].life > 0)
			showLifeAddEffect(ccp(sp->getPosition().x-100,sp->getPositionY()),arr[i].life);
		if (arr[i].gold > 0)
			showGoldAddEffect(ccp(sp->getPosition().x+100,sp->getPositionY()),arr[i].gold);
		beginY = beginY - 130;
		totalCount++;
	}
}

void AchieveLayer::removeItem()
{
	totalCount--;
}

void AchieveLayer::showSocreAddEffect(CCPoint pos, int count)
{
	GameLayer* app = (GameLayer*)GameScene::sharedGameScene()->getMainGameLayer();
	StarCanvas* spp = app->getStarCanvas();
	spp->getScoreControl()->addCurrentScore(count);
	CCPoint p = spp->getScoreControl()->getCurrentScorePosition();

	CCSprite* scoreApp = CCSprite::create();
	CCSprite* baiJia = CCSprite::create(g_sWhiteJiaImage);
	baiJia->setAnchorPoint(ccp(0,0));
	scoreApp->addChild(baiJia);

    NumberSprite* pSprite = NumberSprite::create("white36",count);
	pSprite->setAnchorPoint(ccp(0,0));
	pSprite->setPositionX(baiJia->getContentSize().width+5);
	scoreApp->addChild(pSprite);

    scoreApp->setPosition(ccp(pos.x-(pSprite->getPositionX()+pSprite->realWidth)*0.5,pos.y));
    scoreApp->setAnchorPoint(ccp(0, 0));
    this->addChild(scoreApp);
    scoreApp->runAction(
        CCSequence::create(
            CCDelayTime::create(0.5f),
			CCMoveTo::create(1.0f, ccp(scoreApp->getPositionX(), scoreApp->getPositionY()+150)),
            CCRemoveSelf::create(),
            NULL)
			);
}

void AchieveLayer::showLifeAddEffect(CCPoint pos,int count)
{
	BackgroundLayer* app = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	app->addLifeCount(count);

	CCSprite* lifeApp = CCSprite::create();
	CCSprite* tao = CCSprite::create(g_sTaoxinImage);
	tao->setAnchorPoint(ccp(0,0));
	lifeApp->addChild(tao);

	CCSprite* baiJia = CCSprite::create(g_sWhiteJiaImage);
	baiJia->setAnchorPoint(ccp(0,0));
	baiJia->setPosition(ccp(tao->getContentSize().width+5,0));
	lifeApp->addChild(baiJia);

    NumberSprite* pSprite = NumberSprite::create("white36",count);
	pSprite->setAnchorPoint(ccp(0,0));
	pSprite->setPositionX(baiJia->getPositionX()+baiJia->getContentSize().width+5);
	lifeApp->addChild(pSprite);

	lifeApp->setPosition(ccp(pos.x-(pSprite->getPositionX()+pSprite->realWidth)*0.5,pos.y));
    this->addChild(lifeApp);
    lifeApp->runAction(
        CCSequence::create(
            CCDelayTime::create(0.5f),
			CCMoveTo::create(1.0f, ccp(lifeApp->getPositionX(), lifeApp->getPositionY()+150)),
            CCRemoveSelf::create(),
            NULL)
			);
}

void AchieveLayer::showGoldAddEffect(CCPoint pos,int count)
{
	BackgroundLayer* app = (BackgroundLayer*)GameScene::sharedGameScene()->getBackgroundLayer();
	app->addGoldCount(count);

	CCSprite* goldApp = CCSprite::create();
	CCSprite* tao = CCSprite::create(g_sGoldBGImage);
	tao->setAnchorPoint(ccp(0,0));
	goldApp->addChild(tao);

	CCSprite* baiJia = CCSprite::create(g_sWhiteJiaImage);
	baiJia->setAnchorPoint(ccp(0,0));
	baiJia->setPosition(ccp(tao->getContentSize().width+5,0));
	goldApp->addChild(baiJia);

    NumberSprite* pSprite = NumberSprite::create("white36",count);
	pSprite->setAnchorPoint(ccp(0,0));
	pSprite->setPositionX(baiJia->getPositionX()+baiJia->getContentSize().width+5);
	goldApp->addChild(pSprite);

    goldApp->setPosition(ccp(pos.x-(pSprite->getPositionX()+pSprite->realWidth)*0.5,pos.y));
    this->addChild(goldApp);
    goldApp->runAction(
        CCSequence::create(
            CCDelayTime::create(0.5f),
			CCMoveTo::create(1.0f, ccp(goldApp->getPositionX(), goldApp->getPositionY()+150)),
            CCRemoveSelf::create(),
            NULL)
			);
}
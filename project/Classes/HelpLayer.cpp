#include "HelpLayer.h"
#include "ResourceConfig.h"
#include "GameScene.h"
#include "MyCCMenu.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

HelpLayer::HelpLayer()
	: beginY(0.0f)
{

}


bool HelpLayer::init()
{
    bool bRet = false;

    do
    {
		CC_BREAK_IF (!CCLayer::init());
		CCSprite *p = CCSprite::create(g_sPanelBGImage);
		CCSize ps = p->getContentSize();

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		CCScale9Sprite * bg = CCScale9Sprite::create(g_sPanelBGImage,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		bg->setPreferredSize(CCSizeMake(s.width,s.height-beginY));
		this->setTouchEnabled(true);
		this->setTouchPriority(-999);

		p = CCSprite::create(g_sPanelBGImage2);
		ps = p->getContentSize();
		bg = CCScale9Sprite::create(g_sPanelBGImage2,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		bg->setPreferredSize(CCSizeMake(s.width-20,s.height-20-beginY));
		bg->setPositionX(10);
		bg->setPositionY(10);

		CCMenuItemImage * back = CCMenuItemImage::create(g_sBackButtonUpBGImage,g_sBackButtonDownBGImage,
														this, 
														menu_selector(HelpLayer::onCommandBack));
		back->setAnchorPoint(ccp(0,1));

		MyCCMenu * backMenu = MyCCMenu::create(back,NULL);
		this->addChild(backMenu);
		backMenu->setPositionX(28);
		backMenu->setPositionY(1000-beginY);
		backMenu->setTouchPriority(-1000);

		bRet = true;
	}while(0);

	return bRet;

}

void HelpLayer::onCommandBack(CCObject * pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
	GameScene::sharedGameScene()->hideHelpLayer();
}

void HelpLayer::onShow(int type)
{
	from = type;

}
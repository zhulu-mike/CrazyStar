#include "AchieveView.h"
#include "cocos-ext.h"
#include "AchieveManager.h"
#include "AchieveItemSprite.h"
#include "ResourceConfig.h"
#include "MyCCMenu.h"
#include "GameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

AchieveView::AchieveView()
	: view(NULL)
	, beginY(20)
	, beginX(24)
	, gapX(30)
	, gapY(20)
	, viewBeginY(70)
{


}

bool AchieveView::init()
{
	 bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCNode::init());

        CCSize s = CCDirector::sharedDirector()->getWinSize();

		CCSprite *p = CCSprite::create(g_sPanelBGImage);
		CCSize ps = p->getContentSize();

        
		CCScale9Sprite * bg = CCScale9Sprite::create(g_sPanelBGImage,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		bg->setPreferredSize(CCSizeMake(s.width,s.height));
		this->setTouchEnabled(true);
		this->setTouchPriority(-1999);

		p = CCSprite::create(g_sPanelBGImage2);
		ps = p->getContentSize();
		bg = CCScale9Sprite::create(g_sPanelBGImage2,CCRectMake(0,0,ps.width,ps.height),CCRectMake(20,20,ps.width-40,ps.height-40));
		this->addChild(bg);
		bg->setAnchorPoint(ccp(0,0));
		bg->setPreferredSize(CCSizeMake(s.width-20,s.height-20));
		bg->setPositionX(10);
		bg->setPositionY(10);

		CCMenuItemImage * back = CCMenuItemImage::create(g_sBackButtonUpBGImage,g_sBackButtonDownBGImage,
														this, 
														menu_selector(AchieveView::onCommandBack));
		back->setAnchorPoint(ccp(0,1));

		MyCCMenu * backMenu = MyCCMenu::create(back,NULL);
		this->addChild(backMenu);
		backMenu->setPositionX(28);
		backMenu->setPositionY(s.height-beginY);
		backMenu->setTouchPriority(-2000);

		view = CCScrollView::create();
		this->addChild(view);
		view->setPosition(ccp(beginX,viewBeginY));
		view->setViewSize(CCSizeMake(s.width-beginX*2, s.height-viewBeginY*2));
		view->setAnchorPoint(ccp(0,0));
		view->setTouchPriority(-1999);
		view->setDirection(kCCScrollViewDirectionVertical);
		
		CCSize viewSize = view->getViewSize();

		std::vector<AchieveManager::AchieveVO> vos = AchieveManager::sharedAchieveManager()->getAchieves();
		int i = 0;
		int size = vos.size();
		for (i=0;i<size;i++)
		{
			AchieveItemSprite * item = AchieveItemSprite::create(vos[i]);
			view->addChild(item);
			int col = (i % 2) == 0 ? 0 : 1;
			int row = i * 0.5;
			item->setPosition(ccp(col*350+350*0.5+col*gapX, viewSize.height-row*120-60-row*gapY));
		}

		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,this->getTouchPriority(),true);
        bRet = true;

    }while(0);
    return bRet;

}

bool AchieveView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void AchieveView::onCommandBack(CCObject * pSender)
{
	GameScene::sharedGameScene()->hideAchieveViewLayer();
}
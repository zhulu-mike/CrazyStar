#include "GameLayer.h"
#include "Utils.h"
#include "LevelTips.h"
#include "GameScene.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

GameLayer::GameLayer()
    : m_pCurrentScore(NULL)
    , m_popColor(kStarNone)
    , m_nSelectedStatus(0)
{

}

GameLayer::~GameLayer()
{
    for (int i = 0; i < MAP_SIZE; ++ i)
        for (int j = 0; j < MAP_SIZE; ++ j)
            m_starMap[i][j]->release();
}

bool GameLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF (!CCLayer::init());
        
        setTouchEnabled( true );

        showLevelInfo();
        showTargetScore();
        showCurrentScore();

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		float totalWidth = MAP_SIZE * 48 + (MAP_SIZE-1) * 5;
		beginX = (s.width - totalWidth) * 0.5;
		beginY = 5;

        initStarImage();

        generateMap();

		

        bRet = true;
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(g_gameBackGroundSound,true);
    }while(0);

    return bRet;
}

void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it ++)
    {
        CCPoint location = ((CCTouch*)(*it))->getLocation();
        int xIndex = floor((location.x - beginX) / 53.f);
        int yIndex = floor((location.y - beginY) / 53.f);

        m_popStar.clear();
        m_popColor = kStarNone;
        popStar(xIndex, yIndex);

        if (m_popStar.size() == 1)
        {
            m_starMap[xIndex][yIndex]->setStarColor(m_popColor);
        }
        else if (m_popStar.size() > 1)
        {
            addCurrentScore(5 * m_popStar.size() * m_popStar.size());
            removeStar();
            fillHole();
			if (m_popStar.size() > 10)
			{
				 SimpleAudioEngine::sharedEngine()->playEffect(g_waOSound);
			}
        }

        break;
    }

    if (!m_popStar.empty())
    {
        if (isOver())
        {
            removeAll();
        }
    }
}

void GameLayer::showLevelInfo()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemImage* pItemButton = CCMenuItemImage::create(
        g_sBombImage, 
        g_sBombImage, 
        this, 
        menu_selector(GameLayer::onCommandItem));
    CCMenuItemImage* pMagicButton = CCMenuItemImage::create(
        g_sMagicImage, 
        g_sMagicImage, 
        this, 
        menu_selector(GameLayer::onCommandMagic));
    CCMenuItemImage* pBackButton = CCMenuItemImage::create(
        g_sBombImage, 
        g_sBombImage, 
        this, 
        menu_selector(GameLayer::onCommandBack));

    CCMenu* pMenu = CCMenu::create(pItemButton, pMagicButton, pBackButton, NULL);
    pMenu->setPosition(ccp(s.width-100, s.height-100));
    pMenu->alignItemsHorizontally();
    this->addChild(pMenu);

    CCSprite* pSprite = CCSprite::create(g_sLevelImage, CCRectMake(0, 0, 230, 39));
    pSprite->setPosition(ccp(120, s.height-100));
    this->addChild(pSprite);
}

void GameLayer::showTargetScore()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    char txt[64] = {0};
    sprintf(txt, "target : %d", LevelTips::getLevelTarget());

    CCLabelTTF *pTargetScore = CCLabelTTF::create(txt, "Arial", 25, CCSizeMake(200, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    pTargetScore->setAnchorPoint(ccp(0, 0));
    pTargetScore->setPosition(ccp(0, s.height - 76));

    this->addChild(pTargetScore);
}

void GameLayer::showCurrentScore()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    char txt[64] = {0};
    sprintf(txt, "score : %d", LevelTips::m_currentScore);

    m_pCurrentScore = CCLabelTTF::create(txt, "Arial", 25, CCSizeMake(200, 30), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    m_pCurrentScore->setAnchorPoint(ccp(0, 0));
    m_pCurrentScore->setPosition(ccp(0, s.height - 122));

    this->addChild(m_pCurrentScore);
}

void GameLayer::addCurrentScore(int nScore)
{
    char txt[64] = {0};
    sprintf(txt, "score : %d", LevelTips::m_currentScore += nScore);

    m_pCurrentScore->setString(txt);
}

void GameLayer::onCommandBack(CCObject* pSender)
{
    LevelTips::m_level = 1;
    LevelTips::m_currentScore = 0;
	onDispose();
    GameScene::switchToMainMenu();
}

void GameLayer::onCommandItem(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
}

void GameLayer::onCommandMagic(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);

void GameLayer::onDispose()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void GameLayer::initStarImage()
{
    m_pStarBatchNode[kStarRed] = CCSpriteBatchNode::create(g_sRedStarImage);
    addChild(m_pStarBatchNode[kStarRed], 0, kStarRed);
    
    m_pStarBatchNode[kStarYellow] = CCSpriteBatchNode::create(g_sYellowStarImage);
    addChild(m_pStarBatchNode[kStarYellow], 0, kStarYellow);

    m_pStarBatchNode[kStarGreen] = CCSpriteBatchNode::create(g_sGreenStarImage);
    addChild(m_pStarBatchNode[kStarGreen], 0, kStarGreen);

    m_pStarBatchNode[kStarBlue] = CCSpriteBatchNode::create(g_sBlueStarImage);
    addChild(m_pStarBatchNode[kStarBlue], 0, kStarBlue);

    m_pStarBatchNode[kStarPurple] = CCSpriteBatchNode::create(g_sPurpleStarImage);
    addChild(m_pStarBatchNode[kStarPurple], 0, kStarPurple);
}

void GameLayer::generateMap()
{
    //set rand() seed
    srand((unsigned)time(NULL));

    for (int i = 0; i < MAP_SIZE; ++ i) 
    {
        for (int j = 0; j < MAP_SIZE; ++ j)
        {
            int nColor = randLimit(kStarRed, kStarPurple);
            CCTexture2D* pTexture = m_pStarBatchNode[nColor]->getTexture();

            m_starMap[i][j] = StarSprite::create();
            m_starMap[i][j]->initWithTexture(pTexture, CCRectMake(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height));
            m_starMap[i][j]->setPosition(ccp(beginX + 53 * i, CCDirector::sharedDirector()->getWinSize().height));
            m_starMap[i][j]->setAnchorPoint(ccp(0, 0));
            m_starMap[i][j]->setStarColor(nColor);
            
            m_starMap[i][j]->retain();

            m_pStarBatchNode[nColor]->addChild(m_starMap[i][j], 0);           
            
            m_starMap[i][j]->moveToDown(ccp(beginX + 53 * i , 5 + 53 * j), i % 2 ? j * 0.1 : (j * 0.1 + 0.1));
        }
    }
}

void GameLayer::popStar(int x, int y)
{
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE)
    {
        return ;
    }

    if (m_starMap[x][y]->getStarColor() <= kStarNone || m_starMap[x][y]->getStarColor() >= kStarMax)
    {
        return ;
    }

    if (m_popStar.empty())
    {
        m_popColor = m_starMap[x][y]->getStarColor();
    }
    else if (m_popColor != m_starMap[x][y]->getStarColor())
    {
        return;
    }

    m_starMap[x][y]->setStarColor(kStarNone);
    m_popStar.push_back(ccp(x, y));

    /*四个方向*/
    for (int i = 0; i < 4; ++ i)
    {
        switch(i)
        {
        case kNorth:
            popStar(x, y+1);
            break;
        case kEast:
            popStar(x+1, y);
            break;
        case kSouth:
            popStar(x, y-1);
            break;
        case kWest:
            popStar(x-1, y);
            break;
        }
    }
}

void GameLayer::removeStar()
{
    int x = 0, y = 0;

    for (std::size_t i = 0; i < m_popStar.size(); ++ i)
    {
        x = m_popStar[i].x;
        y = m_popStar[i].y;

        m_pStarBatchNode[m_popColor]->removeChild(m_starMap[x][y], true);
    }
}

void GameLayer::fillHole()
{
    /*首先横向循环*/
    for (int i = 0; i < MAP_SIZE; ++ i)
    {
        int nonePos = -1; 
        for (int j = 0; j < MAP_SIZE; ++ j)
        {
            if (m_starMap[i][j]->getStarColor() == kStarNone && nonePos == -1)
            {
                nonePos = j;
                continue;
            }

            if (m_starMap[i][j]->getStarColor() != kStarNone && nonePos != -1)
            {
                m_starMap[i][j]->stopAllActions();
                m_starMap[i][j]->moveToDown(ccp(beginX + 53 * i , beginY + 53 * nonePos));

                CC_SWAP(m_starMap[i][nonePos], m_starMap[i][j], StarSprite*);
                nonePos ++;
            }
        }
    }

    /*然后纵向循环*/
    int nonePos = -1; 
    for (int j = 0; j < MAP_SIZE; ++ j)
    {
        if (m_starMap[j][0]->getStarColor() == kStarNone && nonePos == -1)
        {
            nonePos = j;
            continue;
        }

        if (m_starMap[j][0]->getStarColor() == kStarNone || nonePos == -1)
            continue;

        /*移动一列*/
        for (int i = 0; i < MAP_SIZE && m_starMap[j][i]->getStarColor() != kStarNone; ++ i)
        {
            m_starMap[j][i]->stopAllActions();
            m_starMap[j][i]->moveToLeft(ccp(beginX + 53 * nonePos , beginY + 53 * i));

            CC_SWAP(m_starMap[nonePos][i], m_starMap[j][i], StarSprite*);
        }

        nonePos ++;
    }
}

bool GameLayer::isOver()
{
    for (int i = 0; i < MAP_SIZE; ++ i)
    {
        for (int j = 0; j < MAP_SIZE; ++ j)
        {
            if (m_starMap[i][j]->getStarColor() == kStarNone)
                continue;

            for (int k = 0; k < 4; ++ k)
            {
                switch(k)
                {
                case kNorth:
                    if (isSameColor(i, j+1, m_starMap[i][j]->getStarColor()))
                        return false;
                    break;
                case kEast:
                    if (isSameColor(i+1, j, m_starMap[i][j]->getStarColor()))
                        return false;
                    break;
                case kSouth:
                    if (isSameColor(i, j-1, m_starMap[i][j]->getStarColor()))
                        return false;
                    break;
                case kWest:
                    if (isSameColor(i-1, j, m_starMap[i][j]->getStarColor()))
                        return false;
                    break;
                }
            }
        }
    }

    return true;
}

bool GameLayer::isSameColor(int x, int y, int kColor)
{
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE)
    {
        return false;
    }

    if (m_starMap[x][y]->getStarColor() == kColor)
    {
        return true;
    }

    return false;
}

void GameLayer::nextLevel()
{
    LevelTips::m_level += 1;
	onDispose();
    GameScene::switchToLevelTips();
}

void GameLayer::removeAll()
{
    StarSprite* pSprite = NULL;
    int count = 0;

    for (int i = MAP_SIZE - 1; i >= 0; -- i)
    {
        for (int j = 0; j < MAP_SIZE; ++ j)
        {
            if (m_starMap[j][i]->getStarColor() == kStarNone)
            {
                continue;
            }

            m_starMap[j][i]->runAction(
                CCSequence::create(
                    CCDelayTime::create(count++ * 0.2), 
                    CCMoveBy::create(0.2, m_starMap[j][i]->getPosition()), 
                    CCRemoveSelf::create(), 
                    NULL));

            if (count <= 4)
                addCurrentScore(5 + (count-1)*10);

            pSprite = m_starMap[j][i];
        }
    }

    if (pSprite != NULL)
    {
        pSprite->stopAllActions();

        pSprite->runAction(
            CCSequence::create(
            CCDelayTime::create(count * 0.2), 
            CCMoveBy::create(0.2, pSprite->getPosition()), 
            CCRemoveSelf::create(),
            CCCallFunc::create(this, callfunc_selector(GameLayer::gameOver)),
            NULL));
    }
    else
    {
        gameOver();
    }
}

void GameLayer::gameOver()
{
    if (LevelTips::m_currentScore >= LevelTips::getLevelTarget())
        nextLevel();
    else
        onCommandBack(NULL);
}
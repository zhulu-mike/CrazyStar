#include "StarCanvas.h"
#include <SimpleAudioEngine.h>
#include "ResourceConfig.h"
#include "Utils.h"
#include "StarSprite.h"
#include "ScoreControl.h"
#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

#define SHOW_STAR_WIDTH (m_fStarWidth+m_fIntervalX)
#define SHOW_STAR_HEIGHT (m_fStarHeight+m_fIntervalY)
#define REAL_POS_BY_INDEX(x, y) ccp(m_fBeginX+SHOW_STAR_WIDTH*x, m_fBeginY+SHOW_STAR_HEIGHT*y)

StarCanvas::StarCanvas()
    : m_nPopColor(kStarNone)
    , m_fBeginX(5)
    , m_fBeginY(5)
    , m_fIntervalX(5)
    , m_fIntervalY(5)
    , m_fStarWidth(48)
    , m_fStarHeight(48)
{

}

StarCanvas::~StarCanvas()
{
    releaseAllStar();
}

bool StarCanvas::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!CCNode::init());

        /*��ʼ������ͼƬ*/
        m_pStarBatchNode[kStarRed] = CCSpriteBatchNode::create(g_sRedStarImage);
        CC_BREAK_IF(!m_pStarBatchNode[kStarRed]);
        addChild(m_pStarBatchNode[kStarRed], 0, kStarRed);

        m_pStarBatchNode[kStarYellow] = CCSpriteBatchNode::create(g_sYellowStarImage);
        CC_BREAK_IF(!m_pStarBatchNode[kStarYellow]);
        addChild(m_pStarBatchNode[kStarYellow], 0, kStarYellow);

        m_pStarBatchNode[kStarGreen] = CCSpriteBatchNode::create(g_sGreenStarImage);
        CC_BREAK_IF(!m_pStarBatchNode[kStarGreen]);
        addChild(m_pStarBatchNode[kStarGreen], 0, kStarGreen);

        m_pStarBatchNode[kStarBlue] = CCSpriteBatchNode::create(g_sBlueStarImage);
        CC_BREAK_IF(!m_pStarBatchNode[kStarBlue]);
        addChild(m_pStarBatchNode[kStarBlue], 0, kStarBlue);

        m_pStarBatchNode[kStarPurple] = CCSpriteBatchNode::create(g_sPurpleStarImage);
        CC_BREAK_IF(!m_pStarBatchNode[kStarPurple]);
        addChild(m_pStarBatchNode[kStarPurple], 0, kStarPurple);

        /*��ʼ���÷�*/
        m_pScoreControl = ScoreControl::create();
        CC_BREAK_IF(!m_pScoreControl);
        addChild(m_pScoreControl);

        bRet = true;
    }while(0);

    return bRet;
}

void StarCanvas::onEnter()
{
    CCNode::onEnter();

    generateStarMap();
}

void StarCanvas::onExit()
{
    CCNode::onExit();

    releaseAllStar();
}

void StarCanvas::generateStarMap()
{
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < MAP_SIZE; ++ i) 
        for (int j = 0; j < MAP_SIZE; ++ j)
            _generateOneStar(i, j, randLimit(kStarRed, kStarPurple));
}

void StarCanvas::releaseAllStar()
{
    for (int i = 1; i < kStarMax; ++ i)
        m_pStarBatchNode[i]->removeAllChildren();

    for (int i = 0; i < MAP_SIZE; ++ i) 
        for (int j = 0; j < MAP_SIZE; ++ j)
            m_pStarMap[i][j]->release();
}

void StarCanvas::_generateOneStar(int x, int y, int c)
{
    CCTexture2D* pTexture = m_pStarBatchNode[c]->getTexture();

    m_pStarMap[x][y] = StarSprite::create();

    m_pStarMap[x][y]->initWithTexture(pTexture, CCRectMake(0, 0, pTexture->getContentSize().width, pTexture->getContentSize().height));
    m_pStarMap[x][y]->setPosition(ccp(m_fBeginX + 53 * x, CCDirector::sharedDirector()->getWinSize().height));
    m_pStarMap[x][y]->setAnchorPoint(ccp(0, 0));
    m_pStarMap[x][y]->setStarColor(c);
    m_pStarMap[x][y]->setStarType(c);
    m_pStarMap[x][y]->retain();
    m_pStarMap[x][y]->moveToDown(REAL_POS_BY_INDEX(x, y), x % 2 ? y * 0.1 : (y * 0.1 + 0.1));

    m_pStarBatchNode[c]->addChild(m_pStarMap[x][y], 0);
}

void StarCanvas::touchStarCanvas(cocos2d::CCPoint& location)
{
    int xIndex = floor((location.x-m_fBeginX)/SHOW_STAR_WIDTH);
    int yIndex = floor((location.y-m_fBeginY)/SHOW_STAR_HEIGHT);

    m_popStar.clear();
    m_nPopColor = kStarNone;
    popStar(xIndex, yIndex);

    if (m_popStar.size() == 1)
    {
        m_pStarMap[xIndex][yIndex]->setStarColor(m_nPopColor);
    }
    else if (m_popStar.size() > 1)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(g_sSelectedSound);
        m_pScoreControl->addCurrentScore(5 * m_popStar.size() * m_popStar.size());
        removeStar();
        fillHole();

        if (m_popStar.size() > 10)
        {
            SimpleAudioEngine::sharedEngine()->playEffect(g_waOSound);
        }
    }


    if (!m_popStar.empty())
    {
        if (isHasPopStar())
        {
            clearAllStar();
        }
    }
}

void StarCanvas::popStar(int x, int y)
{
    RETURN_NONE_IF(x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE);

    RETURN_NONE_IF(m_pStarMap[x][y]->getStarColor() <= kStarNone || m_pStarMap[x][y]->getStarColor() >= kStarMax);

    RETURN_NONE_IF(!m_popStar.empty() && m_nPopColor != m_pStarMap[x][y]->getStarColor());

    if (m_popStar.empty())
        m_nPopColor = m_pStarMap[x][y]->getStarColor();

    m_pStarMap[x][y]->setStarColor(kStarNone);
    m_popStar.push_back(ccp(x, y));

    /*�ֱ��ж��ĸ������Ƿ�����ͬ����*/
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

void StarCanvas::removeStar()
{
    int x = 0, y = 0;

    for (std::size_t i = 0; i < m_popStar.size(); ++ i)
    {
        x = m_popStar[i].x;
        y = m_popStar[i].y;

		playPopEffect(CCPointMake(m_pStarMap[x][y]->getPosition().x, m_pStarMap[x][y]->getPosition().y), m_pStarMap[x][y]->getStarType());
       
		m_pStarBatchNode[m_nPopColor]->removeChild(m_pStarMap[x][y], true);
    }
}

void StarCanvas::fillHole()
{
    /*���Ⱥ���ѭ��*/
    for (int i = 0; i < MAP_SIZE; ++ i)
    {
        int nonePos = -1; 
        for (int j = 0; j < MAP_SIZE; ++ j)
        {
            if (m_pStarMap[i][j]->getStarColor() == kStarNone && nonePos == -1)
            {
                nonePos = j;
                continue;
            }

            if (m_pStarMap[i][j]->getStarColor() != kStarNone && nonePos != -1)
            {
                m_pStarMap[i][j]->stopAllActions();
                m_pStarMap[i][j]->moveToDown(REAL_POS_BY_INDEX(i, nonePos));

                CC_SWAP(m_pStarMap[i][nonePos], m_pStarMap[i][j], StarSprite*);
                nonePos ++;
            }
        }
    }

    /*Ȼ������ѭ��*/
    int nonePos = -1; 
    for (int j = 0; j < MAP_SIZE; ++ j)
    {
        if (m_pStarMap[j][0]->getStarColor() == kStarNone && nonePos == -1)
        {
            nonePos = j;
            continue;
        }

        if (m_pStarMap[j][0]->getStarColor() == kStarNone || nonePos == -1)
            continue;

        /*�ƶ�һ��*/
        for (int i = 0; i < MAP_SIZE && m_pStarMap[j][i]->getStarColor() != kStarNone; ++ i)
        {
            m_pStarMap[j][i]->stopAllActions();
            m_pStarMap[j][i]->moveToLeft(REAL_POS_BY_INDEX(nonePos, i));

            CC_SWAP(m_pStarMap[nonePos][i], m_pStarMap[j][i], StarSprite*);
        }

        nonePos ++;
    }
}

bool StarCanvas::isHasPopStar()
{
    for (int i = 0; i < MAP_SIZE; ++ i)
    {
        for (int j = 0; j < MAP_SIZE; ++ j)
        {
            if (m_pStarMap[i][j]->getStarColor() == kStarNone)
                continue;

            for (int k = 0; k < 4; ++ k)
            {
                switch(k)
                {
                case kNorth:
                    if (isSameColor(i, j+1, m_pStarMap[i][j]->getStarColor()))
                        return false;
                    break;
                case kEast:
                    if (isSameColor(i+1, j, m_pStarMap[i][j]->getStarColor()))
                        return false;
                    break;
                case kSouth:
                    if (isSameColor(i, j-1, m_pStarMap[i][j]->getStarColor()))
                        return false;
                    break;
                case kWest:
                    if (isSameColor(i-1, j, m_pStarMap[i][j]->getStarColor()))
                        return false;
                    break;
                }
            }
        }
    }

    return true;
}

bool StarCanvas::isSameColor(int x, int y, int kColor)
{
    RETURN_VALUE_IF(x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE, false);

    RETURN_VALUE_IF(m_pStarMap[x][y]->getStarColor() == kColor, true);

    return false;
}

void StarCanvas::clearAllStar()
{
    StarSprite* pSprite = NULL;
    int count = 0;

    for (int i = MAP_SIZE - 1; i >= 0; -- i)
    {
        for (int j = 0; j < MAP_SIZE; ++ j)
        {
            if (m_pStarMap[j][i]->getStarColor() == kStarNone)
            {
                continue;
            }

            m_pStarMap[j][i]->runAction(
                CCSequence::create(
                    CCDelayTime::create(count++ * 0.2f), 
                    CCMoveBy::create(0.2f, m_pStarMap[j][i]->getPosition()), 
                    CCRemoveSelf::create(), 
                    NULL));

            if (count <= 4)
                m_pScoreControl->addCurrentScore(5 + (count-1)*10);

            pSprite = m_pStarMap[j][i];
        }
    }

    if (pSprite != NULL)
    {
        pSprite->stopAllActions();

        pSprite->runAction(
            CCSequence::create(
            CCDelayTime::create(count * 0.2f), 
            CCMoveBy::create(0.2f, pSprite->getPosition()), 
            CCRemoveSelf::create(),
            CCCallFunc::create(this, callfunc_selector(StarCanvas::gameOver)),
            NULL));
    }
    else
    {
        gameOver();
    }
}

void StarCanvas::gameOver()
{
    if (m_pScoreControl->isUpLevel())
    {
        m_pScoreControl->addCurrentLevel(1);
        GameScene::sharedGameScene()->switchToGameLayer();
    }
    else
    {
        m_pScoreControl->clearAllScore();
        GameScene::sharedGameScene()->switchToGameLayer();
    }
}

void StarCanvas::playPopEffect(CCPoint& point, int type)
{
    CCParticleSystem* mitter = CCParticleFireworks::create();
    
    this->addChild(mitter);

    ccColor4F startColorVar = {0.0f, 0.0f, 0.0f, 0.0f};
    ccColor4F startColor = {0.0f, 0.0f, 0.0f, 1.0f};

    if (type == kStarRed){
        startColor.r = 1.0f;
        mitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(g_sSmallRedStarImage) );
    }else if (type == kStarYellow){
        startColor.r = 1.0f;
        startColor.g = 1.0f;
        mitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(g_sSmallYellowStarImage) );
    }else if (type == kStarGreen){
        startColor.g = 1.0f;
        mitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(g_sSmallGreenStarImage) );
    }else if (type == kStarBlue){
        startColor.b = 1.0f;
        mitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(g_sSmallBlueStarImage) );
    }else if (type == kStarPurple){
        startColor.r = 1.0f;
        startColor.b = 1.0f;
        mitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(g_sSmallZiStarImage) );
    }
    mitter->setPosition(point.x, point.y);
    mitter->setTotalParticles(20);
    mitter->setEmissionRate(100);

    mitter->setGravity(CCPointMake(0,-500));

    mitter->setStartSize(20);
    mitter->setStartSizeVar(10);
    mitter->setEndSize(kCCParticleStartSizeEqualToEndSize);
    mitter->setEndSizeVar(0);

    mitter->setSpeedVar(50);
    mitter->setSpeed(500);

    mitter->setLife(2);
    mitter->setLifeVar(0);


    mitter->setStartColorVar(startColorVar);
    mitter->setStartColor(startColor);
    mitter->setEndColor(startColor);
    mitter->setEndColorVar(startColorVar);
    //mitter->setStartRadius(20);

    mitter->setAngle(30);
    mitter->setAngleVar(300);

    mitter->setEmitterMode(kCCParticleModeGravity);
    mitter->setDuration(0.2f);
    mitter->setAutoRemoveOnFinish(true);
}

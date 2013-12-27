#include "ScoreControl.h"
#include "ResourceConfig.h"
#include "NumberSprite.h"
#include "Utils.h"

USING_NS_CC;

ScoreControl::ScoreControl()
    : m_nCurrentLevel(1)
    , m_nCurrentScore(0)
	,m_nLastScore(0)
    , m_pCurrentScoreLabel(NULL)
    , m_pTargetScoreLabel(NULL)
	, m_pGuan(NULL)
	, m_pMuBiao(NULL)
	, m_pLevelImg(NULL)
	, m_pTargetImg(NULL)
{

}

ScoreControl::~ScoreControl()
{

}

bool ScoreControl::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!CCNode::init());

        CCSize s = CCDirector::sharedDirector()->getWinSize();

		CCSprite*di = CCSprite::create(g_sDiImage);
		this->addChild(di);
		di->setAnchorPoint(ccp(0,1));
		di->setPositionX(10);
		di->setPositionY(s.height-65);

		m_pGuan = CCSprite::create(g_sGuanImage);
		this->addChild(m_pGuan);
		m_pGuan->setAnchorPoint(ccp(0,1));
		m_pGuan->setPositionX(50);
		m_pGuan->setPositionY(s.height-65);

		m_pMuBiao = CCSprite::create(g_sMuBiaoImage);
		this->addChild(m_pMuBiao);
		m_pMuBiao->setAnchorPoint(ccp(0,1));
		m_pMuBiao->setPositionX(241);
		m_pMuBiao->setPositionY(s.height-65);

		setCurrentLevel(1);
		setCurrentScore(0);
        bRet = true;

    }while(0);

    return bRet;
}

void ScoreControl::setCurrentLevel(int nLevel)
{
    m_nCurrentLevel = nLevel;
	updateLevel();
    setTargetScore();
}


void ScoreControl::addCurrentLevel(int nLevel)
{
	setCurrentLevel(m_nCurrentLevel+nLevel);
	m_nLastScore = m_nCurrentScore;
    setTargetScore();
}

void ScoreControl::addCurrentScore(int nScore)
{
	setCurrentScore(m_nCurrentScore+nScore);
}

void ScoreControl::setCurrentScore(int nScore)
{
    m_nCurrentScore = nScore;

    if (m_pCurrentScoreLabel != NULL)
	{
		m_pCurrentScoreLabel->removeFromParent();
		m_pCurrentScoreLabel = NULL;
	}
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pCurrentScoreLabel = NumberSprite::create("white60",nScore);
	this->addChild(m_pCurrentScoreLabel);
	m_pCurrentScoreLabel->setAnchorPoint(ccp(0,0));
	m_pCurrentScoreLabel->setPositionX(s.width*0.5-m_pCurrentScoreLabel->realWidth*0.5);
	m_pCurrentScoreLabel->setPositionY(s.height-176);
}

void ScoreControl::setTargetScore()
{
   // m_pTargetScoreLabel->setString(StringFormatHelper()("target : %d", getTargetScore()));
	if (m_pTargetImg != NULL)
	{
		m_pTargetImg->removeFromParent();
		m_pTargetImg = NULL;
	}
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pTargetImg = NumberSprite::create("white48",getTargetScore());
	this->addChild(m_pTargetImg);
	m_pTargetImg->setAnchorPoint(ccp(0,0));
	m_pTargetImg->setPositionX(m_pMuBiao->getPositionX()+m_pMuBiao->getContentSize().width+20);
	m_pTargetImg->setPositionY(s.height-105);
}

int ScoreControl::getTargetScore()
{
    if (m_nCurrentLevel < 4)
        return 250*m_nCurrentLevel*(m_nCurrentLevel+3);
    else if (m_nCurrentLevel < 54)
        return 4500+2020*(m_nCurrentLevel-3)+10*(m_nCurrentLevel*m_nCurrentLevel-7*m_nCurrentLevel+12);
    else
        return 133000+(m_nCurrentLevel-54)*3000;

    return 0;
}

bool ScoreControl::isUpLevel()
{
    RETURN_VALUE_IF(m_nCurrentScore < getTargetScore(), false);

    return true;
	//return false;
}

void ScoreControl::clearAllScore()
{
    setCurrentLevel(1);
    setCurrentScore(0);
}

cocos2d::CCPoint ScoreControl::getCurrentScorePosition()
{
    return m_pCurrentScoreLabel->getPosition();
}

void ScoreControl::renewScore()
{
	setCurrentScore(m_nLastScore);
}

int ScoreControl::getCurrentLevelScore()
{
	return m_nCurrentScore - m_nLastScore;
}

void ScoreControl::updateLevel()
{
	if(m_pLevelImg != NULL){
		m_pLevelImg->removeFromParent();
		m_pLevelImg = NULL;
	}
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pLevelImg = NumberSprite::create("white48",m_nCurrentLevel);
	this->addChild(m_pLevelImg);
	m_pLevelImg->setAnchorPoint(ccp(0,0));
	m_pLevelImg->setPositionX(64);
	m_pLevelImg->setPositionY(s.height-109);

	m_pGuan->setPositionX(m_pLevelImg->getPositionX()+m_pLevelImg->realWidth+10);
}
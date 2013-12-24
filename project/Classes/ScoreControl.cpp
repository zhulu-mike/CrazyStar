#include "ScoreControl.h"
#include "Utils.h"

USING_NS_CC;

ScoreControl::ScoreControl()
    : m_nCurrentLevel(1)
    , m_nCurrentScore(0)
	,m_nLastScore(0)
    , m_pCurrentScoreLabel(NULL)
    , m_pTargetScoreLabel(NULL)
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

        /*初始化当前分数和目标分数*/
        m_pTargetScoreLabel = CCLabelTTF::create(StringFormatHelper()("target : 0"), 
                                        "Arial", 
                                        20, 
                                        CCSizeMake(200, 30), 
                                        kCCTextAlignmentLeft, 
                                        kCCVerticalTextAlignmentCenter);
        m_pTargetScoreLabel->setAnchorPoint(ccp(0, 0));
        m_pTargetScoreLabel->setPosition(ccp(0, s.height - 76));

        this->addChild(m_pTargetScoreLabel);

        m_pCurrentScoreLabel = CCLabelTTF::create(StringFormatHelper()("score : 0"), 
                                        "Arial", 
                                        20, 
                                        CCSizeMake(200, 30), 
                                        kCCTextAlignmentLeft, 
                                        kCCVerticalTextAlignmentCenter);
        m_pCurrentScoreLabel->setAnchorPoint(ccp(0, 0));
        m_pCurrentScoreLabel->setPosition(ccp(0, s.height - 122));
        
        this->addChild(m_pCurrentScoreLabel);

        setTargetScore();

        bRet = true;

    }while(0);

    return bRet;
}

void ScoreControl::setCurrentLevel(int nLevel)
{
    m_nCurrentLevel = nLevel;

    setTargetScore();
}


void ScoreControl::addCurrentLevel(int nLevel)
{
    m_nCurrentLevel += nLevel;
	m_nLastScore = m_nCurrentScore;
    setTargetScore();
}

void ScoreControl::addCurrentScore(int nScore)
{
    m_pCurrentScoreLabel->setString(StringFormatHelper()("score : %d", m_nCurrentScore+=nScore));
}

void ScoreControl::setCurrentScore(int nScore)
{
    m_nCurrentScore = nScore;

    m_pCurrentScoreLabel->setString(StringFormatHelper()("score : %d", nScore));
}

void ScoreControl::setTargetScore()
{
    m_pTargetScoreLabel->setString(StringFormatHelper()("target : %d", getTargetScore()));
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
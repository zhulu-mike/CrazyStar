#include "AchieveManager.h"
#include "support/tinyxml2/tinyxml2.h"

USING_NS_CC;

AchieveManager* AchieveManager::_instance = NULL;

AchieveManager::AchieveManager()
{

}

AchieveManager* AchieveManager::sharedAchieveManager()
{
    if (_instance == NULL)
        _instance = new AchieveManager();
    
    return _instance;
}

void AchieveManager::destory()
{
    if (_instance != NULL)
        delete _instance;
}

void AchieveManager::loadConfigFile(const char* fileName)
{
	CCAssert(fileName != NULL, "Load achieve config faild!");

    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(fileName);
    tinyxml2::XMLElement* pRootElem = xmlDoc.RootElement();

	tinyxml2::XMLElement* pChildElem = pRootElem->FirstChildElement("p");

    while(pChildElem != NULL)
    {
		parseConfigItem(achives, pChildElem->IntAttribute("id"), 
				   pChildElem->IntAttribute("score"), 
                   pChildElem->IntAttribute("life"),
                   pChildElem->IntAttribute("gold"),
				   pChildElem->BoolAttribute("again"),
				   pChildElem->IntAttribute("difflevel"),
				   pChildElem->Attribute("condition"));

        pChildElem = pChildElem->NextSiblingElement("p");
    }
}

void AchieveManager::parseConfigItem(std::vector<AchieveVO> &arr,int id, int score,int life, int gold, bool again, int difflevel, const char* conditions)
{ 
	struct AConditon con;
	char conChar[64];
	char *conChars = strcpy(conChar,conditions);
	char * cc = strtok(conChars,"-");
	con.type = atoi(cc);
	cc = strtok(NULL,"-");
	con.value = atoi(cc);

	struct AchieveVO vo;
	vo.id = id;
	vo.again = again;
	vo.condit = con;
	vo.difflevel = difflevel;
	vo.gold = gold;
	vo.life = life;
	vo.score = score;
	vo.complete = false;
	arr.push_back(vo);
}

std::vector<AchieveManager::AchieveVO> AchieveManager::getCanCompleteAchieve(int type, int value)
{
	int size = achives.size();
	std::vector<AchieveVO> ret;
	for (int i=0;i < size; i++)
	{
		if (achives[i].condit.type == type)
		{
			if (achives[i].again && isComplete(type, value, achives[i].condit.value)){
				ret.push_back(achives[i]);
				achives[i].completeCount++;
			}else if (!achives[i].again && !achives[i].complete && isComplete(type, value, achives[i].condit.value)){
				ret.push_back(achives[i]);
				achives[i].complete = true;
				achives[i].completeCount = 1;
			}
		}
	}
	return ret;
}

bool AchieveManager::isComplete(int type, int value, int standard)
{
	bool ret = false;
	//�����ۻ����˶��ٷ�
	if (type == 1)
	{
		ret = value >= standard;
	}else if (type == 2)
	{
		//ͨ�صڼ���
		ret = value >= standard;
	}else if (type == 3)
	{
		//һ��������������
		ret = value >= standard;
	}else if (type == 4)
	{
		//���ص÷ֳ���Ŀ��ֶ���
		ret = value >= standard;
	}else if (type == 5)
	{
		//���صö��ٷ�
		ret = value >= standard;
	}else if (type == 6)
	{
		//ʣ�ཱ�����˶��ٷ�
		ret = value >= standard;
	}
	else if (type == 7)
	{
		//ʣ����������С�ڵ��ڶ���
		ret = value <= standard;
	}
	else if (type == 8)
	{
		//�����������ǵĴ���
		ret = value >= standard;
	}
	else if (type == 9)
	{
		//ʣ�������������ڶ���
		ret = value >= standard;
	}
	else if (type == 10)
	{
		//�ۻ���ս�ؿ�����
		ret = value >= standard;
	}
	else if (type == 11)
	{
		//��Ϸ���ۻ��÷ֶ��� 
		ret = value >= standard;
	}
	return ret;
}
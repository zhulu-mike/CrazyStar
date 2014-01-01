#ifndef _ACHIEVE_MANAGER_H
#define _ACHIEVE_MANAGER_H

#include "cocos2d.h"

class AchieveManager
{
public:
    static AchieveManager* sharedAchieveManager();
    static void destory();

	struct AConditon
	{
		int type;
		int value;
	};

	struct AchieveVO
	{
		int id;
		int score;
		int life;
		int gold;
		bool again;
		int difflevel;
		AConditon condit;
		bool complete;
		int completeCount;
	};

	std::vector<AchieveManager::AchieveVO> getAchieves(){return achives;};

private:
    static AchieveManager* _instance;
	std::vector<AchieveVO> achives;
	void parseConfigItem(std::vector<AchieveVO> &arr,int id, int score,int life, int gold, bool again, int difflevel, const char* conditions);
	bool isComplete(int type, int value, int standard);
public:
    AchieveManager();
	void loadConfigFile(const char* fileName);
	std::vector<AchieveManager::AchieveVO> getCanCompleteAchieve(int type, int value);















};

#endif
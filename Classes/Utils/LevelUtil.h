//
//  LevelUtil.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#ifndef __TenWaterDrop__LevelUtil__
#define __TenWaterDrop__LevelUtil__

#include <string>
#include <vector>

class StageInfo {
public:
    std::string zappers;
    std::string solutions;
    int complexity, tapCounts, level;
};

class LevelUtil {
public:
    
    static int getUserCurLevelStage(int level);
    
    static void setUserCurLevelStage(int level, int stage);
    
    static int getUserClassicStage();
    
    static void setUserClassicStage(int stage);
    
    static int getLevelCount();
    
    static int getLevelStageCount(int level);
    
    static void loadLevel(int level);
    
    static StageInfo* getLevelStageInfo(int level, int stage);
    
    static void readInXML(const char * file, std::vector<StageInfo>* curData);

    static StageInfo* getClassicStageInfo(int stage);
    
    static int getClassicStageCount();
    
private:
    
    static const int LEVEL_COUNT = 11;
    
    static std::vector<StageInfo>* _levels[LEVEL_COUNT];
    
    static std::vector<StageInfo> _classic;
    
    static void readInLevel(int level);
    static void readInClassic();
};

#endif /* defined(__TenWaterDrop__LevelUtil__) */

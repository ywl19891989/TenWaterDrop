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

class LevelInfo {
public:
    std::string zappers;
    std::string solutions;
    int complexity, tapCounts, level;
};

class LevelUtil {
public:
    
    static int getUserCurStageLevel(int stage);
    
    static void setUserCurStageLevel(int stage, int level);
    
    static int getStageCount();
    
    static int getStageLevelCount(int stage);
    
    static void loadStage(int stage);
    
    static LevelInfo* getStageLevelInfo(int stage, int level);

private:
    
    static const int LEVEL_COUNT = 11;
    
    static std::vector<LevelInfo>* _stages[LEVEL_COUNT];
    
    static void readInStage(int stage);
};

#endif /* defined(__TenWaterDrop__LevelUtil__) */

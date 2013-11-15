//
//  StageModel.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#ifndef __TenWaterDrop__StageModel__
#define __TenWaterDrop__StageModel__

#include <vector>

class LevelInfo {
public:
    int _levelId;
    int _initDatas[36];
    std::vector<int> _solutions;
    int _tapCount;
    int _complexity;
};

class StageInfo {
public:
    int getLevelCount();
    LevelInfo* getLevelInfo(int level);
    std::vector<LevelInfo*> _levels;
};

class StageModel {
private:
    StageModel();
public:
    static StageModel* share(){
        static StageModel share;
        return &share;
    }
    
    int getStageCount();
    StageInfo* getStage(int level);
    
private:
    StageInfo* _stages[11];
};

#endif /* defined(__TenWaterDrop__StageModel__) */

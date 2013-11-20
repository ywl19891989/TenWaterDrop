//
//  LevelUtil.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#include "LevelUtil.h"
#include "cocos2d.h"

USING_NS_CC;

std::vector<StageInfo>* LevelUtil::_levels[LEVEL_COUNT] = {NULL};

void LevelUtil::loadLevel(int level){
    if(level > 0 && level <= LEVEL_COUNT && _levels[level - 1] == NULL){
        readInLevel(level);
    }
}

int LevelUtil::getUserCurLevelStage(int level){
    
    char temp[128];
    sprintf(temp, "user_level_%d_stage", level);
    
    CCUserDefault* save = CCUserDefault::sharedUserDefault();
    int curLevel = save->getIntegerForKey(temp, 1);
    
    return curLevel;
}

void LevelUtil::setUserCurLevelStage(int level, int stage){
    
    char temp[128];
    sprintf(temp, "user_level_%d_stage", level);
    
    CCUserDefault* save = CCUserDefault::sharedUserDefault();
    
    int oldStage = getUserCurLevelStage(level);
    if(oldStage < stage){
        save->setIntegerForKey(temp, stage);
        CCLOG("set %s, %d", temp, stage);
    }
}

int LevelUtil::getLevelCount(){
    return LEVEL_COUNT;
}

int LevelUtil::getLevelStageCount(int level){
    
    loadLevel(level);
    
    if(level > 0 && level <= LEVEL_COUNT){
        return _levels[level - 1]->size();
    }
    
    return 0;
}

StageInfo* LevelUtil::getLevelStageInfo(int level, int stage){
    
    loadLevel(level);
    
    if(level > 0 && level <= _levels[level - 1]->size()){
        return &_levels[level - 1]->at(stage - 1);
    }
    
    return NULL;
}

void LevelUtil::readInLevel(int level){
    
    char temp[128];
    
    sprintf(temp, "level/LevelPack%d.xml", level);
    CCLOG("readinLevel %d, file: %s", level, temp);
    _levels[level - 1] = new std::vector<StageInfo>;
    
    std::vector<StageInfo>* curLevel = _levels[level - 1];
    
    tinyxml2::XMLElement* curNode = NULL;
    tinyxml2::XMLElement* rootNode = NULL;
    
    tinyxml2::XMLDocument *xmlDoc;
    
    do
    {
        xmlDoc = new tinyxml2::XMLDocument();
        
        unsigned long nSize;
        
        const char* pXmlBuffer = (const char*)CCFileUtils::sharedFileUtils()->getFileData(temp, "rb", &nSize);
        
        if(NULL == pXmlBuffer)
        {
            CCLOG("can not read xml file");
            break;
        }
        
        xmlDoc->Parse(pXmlBuffer);
        
        delete[] pXmlBuffer;
        // get root node
        rootNode = xmlDoc->RootElement();
        
        if (NULL == rootNode)
        {
            CCLOG("read root node error");
            break;
        }
        
        // find the node
        curNode = rootNode->FirstChildElement();
        StageInfo info;
        if (!curNode)
        {
            // There is not xml node, delete xml file.
            CCLOG("this is not a xml File");
            return;
        }
        
        while (NULL != curNode)
        {
            info.level = atoi(curNode->Attribute("number"));
            info.tapCounts = atoi(curNode->Attribute("tapsCount"));
            info.complexity = atoi(curNode->Attribute("complexity"));
            
            info.zappers = curNode->Attribute("zappers");
            info.solutions = curNode->Attribute("solutions");
        
            curLevel->push_back(info);
            
            curNode = curNode->NextSiblingElement();
        }
    } while (0);
}
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

std::vector<LevelInfo>* LevelUtil::_stages[11] = {NULL};

void LevelUtil::loadStage(int stage){
    if(stage > 0 && stage <= 11 && _stages[stage - 1] == NULL){
        readInStage(stage);
    }
}

int LevelUtil::getUserCurStageLevel(int stage){
    
    char temp[128];
    sprintf(temp, "user_stage_%d_level", stage);
    
    CCUserDefault* save = CCUserDefault::sharedUserDefault();
    int curLevel = save->getIntegerForKey(temp, 1);
    
    return curLevel;
}

void LevelUtil::setUserCurStageLevel(int stage, int level){
    
    char temp[128];
    sprintf(temp, "user_stage_%d_level", stage);
    
    CCUserDefault* save = CCUserDefault::sharedUserDefault();
    save->setIntegerForKey(temp, level);
}

int LevelUtil::getStageCount(){
    return 11;
}

int LevelUtil::getStageLevelCount(int stage){
    
    loadStage(stage);
    
    if(stage > 0 && stage <= 11){
        return _stages[stage - 1]->size();
    }
    
    return 0;
}

LevelInfo* LevelUtil::getStageLevelInfo(int stage, int level){
    
    loadStage(stage);
    
    if(level > 0 && level <= _stages[stage - 1]->size()){
        return &_stages[stage - 1]->at(level);
    }
    
    return NULL;
}

void LevelUtil::readInStage(int stage){
    
    char temp[128];
    
    sprintf(temp, "level/LevelPack%d.xml", stage);
    
    _stages[stage - 1] = new std::vector<LevelInfo>;
    
    std::vector<LevelInfo>* curLevel = _stages[stage - 1];
    
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
        LevelInfo info;
        if (!curNode)
        {
            // There is not xml node, delete xml file.
            CCLOG("this is not a xml File");
            return;
        }
        
        while (NULL != curNode)
        {
            CCLOG("name %s", curNode->Name());
            
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
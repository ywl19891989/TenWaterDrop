//
//  SelectLevelScene.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#ifndef __TenWaterDrop__SelectLevelScene__
#define __TenWaterDrop__SelectLevelScene__

#include "cocos2d.h"

class SelectLevelScene : public cocos2d::CCScene {
public:
    CREATE_FUNC(SelectLevelScene);
    bool init();
    
    void onClickBtn(cocos2d::CCNode* node);
    
    void prev();
    void next();
    
    void updateLevel();
    
    void setCurLevel(int stage);
    
private:
    int _curLevel;
    cocos2d::CCSprite *_stageImg, *_stageClickedImg, *_stageClickedImgMask;
    cocos2d::CCLabelTTF *_stageIndexText;
};

class SelectStageScene : public cocos2d::CCScene {
public:
    static SelectStageScene* create(int level);
    bool init(int stage);
    
    void onClickBtn(cocos2d::CCNode* node);
    
    void prev();
    void next();
    
    void updateStage();
    
private:
    int _selectLevel, _userCurStage, _curPage, _totalPages;
    cocos2d::CCNode *_midArea;
    cocos2d::CCMenuItem* _grids[16];
    cocos2d::CCMenuItem* _gridLocks[16];
    cocos2d::CCLabelTTF* _gridTexts[16];
    cocos2d::CCLabelTTF *_indexText;
};

#endif /* defined(__TenWaterDrop__SelectLevelScene__) */

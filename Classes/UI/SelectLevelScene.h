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

class SelectStageScene : public cocos2d::CCScene {
public:
    CREATE_FUNC(SelectStageScene);
    bool init();
    
    void onClickBtn(cocos2d::CCNode* node);
    
    void prev();
    void next();
    
    void updateStage();
    
    void setCurStage(int stage);
    
private:
    int _curStage;
    cocos2d::CCSprite *_stageImg, *_stageClickedImg, *_stageClickedImgMask;
    cocos2d::CCLabelTTF *_stageIndexText;
};

class SelectLevelScene : public cocos2d::CCScene {
public:
    static SelectLevelScene* create(int stage);
    bool init(int stage);
    
    void onClickBtn(cocos2d::CCNode* node);
    
    void prev();
    void next();
    
    void updateStage();
    
private:
    int _selectStage, _userCurLevel, _curPage, _totalPages;
    cocos2d::CCNode *_midArea;
    cocos2d::CCMenuItem* _grids[16];
    cocos2d::CCMenuItem* _gridLocks[16];
    cocos2d::CCLabelTTF* _gridTexts[16];
    cocos2d::CCLabelTTF *_indexText;
};

#endif /* defined(__TenWaterDrop__SelectLevelScene__) */

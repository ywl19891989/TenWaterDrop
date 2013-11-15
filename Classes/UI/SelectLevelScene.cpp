//
//  SelectLevelScene.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#include "SelectLevelScene.h"
#include "UIUtil.h"
#include "ResourceName.h"
#include "LayoutUtil.h"
#include "CoverScene.h"
#include "Constants.h"
#include "LevelUtil.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_RES;

/////////////////////////////////////////////////
/////////////// SelectStageScene ////////////////
/////////////////////////////////////////////////

bool SelectStageScene::init(){
    
    if(!CCScene::init()){
        return false;
    }
    
    CCSprite* bg = CCSprite::create(Images::game::game_bg_jpg);
	addChild(bg, -1);
	bg->setAnchorPoint(ccp(0, 0));
    
	CCMenu* menu = CCMenu::create();
	addChild(menu, 1);
	menu->setAnchorPoint(ccp(0, 0));
	menu->setPosition(ccp(0, 0));
    
	CCMenuItem* backItem = UIUtil::getSingleImageBtn(
                                                     Images::common::back);
	menu->addChild(backItem);
	backItem->setTarget(this, menu_selector(SelectStageScene::onClickBtn));
	backItem->setTag(-1);
	backItem->setAnchorPoint(ccp(1, 0));
    LayoutUtil::layoutTo(backItem, 0, 1, bg, 0, 1, 4, -4);
    
    _stageImg = CCSprite::create(Images::selectLevel::level1);
    _stageClickedImg = CCSprite::create(Images::selectLevel::level1);
    _stageClickedImgMask = CCSprite::create(Images::selectLevel::level1);
    _stageClickedImgMask->setColor(ccBLACK);
    _stageClickedImgMask->setOpacity(80);
    _stageClickedImg->addChild(_stageClickedImgMask, 1);
    LayoutUtil::layoutToParentCenter(_stageClickedImgMask, _stageClickedImg);
    
    CCMenuItem* stageItem = CCMenuItemSprite::create(_stageImg, _stageClickedImg);
    stageItem->setTarget(this, menu_selector(SelectStageScene::onClickBtn));
    stageItem->setScale(1.3);
    stageItem->setTag(1);
    menu->addChild(stageItem);
    LayoutUtil::layoutToParentCenter(stageItem, this);
    
    CCMenuItem* leftArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    leftArrow->setTarget(this, menu_selector(SelectStageScene::prev));
    menu->addChild(leftArrow);
    LayoutUtil::layoutTo(leftArrow, 1, 0.5, stageItem, 0, 0.5, -18);
    
    CCSprite* leftArrowBg = CCSprite::create(Images::selectLevel::icon_arrow);
    leftArrowBg->setScale(1.1);
    leftArrowBg->setColor(ccBLACK);
    addChild(leftArrowBg, 0);
    LayoutUtil::layoutToCenter(leftArrowBg, leftArrow);
    
    
    CCMenuItem* rightArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    rightArrow->setTarget(this, menu_selector(SelectStageScene::next));
    menu->addChild(rightArrow);
    rightArrow->setScaleX(-1);
    LayoutUtil::layoutTo(rightArrow, 0, 0.5, stageItem, 1, 0.5, 18);
    
    CCSprite* rightArrowBg = CCSprite::create(Images::selectLevel::icon_arrow);
    rightArrowBg->setScaleX(-1.1);
    rightArrowBg->setScaleY(1.1);
    rightArrowBg->setColor(ccBLACK);
    addChild(rightArrowBg, 0);
    LayoutUtil::layoutToCenter(rightArrowBg, rightArrow);
    
    _stageIndexText = CCLabelTTF::create("01/11", "arial-bold", 30);
    _stageIndexText->setColor(ccBLACK);
    addChild(_stageIndexText, 1);
    LayoutUtil::layoutTo(_stageIndexText, 0.5, 0, stageItem, 0.5, 1, 0, -20);
    
    CCLabelTTF* title = CCLabelTTF::create("选择难度", "arial-bold", 38);
    title->setColor(ccBLACK);
    addChild(title, 1);
    LayoutUtil::layoutTo(title, 0.5, 0, _stageIndexText, 0.5, 1, 0, 20);
    
    _curStage = 0;
    
    return true;
}

void SelectStageScene::setCurStage(int stage){
    _curStage = stage - 1;
    updateStage();
}

void SelectStageScene::onClickBtn(cocos2d::CCNode *node){
    
    int tag = node->getTag();
    
    if(tag == -1){
        CoverScene* cover = CoverScene::create();
    
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, cover);
    
        CCDirector::sharedDirector()->replaceScene(trans);
    }else if (tag == 1){
        SelectLevelScene* selectLevel = SelectLevelScene::create(_curStage + 1);
        
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, selectLevel);
        
        CCDirector::sharedDirector()->replaceScene(trans);
    }
}

void SelectStageScene::next(){
    _curStage++;
    _curStage = _curStage % 11;
    updateStage();
}

void SelectStageScene::prev(){
    _curStage--;
    _curStage += 11;
    _curStage = _curStage % 11;
    updateStage();
}

void SelectStageScene::updateStage(){
    char temp[128];
    sprintf(temp, "Images/selectLevel/level%d.png", _curStage + 1);
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(temp);
    _stageImg->setTexture(tex);
    _stageClickedImg->setTexture(tex);
    _stageClickedImgMask->setTexture(tex);
    
    sprintf(temp, "%02d/11", _curStage + 1);
    _stageIndexText->setString(temp);
}

/////////////////////////////////////////////////
/////////////// SelectLevelScene ////////////////
/////////////////////////////////////////////////

SelectLevelScene* SelectLevelScene::create(int stage){
    SelectLevelScene* selectLevel = new SelectLevelScene();
    selectLevel->init(stage);
    selectLevel->autorelease();
    return selectLevel;
}

bool SelectLevelScene::init(int stage){
    
    if(!CCScene::init()){
        return false;
    }
    
    _selectStage = stage;
    
    CCSprite* bg = CCSprite::create(Images::game::game_bg_jpg);
	addChild(bg, -1);
	bg->setAnchorPoint(ccp(0, 0));
    
	CCMenu* menu = CCMenu::create();
	addChild(menu, 1);
	menu->setAnchorPoint(ccp(0, 0));
	menu->setPosition(ccp(0, 0));
    
	CCMenuItem* backItem = UIUtil::getSingleImageBtn(
                                                     Images::common::back);
	menu->addChild(backItem);
	backItem->setTarget(this, menu_selector(SelectLevelScene::onClickBtn));
	backItem->setTag(-1);
	backItem->setAnchorPoint(ccp(1, 0));
    LayoutUtil::layoutTo(backItem, 0, 1, bg, 0, 1, 4, -4);
    
    CCLabelTTF* title = CCLabelTTF::create("选择关卡", "arial-bold", 38);
    title->setColor(ccBLACK);
    addChild(title, 1);
    LayoutUtil::layoutTo(title, 0.5, 0, bg, 0.5, 1, 0, -110);
    
    CCLabelTTF* subTitleText = CCLabelTTF::create("难度:01/11", "arial-bold", 30);
    subTitleText->setColor(ccBLACK);
    addChild(subTitleText, 1);
    LayoutUtil::layoutTo(subTitleText, 0.5, 1, title, 0.5, 0, 0, -20);
    
    CCSize midSize = CCSize(400, 400);
    
    _midArea = CCNode::create();
    _midArea->setContentSize(midSize);
    addChild(_midArea, 1);
    LayoutUtil::layoutToCenter(_midArea, bg, 0, -30);
    
    _userCurLevel = LevelUtil::getUserCurStageLevel(_selectStage);
    
    int totalCount = LevelUtil::getStageLevelCount(_selectStage);
    
    _totalPages = totalCount/16 + (totalCount % 16 == 0 ? 0 : 1);
    
    for (int i = 0; i < 16; i++) {
        int index = i + _curPage * 16;
        
        int row = i / 4;
        int col = i % 4;
        
        _grids[i] = UIUtil::getSingleImageBtn(Images::selectLevel::unlock);
        _grids[i]->setTarget(this, menu_selector(SelectLevelScene::onClickBtn));
        menu->addChild(_grids[i]);
        LayoutUtil::layoutTo(_grids[i], 0.5, 0.5, _midArea, 0.5, 1, (col - 1.5f) * (midSize.width * 0.25f), (-row - 0.5) * (midSize.height * 0.25f));
        
        _gridTexts[i] = CCLabelTTF::create("1", "arial", 32);
        _gridTexts[i]->setColor(ccBLACK);
        _grids[i]->addChild(_gridTexts[i], 1);
        LayoutUtil::layoutToParentCenter(_gridTexts[i], _grids[i]);
        
        _gridLocks[i] = UIUtil::getSingleImageBtn(Images::selectLevel::lock);
        menu->addChild(_gridLocks[i]);
        LayoutUtil::layoutToCenter(_gridLocks[i], _grids[i]);
        
        _grids[i]->setVisible(index + 1 <= _userCurLevel);
        _gridLocks[i]->setVisible(index + 1 > _userCurLevel && index < totalCount);
    }
    
    CCMenuItem* leftArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    leftArrow->setTarget(this, menu_selector(SelectLevelScene::prev));
    menu->addChild(leftArrow);
    LayoutUtil::layoutTo(leftArrow, 1, 0.5, _midArea, 0, 0.5, 0);
    
    CCSprite* leftArrowBg = CCSprite::create(Images::selectLevel::icon_arrow);
    leftArrowBg->setScale(1.1);
    leftArrowBg->setColor(ccBLACK);
    addChild(leftArrowBg, 0);
    LayoutUtil::layoutToCenter(leftArrowBg, leftArrow);
    
    
    CCMenuItem* rightArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    rightArrow->setTarget(this, menu_selector(SelectLevelScene::next));
    menu->addChild(rightArrow);
    rightArrow->setScaleX(-1);
    LayoutUtil::layoutTo(rightArrow, 0, 0.5, _midArea, 1, 0.5, 0);
    
    CCSprite* rightArrowBg = CCSprite::create(Images::selectLevel::icon_arrow);
    rightArrowBg->setScaleX(-1.1);
    rightArrowBg->setScaleY(1.1);
    rightArrowBg->setColor(ccBLACK);
    addChild(rightArrowBg, 0);
    LayoutUtil::layoutToCenter(rightArrowBg, rightArrow);
    
    cocos2d::extension::CCScale9Sprite* numBg = cocos2d::extension::CCScale9Sprite::create(CCRect(16, 16, 2, 2), Images::common::numBg);
    numBg->setContentSize(CCSize(110, numBg->getContentSize().height));
    addChild(numBg, 1);
    LayoutUtil::layoutTo(numBg, 1, 0, _midArea, 1, 1, 60, 5);
    
    char temp[32];
    sprintf(temp, "%d/%d", _curPage + 1, _totalPages);
    
    _indexText = CCLabelTTF::create(temp, "arial", 26);
    _indexText->setAnchorPoint(ccp(1, 0));
    addChild(_indexText, 1);
    LayoutUtil::layoutTo(_indexText, 1, 0.5, numBg, 0.7, 0.5, 0, 0);
    
    sprintf(temp, "难度:%02d/11", _selectStage);
    subTitleText->setString(temp);
    
    return true;
}

void SelectLevelScene::onClickBtn(cocos2d::CCNode *node){
    
    int tag = node->getTag();
    
    if(tag == -1){
        SelectStageScene* selectStage = SelectStageScene::create();
        selectStage->setCurStage(_selectStage);
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, selectStage);
        CCDirector::sharedDirector()->replaceScene(trans);
    }else if (tag >= 0){
        
    }
}

void SelectLevelScene::next(){
    _curPage++;
    _curPage = _curPage % _totalPages;
    updateStage();
}

void SelectLevelScene::prev(){
    _curPage--;
    _curPage += _totalPages;
    _curPage = _curPage % _totalPages;
    updateStage();
}

void SelectLevelScene::updateStage(){
    
    char temp[64];
    
    int totalCount = LevelUtil::getStageLevelCount(_selectStage);
    
    for (int i = 0; i < 16; i++) {
        int index = i + _curPage * 16;
        
        sprintf(temp, "%d", index + 1);
        
        _gridTexts[i]->setString(temp);
        
        _grids[i]->setVisible(index + 1 <= _userCurLevel);
        _gridLocks[i]->setVisible(index + 1 > _userCurLevel && index < totalCount);
    }
    
    sprintf(temp, "%d/%d", _curPage + 1, _totalPages);
    _indexText->setString(temp);
}
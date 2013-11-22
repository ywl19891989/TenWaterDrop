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
#include "MusicBtn.h"
#include "LevelGameScene.h"
#include "AdUtil.h"

USING_NS_CC;
USING_NS_RES;

/////////////////////////////////////////////////
/////////////// SelectLevelScene ////////////////
/////////////////////////////////////////////////

bool SelectLevelScene::init(){
    
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
	backItem->setTarget(this, menu_selector(SelectLevelScene::onClickBtn));
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
    stageItem->setTarget(this, menu_selector(SelectLevelScene::onClickBtn));
    stageItem->setScale(1.3);
    stageItem->setTag(1);
    menu->addChild(stageItem);
    LayoutUtil::layoutToParentCenter(stageItem, this);
    
    CCMenuItem* leftArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    leftArrow->setTarget(this, menu_selector(SelectLevelScene::prev));
    menu->addChild(leftArrow);
    LayoutUtil::layoutTo(leftArrow, 1, 0.5, stageItem, 0, 0.5, -18);
    
    CCSprite* leftArrowBg = CCSprite::create(Images::selectLevel::icon_arrow);
    leftArrowBg->setScale(1.1);
    leftArrowBg->setColor(ccBLACK);
    addChild(leftArrowBg, 0);
    LayoutUtil::layoutToCenter(leftArrowBg, leftArrow);
    
    
    CCMenuItem* rightArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    rightArrow->setTarget(this, menu_selector(SelectLevelScene::next));
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
    
    MusicBtn* musicBtn = MusicBtn::create();
    addChild(musicBtn, 1);
	LayoutUtil::layoutTo(musicBtn, 0, 0, bg, 0, 0, 5, 5);
    
    _curLevel = 0;
    
    AdUtil::showAd();
    
    return true;
}

void SelectLevelScene::onEnter(){
    CCScene::onEnter();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
}

void SelectLevelScene::onExit(){
    CCScene::onExit();
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
}

void SelectLevelScene::keyBackClicked(){
    CoverScene* cover = CoverScene::create();
    
    CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, cover);
    
    CCDirector::sharedDirector()->replaceScene(trans);
}

void SelectLevelScene::setCurLevel(int level){
    _curLevel = level - 1;
    updateLevel();
}

void SelectLevelScene::onClickBtn(cocos2d::CCNode *node){
    
    int tag = node->getTag();
    
    if(tag == -1){
        keyBackClicked();
    }else if (tag == 1){
        SelectStageScene* selectLevel = SelectStageScene::create(_curLevel + 1);
        
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, selectLevel);
        
        CCDirector::sharedDirector()->replaceScene(trans);
    }
}

void SelectLevelScene::next(){
    _curLevel++;
    _curLevel = _curLevel % 11;
    updateLevel();
}

void SelectLevelScene::prev(){
    _curLevel--;
    _curLevel += 11;
    _curLevel = _curLevel % 11;
    updateLevel();
}

void SelectLevelScene::updateLevel(){
    char temp[128];
    sprintf(temp, "Images/selectLevel/level%d.png", _curLevel + 1);
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(temp);
    _stageImg->setTexture(tex);
    _stageClickedImg->setTexture(tex);
    _stageClickedImgMask->setTexture(tex);
    
    sprintf(temp, "%02d/11", _curLevel + 1);
    _stageIndexText->setString(temp);
}

/////////////////////////////////////////////////
/////////////// SelectStageScene ////////////////
/////////////////////////////////////////////////

SelectStageScene* SelectStageScene::create(int level){
    SelectStageScene* selectStage = new SelectStageScene();
    selectStage->init(level);
    selectStage->autorelease();
    return selectStage;
}

bool SelectStageScene::init(int level){
    
    if(!CCScene::init()){
        return false;
    }
    
    _selectLevel = level;
    
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

    
    for (int i = 0; i < 16; i++) {
        
        int row = i / 4;
        int col = i % 4;
        
        _grids[i] = UIUtil::getSingleImageBtn(Images::selectLevel::unlock);
        _grids[i]->setTarget(this, menu_selector(SelectStageScene::onClickBtn));
        menu->addChild(_grids[i]);
        LayoutUtil::layoutTo(_grids[i], 0.5, 0.5, _midArea, 0.5, 1, (col - 1.5f) * (midSize.width * 0.25f), (-row - 0.5) * (midSize.height * 0.25f));
        
        _gridTexts[i] = CCLabelTTF::create("1", "arial", 32);
        _gridTexts[i]->setColor(ccBLACK);
        addChild(_gridTexts[i], 9);
        LayoutUtil::layoutToCenter(_gridTexts[i], _grids[i]);
        
        _gridLocks[i] = UIUtil::getSingleImageBtn(Images::selectLevel::lock);
        menu->addChild(_gridLocks[i]);
        LayoutUtil::layoutToCenter(_gridLocks[i], _grids[i]);
        
        _grids[i]->setVisible(false);
    }
    
    CCMenuItem* leftArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    leftArrow->setTarget(this, menu_selector(SelectStageScene::prev));
    menu->addChild(leftArrow);
    LayoutUtil::layoutTo(leftArrow, 1, 0.5, _midArea, 0, 0.5, 0);
    
    CCSprite* leftArrowBg = CCSprite::create(Images::selectLevel::icon_arrow);
    leftArrowBg->setScale(1.1);
    leftArrowBg->setColor(ccBLACK);
    addChild(leftArrowBg, 0);
    LayoutUtil::layoutToCenter(leftArrowBg, leftArrow);
    
    
    CCMenuItem* rightArrow = UIUtil::getSingleImageBtn(Images::selectLevel::icon_arrow);
    rightArrow->setTarget(this, menu_selector(SelectStageScene::next));
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
    
    _indexText = CCLabelTTF::create("1/1", "arial", 26);
    _indexText->setAnchorPoint(ccp(1, 0));
    addChild(_indexText, 1);
    LayoutUtil::layoutTo(_indexText, 1, 0.5, numBg, 0.7, 0.5, 0, 0);
    
    sprintf(temp, "难度:%02d/11", _selectLevel);
    subTitleText->setString(temp);
    
    MusicBtn* musicBtn = MusicBtn::create();
    addChild(musicBtn, 1);
	LayoutUtil::layoutTo(musicBtn, 0, 0, bg, 0, 0, 5, 5);
    
    updateStage();
    
    AdUtil::showAd();
    
    return true;
}

void SelectStageScene::onEnter(){
    CCScene::onEnter();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
}

void SelectStageScene::onExit(){
    CCScene::onExit();
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
}

void SelectStageScene::keyBackClicked(){
    SelectLevelScene* selectLevel= SelectLevelScene::create();
    selectLevel->setCurLevel(_selectLevel);
    CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, selectLevel);
    CCDirector::sharedDirector()->replaceScene(trans);
}

void SelectStageScene::onClickBtn(cocos2d::CCNode *node){
    
    int tag = node->getTag();
    
    if(tag == -1){
        keyBackClicked();
    }else if (tag >= 0){
        CCLOG("clicked %d level %d, stage %d", tag, _selectLevel, tag + 1);
        LevelGameScene* levelGame = LevelGameScene::create();
        levelGame->setData(_selectLevel, tag + 1);
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, levelGame);
        CCDirector::sharedDirector()->replaceScene(trans);
    }
}

void SelectStageScene::next(){
    _curPage++;
    _curPage = _curPage % _totalPages;
    updateStage();
}

void SelectStageScene::prev(){
    _curPage--;
    _curPage += _totalPages;
    _curPage = _curPage % _totalPages;
    updateStage();
}

void SelectStageScene::updateStage(){
    
    char temp[64];
    
    _userCurStage = LevelUtil::getUserCurLevelStage(_selectLevel);
    
    int totalCount = LevelUtil::getLevelStageCount(_selectLevel);
    
    _totalPages = totalCount/16 + (totalCount % 16 == 0 ? 0 : 1);
    
    CCLOG("level %d, stageCount %d, pages %d", _selectLevel, totalCount, _totalPages);
    
    for (int i = 0; i < 16; i++) {
        int index = i + _curPage * 16;
        
        sprintf(temp, "%d", index + 1);
        
        _gridTexts[i]->setString(temp);
        
        if(index + 1 <= _userCurStage){
            _gridTexts[i]->setColor(ccBLACK);
        }else if(index + 1 > _userCurStage && index + 1 <= totalCount){
            _gridTexts[i]->setColor(ccRED);
        }
        _gridTexts[i]->setVisible(index + 1 <= totalCount);
        _grids[i]->setVisible(index + 1 <= _userCurStage);
        _gridLocks[i]->setVisible(index + 1 > _userCurStage && index < totalCount);
        _grids[i]->setTag(index);
    }
    
    sprintf(temp, "%d/%d", _curPage + 1, _totalPages);
    _indexText->setString(temp);
}
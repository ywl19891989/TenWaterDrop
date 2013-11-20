/*
 * ClassicGameScene.cpp
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#include "ClassicGameScene.h"
#include "ResourceName.h"
#include "CoverScene.h"
#include "WaterSprite.h"
#include "ReMainWaterNumSprite.h"
#include "LayoutUtil.h"
#include "UIUtil.h"
#include "ClassicResultDialog.h"
#include "Constants.h"
#include "MusicBtn.h"

USING_NS_CC;
using namespace Resources;

ClassicGameScene::ClassicGameScene() {
	// TODO Auto-generated constructor stub

}

ClassicGameScene::~ClassicGameScene() {
	// TODO Auto-generated destructor stub
    _dropArrays->release();
}

bool ClassicGameScene::init() {
	if (!CCScene::init()) {
		return false;
	}

	CCSprite* bg = CCSprite::create(Images::game::game_bg_jpg);
	addChild(bg, -1);
	bg->setAnchorPoint(ccp(0, 0));

	CCMenu* menu = CCMenu::create();
	addChild(menu);
	menu->setAnchorPoint(ccp(0, 0));
	menu->setPosition(ccp(0, 0));

	_gridBg = CCSprite::create(Images::game::cell);
    _gridBg->setAnchorPoint(CCPointZero);
	addChild(_gridBg);
    LayoutUtil::layoutToCenter(_gridBg, bg, 0, -30);

	CCMenuItem* backItem = UIUtil::getSingleImageBtn(
			Images::common::back);
	menu->addChild(backItem);
	backItem->setTarget(this, menu_selector(ClassicGameScene::onClickBtn));
	backItem->setTag(-1);
	backItem->setAnchorPoint(ccp(1, 0));
    LayoutUtil::layoutTo(backItem, 0, 1, bg, 0, 1, 4, -4);
    
    CCMenuItem* resetItem = UIUtil::getSingleImageBtn(Images::game::btn_reset);
	menu->addChild(resetItem);
	resetItem->setTarget(this, menu_selector(ClassicGameScene::onClickBtn));
	resetItem->setTag(-2);
    LayoutUtil::layoutTo(resetItem, 1, 1, bg, 1, 1, -4, -4);
    
    CCMenu* gridMenu = CCMenu::create();
    addChild(gridMenu, 0);
    LayoutUtil::layoutToParent(gridMenu, 0, 0, this, 0, 0);

	for (int i = 0; i < ROW_NUM; i++) {
		for (int j = 0; j < COL_NUM; j++) {
			int index = i * COL_NUM + j;
			_waterNums[index] = rand() % 4 + 1;

			_waters[index] = WaterSprite::create();
			_waters[index]->setWaterNum(_waterNums[index]);
			addChild(_waters[index], 2);
            _waters[index]->setExplodeListener(this);
            _waters[index]->setTag(index);

			float px = OFFSET_X + j * GRID_WIDTH;
			float py = OFFSET_Y + i * GRID_HEIGHT;
            LayoutUtil::layoutTo(_waters[index], 0.5, 0.5, _gridBg, 0, 0, px, py);
            
            CCMenuItem* item = CCMenuItem::create();
            item->setContentSize(_waters[index]->getContentSize());
            gridMenu->addChild(item);
            item->setTag(index);
            item->setTarget(this, menu_selector(ClassicGameScene::onClickGrid));
            LayoutUtil::layoutToCenter(item, _waters[index]);
		}
	}


	CCSprite* levelInfo = CCSprite::create(Images::game::level);
	addChild(levelInfo, 1);
    LayoutUtil::layoutTo(levelInfo, 1, 0, _gridBg, 1, 1, -20, 4);

	_remainNumText = ReMainWaterNumSprite::create();
	addChild(_remainNumText, 1);
	LayoutUtil::layoutTo(_remainNumText, 1, 0.5, levelInfo, 0, 0.5, -25, 0);
    
    MusicBtn* musicBtn = MusicBtn::create();
    addChild(musicBtn, 1);
	LayoutUtil::layoutTo(musicBtn, 0, 0, bg, 0, 0, 5, 5);
    
    _remainWaterNum = 1;
    _remainNumText->setRemainWaterNum(_remainWaterNum);
    
    _dropArrays = CCArray::create();
    _dropArrays->retain();
    
    _remainClearNode = 0;
    
    scheduleUpdate();

	return true;
}

void ClassicGameScene::update(float dt){
    
    detectDrops();
    
    bool hasNoGridWater = true;
    
    for (int i = 0; i < TOTAL_NUM; i++) {
        if(_waterNums[i] != NO_WATER){
            hasNoGridWater = false;
        }
    }
    
    if(_remainClearNode == 0 && _dropArrays->count() == 0 && (_remainWaterNum == 0 || hasNoGridWater)){
        bool isWin = hasNoGridWater;
        ClassicResultDialog* dialog = ClassicResultDialog::create(isWin);
        addChild(dialog, 100);
        
        dialog->setScale(0.75);
        dialog->setAnchorPoint(ccp(0.5, 0.5));
        LayoutUtil::layoutToParentCenter(dialog, this, 0, -10);
        dialog->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.6, 1)));
        
        unscheduleUpdate();
    }
}

void ClassicGameScene::detectDrops(){
    for (int i = 0; i < _dropArrays->count(); i++) {
        CCSprite* drop = dynamic_cast<CCSprite*>(_dropArrays->objectAtIndex(i));
        if(drop != NULL){
            CCPoint pos = drop->getPosition();
            int index = getGridIndexByPos(pos);
            int startIndex = drop->getTag();
            
            if(startIndex != index && isGridValid(index)){
                addGridWater(index);
                removeDrop(drop);
            }else if (index == -1){
                showDropWall(startIndex, drop->getRotation());
                removeDrop(drop);
            }
        }
    }
}

void ClassicGameScene::showDropWall(int startIndex, int rotation){
    CCSprite* wallDrop = CCSprite::create(Images::game::wall_drop_1);
    wallDrop->setAnchorPoint(ccp(1, 0.5));
    wallDrop->setRotation(rotation);
    
    addChild(wallDrop, 10);
    
    int row = startIndex / COL_NUM;
    int col = startIndex % COL_NUM;
    
    float addOffsetX = 0;
    float addOffsetY = 0;
    
    if(rotation == ROTATION_RIGHT){
        col = COL_NUM;
        addOffsetX = -0.5f * GRID_WIDTH;
    }else if(rotation == ROTATION_LEFT){
        col = 0;
        addOffsetX = -0.5f * GRID_WIDTH;
    }else if(rotation == ROTATION_DOWN){
        row = 0;
        addOffsetY = -0.5f * GRID_HEIGHT;
    }else if(rotation == ROTATION_UP){
        row = ROW_NUM;
        addOffsetY = -0.5f * GRID_HEIGHT;
    }
    
    LayoutUtil::layoutTo(wallDrop, 1, 0.5, _gridBg, 0, 0, OFFSET_X + col * GRID_WIDTH + addOffsetX, OFFSET_Y + row * GRID_HEIGHT + addOffsetY);
    
    CCPoint pos = wallDrop->getPosition();
    
    CCLOG("pos %f, %f, rotation %d", pos.x, pos.y, rotation);
    
    CCTextureCache* textureCache = CCTextureCache::sharedTextureCache();
    CCArray* arr = CCArray::create();
    char temp[64];
    for (int i = 0; i < 5; i++) {
        sprintf(temp, "Images/game/wall_drop_%d.png", i + 1);
        CCTexture2D* tex = textureCache->addImage(temp);
        if(tex){
            CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(tex, CCRect(0, 0, tex->getContentSize().width, tex->getContentSize().height));
            arr->addObject(frame);
        }else{
            break;
        }
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr);
    animation->setDelayPerUnit(0.1);
    CCAnimate* animate = CCAnimate::create(animation);
    wallDrop->runAction(CCSequence::create(animate, CCCallFuncN::create(this, callfuncN_selector(ClassicGameScene::clearNode)), NULL));
    _remainClearNode++;
}

int ClassicGameScene::getGridIndexByPos(cocos2d::CCPoint & pos){
    CCRect rect = CCRectZero;
    rect.size.setSize(GRID_WIDTH, GRID_HEIGHT);
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            
            int index = j + i * COL_NUM;
            
            rect.origin = _gridBg->getPosition();
            rect.origin.x += (OFFSET_X + (j - 0.5f) * GRID_WIDTH);
            rect.origin.y += (OFFSET_Y + (i - 0.5f) * GRID_HEIGHT);
            
            if(rect.containsPoint(pos)){
                return index;
            }
        }
    }
    
    return -1;
}

void ClassicGameScene::onExplodeEnd(WaterSprite *water){
    
    float poss[4][2] = { {0.5, 1}, {0.5, 0}, {1, 0.5}, {0, 0.5}};
    float rotation[4] = {ROTATION_UP, ROTATION_DOWN, ROTATION_RIGHT, ROTATION_LEFT};
    float movPos[4][2] = { {0, 500}, {0, -500}, {500, 0}, {-500, 0}};
    
    for (int i = 0; i < 4; i++) {
        CCSprite* drop = CCSprite::create(Images::game::drop);
        drop->setAnchorPoint(ccp(1, 0.5));
        drop->setRotation(rotation[i]);
        addChild(drop, 1);
        drop->setTag(water->getTag());
        
        LayoutUtil::layoutTo(drop, 1, 0.5, water, poss[i][0], poss[i][1]);
        CCMoveBy* move = CCMoveBy::create(2.5, ccp(movPos[i][0], movPos[i][1]));
        drop->runAction(CCSequence::create(move, CCCallFuncN::create(this, callfuncN_selector(ClassicGameScene::removeDrop)), NULL));
        
        _dropArrays->addObject(drop);
    }
}

bool ClassicGameScene::hasWater(){
    return _remainWaterNum > 0;
}

bool ClassicGameScene::isGridValid(int index){
    return _waterNums[index] > 0 && _waterNums[index] < 5;
}

void ClassicGameScene::addGridWater(int index){
    _waterNums[index]++;
    if(_waterNums[index] == 5){
        _waters[index]->showExplode();
        _remainClearNode += 4;
        _waterNums[index] = 0;
        _waters[index] = NULL;
    }else{
        _waters[index]->setWaterNum(_waterNums[index]);
    }
}

void ClassicGameScene::setRemainWater(int remainWater){
    _remainWaterNum = remainWater;
    _remainNumText->setRemainWaterNum(_remainWaterNum);
}

void ClassicGameScene::removeDrop(cocos2d::CCSprite *drop){
    if(_dropArrays->containsObject(drop)){
        _dropArrays->removeObject(drop);
    }
    clearNode(drop);
}

void ClassicGameScene::clearNode(cocos2d::CCNode *node){
    node->removeFromParent();
    _remainClearNode--;
}

void ClassicGameScene::onClickGrid(cocos2d::CCNode *node){
    int index = node->getTag();
    int row = index / COL_NUM;
    int col = index % COL_NUM;
    CCLOG("clicked row %d col %d", row, col);
    if(isGridValid(index) && hasWater()){
        addGridWater(index);
        setRemainWater(_remainWaterNum - 1);
    }
}

void ClassicGameScene::onClickBtn(CCNode* node) {
	int tag = node->getTag();

	if (tag == -1) {
		CoverScene* cover = CoverScene::create();
        
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, cover);
        
        CCDirector::sharedDirector()->replaceScene(trans);
	}else if (tag == -2){
        ClassicGameScene* classicScene = ClassicGameScene::create();
        
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, classicScene);
        
        CCDirector::sharedDirector()->replaceScene(trans);
    }
}

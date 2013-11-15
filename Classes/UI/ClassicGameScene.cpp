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

USING_NS_CC;
using namespace Resources;

ClassicGameScene::ClassicGameScene() {
	// TODO Auto-generated constructor stub

}

ClassicGameScene::~ClassicGameScene() {
	// TODO Auto-generated destructor stub
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

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* gridBg = CCSprite::create(Images::game::cell);
	addChild(gridBg);
	gridBg->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 16));

	CCMenuItem* backItem = UIUtil::getSingleImageBtn(
			Images::common::back);
	menu->addChild(backItem);
	backItem->setTarget(this, menu_selector(ClassicGameScene::onClickBtn));
	backItem->setTag(-1);
	backItem->setAnchorPoint(ccp(1, 0));
    LayoutUtil::layoutTo(backItem, 0, 1, bg, 0, 1, 4, -4);
    
    CCMenuItem* pauseItem = UIUtil::getSingleImageBtn(Images::game::btn_pause);
	menu->addChild(pauseItem);
	pauseItem->setTarget(this, menu_selector(ClassicGameScene::onClickBtn));
	pauseItem->setTag(-2);
	pauseItem->setAnchorPoint(ccp(1, 0));
    LayoutUtil::layoutTo(pauseItem, 1, 1, bg, 1, 1, -4, -4);

	srand( time(NULL));
    
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

			float px = 30 + j * 52;
			float py = 30 + i * 52;
            LayoutUtil::layoutTo(_waters[index], 0.5, 0.5, gridBg, 0, 0, px, py);
            
            CCMenuItem* item = CCMenuItem::create();
            item->setContentSize(_waters[index]->getContentSize());
            gridMenu->addChild(item);
            item->setTag(index);
            item->setTarget(this, menu_selector(ClassicGameScene::onClickGrid));
            LayoutUtil::layoutToCenter(item, _waters[index]);
		}
	}

	CCSize gridSize = gridBg->getContentSize();

	float levelOffsetX = 24;

	CCSprite* levelInfo = CCSprite::create(Images::game::level);
	gridBg->addChild(levelInfo, 1);
	levelInfo->setAnchorPoint(ccp(1, 0));
	levelInfo->setPosition(ccp(gridSize.width - levelOffsetX, gridSize.height + 5));

	CCSize levelInfoSize = levelInfo->getContentSize();

	_remainNumText = ReMainWaterNumSprite::create();
	gridBg->addChild(_remainNumText, 1);
	_remainNumText->setAnchorPoint(ccp(1, 0.5));
	_remainNumText->setPosition(ccp(gridSize.width - levelOffsetX -30 - levelInfoSize.width , gridSize.height + 5 + levelInfoSize.height/2));
    
    _remainWaterNum = 10;
    _remainNumText->setRemainWaterNum(_remainWaterNum);

	return true;
}

void ClassicGameScene::update(float dt){
    
}

void ClassicGameScene::onExplodeEnd(WaterSprite *water){
    
    float poss[4][2] = { {0.5, 1}, {0.5, 0}, {1, 0.5}, {0, 0.5}};
    float rotation[4] = {-90, 90, 0, 180};
    float movPos[4][2] = { {0, 500}, {0, -500}, {500, 0}, {-500, 0}};
    
    for (int i = 0; i < 4; i++) {
        CCSprite* drop = CCSprite::create(Images::game::drop_east);
        drop->setRotation(rotation[i]);
        addChild(drop, 1);
        
        LayoutUtil::layoutTo(drop, 0.5, 0.5, water, poss[i][0], poss[i][1]);
        CCMoveBy* move = CCMoveBy::create(3, ccp(movPos[i][0], movPos[i][1]));
        drop->runAction(CCSequence::create(move, CCCallFuncN::create(this, callfuncN_selector(ClassicGameScene::clearNode)), NULL));
    }
}

void ClassicGameScene::clearNode(cocos2d::CCNode *node){
    node->removeFromParent();
}

void ClassicGameScene::onClickGrid(cocos2d::CCNode *node){
    int index = node->getTag();
    int row = index / COL_NUM;
    int col = index % COL_NUM;
    CCLOG("clicked row %d col %d", row, col);
    if(_waterNums[index] > 0 && _waterNums[index] < 5 && _remainWaterNum > 0){
        _waterNums[index]++;
        _remainWaterNum--;
        _remainNumText->setRemainWaterNum(_remainWaterNum);
        if(_waterNums[index] == 5){
            _waters[index]->showExplode();
            _waterNums[index] = 0;
            _waters[index] = NULL;
        }else{
            _waters[index]->setWaterNum(_waterNums[index]);
        }
    }
}

void ClassicGameScene::onClickBtn(CCNode* node) {
	int tag = node->getTag();

	if (tag == -1) {
		CCDirector::sharedDirector()->replaceScene(CoverScene::create());
	}else if (tag == -2){
        
    }
}

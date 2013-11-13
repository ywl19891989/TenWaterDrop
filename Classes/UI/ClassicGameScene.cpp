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

	CCSprite* gridBg = CCSprite::create(Images::game::cell_png);
	addChild(gridBg);
	gridBg->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 16));

	CCMenuItemImage* backItem = CCMenuItemImage::create(
			Images::common::back_png, Images::common::back_down_png);
	menu->addChild(backItem);
	backItem->setTarget(this, menu_selector(ClassicGameScene::onClickBtn));
	backItem->setTag(-1);
	backItem->setAnchorPoint(ccp(1, 0));
	backItem->setPosition(ccp(winSize.width - 5, 5));

	srand( time(NULL));

	for (int i = 0; i < ROW_NUM; i++) {
		for (int j = 0; j < COL_NUM; j++) {
			int index = i * COL_NUM + j;
			_waterNums[index] = rand() % 4 + 1;

			_waters[index] = WaterSprite::create();
			_waters[index]->setAnchorPoint(ccp(0.5, 0.5));
			_waters[index]->setWaterNum(_waterNums[index]);
			gridBg->addChild(_waters[index], 1);

			float px = 30 + j * 52;
			float py = 30 + i * 52;

			_waters[index]->setPosition(ccp(px, py));
		}
	}

	CCSize gridSize = gridBg->getContentSize();

	float levelOffsetX = 24;

	CCSprite* levelInfo = CCSprite::create(Images::game::level_png);
	gridBg->addChild(levelInfo, 1);
	levelInfo->setAnchorPoint(ccp(1, 0));
	levelInfo->setPosition(ccp(gridSize.width - levelOffsetX, gridSize.height + 5));

	CCSize levelInfoSize = levelInfo->getContentSize();

	_remainNum = ReMainWaterNumSprite::create();
	_remainNum->setRemainWaterNum(10);
	gridBg->addChild(_remainNum, 1);
	_remainNum->setAnchorPoint(ccp(1, 0.5));
	_remainNum->setPosition(ccp(gridSize.width - levelOffsetX -30 - levelInfoSize.width , gridSize.height + 5 + levelInfoSize.height/2));

	return true;
}

void ClassicGameScene::onClickBtn(CCNode* node) {
	int tag = node->getTag();

	if (tag == -1) {
		CCDirector::sharedDirector()->replaceScene(CoverScene::create());
	}
}

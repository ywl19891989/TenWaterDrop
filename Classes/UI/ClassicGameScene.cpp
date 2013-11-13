/*
 * ClassicGameScene.cpp
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#include "ClassicGameScene.h"
#include "ResourceName.h"
#include "CoverScene.h"

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
	gridBg->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	CCMenuItemImage* backItem = CCMenuItemImage::create(
			Images::common::back_png, Images::common::back_down_png);
	menu->addChild(backItem);
	backItem->setTarget(this, menu_selector(ClassicGameScene::onClickBtn));
	backItem->setTag(-1);
	backItem->setAnchorPoint(ccp(1, 0));
	backItem->setPosition(ccp(winSize.width - 5, 5));

	return true;
}

void ClassicGameScene::onClickBtn(CCNode* node) {
	int tag = node->getTag();

	if(tag == -1){
		CCDirector::sharedDirector()->replaceScene(CoverScene::create());
	}
}

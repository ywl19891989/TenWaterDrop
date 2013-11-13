/*
 * CoverScene.cpp
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#include "CoverScene.h"
#include "ResourceName.h"
#include "ClassicGameScene.h"

USING_NS_CC;
using namespace Resources;

CoverScene::CoverScene() {
	// TODO Auto-generated constructor stub

}

CoverScene::~CoverScene() {
	// TODO Auto-generated destructor stub
}

bool CoverScene::init() {

	if (!CCScene::init()) {
		return false;
	}

	CCSprite* bg = CCSprite::create(Images::cover::main_bg_jpg);
	addChild(bg, -1);
	bg->setAnchorPoint(ccp(0, 0));

	CCMenu* menu = CCMenu::create();
	addChild(menu);
	menu->setAnchorPoint(ccp(0, 0));
	menu->setPosition(ccp(0, 0));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage* classicItem = CCMenuItemImage::create(
			Images::cover::classic_png, Images::cover::classic_down_png);
	menu->addChild(classicItem);
	classicItem->setTarget(this, menu_selector(CoverScene::onClickBtn));
	classicItem->setTag(0);
	classicItem->setAnchorPoint(ccp(0.5, 0));
	classicItem->setPosition(ccp(winSize.width / 2, 360));

	CCMenuItemImage* upgradeItem = CCMenuItemImage::create(
			Images::cover::shengji_png, Images::cover::shengji_down_png);
	menu->addChild(upgradeItem);
	upgradeItem->setTarget(this, menu_selector(CoverScene::onClickBtn));
	upgradeItem->setTag(1);
	upgradeItem->setAnchorPoint(ccp(0.5, 0));
	upgradeItem->setPosition(ccp(winSize.width / 2, 210));

	return true;
}

void CoverScene::onClickBtn(cocos2d::CCNode* node) {
	int tag = node->getTag();

	if (tag == 0) {
		CCDirector::sharedDirector()->replaceScene(ClassicGameScene::create());
	} else if (tag == 1) {

	}
}

/*
 * CoverScene.cpp
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#include "CoverScene.h"
#include "ResourceName.h"
#include "ClassicGameScene.h"
#include "LayoutUtil.h"
#include "UIUtil.h"
#include "Constants.h"
#include "LevelGameScene.h"
#include "SelectLevelScene.h"

#include <string>
#include <map>


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
    LayoutUtil::layoutTo(menu, 0, 0, bg, 0, 0);

	
	CCMenuItemImage* upgradeItem = CCMenuItemImage::create(
			Images::cover::shengji, Images::cover::shengji_down);
	menu->addChild(upgradeItem);
	upgradeItem->setTarget(this, menu_selector(CoverScene::onClickBtn));
	upgradeItem->setTag(1);
	LayoutUtil::layoutTo(upgradeItem, 0.5, 0, bg, 0.5, 0, 10, 200);
    
    CCMenuItemImage* classicItem = CCMenuItemImage::create(
                                                           Images::cover::classic, Images::cover::classic_down);
	menu->addChild(classicItem);
	classicItem->setTarget(this, menu_selector(CoverScene::onClickBtn));
	classicItem->setTag(0);
	LayoutUtil::layoutTo(classicItem, 0.5, 0, upgradeItem, 0.5, 1, 0, 30);
    
    _enableMusic = UIUtil::getSingleImageBtn(Images::common::musicoff);
	menu->addChild(_enableMusic);
	_enableMusic->setTarget(this, menu_selector(CoverScene::enableMusic));
	LayoutUtil::layoutTo(_enableMusic, 0, 0, bg, 0, 0, 5, 5);
    
    _disableMusic = UIUtil::getSingleImageBtn(Images::common::musicon);
	menu->addChild(_disableMusic);
	_disableMusic->setTarget(this, menu_selector(CoverScene::disableMusic));
	LayoutUtil::layoutToCenter(_disableMusic, _enableMusic);
    
    _disableMusic->setVisible(Constants::isMusicEnabled());
    _enableMusic->setVisible(!Constants::isMusicEnabled());
    
    CCMenuItem* help = UIUtil::getSingleImageBtn(Images::common::help);
	menu->addChild(help);
	help->setTarget(this, menu_selector(CoverScene::onClickHelp));
	LayoutUtil::layoutTo(help, 1, 0, bg, 1, 0, -5, 5);


	return true;
}

void CoverScene::onEnter(){
    CCScene::onEnter();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
}

void CoverScene::onExit(){
    CCScene::onExit();
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
}

void CoverScene::keyBackClicked(){
    CCDirector::sharedDirector()->end();
}

void CoverScene::update(float dt) {
    _disableMusic->setVisible(Constants::isMusicEnabled());
    _enableMusic->setVisible(!Constants::isMusicEnabled());
}

void CoverScene::onClickHelp(cocos2d::CCNode *node){
    
}

void CoverScene::enableMusic(cocos2d::CCNode *node){
    Constants::enableMusic();
    update(0);
}

void CoverScene::disableMusic(cocos2d::CCNode *node){
    Constants::disableMusic();
    update(0);
}

void CoverScene::onClickBtn(cocos2d::CCNode* node) {
	int tag = node->getTag();

	if (tag == 0) {
        ClassicGameScene* classicScene = ClassicGameScene::create();
        
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, classicScene);
        
        CCDirector::sharedDirector()->replaceScene(trans);
	} else if (tag == 1) {
        SelectLevelScene* selectLevel = SelectLevelScene::create();
        
        CCTransitionFade* trans = CCTransitionFade::create(Constants::REPLACE_SCENE_TIME, selectLevel);
        
        CCDirector::sharedDirector()->replaceScene(trans);
	}
}

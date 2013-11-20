//
//  MusicBtn.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-20.
//
//

#include "MusicBtn.h"
#include "ResourceName.h"
#include "LayoutUtil.h"
#include "UIUtil.h"
#include "Constants.h"

USING_NS_CC;
USING_NS_RES;

bool MusicBtn::init(){
    
    if(!CCNode::init()){
        return false;
    }
    
    CCMenu* menu = CCMenu::create();
    addChild(menu, 1);
    
    _enableMusic = UIUtil::getSingleImageBtn(Images::common::musicoff);
	menu->addChild(_enableMusic);
	_enableMusic->setTarget(this, menu_selector(MusicBtn::enableMusic));
	
    
    _disableMusic = UIUtil::getSingleImageBtn(Images::common::musicon);
	menu->addChild(_disableMusic);
	_disableMusic->setTarget(this, menu_selector(MusicBtn::disableMusic));
    
    setContentSize(_enableMusic->getContentSize());
    
    LayoutUtil::layoutToParent(menu, 0, 0, this, 0, 0);
    LayoutUtil::layoutToParentCenter(_enableMusic, this);
	LayoutUtil::layoutToCenter(_disableMusic, _enableMusic);
    
    _disableMusic->setVisible(Constants::isMusicEnabled());
    _enableMusic->setVisible(!Constants::isMusicEnabled());
    
    return true;
}

void MusicBtn::updateMusic() {
    _disableMusic->setVisible(Constants::isMusicEnabled());
    _enableMusic->setVisible(!Constants::isMusicEnabled());
}

void MusicBtn::enableMusic(cocos2d::CCNode *node){
    Constants::enableMusic();
    updateMusic();
}

void MusicBtn::disableMusic(cocos2d::CCNode *node){
    Constants::disableMusic();
    updateMusic();
}

//
//  ClassicResultDialog.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#include "ClassicResultDialog.h"
#include "MenuDispatch.h"
#include "ResourceName.h"
#include "LayoutUtil.h"
#include "ClassicGameScene.h"
#include "LevelUtil.h"
#include "UIUtil.h"

USING_NS_CC;
USING_NS_RES;

ClassicResultDialog* ClassicResultDialog::create(bool isWin){
    ClassicResultDialog* dialog = new ClassicResultDialog();
    dialog->init(isWin);
    dialog->autorelease();
    
    return dialog;
}

bool ClassicResultDialog::init(bool isWin){
    
    if(!CCNode::init()){
        return false;
    }
    
    MenuDispatch* menu = MenuDispatch::create();
    menu->setIsSwallowAll(true);
    addChild(menu, 1);
    
    if(isWin){
        CCSprite* bg = CCSprite::create(Images::game::dialogBg_win);
        addChild(bg, -1);
        setContentSize(bg->getContentSize());
        LayoutUtil::layoutToParentCenter(bg, this);
        
        CCMenuItem* item = UIUtil::getSingleImageBtn(Images::game::btn_next);
        menu->registerBtn(item);
        addChild(item, 1);
        LayoutUtil::layoutToCenter(item, bg, 10, -50);
        item->setTarget(this, menu_selector(ClassicResultDialog::onClickBtn));
    }else{
        CCSprite* bg = CCSprite::create(Images::game::dialogBg_lose);
        addChild(bg, -1);
        setContentSize(bg->getContentSize());
        LayoutUtil::layoutToParentCenter(bg, this);
        
        CCMenuItem* item = UIUtil::getSingleImageBtn(Images::game::btn_retry);
        menu->registerBtn(item);
        addChild(item, 1);
        LayoutUtil::layoutToCenter(item, bg, 10, -50);
        item->setTarget(this, menu_selector(ClassicResultDialog::onClickBtn));
    }
    
    
    _isWin = isWin;
    
    return true;
}

void ClassicResultDialog::onClickBtn(cocos2d::CCNode *node){
    CCDirector::sharedDirector()->replaceScene(ClassicGameScene::create());
}
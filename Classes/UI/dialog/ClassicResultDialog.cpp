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
    
    if(isWin){
        CCSprite* bg = CCSprite::create(Images::game::dialogBg_win);
        addChild(bg, -1);
        setContentSize(bg->getContentSize());
        LayoutUtil::layoutToParentCenter(bg, this);
        
        CCSprite* res = CCSprite::create(Images::game::classic_winFg);
        addChild(res, 1);
        LayoutUtil::layoutToCenter(res, bg, 0, -30);
    }else{
        CCSprite* bg = CCSprite::create(Images::game::dialogBg_lose);
        addChild(bg, -1);
        setContentSize(bg->getContentSize());
        LayoutUtil::layoutToParentCenter(bg, this);
        
        CCSprite* res = CCSprite::create(Images::game::classic_loseFg);
        addChild(res, 1);
        LayoutUtil::layoutToCenter(res, bg, 0, -30);
    }
    
    MenuDispatch* menu = MenuDispatch::create();
    menu->setIsSwallowAll(true);
    addChild(menu, 1);
    
    CCMenuItem* item = CCMenuItem::create();
    item->setContentSize(getContentSize());
    addChild(item);
    menu->registerBtn(item);
    LayoutUtil::layoutToParentCenter(item, this);
    item->setTarget(this, menu_selector(ClassicResultDialog::onClickBtn));
    
    _isWin = isWin;
    
    return true;
}

void ClassicResultDialog::onClickBtn(cocos2d::CCNode *node){
    CCDirector::sharedDirector()->replaceScene(ClassicGameScene::create());
}
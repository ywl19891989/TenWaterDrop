//
//  UIUtil.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-14.
//
//

#include "UIUtil.h"
#include "LayoutUtil.h"

USING_NS_CC;

CCMenuItem* UIUtil::getSingleImageBtn(const char *imgpath, int tag/* = 0*/){
    
    CCSprite* normal= CCSprite::create(imgpath);
    
    CCSprite* select = CCSprite::create(imgpath);
    CCSprite* selectMask = CCSprite::create(imgpath);
    selectMask->setOpacity(80);
    selectMask->setColor(ccBLACK);
    select->addChild(selectMask, 1);
    LayoutUtil::layoutToParentCenter(selectMask, select);
    
    CCMenuItem* item = CCMenuItemSprite::create(normal, select);
    item->setTag(tag);
    
    return item;
}
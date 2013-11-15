//
//  TestWaterScene.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-14.
//
//

#include "TestWaterScene.h"
#include "ResourceName.h"
#include "LayoutUtil.h"
#include "UIUtil.h"

USING_NS_CC;
USING_NS_RES;

bool TestWaterScene::init(){

    if(!CCScene::init()){
        return false;
    }
    
    _curWaterNum = 0;
    
    
    
    _water = CCSprite::create("Images/testwater2/water_1_1.png");
    addChild(_water);
    LayoutUtil::layoutToParentCenter(_water, this);
    
    
    
    CCMenu* menu = CCMenu::create();
    addChild(menu);
    LayoutUtil::layoutToParent(menu, 0, 0, this, 0, 0);
    
    CCMenuItem* prev = UIUtil::getSingleImageBtn(Images::game::btn_continue);
    menu->addChild(prev);
    prev->setTarget(this, menu_selector(TestWaterScene::prev));
    LayoutUtil::layoutToParent(prev, 1, 0, this, 0.5, 0, -10, 50);
    
    CCMenuItem* next = UIUtil::getSingleImageBtn(Images::game::btn_continue);
    menu->addChild(next);
    next->setTarget(this, menu_selector(TestWaterScene::next));
    LayoutUtil::layoutToParent(next, 0, 0, this, 0.5, 0, 10, 50);
    
    reset();
    
    return true;
}

void TestWaterScene::prev(){
    _curWaterNum++;
    _curWaterNum %= 4;
    reset();
}

void TestWaterScene::next(){
    _curWaterNum--;
    _curWaterNum += 4;
    _curWaterNum %= 4;
    reset();
}

void TestWaterScene::reset(){
    char temp[64];
    int index = _curWaterNum + 1;
    
    CCTextureCache* textureCache = CCTextureCache::sharedTextureCache();
    CCArray* arr = CCArray::create();
    for (int i = 0; i < 10; i++) {
        sprintf(temp, "Images/testwater2/water_%d_%d.png", index, i + 1);
        CCTexture2D* tex = textureCache->addImage(temp);
        if(tex){
            CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(tex, CCRect(0, 0, tex->getContentSize().width, tex->getContentSize().height));
            arr->addObject(frame);
        }else{
            break;
        }
    }
    CCTexture2D* first = dynamic_cast<CCTexture2D*>(arr->objectAtIndex(0));
    _water->setTexture(first);
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr);
    animation->setDelayPerUnit(0.15);
    CCAnimate* animate = CCAnimate::create(animation);
    CCSequence* action = CCSequence::create(animate, CCDelayTime::create(0.4), NULL);
    _water->stopAllActions();
    _water->runAction(CCRepeatForever::create(action));
}
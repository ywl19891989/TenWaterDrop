/*
 * WaterSprite.cpp
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#include "WaterSprite.h"
#include "ResourceName.h"
#include "LayoutUtil.h"

USING_NS_CC;
using namespace Resources;

WaterSprite::WaterSprite() {
	// TODO Auto-generated constructor stub

}

WaterSprite::~WaterSprite() {
	// TODO Auto-generated destructor stub
}

bool WaterSprite::init() {

	if (!CCNode::init()) {
		return false;
	}

	setContentSize(CCSizeMake(50, 50));

	for (int i = 0; i < 4; i++) {
		sprintf(_tempStr, "Images/game/drop_%d.png", i + 1);
		_water[i] = CCSprite::create(_tempStr);
		addChild(_water[i]);
        LayoutUtil::layoutToParentCenter(_water[i], this);
	}
    
    _waterExplode = CCSprite::create(Images::game::explode_1);
    addChild(_waterExplode);
    LayoutUtil::layoutToParentCenter(_waterExplode, this);
    _waterExplode->setVisible(false);

	setWaterNum(0);

	return true;
}

void WaterSprite::setWaterNum(int num) {
	_waterNum = num;
	for (int i = 0; i < 4; i++) {
        _water[i]->stopAllActions();
		_water[i]->setVisible( (i + 1) == _waterNum);
        if((i + 1) == _waterNum){
            _water[i]->setScale(0.8f);
            CCScaleTo* scale = CCScaleTo::create(1.2, 1);
            CCEaseElasticOut* ee = CCEaseElasticOut::create(scale, 0.18);
            _water[i]->runAction(ee);
        }
	}
}

void WaterSprite::addWater(){
    if(_waterNum == 4){
        showExplode();
    }else{
        setWaterNum(_waterNum + 1);
    }
}

void WaterSprite::showExplode(){
    setWaterNum(0);
    
    _waterExplode->setVisible(true);
    
    CCTextureCache* textureCache = CCTextureCache::sharedTextureCache();
    CCArray* arr = CCArray::create();
    for (int i = 0; i < 10; i++) {
        sprintf(_tempStr, "Images/game/explode_%d.png", i + 1);
        CCTexture2D* tex = textureCache->addImage(_tempStr);
        if(tex){
            CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(tex, CCRect(0, 0, tex->getContentSize().width, tex->getContentSize().height));
            arr->addObject(frame);
        }else{
            break;
        }
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(arr);
    animation->setDelayPerUnit(0.06);
    CCAnimate* animate = CCAnimate::create(animation);
    CCSequence* action = CCSequence::create(animate, CCCallFunc::create(this, callfunc_selector(WaterSprite::explodeEnd)), NULL);
    _waterExplode->runAction(action);
}

void WaterSprite::setExplodeListener(ExplodeListener *listener){
    _explodeListener = listener;
}

void WaterSprite::explodeEnd(){
    _waterExplode->setVisible(false);
    _explodeListener->onExplodeEnd(this);
}

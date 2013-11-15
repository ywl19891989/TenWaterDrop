//
//  Constants.cpp
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#include "Constants.h"
#include "cocos2d.h"

USING_NS_CC;

bool Constants::_isMusicEnabled = true;
const char * Constants::MUSICENABLE_KEY = "constants_musicEnabled";

Constants::Constants(){
    
}

void Constants::init(){
    CCUserDefault* save = CCUserDefault::sharedUserDefault();
    _isMusicEnabled = save->getBoolForKey(MUSICENABLE_KEY, true);
}

bool Constants::isMusicEnabled(){
    return _isMusicEnabled;
}

void Constants::enableMusic(){
    _isMusicEnabled = true;
    updateConfig();
}

void Constants::disableMusic(){
    _isMusicEnabled = false;
    updateConfig();
}

void Constants::updateConfig(){
    CCUserDefault* save = CCUserDefault::sharedUserDefault();
    save->setBoolForKey(MUSICENABLE_KEY, _isMusicEnabled);
}
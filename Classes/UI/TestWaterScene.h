//
//  TestWaterScene.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-14.
//
//

#ifndef __TenWaterDrop__TestWaterScene__
#define __TenWaterDrop__TestWaterScene__

#include "cocos2d.h"

class TestWaterScene : public cocos2d::CCScene {
public:
    CREATE_FUNC(TestWaterScene)
    
    bool init();
    
    void next();
    void prev();
    
    void reset();
    
private:
    int _curWaterNum;
    cocos2d::CCSprite *_water;
};

#endif /* defined(__TenWaterDrop__TestWaterScene__) */

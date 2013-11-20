//
//  GridSprite.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-20.
//
//

#ifndef __TenWaterDrop__GridSprite__
#define __TenWaterDrop__GridSprite__

#include "cocos2d.h"

class GridSprite : public cocos2d::CCNode {
public:
    CREATE_FUNC(GridSprite);
    
    bool init();
    
    void setInfo(std::string info);
};

#endif /* defined(__TenWaterDrop__GridSprite__) */

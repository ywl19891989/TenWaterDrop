//
//  MusicBtn.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-20.
//
//

#ifndef __TenWaterDrop__MusicBtn__
#define __TenWaterDrop__MusicBtn__

#include "cocos2d.h"

class MusicBtn : public cocos2d::CCNode {
public:
    CREATE_FUNC(MusicBtn);
    bool init();
    
    
    void enableMusic(cocos2d::CCNode* node);
    void disableMusic(cocos2d::CCNode* node);
    
    void updateMusic();
    
private:

    cocos2d::CCMenuItem *_enableMusic, *_disableMusic;
    
};

#endif /* defined(__TenWaterDrop__MusicBtn__) */

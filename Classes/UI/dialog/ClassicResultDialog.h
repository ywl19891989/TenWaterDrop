//
//  ClassicResultDialog.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#ifndef __TenWaterDrop__ClassicResultDialog__
#define __TenWaterDrop__ClassicResultDialog__

#include "cocos2d.h"

class ClassicResultDialog : public cocos2d::CCNode {
public:
    static ClassicResultDialog* create(bool isWin);
    
    bool init(bool isWin);
    
    void onClickBtn(cocos2d::CCNode* node);
    
private:
    bool _isWin;
};

#endif /* defined(__TenWaterDrop__ClassicResultDialog__) */

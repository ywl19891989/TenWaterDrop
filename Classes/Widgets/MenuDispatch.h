//
//  MenuDispatch.h
//  voyage
//
//  Created by wenlong on 13-9-11.
//
//

#ifndef __voyage__MenuDispatch__
#define __voyage__MenuDispatch__

#include "cocos2d.h"
#include "cocos-ext.h"

class MenuDispatch : public cocos2d::CCMenu {
public:
    CREATE_FUNC(MenuDispatch);
    bool init();
    
    MenuDispatch();
    ~MenuDispatch();
    
    bool isSwallowAll();
    void setIsSwallowAll(bool isSwallow);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void registerBtn(cocos2d::CCMenuItem* btn);
    void removeAllObjects();
    
    bool isNodeVisible(cocos2d::CCNode * node);
    
    cocos2d::CCMenuItem* itemForTouch(cocos2d::CCTouch *touch);
    
    bool isInDetectArea(cocos2d::CCTouch* touch);
    void setDetectArea(const cocos2d::CCRect & node);
    void setDetectAreaByTableView(cocos2d::extension::CCTableView * tableView);
    
private:
    cocos2d::CCArray *_btns;
    cocos2d::CCRect _detectArea;
    bool _isSwallowAll;
};

#endif /* defined(__voyage__MenuDispatch__) */

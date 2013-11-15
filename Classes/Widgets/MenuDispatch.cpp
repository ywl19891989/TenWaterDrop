//
//  MenuDispatch.cpp
//  voyage
//
//  Created by wenlong on 13-9-11.
//
//

#include "MenuDispatch.h"

USING_NS_CC;

MenuDispatch::MenuDispatch():
_detectArea(CCRectZero),
_isSwallowAll(false),
_btns(NULL){
    _btns = CCArray::create();
    _btns->retain();
    CCLOG("MenuDispatch %08p", this);
}

MenuDispatch::~MenuDispatch(){
    removeAllObjects();
    _btns->release();
    CCLOG("~MenuDispatch %08p", this);
}

bool MenuDispatch::isSwallowAll(){
    return _isSwallowAll;
}

void MenuDispatch::setIsSwallowAll(bool isSwallow){
    _isSwallowAll = isSwallow;
}

void MenuDispatch::setDetectArea(const cocos2d::CCRect & node){
    _detectArea = node;
}

void MenuDispatch::setDetectAreaByTableView(cocos2d::extension::CCTableView *tableView){
    CCRect rect = CCRectZero;
    rect.origin = tableView->convertToWorldSpace(CCPointZero);
    rect.size = tableView->getViewSize();
    setDetectArea(rect);
}

bool MenuDispatch::isInDetectArea(cocos2d::CCTouch* touch){
    
    if(_detectArea.equals(CCRectZero)){
        return true;
    }
    
    CCPoint touchLocation = touch->getLocation();
    
//    CCLOG("local %f, %f, r %f %f", touchLocation.x, touchLocation.y, _detectArea.size.width, _detectArea.size.height);
    
    if (_detectArea.containsPoint(touchLocation))
    {
        return true;
    }
    
    return false;
}

bool MenuDispatch::init(){
    
    if(!CCMenu::init()){
        return false;
    }
    
    return true;
}

void MenuDispatch::registerBtn(cocos2d::CCMenuItem *btn){
    _btns->addObject(btn);
    CCLOG("registerBtn btn rc %d", btn->retainCount());
}

void MenuDispatch::removeAllObjects(){
    if(_btns->count() > 0){
        CCLOG("removeAllObjects btn rc %d", _btns->objectAtIndex(0)->retainCount());
    }
    _btns->removeAllObjects();
}

bool MenuDispatch::isNodeVisible(cocos2d::CCNode *node){
    bool res = true;
    for (CCNode *c = node; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            res = false;
            break;
        }
    }
    
    return res;
}

bool MenuDispatch::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    
    if (m_eState != kCCMenuStateWaiting || !isNodeVisible(this) || !isInDetectArea(touch) || !isEnabled())
    {
        CCLOG("res false");
        return false;
    }
    
    m_pSelectedItem = this->itemForTouch(touch);
    if (m_pSelectedItem)
    {
        m_eState = kCCMenuStateTrackingTouch;
        m_pSelectedItem->selected();
        CCLOG("res true");
        return true;
    }
    
    if(_isSwallowAll){
        CCLOG("_isSwallowAll res true");
        return true;
    }
    
    CCLOG("end res false");
    return false;
}

CCMenuItem* MenuDispatch::itemForTouch(CCTouch *touch)
{
    CCPoint touchLocation = touch->getLocation();
    
    if (_btns && _btns->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(_btns, pObject)
        {
            CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
            if (pChild && isNodeVisible(pChild) && pChild->isEnabled())
            {
                CCPoint local = pChild->convertToNodeSpace(touchLocation);
                CCRect r = pChild->rect();
                r.origin = CCPointZero;
                
                if (r.containsPoint(local))
                {
                    return pChild;
                }
            }
        }
    }
    
    return NULL;
}


void MenuDispatch::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    
    if(m_eState != kCCMenuStateTrackingTouch){
        return;
    }
    
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
    if (m_pSelectedItem)
    {
        m_pSelectedItem->unselected();
        m_pSelectedItem->activate();
    }
    m_eState = kCCMenuStateWaiting;
}

void MenuDispatch::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    
    if(m_eState != kCCMenuStateTrackingTouch){
        return;
    }
    
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
    if (m_pSelectedItem)
    {
        m_pSelectedItem->unselected();
    }
    m_eState = kCCMenuStateWaiting;
}

void MenuDispatch::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    
    if(m_eState != kCCMenuStateTrackingTouch){
        return;
    }
    
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
    CCMenuItem *currentItem = this->itemForTouch(touch);
    if (currentItem != m_pSelectedItem)
    {
        if (m_pSelectedItem)
        {
            m_pSelectedItem->unselected();
        }
        m_pSelectedItem = currentItem;
        if (m_pSelectedItem)
        {
            m_pSelectedItem->selected();
        }
    }
}

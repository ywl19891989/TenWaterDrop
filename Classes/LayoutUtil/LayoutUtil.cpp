//
//  LayoutUtil.cpp
//  game-ios
//
//  Created by wenlong on 13-5-14.
//
//

#include "LayoutUtil.h"


void LayoutUtil::layoutTo(cocos2d::CCNode *source, float alineX, float alineY, cocos2d::CCNode *target, float targetX, float targetY, float offsetX/* = 0*/, float offsetY/* = 0*/){
    
    CCPoint srcAnchor = source->isIgnoreAnchorPointForPosition() ? CCPointZero : source->getAnchorPoint();
    
    CCSize srcSize = source->boundingBox().size;
    CCPoint srcDiff = ccp( srcSize.width * (srcAnchor.x - alineX), srcSize.height * (srcAnchor.y - alineY));
    
    CCPoint pos = target->getPosition();
    CCSize targetSize = target->boundingBox().size;
    CCPoint targetAnchor = target->isIgnoreAnchorPointForPosition() ? CCPointZero : target->getAnchorPoint();
    CCPoint targetDiff = ccp( (targetX - targetAnchor.x) * targetSize.width + offsetX, (targetY - targetAnchor.y) * targetSize.height + offsetY);
    source->setPosition(ccpAdd(pos, ccpAdd(srcDiff, targetDiff)));
}

void LayoutUtil::layoutToCenter(cocos2d::CCNode *source, cocos2d::CCNode *target, float offsetX /* = 0 */, float offsetY/* = 0 */){
    layoutTo(source, 0.5, 0.5, target, 0.5, 0.5, offsetX, offsetY);
}

void LayoutUtil::layoutTo(CCNode* src, ccLayoutPosion srcPos, CCNode* target, ccLayoutPosion targetPos, float offsetX/* = 0 */, float offsetY/* = 0*/){
    
    float aline[18] = {
        0.5, 0.5,   // kPosCenter
        0, 0.5,     // kPosLeftCenter
        1, 0.5,     // kPosRightCenter
        0.5, 1,     // kPosTopCenter
        0.5, 0,     // kPosBottomCenter
        0, 1,       // kPosLeftTop
        0, 0,       // kPosLeftBottom
        1, 1,       // kPosRightTop
        1, 0        // kPosRightBottom
    };
    
    layoutTo(src, aline[srcPos * 2], aline[srcPos * 2 + 1], target,  aline[targetPos * 2], aline[targetPos * 2 + 1], offsetX, offsetY);
}

void LayoutUtil::layoutToParent(cocos2d::CCNode *source, float alineX, float alineY, cocos2d::CCNode *target, float targetX, float targetY, float offsetX/* = 0*/, float offsetY/* = 0*/){
    CCPoint srcAnchor = source->isIgnoreAnchorPointForPosition() ? CCPointZero : source->getAnchorPoint();
    
    CCSize srcSize = source->boundingBox().size;
    CCPoint srcDiff = ccp( srcSize.width * (srcAnchor.x - alineX), srcSize.height * (srcAnchor.y - alineY));
    
    CCPoint pos = CCPointZero;
    CCSize targetSize = target->boundingBox().size;
    CCPoint targetDiff = ccp( (targetX) * targetSize.width + offsetX, (targetY) * targetSize.height + offsetY);
    source->setPosition(ccpAdd(pos, ccpAdd(srcDiff, targetDiff)));
}

void LayoutUtil::layoutToParentCenter(cocos2d::CCNode *source, cocos2d::CCNode *target, float offsetX /* = 0 */, float offsetY/* = 0 */){
    layoutToParent(source, 0.5, 0.5, target, 0.5, 0.5, offsetX, offsetY);
}

void LayoutUtil::layoutToParent(CCNode* src, ccLayoutPosion srcPos, CCNode* target, ccLayoutPosion targetPos, float offsetX/* = 0 */, float offsetY/* = 0*/){
    float aline[18] = {
        0.5, 0.5,   // kPosCenter
        0, 0.5,     // kPosLeftCenter
        1, 0.5,     // kPosRightCenter
        0.5, 1,     // kPosTopCenter
        0.5, 0,     // kPosBottomCenter
        0, 1,       // kPosLeftTop
        0, 0,       // kPosLeftBottom
        1, 1,       // kPosRightTop
        1, 0        // kPosRightBottom
    };
    
    layoutToParent(src, aline[srcPos * 2], aline[srcPos * 2 + 1], target,  aline[targetPos * 2], aline[targetPos * 2 + 1], offsetX, offsetY);
}

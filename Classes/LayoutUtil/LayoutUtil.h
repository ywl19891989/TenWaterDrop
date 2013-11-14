//
//  LayoutUtil.h
//  game-ios
//
//  Created by wenlong on 13-5-14.
//
//

#ifndef __FrameWork_Cocos2d__LayoutUtil__
#define __FrameWork_Cocos2d__LayoutUtil__

#include "cocos2d.h"

using namespace cocos2d;

enum ccLayoutPosion {
    kLayoutPosCenter = 0,
    
    kLayoutPosLeftCenter = 1,
    kLayoutPosRightCenter = 2,
    kLayoutPosTopCenter = 3,
    kLayoutPosBottomCenter = 4,
    
    kLayoutPosLeftTop = 5,
    kLayoutPosLeftBottom = 6,
    kLayoutPosRightTop = 7,
    kLayoutPosRightBottom = 8,
};

class LayoutUtil {
public:
    static void layoutTo(CCNode* source, float alineX, float alineY, CCNode* target, float targetX, float targetY, float offsetX = 0, float offsetY = 0);
    
    static void layoutToCenter(cocos2d::CCNode *source, cocos2d::CCNode *target, float offsetX = 0 , float offsetY = 0);
    
    static void layoutToParent(CCNode* source, float alineX, float alineY, CCNode* target, float targetX, float targetY, float offsetX = 0, float offsetY = 0);
    
    static void layoutToParentCenter(cocos2d::CCNode *source, cocos2d::CCNode *target, float offsetX = 0 , float offsetY = 0);
    
    static void layoutTo(CCNode* src, ccLayoutPosion srcPos, CCNode* targer, ccLayoutPosion pos, float offsetX = 0 , float offsetY = 0);
    
    static void layoutToParent(CCNode* src, ccLayoutPosion srcPos, CCNode* targer, ccLayoutPosion pos, float offsetX = 0 , float offsetY = 0);
};

#endif /* defined(__FrameWork_Cocos2d__LayoutUtil__) */

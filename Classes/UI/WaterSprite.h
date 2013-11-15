/*
 * WaterSprite.h
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#ifndef WATERSPRITE_H_
#define WATERSPRITE_H_

#include "cocos2d.h"

class WaterSprite;
class ExplodeListener {
public:
    virtual void onExplodeEnd(WaterSprite* src) = 0;
};

class WaterSprite : public cocos2d::CCNode{
public:
	WaterSprite();
	virtual ~WaterSprite();

	CREATE_FUNC(WaterSprite);
	bool init();

	void setWaterNum(int num);
    
    void addWater();
    
    void showExplode();
    
    void explodeEnd();
    
    void setExplodeListener(ExplodeListener* listener);

private:
	int _waterNum;
	cocos2d::CCSprite* _water[4], *_waterExplode;
    char _tempStr[64];
    ExplodeListener* _explodeListener;
};

#endif /* WATERSPRITE_H_ */

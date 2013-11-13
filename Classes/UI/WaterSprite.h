/*
 * WaterSprite.h
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#ifndef WATERSPRITE_H_
#define WATERSPRITE_H_

#include "cocos2d.h"

class WaterSprite : public cocos2d::CCNode{
public:
	WaterSprite();
	virtual ~WaterSprite();

	CREATE_FUNC(WaterSprite);
	bool init();

	void setWaterNum(int num);

private:
	int _waterNum;
	cocos2d::CCSprite* _water[4];
};

#endif /* WATERSPRITE_H_ */

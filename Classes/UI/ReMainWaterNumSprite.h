/*
 * ReMainWaterNumSprite.h
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#ifndef ReMainWaterNumSprite_H_
#define ReMainWaterNumSprite_H_

#include "cocos2d.h"

class ReMainWaterNumSprite : public cocos2d::CCNode{
public:
	ReMainWaterNumSprite();
	virtual ~ReMainWaterNumSprite();

	CREATE_FUNC(ReMainWaterNumSprite);
	bool init();

	void setRemainWaterNum(int remainNum);

private:
	int _remainNum;
	cocos2d::CCSprite* _remainSprites[20];
	cocos2d::CCLabelTTF *_remainNumText;
};

#endif /* WATERNUMSPRITE_H_ */

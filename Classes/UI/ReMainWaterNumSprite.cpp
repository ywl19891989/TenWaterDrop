/*
 * ReMainWaterNumSprite.cpp
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#include "ReMainWaterNumSprite.h"

USING_NS_CC;

ReMainWaterNumSprite::ReMainWaterNumSprite() {
	// TODO Auto-generated constructor stub

}

ReMainWaterNumSprite::~ReMainWaterNumSprite() {
	// TODO Auto-generated destructor stub
}

bool ReMainWaterNumSprite::init() {

	if (!CCNode::init()) {
		return false;
	}

	char temp[64];

	setContentSize(CCSizeMake(92, 70));

	for (int i = 0; i < 20; i++) {
		sprintf(temp, "Images/game/s%d.png", i + 1);
		_remainSprites[i] = CCSprite::create(temp);
		addChild(_remainSprites[i]);
		_remainSprites[i]->setPosition(ccp(46, 35));
	}

	_remainNumText = CCLabelTTF::create("1", "arial", 34);
	_remainNumText->setColor(ccBLACK);
	addChild(_remainNumText, 1);
	_remainNumText->setPosition(ccp(46, 35));

	setRemainWaterNum(0);

	return true;
}

void ReMainWaterNumSprite::setRemainWaterNum(int num) {
	_remainNum = num;
	for (int i = 0; i < 20; i++) {
		_remainSprites[i]->setVisible((i + 1) == _remainNum);
	}
	char temp[32];
	sprintf(temp, "%d", _remainNum);
	_remainNumText->setString(temp);
}

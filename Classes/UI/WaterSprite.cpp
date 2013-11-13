/*
 * WaterSprite.cpp
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#include "WaterSprite.h"
#include "ResourceName.h"

USING_NS_CC;
using namespace Resources;

WaterSprite::WaterSprite() {
	// TODO Auto-generated constructor stub

}

WaterSprite::~WaterSprite() {
	// TODO Auto-generated destructor stub
}

bool WaterSprite::init() {

	if (!CCNode::init()) {
		return false;
	}

	char temp[64];

	setContentSize(CCSizeMake(50, 50));

	for (int i = 0; i < 4; i++) {
		sprintf(temp, "Images/game/drop%d.png", 4 - i);
		_water[i] = CCSprite::create(temp);
		addChild(_water[i]);
		_water[i]->setPosition(ccp(25, 25));
	}

	setWaterNum(0);

	return true;
}

void WaterSprite::setWaterNum(int num) {
	_waterNum = num;
	for (int i = 0; i < 4; i++) {
		_water[i]->setVisible( (i + 1) == _waterNum);
	}
}

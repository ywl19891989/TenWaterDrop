/*
 * ClassicGameScene.h
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#ifndef CLASSICGAMESCENE_H_
#define CLASSICGAMESCENE_H_

#include "cocos2d.h"

class ClassicGameScene : public cocos2d::CCScene{
public:
	ClassicGameScene();
	virtual ~ClassicGameScene();

	CREATE_FUNC(ClassicGameScene);
	bool init();

	void onClickBtn(cocos2d::CCNode* node);
};

#endif /* CLASSICGAMESCENE_H_ */

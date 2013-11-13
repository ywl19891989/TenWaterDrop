/*
 * CoverScene.h
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#ifndef __TENWATERDROP_COVERSCENE_H_
#define __TENWATERDROP_COVERSCENE_H_

#include "cocos2d.h"

class CoverScene: public cocos2d::CCScene {
public:
	CoverScene();
	virtual ~CoverScene();

	CREATE_FUNC( CoverScene);

	bool init();

	void onClickBtn(cocos2d::CCNode* node);
};

#endif /* COVERSCENE_H_ */

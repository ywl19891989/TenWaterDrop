/*
 * ClassicGameScene.h
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#ifndef CLASSICGAMESCENE_H_
#define CLASSICGAMESCENE_H_

#include "cocos2d.h"
#include "WaterSprite.h"

class ReMainWaterNumSprite;
class ClassicGameScene : public cocos2d::CCScene, public ExplodeListener{
public:
	ClassicGameScene();
	virtual ~ClassicGameScene();

	CREATE_FUNC(ClassicGameScene);
	bool init();

	void onClickBtn(cocos2d::CCNode* node);
    void onClickGrid(cocos2d::CCNode* node);
    
    void update(float dt);
    
    void onExplodeEnd(WaterSprite* water);
    
    void clearNode(cocos2d::CCNode* node);

private:

	static const int ROW_NUM = 6;
	static const int COL_NUM = 6;
	static const int TOTAL_NUM = ROW_NUM * COL_NUM;

	WaterSprite * _waters[TOTAL_NUM];
	ReMainWaterNumSprite *_remainNumText;
	int _waterNums[TOTAL_NUM], _remainWaterNum;
};

#endif /* CLASSICGAMESCENE_H_ */

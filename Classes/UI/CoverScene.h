/*
 * CoverScene.h
 *
 *  Created on: 2013-11-13
 *      Author: hali
 */

#ifndef __TENWATERDROP_COVERSCENE_H_
#define __TENWATERDROP_COVERSCENE_H_

#include "cocos2d.h"

class CoverScene: public cocos2d::CCScene, public cocos2d::CCKeypadDelegate{
public:
	CoverScene();
	virtual ~CoverScene();

	CREATE_FUNC( CoverScene);

	bool init();
    
    void update(float dt);
    
    virtual void onEnter();
    virtual void onExit();

	void onClickBtn(cocos2d::CCNode* node);
    
    void onClickHelp(cocos2d::CCNode* node);
    void enableMusic(cocos2d::CCNode* node);
    void disableMusic(cocos2d::CCNode* node);
    
    virtual void keyBackClicked();
    
private:
    cocos2d::CCMenuItem *_enableMusic, *_disableMusic;
};

#endif /* COVERSCENE_H_ */

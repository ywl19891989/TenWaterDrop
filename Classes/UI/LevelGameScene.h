//
//  LevelGameScene.h
//  TenWaterDrop
//
//  Created by wenlong on 13-11-15.
//
//

#ifndef __TenWaterDrop__LevelGameScene__
#define __TenWaterDrop__LevelGameScene__

#include "cocos2d.h"
#include "WaterSprite.h"

class ReMainWaterNumSprite;
class LevelGameScene : public cocos2d::CCScene, public ExplodeListener{
public:
	LevelGameScene();
	virtual ~LevelGameScene();
    
	CREATE_FUNC(LevelGameScene);
	bool init();
    
	void onClickBtn(cocos2d::CCNode* node);
    void onClickGrid(cocos2d::CCNode* node);
    
    void update(float dt);
    
    void onExplodeEnd(WaterSprite* water);
    
    void clearNode(cocos2d::CCNode* node);
    
    int getGridIndexByPos(cocos2d::CCPoint & pos);
    
    void detectDrops();
    
    bool isGridValid(int index);
    bool hasWater();
    void addGridWater(int index);
    void setRemainWater(int remainWater);
    
    void removeDrop(cocos2d::CCSprite* drop);
    
    void showDropWall(int index, int rotation);
    
    void setData(int level, int stage);
    
    void nextStage(cocos2d::CCNode* node);
    void retryStage(cocos2d::CCNode* node);
    
private:
    
	static const int ROW_NUM = 6;
	static const int COL_NUM = 6;
	static const int TOTAL_NUM = ROW_NUM * COL_NUM;
    static const int OFFSET_X = 30;
    static const int OFFSET_Y = 30;
    static const int GRID_WIDTH = 52;
    static const int GRID_HEIGHT = 52;
    static const int NO_WATER = 0;
    
    static const int ROTATION_RIGHT = 0;
    static const int ROTATION_LEFT = 180;
    static const int ROTATION_DOWN = 90;
    static const int ROTATION_UP = -90;
    
	WaterSprite * _waters[TOTAL_NUM];
	ReMainWaterNumSprite *_remainNumText;
	int _waterNums[TOTAL_NUM], _remainWaterNum;
    cocos2d::CCArray* _dropArrays;
    cocos2d::CCSprite *_gridBg;
    
    cocos2d::CCNode *_winNode, *_loseNode;
    
    int _remainClearNode, _curStage, _curLevel;
};

#endif /* defined(__TenWaterDrop__LevelGameScene__) */

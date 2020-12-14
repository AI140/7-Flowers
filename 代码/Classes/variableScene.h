//
// Created on 2020/11/27.
//

#ifndef __VARIABLESCENE_SCENE_H__
#define __VARIABLESCENE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class variableScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void ShowScore(int scoreNum);
    void backToCallback(cocos2d::Ref* pSender);
    void update(float dt);

    void lockCallback(Ref* pSender);

    CREATE_FUNC(variableScene);


private:
    int now= 0;
    int score=0;

    int start=0;
    int finish=0;

    int touchTime=1;   //点击次数

    int lock=0;

};


#endif //PROJ_ANDROID_VARIABLESCENE_H

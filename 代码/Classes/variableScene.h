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

private:
    bool start= false;
};


#endif //PROJ_ANDROID_VARIABLESCENE_H

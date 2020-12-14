//
// Created by 蔡艳菲 on 2020/12/12.
//

#ifndef PROJ_ANDROID_STORYSCENE_H
#define PROJ_ANDROID_STORYSCENE_H

#include "cocos2d.h"

using namespace cocos2d;

class storyScene: public cocos2d::Scene {
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *unused_event);

private:
    int touchTime=1;

    CREATE_FUNC(storyScene);
};


#endif //PROJ_ANDROID_STORYSCENE_H

//
// Created  on 2020/11/27.
//

#ifndef __SNOWSCENE_SCENE_H__
#define __SNOWSCENE_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;

class snowScene : public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void backToCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(snowScene);
};


#endif //PROJ_ANDROID_SNOWSCENE_H

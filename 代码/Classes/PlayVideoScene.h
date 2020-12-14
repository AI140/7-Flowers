//
// Created by ThinkPad on 2020/12/13.
//

#ifndef PROJ_ANDROID_PLAYVIDEOSCENE_H
#define PROJ_ANDROID_PLAYVIDEOSCENE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "variableScene.h"
#include "variableScene2.h"
#include "grammarScene.h"
#include "grammarScene2.h"
#include "grammarScene3.h"
#include "grammarScene4.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class PlayVideoScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void roundoneToCallback(cocos2d::Ref* pSender);
    void roundtwoToCallback(cocos2d::Ref* pSender);
    void roundthreeToCallback(cocos2d::Ref* pSender);
    void roundfourToCallback(cocos2d::Ref* pSender);
    void roundfiveToCallback(cocos2d::Ref* pSender);
    void roundsixToCallback(cocos2d::Ref* pSender);


    bool onTouchBegan(Touch *touch, Event *event);
    void backToCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(PlayVideoScene);
private:
    int click;
};




#endif //PROJ_ANDROID_PLAYVIDEOSCENE_H

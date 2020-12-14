//
// Created on 2020/11/27.
//

#ifndef PROJ_ANDROID_GRAMMARSCENE_H
#define PROJ_ANDROID_GRAMMARSCENE_H

#include "cocos2d.h"

using namespace cocos2d;

class grammarScene : public cocos2d::Scene{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void forwardTurnCallback(Ref* pSender);
    void leftTurnCallback(Ref* pSender);
    void rightTurnCallback(Ref* pSender);

    void backToCallback(cocos2d::Ref* pSender);

    bool onTouchBegan(Touch *touch, Event *unused_event);

    void showCode();

    void forwardTurn();
    void leftTurn();
    void rightTurn();


    CREATE_FUNC(grammarScene);

private:
    int up=1;
    int down=0;
    int left=0;
    int right=0;

    int step=1;

    std::string code_text;

    int touchTime=1; //点击次数

};


#endif //PROJ_ANDROID_GRAMMARSCENE_H

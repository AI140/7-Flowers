//
// Created by 蔡艳菲 on 2020/12/12.
//

#ifndef PROJ_ANDROID_GRAMMARSCENE4_H
#define PROJ_ANDROID_GRAMMARSCENE4_H


#include "cocos2d.h"

using namespace cocos2d;

class grammarScene4 : public cocos2d::Scene{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void forwardTurnCallback(Ref* pSender);
    void leftTurnCallback(Ref* pSender);
    void rightTurnCallback(Ref* pSender);
    void ifButtonCallback(Ref* pSender);
    void forButtonCallback(Ref* pSender);
    void functionButtonCallback(Ref* pSender);

    void backToCallback(Ref *pSender);

    void showCode();
    void update(float dt);

    void forwardTurn();
    void leftTurn();
    void rightTurn();

    bool onTouchBegan(Touch *touch, Event *unused_event);

    CREATE_FUNC(grammarScene4);

    friend class IfPopScene;
    friend class ForPopScene;
    friend class FuncPopScene;
private:
    int up=1;
    int down=0;
    int left=0;
    int right=0;

    int step=1;

    std::string code_text;

    int time=1;   //时间

    int touchTime=1;
    bool use_if=false; //是否使用了if

};


#endif //PROJ_ANDROID_GRAMMARSCENE4_H

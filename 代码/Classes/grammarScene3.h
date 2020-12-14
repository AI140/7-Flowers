//
// Created by 蔡艳菲 on 2020/12/12.
//

#ifndef PROJ_ANDROID_GRAMMARSCENE3_H
#define PROJ_ANDROID_GRAMMARSCENE3_H


#include "cocos2d.h"

using namespace cocos2d;

class grammarScene3 : public cocos2d::Scene{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void forwardTurnCallback(Ref* pSender);
    void leftTurnCallback(Ref* pSender);
    void rightTurnCallback(Ref* pSender);
    void ifButtonCallback(Ref* pSender);
    void forButtonCallback(Ref* pSender);

    void backToCallback(Ref *pSender);

    void forwardTurn();
    void leftTurn();
    void rightTurn();

    void showCode();
    void update(float dt);

    bool onTouchBegan(Touch *touch, Event *unused_event);

    CREATE_FUNC(grammarScene3);

    friend class IfPopScene;
    friend class ForPopScene;
private:
    int up=1;
    int down=0;
    int left=0;
    int right=0;

    int step=1;

    std::string code_text;

    int time=1;   //时间

    int touchTime=1;//点击次数

    bool use_if=false; //是否使用了if

};

#endif //PROJ_ANDROID_GRAMMARSCENE3_H

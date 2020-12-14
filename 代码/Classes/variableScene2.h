//
// Created by ThinkPad on 2020/12/8.
//

#ifndef MYCOCOSDEMO_VARIABLESCENE2_H
#define MYCOCOSDEMO_VARIABLESCENE2_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
USING_NS_CC;

class variableScene2 : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void backToCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(Touch *touch, Event *event);
    int SetText(Layer* layer, int num);

    void Judge();
    void countUpdate(float dt);
    CREATE_FUNC(variableScene2);


private:
    int num=0;//第几题
    int Score=0;   //得分
    int downTime = 15; //倒计时
    int random = 0; //正确答案位置
    int select = -1; //选择的位置
    int touchTime=1;//点击次数
    bool timeOut = true;
    bool start=false;//判断是否开始
    bool click=false;//判断玩家是否做出选择

    //答题图集
    Vector<Sprite*> Answer = Vector<Sprite*>(6);

    //问题和答案文本
    std::string Question[6] = {"1.比大小：a=21, b=12,a__b",
                               "2.比大小：a=121, b=132,a__b",
                               "3.计算：a=5,b=3,a/b=__",
                               "4.计算：a=10,b=3,a//b=__",
                               "5.计算：a=15,b=2,b*=a,b=__",
                               "6.判断：a=3,b=4,b%a-1+b=__"};
    std::string True[6] = {">", "!=", "1.67", "3", "30", "4"};
    std::string False1[6] = {">=", ">", "1", "3.33", "2", "3"};
    std::string False2[6] = {"<", "<=", "2", "4", "15", "4.3"};
};


#endif //MYCOCOSDEMO_VARIABLESCENE2_H

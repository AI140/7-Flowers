//
// Created on 2020/11/27.
//

#include "variableScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

USING_NS_CC;

Scene* variableScene::createScene()
{
    return variableScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool variableScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //设置监听事件
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(variableScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    //设置背景图片
    auto levelBackGround = Sprite::create("background-2.jpg");
    levelBackGround->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    levelBackGround->setScale(2.5,2);
    this->addChild(levelBackGround, 0);
    //设置开始LABEL
    auto label = Label::createWithTTF("Begin", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2 + label->getContentSize().width,
                                origin.y + visibleSize.height - label->getContentSize().height));
    label->setName("begin");
    this->addChild(label, 0);


    //添加矿工
    auto person = Sprite::create("person.png");
    person->setPosition(visibleSize.width / 2, visibleSize.height*2/3+60);
    person->setName("person");
    person->setScale(0.2);
    this->addChild(person, 1);


    //添加矿车
    auto car = Sprite::create("car.png");
    car->setPosition(visibleSize.width-50, visibleSize.height*2/3+50);
    car->setName("car");
    car->setScale(0.2);
    this->addChild(car, 2);
    //矿车上标签
    auto car_label= Label::Label::createWithTTF("Int", "fonts/Marker Felt.ttf", 24);
    car_label->setPosition(visibleSize.width-50, visibleSize.height*2/3+50);
    car_label->setName("car_label");
    this->addChild(car_label,3);


    //设置钩子
    auto hook = Sprite::create("hook.png");
    hook->setPosition(visibleSize.width/2, visibleSize.height*2/3+10);
    hook->setName("hook");
    hook->setScale(2.5);
    this->addChild(hook, 1);


    //设置黄金层
    auto goldLayer = Layer::create();
    goldLayer->setPosition(0, 0);
    goldLayer->setName("goldLayer");
    this->addChild(goldLayer, 1);


    //添加黄金
    const int GOLD_COUNT=8;
    srand(int(time(NULL)));

    // 将矿石层分成2行(GOLD_COUNT/2)列的小方格
    // 生成矿石精灵时，每个精灵在一个方格中随机取位置
    int x_width = int(visibleSize.width)/(GOLD_COUNT/2);
    int y_height = int(visibleSize.height)/3.5;

    // 题库 --数组形式
    std::string intSet[] = {"1", "3", "4", "11", "0", "-10", "-100", "8750", "123", "-984"};
    std::string floatSet[] = {"-2.7", "0.0", "0.9", "12.0", "-0.333333", "81.0", "16.666667", "9.43", "3.14"};
    std::string boolSet[] = {"true", "false"};
    std::string stringSet[] = {"Hello World!", "a", "123", "9.43", "true", "你好", "True", "2*3", "ABC", "矿"};

    // 创建矿石精灵和标签
    for(int i=0;i<8;++i){
        auto gold = Sprite::create("gold1.png");
        // 随机生成位置
        float x_origin = origin.x + i%(GOLD_COUNT/2)*x_width;	// 确定精灵所在小方格的x轴起始坐标
        float y_origin = origin.y + i/4*y_height+20;	// 确定精灵所在小方格的y轴起始坐标
        float x_index = x_origin + rand()%x_width;	// 随机生成精灵位置的x坐标
        float y_index = y_origin + rand()%y_height;	//随机生成精灵位置的y坐标
        gold->setPosition(Vec2(x_index, y_index));
        gold->setScale(0.5);
        // 命名，并加入图层
        gold->setTag(i);
       // goldLayer->addChild(gold, 1);
       this->addChild(gold,1);

        std::string labelText ="";
        //每个类型随机产生两个数据
        switch (i%4) {
            case 0:
                labelText =intSet[rand()%(sizeof(intSet)/sizeof(intSet[0]))];
                break;
            case 1:
                labelText=floatSet[rand()%(sizeof(floatSet)/sizeof(floatSet[0]))];
                break;
            case 2:
                labelText=boolSet[rand()%(sizeof(boolSet)/sizeof(boolSet[0]))];
                break;
            case 3:
                labelText=stringSet[rand()%(sizeof(stringSet)/sizeof(stringSet[0]))];
                break;

        }


        auto goldLabel = Label::createWithTTF(labelText, "fonts/Marker Felt.ttf", 24);
        goldLabel -> setPosition(Vec2(x_index, y_index));	// 放在对应矿石精灵的位置上
        goldLabel -> setTag(i+GOLD_COUNT);
        goldLabel->setScale(0.6);
        this -> addChild(goldLabel, 1);

    }

    this->addChild(goldLayer,1);

    //----------------------------------------------------------------------Orange
    //分数显示框

    auto score = Label::createWithSystemFont("0","Arial",24);
    score->setAnchorPoint(Vec2(0,1));
    score->setPosition(0,visibleSize.height);
    score->setName("score");
    this->addChild(score,1);

    //倒计时显示框
    auto countDown = Label::createWithSystemFont("15s","Arial",24);
    countDown->setAnchorPoint(Vec2(1,1));
    countDown->setPosition(visibleSize.width-countDown->getContentSize().width,visibleSize.height);
    countDown->setName("countDown");
    this->addChild(countDown,1);


    //----------------------------------------------------------------------Orange


    return true;
}

bool variableScene::onTouchBegan(Touch *touch, Event *unused_event) {
    //得到鼠标点击的地方
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto location = touch->getLocation();


    //getChildByName获得每个实例
    auto hook = this->getChildByName("hook");
    auto car = this->getChildByName("car");
    auto person = this->getChildByName("person");
    auto label= this->getChildByName("label");


    //判断是否点击开始
    bool isInBegin = person->getBoundingBox().containsPoint(location);
    if(isInBegin){
        //判断是否需要修改车上label
        Label* car_label= (Label*)this->getChildByName("car_label");
        car_label->setScale(0.8);
        Label* countDown= (Label*)this->getChildByName("countDown");
        countDown->setString("15");
        switch(now){
            case 0: car_label->setString("Int");
                break;
            case 1: car_label->setString("Float");
                break;
            case 2: car_label->setString("Bool");
                break;
            case 3: car_label->setString("String");
                break;

        }
        now++;   //下一辆车

        //矿车和车上的LABEL一起往前运动
        auto actionBy = MoveBy::create(1.0f, Point(-visibleSize.width*1/15,0));
        auto initial=Place::create(Point(visibleSize.width-50,visibleSize.height*2/3+50));

        auto action_re = Repeat::create(actionBy,15);
        auto move = Sequence::create(initial,action_re, nullptr);

        car->runAction(move->clone());
        car_label->runAction(move->clone());
        //定时器更新 每一秒刷新一次 更新倒计时
        this->schedule( schedule_selector(variableScene::update), 1.0f );

    }else{
        //点击其他地方 钩子都运动到此处
        auto catchIt = MoveTo::create(2,location);
        auto back =MoveTo::create(2,Vec2(visibleSize.width/2, visibleSize.height*2/3+10));
        auto hookMove=Sequence::create(catchIt,back, nullptr);

        //找出本局正确的2个黄金
         auto gold1=this->getChildByTag(now);
         auto label1=this->getChildByTag(now+8);
         auto gold2=this->getChildByTag(now+4);
         auto label2=this->getChildByTag(now+4+8);
         //判断是否点击黄金
         bool isInGold1 = gold1->getBoundingBox().containsPoint(location)||
                 label1->getBoundingBox().containsPoint(location);
         bool isInGold2 = gold2->getBoundingBox().containsPoint(location)||
                 label2->getBoundingBox().containsPoint(location);
         if (isInGold1) {
                //发射钩子
                hook->runAction(hookMove);

                //更新当前得分
                score++;
                ShowScore(score);
                //黄金和label同时回去
                auto delay= DelayTime::create(2.0f);
                auto goldMove= Sequence::create(delay,back->clone(),nullptr);
                gold1->runAction(goldMove);
                auto labelMove=Sequence::create(delay,back->clone(),nullptr);
                label1->runAction(labelMove);

            }else{
                if (isInGold2) {
                    //发射钩子
                    hook->runAction(hookMove);
                    //加分
                    score++;
                     ShowScore(score);
                    //黄金和label同时回去
                    auto delay= DelayTime::create(2.0f);
                    auto goldMove= Sequence::create(delay,back->clone(),nullptr);
                    gold2->runAction(goldMove);
                    auto labelMove=Sequence::create(delay,back->clone(),nullptr);
                    label2->runAction(labelMove);
                }else{
                    hook->runAction(hookMove);   //抓错 只有钩子运动 黄金不动
                }

            }
    }

    return true;
}

//-----------------------------------------------Orange
//计分栏
void variableScene::ShowScore(int scoreNum){

    std::string str_score=std::to_string(scoreNum);
    Label* score= (Label*)this->getChildByName("score");
    score->setString(str_score);
    this->addChild(score,1);

}

//倒计时栏
void variableScene::update(float dt){
    Label* countDown = (Label*)this->getChildByName("countDown");
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> num = countDown->getString();
    int downTime = std::stoi(num)-1;
    if(downTime<1){
        this->unscheduleAllSelectors();
    }
    countDown->setString(std::to_string(downTime));
}

//
// Created on 2020/11/27.
//

#include "variableScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

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
/*
    //设置监听事件
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(variableScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
*/
    //设置背景图片
    auto levelBackGround = Sprite::create("background-2.jpg");
    levelBackGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(levelBackGround, 0);

    //添加矿工
    auto person = Sprite::create("person.png");
    person->setPosition(visibleSize.width / 2, visibleSize.height*2/3);
    person->setName("person");
    this->addChild(person, 1);

    //设置矿车层
    auto carLayer = Layer::create();
    carLayer->setPosition(0, visibleSize.height*2/3);
    carLayer->setName("carLayer");
    this->addChild(carLayer, 1);
    //添加矿车
    auto car = Sprite::create("car.png");
    car->setPosition(visibleSize.width / 2, 0);
    car->setName("car");
    carLayer->addChild(car, 1);

    //设置钩子和绳子
    auto hook = Sprite::create("hook.png");
    hook->setPosition(visibleSize.width/2, visibleSize.height*3/4-50);
    hook->setName("hook");
    hook->addChild(hook, 1);
    auto rope = Sprite::create("rope.png");
    rope->setPosition(600, 480);
    rope->setName("rope");
    rope->addChild(rope, 1);


    //设置黄金层
    auto goldLayer = Layer::create();
    goldLayer->setPosition(0, 0);
    goldLayer->setName("goldLayer");
    this->addChild(goldLayer, 1);
    //向黄金层添加黄金（多个）
    auto gold = Sprite::create("gold1.png");
    gold->setPosition(600, 480);
    gold->setName("gold");
    gold->addChild(gold, 1);
    //黄金对应位置添加label  未写
    //...

    //分数显示框（未写）

    //倒计时显示框（未写）


    return true;
}

bool variableScene::onTouchBegan(Touch *touch, Event *unused_event) {
    //得到鼠标点击的地方
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto location = touch->getLocation();

    //控制台输出
    CCLOG("location == %f, location == %f", location.x, location.y);

    //getChildByName获得每个实例
    auto goldLayer = this->getChildByName("goldLayer");
    //多个gold 未写完！
    auto gold = goldLayer->getChildByName("gold");
    auto hook = this->getChildByName("hook");
    auto carLayer= this->getChildByName("carLayer");
    auto car = this->getChildByName("car");
    auto person = this->getChildByName("person");


    //判断是否点击开始
    bool isInBegin = getBoundingBox().containsPoint(location);
    if(isInBegin){
        //矿车动起来

    }

    //判断是否点击黄金
    bool isIngold = gold->getBoundingBox().containsPoint(location);
    if (isIngold) {
        //发射钩子
        auto catchIt = MoveTo::create(2,location);
        auto back =catchIt->reverse();
        hook->runAction(catchIt);



    }
    else {

    }
    return true;
}
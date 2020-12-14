//
// Created on 2020/11/27.
//

#include "variableScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "popScene.h"
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
    auto color=Color3B(60,60,60);


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
    auto person = Sprite::create("person_down.png");
    person->setPosition(visibleSize.width / 2, visibleSize.height*2/3+60);
    person->setName("person");
    person->setScale(0.42);
    this->addChild(person, 1);


    //添加矿车
    auto car = Sprite::create("car.png");
    car->setPosition(visibleSize.width-50, visibleSize.height*2/3+50);
    car->setName("car");
    car->setScale(0.2);
    this->addChild(car, 2);
    //矿车上标签
    auto car_label= Label::createWithTTF("Int", "fonts/XPZ.TTF", 24);
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
    std::string stringSet[] = {"\"Hello World!\"", "\"a\"", "\"123\"", "\"9.43\"", "\"true\"", "\"你好\"", "\"True\"", "\"2*3\"", "\"ABC\"", "\"矿\""};

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


        auto goldLabel = Label::createWithTTF(labelText, "fonts/XPZ.TTF", 24);
        goldLabel -> setPosition(Vec2(x_index, y_index));	// 放在对应矿石精灵的位置上
        goldLabel -> setTag(i+GOLD_COUNT);
        goldLabel->setScale(0.6);
        goldLabel->setColor(color);
        this -> addChild(goldLabel, 1);

    }

    this->addChild(goldLayer,1);

    //退出按钮
    auto backItem = MenuItemImage::create("back.png", "back.png",
                                          CC_CALLBACK_1(variableScene::backToCallback, this));
    backItem->setScale(2.5);
    auto back = Menu::create(backItem, NULL);
    back->setPosition(Vec2(origin.x+visibleSize.width*0+25,origin.y+visibleSize.height-35)); //用不用vec2
    this->addChild(back, 6);

    //分数显示框

    auto score = Label::createWithSystemFont("0","fonts/XPZ.TTF",24);
    score->setAnchorPoint(Vec2(0,1));
    score->setPosition(50,visibleSize.height);
    score->setName("score");
    this->addChild(score,1);

    //倒计时显示框
    auto countDown = Label::createWithSystemFont("15s","fonts/XPZ.TTF",24);
    countDown->setAnchorPoint(Vec2(1,1));
    countDown->setPosition(visibleSize.width-countDown->getContentSize().width,visibleSize.height);
    countDown->setName("countDown");
    this->addChild(countDown,1);


    //添加故事区
    auto story_text = Label::createWithTTF("\t\t不知过了多久，小赛文渐渐苏醒。恢复了一会儿后，他开始观察\n身处的环境。飞船有些损坏，一些零部件松动的厉害，\n\t\t而赛文怎么也找不到工具箱。","fonts/STKAITI.TTF", 15);
    story_text->setPosition(14,visibleSize.height*0+112);
    story_text->setName("story_text");
    story_text->setAnchorPoint(Vec2(0,1));
    this->addChild(story_text,5);

    //故事背景区
    auto story_background = Sprite::create("storyback.png");
    story_background->setPosition(Vec2(visibleSize.width/2-8,visibleSize.height/5+20));
    story_background->setName("story_background");
    story_background->setScale(5,2.2);
    this->addChild(story_background,4);

    auto story_chuan = Sprite::create("storyback1.png");
    story_chuan->setPosition(Vec2(visibleSize.width-20,visibleSize.height/5-4));
    story_chuan->setScale(0.5);
    story_chuan->setName("chuan");
    this->addChild(story_chuan,5);

    return true;
}

bool variableScene::onTouchBegan(Touch *touch, Event *unused_event) {

    Label* story_text=(Label *)this->getChildByName("story_text");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto countDown=(Label*)this->getChildByName("countDown");


    if(touchTime==1){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t“算了，先看看我这是在哪儿。”赛文翻出那张宇宙图鉴，仔细\n对照着……是派森星！可能是降落设置出了问题，但——\n\t\t真是不幸中的万幸。");
        ++touchTime;

        return true;
    }
    if(touchTime==2){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t“应该是派森星的变量矿区，我要在周围探索一下，找找看\n有没有什么可以修复飞船的东西。”\n\t\t赛文说着，拍了拍身上的土，向矿区入口走去……");
        ++touchTime;

        return true;
    }
    if(touchTime==3){
        story_text->setVisible(false);

        Sprite* story_background=(Sprite *)this->getChildByName("story_background");
        story_background->setVisible(false);

        Sprite* story_chuan=(Sprite *)this->getChildByName("chuan");
        story_chuan->setVisible(false);

        ++touchTime;
        return true;

    }




    //得到鼠标点击的地方
    auto location = touch->getLocation();

    //getChildByName获得每个实例
    auto hook = this->getChildByName("hook");
    auto car = this->getChildByName("car");
    auto begin = (Label*)this->getChildByName("begin");
    auto label= this->getChildByName("label");


    //判断是否点击开始
    bool isInBegin = begin->getBoundingBox().containsPoint(location);
    if(isInBegin){

        if(now==4 &&score<6){
            //弹窗 返回
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/wrong.wav", false);
            //弹窗 下一关
            PopScene* popLayer = PopScene::create();
            this->addChild(popLayer,7);
            popLayer->backScene(1);
            return true;
        }

        if(now==4 &&score>=6){
            //胜利音效
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/victory.ogg", false);
            //弹窗 下一关
            PopScene* popLayer = PopScene::create();
            popLayer->nextScene(2);
            popLayer->backScene(0);
            this->addChild(popLayer,7);

            return true;
        }
        start=1;
        //背景音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);
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
                begin->setString("End");
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
        if(start==1){
            //点击其他地方 钩子都运动到此处
            auto catchIt = MoveTo::create(2,location);
            auto back =MoveTo::create(2,Vec2(visibleSize.width/2, visibleSize.height*2/3+10));
            auto callback1 = CallFunc::create([&](){
                lock=0;
            });
            auto hookMove=Sequence::create(catchIt,back,callback1,nullptr);

            //找出本局正确的2个黄金
            auto gold1=this->getChildByTag(now-1);
            auto label1=this->getChildByTag(now+7);
            auto gold2=this->getChildByTag(now+3);
            auto label2=this->getChildByTag(now+4+7);
            //判断是否点击黄金
            bool isInGold1 = gold1->getBoundingBox().containsPoint(location)||
                             label1->getBoundingBox().containsPoint(location);
            bool isInGold2 = gold2->getBoundingBox().containsPoint(location)||
                             label2->getBoundingBox().containsPoint(location);
            if (isInGold1) {
                //正确音效
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/right.mp3", false);
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
                    //正确音效
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/right.mp3", false);
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
                    if(lock==0){
                        //错误音效
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/wrong.wav", false);
                        lock=1;
                        hook->runAction(hookMove);   //抓错 只有钩子运动 黄金不动
                    }
                }

            }
        }

    }

    return true;
}

void variableScene::lockCallback(Ref *pSender) {

    lock=0;
}

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

//返回按钮回调函数
void variableScene::backToCallback(Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);
    auto HelloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HelloWorldScene);
    //两个类互相调用 要把主页面里的B变成指针
}


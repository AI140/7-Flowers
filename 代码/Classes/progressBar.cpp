# include "progressBar.h"
#include "cocos2d.h"
//#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "storyScene.h"

using namespace cocos2d::extension;
using namespace cocos2d;

USING_NS_CC;

Scene* progressBar::createScene()
{
    return progressBar::create();
}


bool progressBar::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/story.mp3", true);

    //创建背景1
    auto background1 = Sprite::create("loadback1.png");
    background1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    background1->setName("background1");
    background1->setScale(1.2);
    this->addChild(background1,-1);

    //创建背景2
    auto background2 = Sprite::create("loadback2.png");
    background2->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    background2->setName("background2");
    background2->setScale(1.2);
    this->addChild(background2,-1);


    // 创建一个进度条边框精灵
    auto borderSprite = Sprite::create("loadBorder.png");
    //borderSprite->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    borderSprite->setPosition(Vec2(origin.x+visibleSize.width/2, 50));
    borderSprite->setScale(1.5);
    this->addChild(borderSprite, 1);

    // 创建一个进度条精灵
    auto barSprite = Sprite::create("loadBar.png");
    loadProgress = ProgressTimer::create(barSprite);
    loadProgress->ProgressTimer::setType(cocos2d::ProgressTimer::Type::BAR);
    loadProgress->setPosition(Vec2(origin.x+visibleSize.width/2, 50));
    loadProgress->setScale(1.5);
    // 进度条属性设置
    loadProgress->setMidpoint(Vec2(0, 0));	//运动方向：从左向右
    loadProgress->setBarChangeRate(Vec2(1, 0));	//x轴
    loadProgress->setPercentage(0);		//设置当前进度条为0%
    this->addChild(loadProgress, 1);
    // 标签
    loadLabel = Label::createWithTTF("游戏资源加载中……", "fonts/XPZ.TTF", 15);
    Color3B color = Color3B(249,100,45);
    loadLabel->setColor(color);
    loadLabel->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/6));
    this->addChild(loadLabel, 1);

    percentLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
    percentLabel->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    percentLabel->setName("percentLabel");
    percentLabel->setVisible(false);
    this->addChild(percentLabel, 1);

    //再创一个定时器 更新背景
    this->schedule(schedule_selector(progressBar::updateBackground), 0.4f );

    // 默认调度器，调用update()函数
    scheduleUpdate();

    return true;
}

void progressBar::updateBackground(float dt){
    Sprite* background1 = (Sprite*)this->getChildByName("background1");
    Sprite* background2 = (Sprite*)this->getChildByName("background2");

    if(change==0){
        background1->setVisible(true);
        background2->setVisible(false);
        change=1;
    }else{
        background2->setVisible(true);
        background1->setVisible(false);
        change=0;
    }
}

void progressBar::update(float dt)
{


    float percent = loadProgress->getPercentage();
    percent += 0.5f;
    loadProgress->setPercentage(percent);	// 进度每次加1%



    if(percent==100.f){
        auto HelloWorldScene = storyScene::createScene();
        Director::getInstance()->replaceScene(HelloWorldScene);
    }

    Label* percentLabel= (Label*) this->getChildByName("percentLabel");

    if(percent>100) {
        unscheduleUpdate();
    }
}

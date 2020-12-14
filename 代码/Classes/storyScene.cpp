//
// Created by 蔡艳菲 on 2020/12/12.
//

#include "storyScene.h"
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "cocos-ext.h"


using namespace cocos2d::extension;
using namespace cocos2d;

USING_NS_CC;

Scene* storyScene::createScene()
{
    return storyScene::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool storyScene::init() {
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
    listener->onTouchBegan = CC_CALLBACK_2(storyScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto background = Sprite::create("star.jpg");
    background->setPosition(visibleSize.width/2,visibleSize.height/2);
    background->setName("background");
    background->setScale(4,4);
    this->addChild(background,-1);

    /*
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "Marker Felt.ttf";
    labelConfig.fontSize = 16;
     */

    // create a TTF Label from the TTFConfig file.
    //添加故事区
    auto story_text = Label::createWithTTF("\t\t在遥远的格利泽581g星球上，年轻的探险家赛文·弗劳瓦斯\n 正在整顿行装，准备启程踏上下一段旅途。","fonts/STKAITI.TTF", 15);
    story_text->setPosition(14,visibleSize.height*0+112);
    story_text->setName("story_text");
    story_text->setAnchorPoint(Vec2(0,1));
    this->addChild(story_text,1);

    //故事背景区
    auto story_background = Sprite::create("storyback.png");
    story_background->setPosition(Vec2(visibleSize.width/2-8,visibleSize.height/5+20));
    story_background->setScale(5,2.2);
    this->addChild(story_background,0);

    auto story_chuan = Sprite::create("storyback1.png");
    story_chuan->setPosition(Vec2(visibleSize.width-20,visibleSize.height/5-4));
    story_chuan->setScale(0.5);
    story_chuan->setName("chuan");
    this->addChild(story_chuan,1);

    //小人
    auto person = Sprite::create("person_right.png");
    person->setPosition(Vec2(visibleSize.width/6,visibleSize.height*2/3));
    person->setName("person");
    person->setScale(0.3);
    this->addChild(person,2);

    return true;
}

bool storyScene::onTouchBegan(Touch *touch, Event *unused_event) {

    Label* story_text=(Label *)this->getChildByName("story_text");
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if(touchTime==1){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t他翻开旅行手册，并将一份宇宙航行全图鉴展开、平铺在\n格利泽星球深蓝色的土地上，拿起放大镜，仔细地搜寻着……");
        ++touchTime;

        auto mirror = Sprite::create("mirror.png");
        mirror->setPosition(Vec2(visibleSize.width/6+15,visibleSize.height*2/3-8));
        mirror->setName("mirror");
        mirror->setScale(1.2);
        this->addChild(mirror,2);

        return true;
    }
    if(touchTime==2){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t“下一站是……派森星，距离20光年，不出意外今夜出发，\n第二天中午就可以着陆。”小赛文自言自语着，他早就在\n宇宙年报上见过派森星的照片，爱好星际旅游的他终于可以去看看了。");
        ++touchTime;

        return true;
    }

    if(touchTime==3){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t收拾停当，小赛文自信又得意地拍了拍自己的小飞船——\n这是一艘陪伴了赛文5年的星际旅行专用航行器，之所以有它，\n赛文才可以一直追寻自己航行宇宙的梦想。\n"
                              "\t\t“出发！”");
        ++touchTime;

        Sprite * mirror =(Sprite*)this->getChildByName("mirror");
        mirror->setVisible(false);

        Sprite * chuan =(Sprite*)this->getChildByName("chuan");
        auto move= MoveTo::create(1.2,Vec2(visibleSize.width/6+38,visibleSize.height*2/3-8));
        chuan->runAction(move);

        return true;
    }

    if(touchTime==4){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);

        Sprite * background =(Sprite*)this->getChildByName("background");

        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("room.png");

        background->setTexture(texture);

        story_text->setString("“滴！滴！滴！”一阵急促的警报声打破了宇宙的宁静。");

        auto warning = Sprite::create("warning.png");
        warning->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+40));
        warning->setScale(0.7);
        warning->setName("warning");
        this->addChild(warning,2);

        Sprite * chuan =(Sprite*)this->getChildByName("chuan");
        auto back = Place::create(Vec2(visibleSize.width-20,visibleSize.height/5-4));
        chuan->runAction(back);

        Sprite * person =(Sprite*)this->getChildByName("person");
        person->setVisible(false);

        ++touchTime;
        return true;

    }

    if(touchTime==5){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t“发生甚么事了？？”操控室里盖着毛毯小憩的赛文一下子被惊醒，\n\t飞船开始了剧烈的晃动，赛文不得不放低重心，用力把住\n\t操控台边沿才能稳定住身体。");

        ++touchTime;
        return true;
    }

    if(touchTime==6){
        //打字音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t突然，飞船急剧降落，赛文一下子撞到了仓顶，他只觉得眼前\n一片漆黑——\n\t\t提示：请点击地图——变量矿区，解锁剧情");

        Sprite * background =(Sprite*)this->getChildByName("background");

        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("black.jpg");

        background->setTexture(texture);

        Sprite * warning =(Sprite*)this->getChildByName("warning");
        warning->setVisible(false);

        ++touchTime;
        return true;

    }
    if(touchTime==7){
        auto HelloWorldScene = HelloWorld::create();
        Director::getInstance()->replaceScene(HelloWorldScene);
    }



   return true;
}
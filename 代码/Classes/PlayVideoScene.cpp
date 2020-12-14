//
// Created by ThinkPad on 2020/12/13.
//
#include "PlayVideoScene.h"

USING_NS_CC;

Scene* PlayVideoScene::createScene()
{
    return PlayVideoScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PlayVideoScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayVideoScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto color=Color3B(112,123,161);

    //设置背景
    auto background=Sprite::create("background1.png");
    background->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    background->setScale(1.12);
    this->addChild(background,1);

    //退出界面按钮
    auto backItem = MenuItemImage::create("back.png", "back.png",
                                          CC_CALLBACK_1(PlayVideoScene::backToCallback, this));
    backItem->setScale(2.5);
    auto back = Menu::create(backItem, NULL);
    back->setPosition(Vec2(origin.x+visibleSize.width-30,origin.y+visibleSize.height-30));
    this->addChild(back,3);

    //设置按钮
    auto label1 = Label::createWithTTF("变量矿区1", "fonts/XPZ.TTF", 24);
    label1->setPosition(Vec2(origin.x+visibleSize.width /7,
                            origin.y+visibleSize.height - 25));
    label1->setName("label1");
    label1->setColor(color);
    this->addChild(label1, 1);
    label1->setVisible(true);

    auto label2 = Label::createWithTTF("变量矿区2", "fonts/XPZ.TTF", 24);
    label2->setPosition(Vec2(origin.x+visibleSize.width / 7,
                             origin.y+visibleSize.height - 65));
    label2->setName("label2");
    label2->setColor(color);
    this->addChild(label2, 1);
    label2->setVisible(true);

    auto label3 = Label::createWithTTF("语法丛林1", "fonts/XPZ.TTF", 24);
    label3->setPosition(Vec2(origin.x+visibleSize.width / 7,
                             origin.y+visibleSize.height - 105));
    label3->setName("label3");
    label3->setColor(color);
    this->addChild(label3, 1);
    label3->setVisible(true);

    auto label4 = Label::createWithTTF("语法丛林2", "fonts/XPZ.TTF", 24);
    label4->setPosition(Vec2(origin.x+visibleSize.width / 7,
                             origin.y+visibleSize.height - 145));
    label4->setName("label4");
    label4->setColor(color);
    this->addChild(label4, 1);
    label4->setVisible(true);

    auto label5 = Label::createWithTTF("语法丛林3", "fonts/XPZ.TTF", 24);
    label5->setPosition(Vec2(origin.x+visibleSize.width / 7,
                             origin.y+visibleSize.height - 185));
    label5->setName("label5");
    label5->setColor(color);
    this->addChild(label5, 1);
    label5->setVisible(true);

    auto label6 = Label::createWithTTF("语法丛林4", "fonts/XPZ.TTF", 24);
    label6->setPosition(Vec2(origin.x+visibleSize.width / 7,
                             origin.y+visibleSize.height - 225));
    label6->setName("label6");
    label6->setColor(color);
    this->addChild(label6, 1);
    label6->setVisible(true);

    //添加二维码
    auto video1=Sprite::create("video/video1.png");
    video1->setPosition(Vec2(origin.x+visibleSize.width *2/ 3,
                             origin.y+visibleSize.height/2));
    video1->setName("video1");
    video1->setScale(2.5);
    video1->setVisible(false);
    this->addChild(video1,1);

    auto video2=Sprite::create("video/video2.png");
    video2->setPosition(Vec2(origin.x+visibleSize.width *2/ 3,
                             origin.y+visibleSize.height/2));
    video2->setName("video2");
    video2->setScale(2.5);
    video2->setVisible(false);
    this->addChild(video2,1);

    auto video3=Sprite::create("video/video3.png");
    video3->setPosition(Vec2(origin.x+visibleSize.width *2/ 3,
                             origin.y+visibleSize.height/2));
    video3->setName("video3");
    video3->setScale(2.5);
    video3->setVisible(false);
    this->addChild(video3,1);

    auto video4=Sprite::create("video/video4.png");
    video4->setPosition(Vec2(origin.x+visibleSize.width *2/ 3,
                             origin.y+visibleSize.height/2));
    video4->setName("video4");
    video4->setScale(2.5);
    video4->setVisible(false);

    this->addChild(video4,1);

    auto video5=Sprite::create("video/video5.png");
    video5->setPosition(Vec2(origin.x+visibleSize.width *2/ 3,
                             origin.y+visibleSize.height/2));
    video5->setName("video5");
    video5->setVisible(false);
    video5->setScale(2.5);
    this->addChild(video5,1);

    auto video6=Sprite::create("video/video6.png");
    video6->setPosition(Vec2(origin.x+visibleSize.width *2/ 3,
                             origin.y+visibleSize.height/2));
    video6->setName("video6");
    video6->setVisible(false);
    video6->setScale(2.5);
    this->addChild(video6,1);
    //-----------------
    //添加每关直达
    auto round1Item = MenuItemImage::create("round1.png", "round1.png",
                                            CC_CALLBACK_1(PlayVideoScene::roundoneToCallback, this));
    round1Item->setScale(0.65);
    auto round1 = Menu::create(round1Item, NULL);
    round1->setPosition(Vec2(origin.x+visibleSize.width *3/7,
                             origin.y+visibleSize.height - 25)); //用不用vec2
    this->addChild(round1, 3);
    round1->setName("round1");
    round1->setVisible(false);
    round1->setEnabled(false);

    auto round2Item = MenuItemImage::create("round2.png", "round2.png",
                                            CC_CALLBACK_1(PlayVideoScene::roundtwoToCallback, this));
    round2Item->setScale(0.65);
    auto round2 = Menu::create(round2Item, NULL);
    round2->setPosition(Vec2(origin.x+visibleSize.width *3/7,
                             origin.y+visibleSize.height - 65)); //用不用vec2
    this->addChild(round2, 3);
    round2->setName("round2");
    round2->setVisible(false);
    round2->setEnabled(false);

    auto round3Item = MenuItemImage::create("round3.png", "round3.png",
                                            CC_CALLBACK_1(PlayVideoScene::roundthreeToCallback, this));
    round3Item->setScale(0.65);
    auto round3 = Menu::create(round3Item, NULL);
    round3->setPosition(Vec2(origin.x+visibleSize.width *3/7,
                             origin.y+visibleSize.height - 105)); //用不用vec2
    this->addChild(round3, 3);
    round3->setName("round3");
    round3->setVisible(false);
    round3->setEnabled(false);

    auto round4Item = MenuItemImage::create("round4.png", "round4.png",
                                            CC_CALLBACK_1(PlayVideoScene::roundfourToCallback, this));
    round4Item->setScale(0.65);
    auto round4 = Menu::create(round4Item, NULL);
    round4->setPosition(Vec2(origin.x+visibleSize.width *3/7,
                             origin.y+visibleSize.height - 145)); //用不用vec2
    this->addChild(round4, 3);
    round4->setName("round4");
    round4->setVisible(false);
    round4->setEnabled(false);

    auto round5Item = MenuItemImage::create("round5.png", "round5.png",
                                            CC_CALLBACK_1(PlayVideoScene::roundfiveToCallback, this));
    round5Item->setScale(0.65);
    auto round5 = Menu::create(round5Item, NULL);
    round5->setPosition(Vec2(origin.x+visibleSize.width *3/7,
                             origin.y+visibleSize.height - 185)); //用不用vec2
    this->addChild(round5, 3);
    round5->setName("round5");
    round5->setVisible(false);
    round5->setEnabled(false);

    auto round6Item = MenuItemImage::create("round6.png", "round6.png",
                                            CC_CALLBACK_1(PlayVideoScene::roundsixToCallback, this));
    round6Item->setScale(0.65);
    auto round6 = Menu::create(round6Item, NULL);
    round6->setPosition(Vec2(origin.x+visibleSize.width *3/7,
                             origin.y+visibleSize.height - 225)); //用不用vec2
    this->addChild(round6, 3);
    round6->setName("round6");
    round6->setVisible(false);
    round6->setEnabled(false);


    //设置监听事件
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(PlayVideoScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}

bool PlayVideoScene::onTouchBegan(Touch *touch, Event *event) {

    auto label1=(Label*)this->getChildByName("label1");
    auto label2=(Label*)this->getChildByName("label2");
    auto label3=(Label*)this->getChildByName("label3");
    auto label4=(Label*)this->getChildByName("label4");
    auto label5=(Label*)this->getChildByName("label5");
    auto label6=(Label*)this->getChildByName("label6");
    auto video1=this->getChildByName("video1");
    auto video2=this->getChildByName("video2");
    auto video3=this->getChildByName("video3");
    auto video4=this->getChildByName("video4");
    auto video5=this->getChildByName("video5");
    auto video6=this->getChildByName("video6");
    auto round1=(Menu*)this->getChildByName("round1");
    auto round2=(Menu*)this->getChildByName("round2");
    auto round3=(Menu*)this->getChildByName("round3");
    auto round4=(Menu*)this->getChildByName("round4");
    auto round5=(Menu*)this->getChildByName("round5");
    auto round6=(Menu*)this->getChildByName("round6");

    auto pos= Director::getInstance()->convertToGL(touch->getLocationInView());

    if(label1->getBoundingBox().containsPoint(pos)||label2->getBoundingBox().containsPoint(pos)
    ||label3->getBoundingBox().containsPoint(pos)||label4->getBoundingBox().containsPoint(pos)
    ||label5->getBoundingBox().containsPoint(pos)||label6->getBoundingBox().containsPoint(pos))
    {
        video1->setVisible(false);
        video2->setVisible(false);
        video3->setVisible(false);
        video4->setVisible(false);
        video5->setVisible(false);
        video6->setVisible(false);
        round1->setVisible(false);
        round2->setVisible(false);
        round3->setVisible(false);
        round4->setVisible(false);
        round5->setVisible(false);
        round6->setVisible(false);
        round1->setEnabled(false);
        round2->setEnabled(false);
        round3->setEnabled(false);
        round4->setEnabled(false);
        round5->setEnabled(false);
        round6->setEnabled(false);

        if(label1->getBoundingBox().containsPoint(pos)){
            video1->setVisible(true);
            round1->setVisible(true);
            round1->setEnabled(true);
        }
        if(label2->getBoundingBox().containsPoint(pos)){
            video2->setVisible(true);
            round2->setVisible(true);
            round2->setEnabled(true);
        }
        if(label3->getBoundingBox().containsPoint(pos)){
            video3->setVisible(true);
            round3->setVisible(true);
            round3->setEnabled(true);
        }
        if(label4->getBoundingBox().containsPoint(pos)){
            video4->setVisible(true);
            round4->setVisible(true);
            round4->setEnabled(true);
        }
        if(label5->getBoundingBox().containsPoint(pos)){
            video5->setVisible(true);
            round5->setVisible(true);
            round5->setEnabled(true);
        }
        if(label6->getBoundingBox().containsPoint(pos)){
            video6->setVisible(true);
            round6->setVisible(true);
            round6->setEnabled(true);
        }

    }
    return true;
}
//退出按钮回调函数
void PlayVideoScene::backToCallback(Ref *pSender) {
    auto HelloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HelloWorldScene);
}

//每关按钮回调函数
void PlayVideoScene::roundoneToCallback(Ref *pSender) {
    auto variableScene = variableScene::createScene();
    Director::getInstance()->replaceScene(variableScene);
}
//每关按钮回调函数
void PlayVideoScene::roundtwoToCallback(Ref *pSender) {
    auto variableScene2 = variableScene2::createScene();
    Director::getInstance()->replaceScene(variableScene2);
}
//每关按钮回调函数
void PlayVideoScene::roundthreeToCallback(Ref *pSender) {
    auto grammarScene = grammarScene::createScene();
    Director::getInstance()->replaceScene(grammarScene);
}
//每关按钮回调函数
void PlayVideoScene::roundfourToCallback(Ref *pSender) {
    auto grammarScene2 = grammarScene2::createScene();
    Director::getInstance()->replaceScene(grammarScene2);
}
//每关按钮回调函数
void PlayVideoScene::roundfiveToCallback(Ref *pSender) {
    auto grammarScene3 = grammarScene3::createScene();
    Director::getInstance()->replaceScene(grammarScene3);
}
//每关按钮回调函数
void PlayVideoScene::roundsixToCallback(Ref *pSender) {
    auto grammarScene4 = grammarScene4::createScene();
    Director::getInstance()->replaceScene(grammarScene4);
}

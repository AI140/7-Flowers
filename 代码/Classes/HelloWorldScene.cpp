
#include "HelloWorldScene.h"
#include "variableScene.h"
#include "variableScene2.h"
#include "grammarScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/backgroundBgm.mp3", true);
    /////////////////////////////


    //背景图片
    auto ground1 = Sprite::create("background1.png");
    if (ground1 == nullptr) {
        problemLoading("'background1.png'");
    } else {
        // position the sprite on the center of the screen
        ground1->setPosition(
                Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        ground1->setScale(1.12);
        // add the sprite as a child to this layer
        this->addChild(ground1, -3);
    }

    //音量按钮
    auto soundItem = MenuItemImage::create("sound.png", "sound.png",
                                          CC_CALLBACK_1(HelloWorld::soundCallback, this));
    soundItem->setScale(0.8);
    auto sound = Menu::create(soundItem, NULL);
    sound->setPosition(Vec2(origin.x+visibleSize.width*0+25,origin.y+visibleSize.height-30));
    this->addChild(sound,6);

    //变量矿区
    auto island1 = Sprite::create("HelloWorld_1.png");
    island1->setScale(0.6);
    if (island1 == nullptr) {
        problemLoading("'HelloWorld_1.png'");
    } else {
        // position the sprite on the center of the screen
        island1->setPosition(
                Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 12*5 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(island1, 1);
    }
    //变量矿区按钮
    auto beginItem1 = MenuItemImage::create("startNormal.png", "startSelected.png",
                                            CC_CALLBACK_1(HelloWorld::beginGame1Callback, this));
    beginItem1->setScale(0.8);
    auto menu1 = Menu::create(beginItem1, NULL);
    menu1->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 7 + origin.y));
    this->addChild(menu1, 2);

    //二维码界面按钮
    auto videoItem = MenuItemImage::create("play.png", "play.png",
                                           CC_CALLBACK_1(HelloWorld::videoToCallback, this));
    videoItem->setScale(0.65);
    auto video = Menu::create(videoItem, NULL);
    video->setPosition(Vec2(origin.x+visibleSize.width-25,origin.y+visibleSize.height-20));
    this->addChild(video,5);


    //语法丛林
    auto island2 = Sprite::create("HelloWorld_2.png");
    island2->setScale(0.6);
    if (island2 == nullptr) {
        problemLoading("'HelloWorld_2.png'");
    } else {
        // position the sprite on the center of the screen
        island2->setPosition(
                Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 12*5 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(island2, 3);
    }
    //语法丛林按钮
    auto beginItem2 = MenuItemImage ::create("startNormal.png","startSelected.png",
                                        CC_CALLBACK_1(HelloWorld::beginGame2Callback,this));
    beginItem2->setScale(0.8);
    auto menu2 = Menu::create(beginItem2,NULL);
    menu2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/7 + origin.y));
    this->addChild(menu2,4);

    //雪雾冰山
    auto island3 = Sprite::create("HelloWorld_3.png");
    island3->setScale(0.6);
    if (island3 == nullptr) {
        problemLoading("'HelloWorld_3.png'");
    } else {
        // position the sprite on the center of the screen
        island3->setPosition(
                Vec2(visibleSize.width * 4 / 5 + origin.x, visibleSize.height / 12*5 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(island3, 3);
    }
    //雪雾冰山按钮
    auto beginItem3 = MenuItemImage ::create("startNormal.png","startSelected.png",
                                        CC_CALLBACK_1(HelloWorld::beginGame3Callback,this));
    beginItem3->setScale(0.8);
    auto menu3 = Menu::create(beginItem3,NULL);
    menu3->setPosition(Vec2(visibleSize.width*4/5 + origin.x, visibleSize.height/7 + origin.y));
    this->addChild(menu3,4);

   return true;

}

//变量矿区回调函数
    void HelloWorld::beginGame1Callback(Ref *pSender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);
        auto variableScene = variableScene::createScene();
        Director::getInstance()->replaceScene(variableScene);
    }

//语法丛林回调函数
void HelloWorld::beginGame2Callback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);
    auto grammarScene = grammarScene::createScene();
    Director::getInstance()->replaceScene(grammarScene);
}

//雪雾冰山回调函数
void HelloWorld::beginGame3Callback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);
    auto snowScene = snowScene::createScene();
    Director::getInstance()->replaceScene(snowScene);
}

//二维码按钮回调函数
void HelloWorld::videoToCallback(Ref *pSender) {
    auto PlayVideoScene = PlayVideoScene::createScene();
    Director::getInstance()->replaceScene(PlayVideoScene);
}

//音量按钮回调函数
void HelloWorld::soundCallback(Ref *pSender) {
    if(!sound){
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        sound = true;
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        sound = false;
    }
}
//
// Created on 2020/11/27.
//

#include "snowScene.h"
USING_NS_CC;

Scene* snowScene::createScene()
{
    return snowScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in snowScene.cpp\n");
}

// on "init" you need to initialize your instance
bool snowScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//退出按钮

    //退出按钮
    auto backItem = MenuItemImage::create("back.png", "back.png",
                                          CC_CALLBACK_1(snowScene::backToCallback, this));
    backItem->setScale(2.5);
    auto back = Menu::create(backItem, NULL);
    back->setPosition(Vec2(origin.x+visibleSize.width*0+25,origin.y+visibleSize.height-20)); //用不用vec2
    this->addChild(back, 6);


    //设置背景图片
    auto levelBackGround = Sprite::create("snowBackground.png");
    levelBackGround->setPosition(Vec2(origin.x+visibleSize.width / 2, origin.y+visibleSize.height / 2));
    levelBackGround->setScale(1.12);
    this->addChild(levelBackGround, 0);



    return true;
}
//返回按钮回调函数
void snowScene::backToCallback(Ref *pSender) {
    auto HelloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HelloWorldScene);
    //两个类互相调用 要把主页面里的B变成指针
}



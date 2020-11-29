
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "variableScene.h"
#include "snowScene.h"
#include "grammarScene.h"

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
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /////////////////////////////

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 3);
    }


    //背景图片
    auto ground1 = Sprite::create("background1.jpg");
    if (ground1 == nullptr)
    {
        problemLoading("'background1.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        ground1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
         ground1->setScale(visibleSize.width,visibleSize.height);
        // add the sprite as a child to this layer
        this->addChild(ground1, -3);
    }

    //变量矿区
    auto island1 = Sprite::create("HelloWorld.png");
    if (island1 == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        island1->setPosition(Vec2(visibleSize.width/5 + origin.x, visibleSize.height/2 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(island1, 1);
    }
    //变量矿区按钮
    auto beginItem1 = MenuItemImage::create("beginNormal.png","beginSelected.png",
            CC_CALLBACK_1(HelloWorld::beginGame1Callback,this));
    auto menu1 = Menu::create(beginItem1,NULL);
    menu1->setPosition(Vec2(visibleSize.width/5 + origin.x, visibleSize.height/4 + origin.y));
    this->addChild(menu1,2);


    //语法丛林
    auto island2 = Sprite::create("HelloWorld.png");
    if (island2 == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        island2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(island2, 3);
    }
    //语法丛林按钮
    auto beginItem2 = MenuItemImage ::create("beginNormal.png","beginSelected.png",
                                        CC_CALLBACK_1(HelloWorld::beginGame2Callback,this));
    auto menu2 = Menu::create(beginItem2,NULL);
    menu2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/4 + origin.y));
    this->addChild(menu2,2);

    //雪雾冰山
    auto island3 = Sprite::create("HelloWorld.png");
    if (island3 == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        island3->setPosition(Vec2(visibleSize.width*4/5 + origin.x, visibleSize.height/2 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(island3, 3);
    }
    //雪雾冰山按钮
    auto beginItem3 = MenuItemImage ::create("beginNormal.png","beginSelected.png",
                                        CC_CALLBACK_1(HelloWorld::beginGame3Callback,this));
    auto menu3 = Menu::create(beginItem3,NULL);
    menu3->setPosition(Vec2(visibleSize.width*4/5 + origin.x, visibleSize.height/4 + origin.y));
    this->addChild(menu3,2);

    return true;
}


//变量矿区回调函数
void HelloWorld::beginGame1Callback(Ref* pSender)
{
    auto variableScene = variableScene::createScene();
    Director::getInstance()->replaceScene(variableScene);
}

//语法丛林回调函数
void HelloWorld::beginGame2Callback(Ref* pSender)
{
    auto grammarScene = grammarScene::create();
    Director::getInstance()->replaceScene(grammarScene);
}

//雪雾冰山回调函数
void HelloWorld::beginGame3Callback(Ref* pSender)
{
    auto snowScene = snowScene::create();
    Director::getInstance()->replaceScene(snowScene);
}


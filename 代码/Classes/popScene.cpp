#include <SimpleAudioEngine.h>
#include "popScene.h"

int sceneName = 0;

Scene* PopScene::scene()
{
    Scene* scene = NULL;
    do
    {
        scene = Scene::create();
        PopScene* layer = PopScene::create();
        scene->addChild(layer);
    }while(0);

    return scene;
}

bool PopScene::init()
{
    bool flag=false;

    Size winSize = Director::getInstance()->getWinSize();
    Sprite* background = Sprite::create("对话.png");
    background->setPosition(Vec2(winSize.width/2, winSize.height/2));
    background->setScale(5);
    this->addChild(background, 0);
    scene_bgSprite = background;
    scene_size = background->getContentSize();
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();

    flag=true;
    return flag;

};




//num=0 主菜单. num=1 变量矿区-1， num=2 变量矿区-2， num=3 语法丛林-1，
// num=4 语法丛林-2， num=5 语法丛林-3， num=6 语法丛林-4， num=7 雪雾深山
void PopScene::nextScene(int num){
    sceneName = num;
}

void PopScene::backScene(int num){
    backName = num;

    if(backName==0){
        //成功菜单
        MenuItemImage* item1 = MenuItemImage::create("nextNormal.png","nextSelected.png",
                                                     CC_CALLBACK_1(PopScene::nextButton, this));
        item1->setName("next");
        MenuItemImage* item2 = MenuItemImage::create("exitNormal.png","exitSelected.png",
                                                     CC_CALLBACK_1(PopScene::backButton, this));
        item2->setName("back");
        Menu* sMenu = Menu::create(item1, item2,  NULL);
        sMenu->setName("sMenu");
        this->addChild(sMenu,0);
        item1->setPosition(Vec2(origin.x - scene_size.width*1.2,  origin.y - scene_size.height*2));
        item2->setPosition(Vec2(scene_size.width + origin.x, origin.y - scene_size.height*2));
    }else{
        //失败菜单
        MenuItemImage* item3 = MenuItemImage::create("replayNormal.png","replaySelected.png",
                                                     CC_CALLBACK_1(PopScene::backButton, this));
        Menu* fMenu = Menu::create(item3, NULL);
        fMenu->setName("fMenu");
        fMenu->setName("fMenu");
        this->addChild(fMenu,0);
        item3->setPosition(Vec2(scene_size.width + origin.x, origin.y - scene_size.height*2));
    }

    this->setTitle();
    this ->setContent();
}


void PopScene::setReword(Sprite* sprite){
    reword = (Sprite*)sprite;
    reword->setPosition(Vec2(visibleSize.width/2, visibleSize.height/24*17));
    this->addChild(reword, 1);
}

bool PopScene::onTouchBegan(Touch * touch, Event * pevent)
{
    return true;
}

//点击菜单按钮的时候调用的事件处理函数
void PopScene::nextButton(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav", false);
    Scene* next = NULL;
    switch (sceneName) {
        case 1:
            next = variableScene::createScene();
            break;
        case 2:
            next = variableScene2::createScene();
            break;
        case 3:
            next = grammarScene::createScene();
           break;
        case 4:
             next = grammarScene2::createScene();
             break;
        case 5:
            next = grammarScene3::createScene();
            break;
        case 6:
            next = grammarScene4::createScene();
            break;
//        case 7:
//            //next = snowScene::createScene();
//            break;
    }
    Director::getInstance()->replaceScene(next);
}

void PopScene::backButton(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav", false);
    Scene* back = NULL;

    switch (backName) {
        case 0:
            back = HelloWorld::createScene();
            break;
        case 1:
            back = variableScene::createScene();
            break;
        case 2:
            back = variableScene2::createScene();
            break;
        case 3:
            back = grammarScene::createScene();
            break;
        case 4:
            back = grammarScene2::createScene();
            break;
        case 5:
            back = grammarScene3::createScene();
            break;
        case 6:
            back = grammarScene4::createScene();
            break;
//        case 7:
//            //back = snowScene::createScene();
//            break;
    }

    Director::getInstance()->replaceScene(back);
}


//设置题目
void PopScene::setTitle()
{
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> str = "";
    if(backName==0){
        str = "Congratulations";
    }else{
        str = "Failure";
    }
    auto title = Label::createWithTTF(str,"fonts/Marker Felt.ttf", 25);
    title->setPosition(Vec2( visibleSize.width/2 ,  visibleSize.height/8 * 7));
    this->addChild(title, 1);
}

//设置层的内容
void PopScene::setContent()
{
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> text = "";
    if(backName==0){
        text = "通关成功！收下奖品吧！";
    }else{
        text = "通关失败，再来一次吧！";
    }
    auto content = Label::createWithTTF(text, "fonts/XPZ.TTF",25);
    content->setPosition(Vec2( visibleSize.width/2,  visibleSize.height/2));
    this->addChild(content, 1);

}

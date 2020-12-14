//
// Created by 蔡艳菲 on 2020/12/12.
//
#include "HelloWorldScene.h"
#include "grammarScene4.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "cocos-ext.h"
#include "popScene.h"
#include "IfPopScene.h"
#include "FuncPopScene.h"
#include "ForPopScene.h"


using namespace cocos2d::extension;
using namespace cocos2d;

USING_NS_CC;

Scene* grammarScene4::createScene()
{
    return grammarScene4::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool grammarScene4::init() {
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
    listener->onTouchBegan = CC_CALLBACK_2(grammarScene4::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // TMXTiledMap::create()
    // 加载TMX瓦片地图
    TMXTiledMap* tileMap = TMXTiledMap::create("winter.tmx");
    tileMap->setPosition(0,20);
    tileMap->setScale(2.8,2.3);
    tileMap->setTag(2);
    this->addChild(tileMap,-2);


    auto background = Sprite::create("winter.png");
    background->setAnchorPoint(Vec2(0,0));
    background->setPosition(Vec2(0,20));
    background->setScale(3,2.5);
    this->addChild(background,-1);



    //设置上、左、右转向按钮
    auto forwardTurn = MenuItemImage ::create("forward.png","forward.png",CC_CALLBACK_1(grammarScene4::forwardTurnCallback,this));
    forwardTurn->setPosition(Vec2(visibleSize.width*3/4+20,visibleSize.height));

    auto leftTurn = MenuItemImage ::create("left.png","left.png",CC_CALLBACK_1(grammarScene4::leftTurnCallback,this));
    leftTurn->setPosition(Vec2(visibleSize.width*3/4+70,visibleSize.height));
    auto rightTurn = MenuItemImage ::create("right.png","right.png",CC_CALLBACK_1(grammarScene4::rightTurnCallback,this));
    rightTurn->setPosition(Vec2(visibleSize.width*3/4+120,visibleSize.height));

    auto ifButton= MenuItemImage::create("if.png","if.png",CC_CALLBACK_1(grammarScene4::ifButtonCallback,this));
    ifButton->setPosition(Vec2(visibleSize.width*3/4+118,visibleSize.height-50));//20
    ifButton->setScale(1.8);


//设置for按钮
    auto forButton= MenuItemImage::create("for.png","for.png",CC_CALLBACK_1(grammarScene4::forButtonCallback,this));
    forButton->setPosition(Vec2(visibleSize.width*3/4+123,visibleSize.height-150));//visibleSize.height-40   78
    forButton->setScale(1.4);



//设置函数按钮
    auto functionButton= MenuItemImage::create("function.png","function.png",CC_CALLBACK_1(grammarScene4::functionButtonCallback,this));
    functionButton->setPosition(Vec2(visibleSize.width*3/4+113,visibleSize.height-256));

//functionButton->setPosition(Vec2(visibleSize.width*3/4+20,40));
    functionButton->setScale(1.37);



    auto menu3 = Menu::create(forwardTurn,leftTurn,rightTurn,ifButton,forButton,functionButton,NULL);
    menu3->setPosition(40,40);
    menu3->setScale(0.7);

    this->addChild(menu3,1);

    /*
    //获得对象层中的坐标,存在向量里
    TMXObjectGroup* objectGroup = tileMap->getObjectGroup("person");
    ValueVector object = objectGroup->getObjects();

    ValueVector::iterator it = object.begin();
    ValueMap m = it->asValueMap();
    auto person = Sprite::create("person_down.jpg");
    person->setPosition(m.at("x").asFloat(),m.at("y").asFloat());
    person->setTag(1);
    person->setScale(2.5);
    this->addChild(person,1);
    */


    auto person = Sprite::create("person_down.png");
    person->setPosition(visibleSize.width/2+60,60);
    person->setTag(1);
    person->setScale(0.3);
    this->addChild(person,3);


    //添加代码输出区
    auto code_text = Label::createWithSystemFont("","Arial",14);
    code_text->setPosition(visibleSize.width*3/4,visibleSize.height-50);
    code_text->setName("code_text");
    code_text->setAnchorPoint(Vec2(0,1));
    this->addChild(code_text,1);

    //添加奖励
    auto reward = Sprite::create("reward4.png");
    reward->setPosition(Vec2(visibleSize.width/3-60,visibleSize.height));
    reward->setScale(0.3);
    reward->setName("reward4");
    this->addChild(reward,2);

    /*
    //添加怪物攻击主角
    auto monster = Sprite::create("HelloWorld.png");
    monster->setScale(0.6);
    monster->setName("monster");
    monster->setVisible(false);

    this->addChild(monster);
     */

    //添加障碍
    auto barrier = Sprite::create("barrier.png");
    barrier->setVisible(true);
    barrier->setPosition(Vec2(visibleSize.width/3-10,visibleSize.height/2+20));
    barrier->setName("barrier");
    barrier->setScale(3);
    this->addChild(barrier,2);

    //退出按钮
    auto backItem = MenuItemImage::create("back.png", "back.png",
                                          CC_CALLBACK_1(grammarScene4::backToCallback, this));
    backItem->setScale(3);
    auto back = Menu::create(backItem, NULL);
    back->setPosition(Vec2(40,visibleSize.height)); //用不用vec2

    this->addChild(back, 1);


    /*
    //创建滚动视图层显示
    Size  scrollSize= CCSizeMake(150, 220);       //容器大小

    //创建容器、设置大小
    LayerColor* scrollLayer = CCLayerColor::create( ccc4(80,0,0,255) );
    scrollLayer->setContentSize(scrollSize);
    scrollLayer->setName("scrollLayer");
    scrollLayer->setPosition(code_text->getPosition()-Vec2(10,200));
    scrollLayer->addChild(code_text,1);


    this->addChild(scrollLayer,-2);
     */

    //设置code_text背景图片
    auto codeBackground = Sprite::create("code_background.png");
    codeBackground->setName("codeBackground");
    codeBackground->setScale(2.6,2.4);
    codeBackground->setPosition(Vec2(visibleSize.width*4/5+25,visibleSize.height*3/4-45));
    this->addChild(codeBackground,0);

    //定时器更新 每一秒刷新一次 更新倒计时
    this->schedule(schedule_selector(grammarScene4::update), 1.0f );

    //添加故事区
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
    auto story_text = Label::createWithTTF("\t\t“天呐……已经下雪了吗？”\n这一路上学到的很多高级技能，我也要经常用起来啊！","fonts/STKAITI.TTF", 15);
    story_text->setPosition(14,visibleSize.height*0+112);
    story_text->setName("story_text");
    story_text->setAnchorPoint(Vec2(0,1));
    this->addChild(story_text,4);

    //故事背景区
    auto story_background = Sprite::create("storyback.png");
    story_background->setPosition(Vec2(visibleSize.width/2-8,visibleSize.height/5+20));
    story_background->setScale(5,2.2);
    story_background->setName("story_background");
    this->addChild(story_background,3);

    auto story_chuan = Sprite::create("storyback1.png");
    story_chuan->setPosition(Vec2(visibleSize.width-20,visibleSize.height/5-4));
    story_chuan->setScale(0.5);
    story_chuan->setName("chuan");
    this->addChild(story_chuan,4);


    return true;
}

bool grammarScene4::onTouchBegan(Touch *touch, Event *unused_event) {
    Label* story_text=(Label *)this->getChildByName("story_text");

    if(touchTime==1){
        story_text->setVisible(false);

        Sprite* story_background=(Sprite *)this->getChildByName("story_background");
        story_background->setVisible(false);

        Sprite* story_chuan=(Sprite *)this->getChildByName("chuan");
        story_chuan->setVisible(false);

        ++touchTime;
        return true;
    }

    return true;
}

void grammarScene4::backToCallback(Ref *pSender) {
    auto HelloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HelloWorldScene);
    //两个类互相调用 要把主页面里的B变成指针
}

void grammarScene4::functionButtonCallback(Ref* pSender){
    FuncPopScene* FuncpopLayer = FuncPopScene::create();

    this->addChild(FuncpopLayer,5);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    for(int i=0;i<5;++i){
       //std::strcat(code_text, FuncpopLayer->content_str[i]);
    }

    if(FuncpopLayer->change==0){
        code_text=code_text+"f()\n";
        showCode();
    }

}


void grammarScene4::forButtonCallback(Ref* pSender){
    ForPopScene* ForpopLayer = ForPopScene::create();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    this->addChild(ForpopLayer,5);
}

void grammarScene4::ifButtonCallback(Ref* pSender){
    IfPopScene* IfpopLayer = IfPopScene::create();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    this->addChild(IfpopLayer,5);
}


void grammarScene4::forwardTurnCallback(Ref* pSender){
    Sprite* person=(Sprite *)this->getChildByTag(1);
    Sprite* reward4=(Sprite *)this->getChildByName("reward4");

    TMXTiledMap* tileMap=(TMXTiledMap *) this->getChildByTag(2);
    auto tileSize=tileMap->getTileSize();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    if(step==9){

        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/victory.ogg", false);

        //获得奖励 出现弹窗
        PopScene* popLayer = PopScene::create();
        popLayer->nextScene(7);
        popLayer->backScene(0);
        popLayer->setReword(reward4);
        popLayer->setName("popLayer");

        this->addChild(popLayer,5);
    }


    //如果是往上走的前进状态
    if(up==1){
        if((step>=1&&step<=2)||(step>=8&&step<=9)){

            code_text=code_text+"forward()\n";
            showCode();

            auto forward=MoveBy::create(1,Vec2(0,tileSize.height*1.4/2));

            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("person_up.png");
            person->setTexture(texture);

            person->runAction(forward);

            /*
            //出现怪兽
            if(step==2||step==8){
                Sprite* monster=(Sprite*) this->getChildByName("monster");
                monster->setVisible(true);
                monster->setPosition(Vec2(0,300));
                auto Move= MoveTo::create(0.5,person->getPosition());
                monster->runAction(Move);

                //主角换失血图片 再换回来
            }
            */

            ++step;


        }else{
            return;
        }

    }
    //如果是往右走的前进状态
    if(right==1){
        if(step>11){
            code_text=code_text+"forward()\n";
            showCode();

            auto forward=MoveBy::create(1,Vec2(tileSize.width/2,0));

            person->runAction(forward);
            ++step;
        }
        else{
            return;
        }

    }
    //如果是往下走的前进状态
    if(down==1){
        if(step>11){
            code_text=code_text+"forward()\n";
            showCode();

            auto forward=MoveBy::create(1,Vec2(0,-tileSize.width/2));

            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("person_down.png");
            person->setTexture(texture);

            person->runAction(forward);

            ++step;
        }

    }
    //如果是往左走的前进状态
    if(left==1){
        if(step>=3&&step<=7){
            code_text=code_text+"forward()\n";
            showCode();

            auto forward=MoveBy::create(1,Vec2(-tileSize.width*1.25/2,0));

            person->runAction(forward);
            ++step;
        }
        if(step==7&&(time%3==1||time%3==2)){//遇到炸弹
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/wrong.wav", false);
            PopScene* popLayer = PopScene::create();
            popLayer->backScene(6);
            //popLayer->setReword();

            this->addChild(popLayer,4);
        }

    }


}

void grammarScene4::leftTurnCallback(Ref* pSender){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    code_text=code_text+"left()\n";
    showCode();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    if(left==1){
        //本来就是左朝向 再左转就朝下
        up=0;
        down=1;
        right=0;
        left=0;
        CCTexture2D* texture1 = CCTextureCache::sharedTextureCache()->addImage("person_down.png");
        person->setTexture(texture1);

        return;
    }
    if(down==1){
        //本来是下朝向 在左转就朝右
        up=0;
        down=0;
        right=1;
        left=0;
        CCTexture2D* texture2 = CCTextureCache::sharedTextureCache()->addImage("person_right.png");
        person->setTexture(texture2);

        return;
    }
    if(right==1){
        //本来是右朝向 再左转就朝上
        up=1;
        down=0;
        right=0;
        left=0;
        CCTexture2D* texture3 = CCTextureCache::sharedTextureCache()->addImage("person_up.png");
        person->setTexture(texture3);

        return;
    }
    if(up==1){
        //本来是上朝向 再左转就朝左
        up=0;
        down=0;
        right=0;
        left=1;
        CCTexture2D* texture4 = CCTextureCache::sharedTextureCache()->addImage("person_left.png");
        person->setTexture(texture4);

        return;
    }
}

void grammarScene4::forwardTurn(){
    Sprite* person=(Sprite *)this->getChildByTag(1);
    Sprite* reward4=(Sprite *)this->getChildByName("reward4");

    TMXTiledMap* tileMap=(TMXTiledMap *) this->getChildByTag(2);
    auto tileSize=tileMap->getTileSize();

    if(step==9){
        //获得奖励 出现弹窗
        PopScene* popLayer = PopScene::create();
        popLayer->nextScene(7);
        popLayer->backScene(0);
        popLayer->setReword(reward4);
        popLayer->setName("popLayer");

        this->addChild(popLayer,5);
    }


    //如果是往上走的前进状态
    if(up==1){
        if((step>=1&&step<=2)||(step>=8&&step<=9)){

            auto forward=MoveBy::create(1,Vec2(0,tileSize.height*1.4/2));

            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("person_up.png");
            person->setTexture(texture);

            person->runAction(forward);

            ++step;


        }else{
            return;
        }

    }
    //如果是往右走的前进状态
    if(right==1){
        if(step>11){

            auto forward=MoveBy::create(1,Vec2(tileSize.width/2,0));

            person->runAction(forward);
            ++step;
        }
        else{
            return;
        }

    }
    //如果是往下走的前进状态
    if(down==1){
        if(step>11){

            auto forward=MoveBy::create(1,Vec2(0,-tileSize.width/2));

            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("person_down.png");
            person->setTexture(texture);

            person->runAction(forward);

            ++step;
        }

    }
    //如果是往左走的前进状态
    if(left==1){
        if(step>=3&&step<=7){

            showCode();

            auto forward=MoveBy::create(1,Vec2(-tileSize.width*1.25/2,0));

            person->runAction(forward);
            ++step;
        }
        if(step==7&&(time%3==1||time%3==2)){//遇到炸弹
            PopScene* popLayer = PopScene::create();
            popLayer->nextScene(2);
            popLayer->backScene(1);
            //popLayer->setReword();

            this->addChild(popLayer,4);
        }

    }


}

void grammarScene4::leftTurn(){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    if(left==1){
        //本来就是左朝向 再左转就朝下
        up=0;
        down=1;
        right=0;
        left=0;
        CCTexture2D* texture1 = CCTextureCache::sharedTextureCache()->addImage("person_down.png");
        person->setTexture(texture1);

        return;
    }
    if(down==1){
        //本来是下朝向 在左转就朝右
        up=0;
        down=0;
        right=1;
        left=0;
        CCTexture2D* texture2 = CCTextureCache::sharedTextureCache()->addImage("person_right.png");
        person->setTexture(texture2);

        return;
    }
    if(right==1){
        //本来是右朝向 再左转就朝上
        up=1;
        down=0;
        right=0;
        left=0;
        CCTexture2D* texture3 = CCTextureCache::sharedTextureCache()->addImage("person_up.png");
        person->setTexture(texture3);

        return;
    }
    if(up==1){
        //本来是上朝向 再左转就朝左
        up=0;
        down=0;
        right=0;
        left=1;
        CCTexture2D* texture4 = CCTextureCache::sharedTextureCache()->addImage("person_left.png");
        person->setTexture(texture4);

        return;
    }
}

void grammarScene4::rightTurn(){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    if(left==1){
        //本来是左朝向 再右转就朝上
        up=1;
        down=0;
        right=0;
        left=0;
        CCTexture2D* texture1 = CCTextureCache::sharedTextureCache()->addImage("person_up.png");
        person->setTexture(texture1);

        return;
    }
    if(down==1){
        //本来是下朝向 在右转就朝左
        up=0;
        down=0;
        right=0;
        left=1;
        CCTexture2D* texture2 = CCTextureCache::sharedTextureCache()->addImage("person_left.png");
        person->setTexture(texture2);

        return;
    }
    if(right==1){
        //本来是右朝向 再右转就朝下
        up=0;
        down=1;
        right=0;
        left=0;
        CCTexture2D* texture3 = CCTextureCache::sharedTextureCache()->addImage("person_down.png");
        person->setTexture(texture3);

        return;
    }
    if(up==1){
        //本来是上朝向 再右转就朝右
        up=0;
        down=0;
        right=1;
        left=0;
        CCTexture2D* texture4 = CCTextureCache::sharedTextureCache()->addImage("person_right.png");
        person->setTexture(texture4);

        return;
    }


}

void grammarScene4::rightTurnCallback(Ref* pSender){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    code_text=code_text+"right()\n";
    showCode();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    if(left==1){
        //本来是左朝向 再右转就朝上
        up=1;
        down=0;
        right=0;
        left=0;
        CCTexture2D* texture1 = CCTextureCache::sharedTextureCache()->addImage("person_up.png");
        person->setTexture(texture1);

        return;
    }
    if(down==1){
        //本来是下朝向 在右转就朝左
        up=0;
        down=0;
        right=0;
        left=1;
        CCTexture2D* texture2 = CCTextureCache::sharedTextureCache()->addImage("person_left.png");
        person->setTexture(texture2);

        return;
    }
    if(right==1){
        //本来是右朝向 再右转就朝下
        up=0;
        down=1;
        right=0;
        left=0;
        CCTexture2D* texture3 = CCTextureCache::sharedTextureCache()->addImage("person_down.png");
        person->setTexture(texture3);

        return;
    }
    if(up==1){
        //本来是上朝向 再右转就朝右
        up=0;
        down=0;
        right=1;
        left=0;
        CCTexture2D* texture4 = CCTextureCache::sharedTextureCache()->addImage("person_right.png");
        person->setTexture(texture4);

        return;
    }


}

void grammarScene4::showCode(){
    Label* text=(Label*)this->getChildByName("code_text");
    text->setString(code_text);
    this->addChild(text,2);

    //Layer * scrollLayer=(Layer*) this->getChildByName("scrollLayer");
    /*
   //创建滚动视图CCScrollView
   //可视区域大小150*100 、 容器为scrollLayer
   cocos2d::ui::ScrollView* scrollView = cocos2d::ui::ScrollView::create();
   scrollView->setPosition(text->getPosition());
   scrollLayer->addChild(scrollView,0);
     */

    // this->addChild(scrollLayer);

    //设置为只能纵向滚动
    //  scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);

    // scrollView->setDelegate(reinterpret_cast<ScrollViewDelegate *>(this));

    return;
}

void grammarScene4::update(float dt){
    Sprite* barrier=(Sprite*)this->getChildByName("barrier");
    if(time%3==0){
        barrier->setVisible(false);
    }else{
        barrier->setVisible(true);
    }
    ++time;

}

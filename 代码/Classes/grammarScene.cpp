//
// Created  on 2020/11/27.
//

#include "grammarScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <cstring>
#include "cocos-ext.h"
#include "HelloWorldScene.h"
#include "popScene.h"


using namespace cocos2d::extension;
using namespace cocos2d;

USING_NS_CC;

Scene* grammarScene::createScene()
{
    return grammarScene::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool grammarScene::init() {
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
    listener->onTouchBegan = CC_CALLBACK_2(grammarScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    // TMXTiledMap::create()
    // 加载TMX瓦片地图
    TMXTiledMap* tileMap = TMXTiledMap::create("ground1.tmx");
    tileMap->setPosition(0,0);
    tileMap->setScale(2.8,2.5);
    tileMap->setTag(2);
    this->addChild(tileMap, -1);

    //设置上、左、右转向按钮
    auto forwardTurn = MenuItemImage ::create("forward.png","forward.png",CC_CALLBACK_1(grammarScene::forwardTurnCallback,this));
    forwardTurn->setPosition(Vec2(visibleSize.width*3/4+20,visibleSize.height));

   auto leftTurn = MenuItemImage ::create("left.png","left.png",CC_CALLBACK_1(grammarScene::leftTurnCallback,this));
    leftTurn->setPosition(Vec2(visibleSize.width*3/4+70,visibleSize.height));
   auto rightTurn = MenuItemImage ::create("right.png","right.png",CC_CALLBACK_1(grammarScene::rightTurnCallback,this));
    rightTurn->setPosition(Vec2(visibleSize.width*3/4+120,visibleSize.height));

    auto menu3 = Menu::create(forwardTurn,leftTurn,rightTurn,NULL);

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
    person->setPosition(visibleSize.width/2+30,55);
    person->setTag(1);
    person->setScale(0.3);
    this->addChild(person,3);


    //添加代码输出区
    auto code_text = Label::createWithSystemFont("","Arial",14);
    code_text->setPosition(visibleSize.width*3/4,visibleSize.height-20);
    code_text->setName("code_text");
    code_text->setAnchorPoint(Vec2(0,1));
    this->addChild(code_text,1);

    //添加奖励
    auto reward = Sprite::create("reward1.png");
    reward->setPosition(Vec2(visibleSize.width/2-70,visibleSize.height));
    reward->setName("reward1");
    reward->setScale(0.3);
    this->addChild(reward,2);

    /*
    //添加怪物攻击主角
    auto monster = Sprite::create("HelloWorld.png");
    monster->setScale(0.6);
    monster->setName("monster");
    monster->setVisible(false);

    this->addChild(monster);
    */



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

    //退出按钮
    auto backItem = MenuItemImage::create("back.png", "back.png",
                                          CC_CALLBACK_1(grammarScene::backToCallback, this));
    backItem->setScale(3);
    auto back = Menu::create(backItem, NULL);
    back->setPosition(Vec2(40,visibleSize.height)); //用不用vec2

    this->addChild(back, 1.8);

    //添加故事区
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
    auto story_text = Label::createWithTTF("\t\t光线突然的强烈，让小赛文有些不适应。不过很快，一片丛林\n的景象映入眼帘。\n\t\t这应该就是语法丛林了——赛文曾在宇宙图鉴上见过的。","fonts/STKAITI.TTF", 15);
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

bool grammarScene::onTouchBegan(Touch *touch, Event *unused_event) {
    Label* story_text=(Label *)this->getChildByName("story_text");
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if(touchTime==1) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        story_text->setString("\t\t“或许这里会住着一些人家，我可以向他们借一些修理飞船的\n工具。”");
        ++touchTime;

        return true;
    }
    if(touchTime==2){
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

void grammarScene::backToCallback(Ref *pSender) {
    auto HelloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HelloWorldScene);
    //两个类互相调用 要把主页面里的B变成指针
}


void grammarScene::forwardTurnCallback(Ref* pSender){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    Sprite* reward1=(Sprite *)this->getChildByName("reward1");

    TMXTiledMap* tileMap=(TMXTiledMap *) this->getChildByTag(2);
    auto tileSize=tileMap->getTileSize();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    if(step==9){
       //获得奖励 出现弹窗
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/victory.ogg", false);
        PopScene* popLayer = PopScene::create();
        popLayer->nextScene(4);
        popLayer->backScene(0);
        popLayer->setReword(reward1);

        this->addChild(popLayer,5);

    }


    //如果是往上走的前进状态
    if(up==1){
        if((step>=1&&step<=3)||(step>=7&&step<=9)){

            code_text=code_text+"forward()\n";
            showCode();

            auto forward=MoveBy::create(1,Vec2(0,tileSize.height*1.2/2));

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
            }*/


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
        if(step>=4&&step<=6){
            code_text=code_text+"forward()\n";
            showCode();

            auto forward=MoveBy::create(1,Vec2(-tileSize.width/2,0));

            person->runAction(forward);
            ++step;
        }

    }


}

void grammarScene::forwardTurn(){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    Sprite* reward1=(Sprite *)this->getChildByName("reward1");

    TMXTiledMap* tileMap=(TMXTiledMap *) this->getChildByTag(2);
    auto tileSize=tileMap->getTileSize();

    if(step==8){
        //获得奖励 出现弹窗
        PopScene* popLayer = PopScene::create();
        popLayer->nextScene(4);
        popLayer->backScene(0);
        popLayer->setReword(reward1);

        this->addChild(popLayer,5);

    }


    //如果是往上走的前进状态
    if(up==1){
        if((step>=1&&step<=3)||(step>=7&&step<=8)){


            auto forward=MoveBy::create(1,Vec2(0,tileSize.height*1.2/2));

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
        if(step>=4&&step<=6){

            auto forward=MoveBy::create(1,Vec2(-tileSize.width/2,0));

            person->runAction(forward);
            ++step;
        }

    }


}

void grammarScene::leftTurnCallback(Ref* pSender){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    code_text=code_text+"left()\n";
    showCode();

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

void grammarScene::leftTurn(){
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

void grammarScene::rightTurn(){
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

void grammarScene::rightTurnCallback(Ref* pSender){
    Sprite* person=(Sprite *)this->getChildByTag(1);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);

    code_text=code_text+"right()\n";
    showCode();

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

void grammarScene::showCode(){
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

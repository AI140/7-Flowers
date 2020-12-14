# include "ForPopScene.h"
#include "grammarScene4.h"
#include "grammarScene3.h"


Scene* ForPopScene::Scene()
{
    cocos2d::Scene* scene = NULL; 
    do
    {
        scene = Scene::create();
        ForPopScene* layer = ForPopScene::create();
        scene->addChild(layer);
    }while(0);

    return scene;
}

bool ForPopScene::init()
{
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* background = Sprite::create("对话.png");
    background->setPosition(Vec2(winSize.width/2, winSize.height/2));
    background->setTag(1);
    background->setScale(5);
    this->addChild(background, 0);
    scene_bgSprite = background;
    scene_size = background->getContentSize();
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();

    // 定义按钮
    MenuItemImage* item_left= MenuItemImage::create("left_normal.png","left_selected.png",
                                                 CC_CALLBACK_1(ForPopScene::left_btn, this));
    MenuItemImage* item_right = MenuItemImage::create("right_normal.png","right_selected.png",
                                                 CC_CALLBACK_1(ForPopScene::right_btn, this));
    MenuItemImage* item_forward = MenuItemImage::create("up_normal.png", "up_selected.png", CC_CALLBACK_1(ForPopScene::forward_btn, this));
    Menu* menu = Menu::create(item_left, item_right, item_forward,  NULL);

    menu->setPosition(Vec2(0,0));
    menu->setTag(2);
    
    // 设置位置
    item_left->setAnchorPoint(Vec2(1, 0.5));
    item_left->setScale(0.4);
    item_left->setPosition(Vec2(origin.x +visibleSize.width/2-20,  origin.y+visibleSize.height/9*7));
    item_right->setAnchorPoint(Vec2(0, 0.5));
    item_right->setScale(0.4);
    item_right->setPosition(Vec2(origin.x +visibleSize.width/2+20,  origin.y+visibleSize.height/9*7));
    item_forward->setAnchorPoint(Vec2(0.5, 0.5));
    item_forward->setScale(0.4);
    item_forward->setPosition(Vec2(origin.x +visibleSize.width/2,  origin.y+visibleSize.height/9*7));
    
    this->addChild(menu,1);

    this->setTitle();
    this ->setContent();

    return true;
}

bool ForPopScene::onTouchBegan(Touch * touch, Event * pevent)
{
    return true;
}

// 设置窗口标题
void ForPopScene::setTitle()
{
    auto title = Label::createWithTTF("For语句块", "fonts/STKAITI.TTF", 20);
    title->setTag(3);
    title->setPosition(Vec2( visibleSize.width/2 ,  visibleSize.height+15));
    this->addChild(title, 1);
}

//设置for语句块编辑框
void ForPopScene::setContent()
{
    auto times_label = Label::createWithTTF("次数：","fonts/STKAITI.TTF",18);
    auto action_label = Label::createWithTTF("动作：", "fonts/STKAITI.TTF", 18);

    action_label->setName("action");

    times_label->setTag(4);
    action_label->setTag(5);
    times_edit->setTag(7);
    action_edit->setTag(8);

    //编辑位置
    times_label->setPosition(Vec2(visibleSize.width/4,  visibleSize.height/9*6));
    action_label->setPosition(Vec2(visibleSize.width/4,  visibleSize.height/9*4));
    times_edit->setPosition(Vec2(visibleSize.width/2,  visibleSize.height/9*6));
    action_edit->setPosition(Vec2(visibleSize.width/2,  visibleSize.height/9*4));

    //定义按钮
    MenuItemImage* item_add = MenuItemImage::create("add_normal.png", "add_selected.png", CC_CALLBACK_1(ForPopScene::add_btn, this));
    MenuItemImage* item_minus = MenuItemImage::create("minus_normal.png", "minus_selected.png", CC_CALLBACK_1(ForPopScene::minus_btn, this));
    MenuItemImage* item_submit = MenuItemImage::create("submit_normal.png", "submit_selected.png", CC_CALLBACK_1(ForPopScene::submit_btn, this));
    MenuItemImage* item_back = MenuItemImage::create("back_normal.png", "back_selected.png", CC_CALLBACK_1(ForPopScene::back_btn, this));
    Menu* menu = Menu::create(item_add, item_minus, item_submit, item_back, NULL);

    menu->setTag(6);

    item_add->setScale(2);
    item_minus->setScale(2);



    item_add->setPosition(Vec2(visibleSize.width/3+5, visibleSize.height/9*6));
    item_minus->setPosition(Vec2(visibleSize.width/3*2-5, visibleSize.height/9*6));

    menu->setPosition(Vec2(0,0));

    item_back->setScale(0.6);
    item_submit->setScale(0.6);

    item_back->setPosition(Vec2(visibleSize.width/2-6, visibleSize.height/4));
    item_back->setAnchorPoint(Vec2(1, 0.5));
    item_submit->setPosition(Vec2(visibleSize.width/2+6, visibleSize.height/4));
    item_submit->setAnchorPoint(Vec2(0, 0.5));

    this->addChild(times_label, 1);
    this->addChild(action_label, 1);
    this->addChild(times_edit, 1);
    this->addChild(action_edit,1);
    this->addChild(action_label, 1);
    this->addChild(menu, 1);
}

// 单击“left”按钮的响应函数
void ForPopScene::left_btn(Ref* pSender)
{
    action_edit->setString("left()");
}

// 单击“right”按钮的响应函数
void ForPopScene::right_btn(Ref* pSender)
{
    action_edit->setString("right()");    
}

// 单击“forward”按钮的响应函数
void ForPopScene::forward_btn(Ref* pSender)
{
    action_edit->setString("forward()");    
}

// 单击“+”按钮的响应函数
void ForPopScene::add_btn(Ref* pSender)
{
    times ++;
    times_edit->setString(std::to_string(times));
}

// 单击“-”按钮的响应函数
void ForPopScene::minus_btn(Ref* pSender)
{
    if(times>0){	//最少循环0次
        times --;
        times_edit->setString(std::to_string(times));
    }
}


//点击“返回”按钮的响应函数
void ForPopScene::back_btn(Ref* pSender)
{
    for(int i=1;i<9;++i){
        this->removeChildByTag(i);
    }

    this->removeChildByName("action");


}

//点击“提交”按钮的响应函数
void ForPopScene::submit_btn(Ref* pSender)
{
    //获取循环次数，操作，生成函数体字符串
    int loop_times = times;
    std::string operation = action_edit->getString();
    std::string for_codes = "for i in range(";
    for_codes = for_codes + std::to_string(times) + "):\n\t" +operation;

    for(int i=1;i<9;++i){
        this->removeChildByTag(i);
    }

    this->removeChildByName("action");

    //当前场景

    auto curr_scene = (grammarScene3*)Director::getInstance()->getRunningScene();

    if(sceneName==6){
        delete curr_scene;
        auto* curr_scene = (grammarScene4*)Director::getInstance()->getRunningScene();
    }

    //更新代码输出框
    curr_scene->code_text = curr_scene->code_text+for_codes+"\n";
    curr_scene->showCode();

    //精灵运动
    for(int i=0; i<loop_times; i++){
        if(operation=="left()"){
            curr_scene->leftTurn();
        }
        else if (operation=="right()"){
            curr_scene->rightTurn();
        }
        else if(operation=="forward()"){
            curr_scene->forwardTurn();
        }
        else{
            curr_scene->code_text += "语句不合法！\n";
            curr_scene->showCode();
            break;
        }
    }

}


# include "IfPopScene.h"
#include "grammarScene4.h"
#include "grammarScene3.h"
#include "grammarScene2.h"
#include <SimpleAudioEngine.h>

Scene* IfPopScene::Scene()
{
    cocos2d::Scene* scene = nullptr;
    do
    {
        scene = Scene::create();
        IfPopScene* layer = IfPopScene::create();
        scene->addChild(layer);
    }while(0);

    return scene;
}

bool IfPopScene::init()
{
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* background = Sprite::create("对话.png");
    background->setPosition(Vec2(winSize.width/2, winSize.height/2));
    background->setScale(5);
    background->setTag(1);
    this->addChild(background, 0);
    scene_bgSprite = background;
    scene_size = background->getContentSize();
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();

    // 定义按钮
    MenuItemImage* item_with_bomb = MenuItemImage::create("with_bomb_normal.png","with_bomb_selected.png",
                                                 CC_CALLBACK_1(IfPopScene::with_bomb_btn, this));
    MenuItemImage* item_no_bomb = MenuItemImage::create("no_bomb_normal.png","no_bomb_selected.png",
                                                 CC_CALLBACK_1(IfPopScene::no_bomb_btn, this));
    MenuItemImage* item_still = MenuItemImage::create("still_normal.png", "still_selected.png", CC_CALLBACK_1(IfPopScene::still_btn, this));
    MenuItemImage* item_forward = MenuItemImage::create("forward_normal.png", "forward_selected.png", CC_CALLBACK_1(IfPopScene::forward_btn, this));
    Menu* menu = Menu::create(item_with_bomb, item_no_bomb, item_still, item_forward,  NULL);
    menu->setTag(2);
    
    // 设置位置
    item_with_bomb->setAnchorPoint(Vec2(1, 0.5));
    item_with_bomb->setScale(0.5);
    item_with_bomb->setPosition(Vec2(visibleSize.width/2-6,  visibleSize.height/9*7));
    item_no_bomb->setAnchorPoint(Vec2(0, 0.5));
    item_no_bomb->setScale(0.5);
    item_no_bomb->setPosition(Vec2(visibleSize.width/2+6,  visibleSize.height/9*7));
    item_still->setAnchorPoint(Vec2(1, 0.5));
    item_still->setScale(0.5);
    item_still->setPosition(Vec2(visibleSize.width/2-6,  visibleSize.height/2));
    item_forward->setAnchorPoint(Vec2(0, 0.5));
    item_forward->setScale(0.5);
    item_forward->setPosition(Vec2(visibleSize.width/2+6,  visibleSize.height/2));

    //设置名字
    item_with_bomb->setName("item_with_bomb");
    item_no_bomb->setName("item_no_bomb");
    item_still->setName("item_still");
    item_forward->setName("item_forward");

    menu->setPosition(Vec2(0,15));

//    //异常1
//    menu->setTouchPriority(kCCMenuHandlerPriority*2-1);
    this->addChild(menu,1);

    this->setTitle();
    this ->setContent();

    return true;
}

bool IfPopScene::onTouchBegan(Touch * touch, Event * pevent)
{
    return true;
}

// 设置窗口标题
void IfPopScene::setTitle()
{
    auto title = Label::createWithTTF("IF语句块", "fonts/STKAITI.TTF", 19);
    title->setTag(3);
;    title->setPosition(Vec2( visibleSize.width/2 ,  visibleSize.height+8));
    this->addChild(title, 1);
}

// 设置if语句块编辑区
void IfPopScene::setContent()
{
    auto content_if = Label::createWithTTF("if ", "fonts/XPZ.TTF",25);
    auto content_colon = Label::createWithTTF(": ", "fonts/XPZ.TTF",25);

    MenuItemImage* item_edit1 = MenuItemImage::create("edit_normal.png", "edit_normal_selected.png", CC_CALLBACK_1(IfPopScene::edit1_btn, this));
    MenuItemImage* item_edit2 = MenuItemImage::create("edit_normal.png", "edit_normal_selected.png", CC_CALLBACK_1(IfPopScene::edit2_btn, this));
    MenuItemImage* item_submit = MenuItemImage::create("submit_normal.png", "submit_selected.png", CC_CALLBACK_1(IfPopScene::submit_btn, this));
    MenuItemImage* item_back = MenuItemImage::create("back_normal.png", "back_selected.png", CC_CALLBACK_1(IfPopScene::back_btn, this));
    Menu* menu = Menu::create(item_edit1, item_edit2, item_submit, item_back, NULL);
    menu->setTag(4);


    content_if->setPosition(Vec2(visibleSize.width/4,  visibleSize.height/9*7));
    content_if->setScale(0.7);
//    item_edit1->setPosition(Vec2(visibleSize.width/3+10, visibleSize.height/9*4+15));
//    item_edit1->setScale(0.7);
    content_colon->setPosition(Vec2(visibleSize.width/4*3, visibleSize.height/9*7));
    content_colon->setScale(0.7);
//    item_edit2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/9*3+10));
//    item_edit2->setScale(0.7);

    content_colon->setTag(5);
    content_if->setTag(6);


    menu->setPosition(Vec2(10,0));

    item_back->setScale(0.7);
    item_submit->setScale(0.7);

    
    item_back->setPosition(Vec2(visibleSize.width/2-6, visibleSize.height/4));
    item_back->setAnchorPoint(Vec2(1, 0.5));
    item_submit->setPosition(Vec2(visibleSize.width/2+6, visibleSize.height/4));
    item_submit->setAnchorPoint(Vec2(0, 0.5));

    item_edit1->setName("item_edit1");
    item_edit2->setName("item_edit2");
    item_submit->setName("item_submit");
    item_back->setName("item_back");

    this->addChild(content_if, 1);
    this->addChild(content_colon, 1);
    this->addChild(menu, 1);
}

// 点击“炸弹出现”按钮的响应函数
void IfPopScene::with_bomb_btn(Ref* pSender)
{
    /*//未选定编辑框
    if(edit_curr== nullptr || edit_curr_index==0){
        return;
    } 
    // 修改编辑框
    MenuItemImage* item_curr = (MenuItemImage *)this->getChildByName("item_with_bomb");
    edit_curr->setNormalImage(item_curr->getNormalImage());
    edit_curr->setSelectedImage(item_curr->getSelectedImage());

    if(edit_curr_index==1){
        condition_str = "炸弹出现";
    }else if(edit_curr_index==2){
        exec_str = "炸弹出现";
    } */
    condition_str = "炸弹出现";
    if_codes = "if "+condition_str+":\n"+"\t"+exec_str;
}

//点击“炸弹消失”按钮的响应函数
void IfPopScene::no_bomb_btn(Ref* pSender)
{
    /*//未选定编辑框
    if(edit_curr== nullptr || edit_curr_index==0){
        return;
    } 
    // 修改编辑框
    MenuItemImage* item_curr = (MenuItemImage *)this->getChildByName("item_no_bomb");
    edit_curr->setNormalImage(item_curr->getNormalImage());
    edit_curr->setSelectedImage(item_curr->getSelectedImage());

    if(edit_curr_index==1){
        condition_str = "炸弹消失";
    }else if(edit_curr_index==2){
        exec_str = "炸弹消失";
    } */
    condition_str = "炸弹消失";
    if_codes = "if "+condition_str+":\n"+"\t"+exec_str;
}

//点击“等待”按钮的响应函数
void IfPopScene::still_btn(Ref* pSender)
{
    /*//未选定编辑框
    if(edit_curr== nullptr || edit_curr_index==0){
        return;
    } 
    // 修改编辑框
    MenuItemImage* item_curr = (MenuItemImage *)this->getChildByName("item_still");
    edit_curr->setNormalImage(item_curr->getNormalImage());
    edit_curr->setSelectedImage(item_curr->getSelectedImage());

    if(edit_curr_index==1){
        condition_str = "等待";
    }else if(edit_curr_index==2){
        exec_str = "等待";
    } */
    exec_str = "等待";
    if_codes = "if "+condition_str+":\n"+"\t"+exec_str;
}

//点击“前进”按钮的响应函数
void IfPopScene::forward_btn(Ref* pSender)
{
    /*//未选定编辑框
    if(edit_curr== nullptr || edit_curr_index==0){
        return;
    } 
    // 修改编辑框
    MenuItemImage* item_curr = (MenuItemImage *)this->getChildByName("item_forward");
    edit_curr->setNormalImage(item_curr->getNormalImage());
    edit_curr->setSelectedImage(item_curr->getSelectedImage());

    if(edit_curr_index==1){
        condition_str = "forward()";
    }else if(edit_curr_index==2){
        exec_str = "forward()";
    } */
    exec_str = "forward()";
    if_codes = "if "+condition_str+":\n"+"\t"+exec_str;
}

//点击编辑框1的响应函数
void IfPopScene::edit1_btn(Ref* pSender)
{
    // 修改编辑框指针
    edit_curr = (MenuItemImage* )this->getChildByName("item_edit1");
    edit_curr_index = 1;
}

//点击编辑框2的响应函数
void IfPopScene::edit2_btn(Ref* pSender)
{
    // 修改编辑框指针
    edit_curr = (MenuItemImage* )this->getChildByName("item_edit2");
    edit_curr_index = 2;
}

//点击“返回”按钮的响应函数
void IfPopScene::back_btn(Ref* pSender)
{
    for(int i=1;i<7;++i){
        this->removeChildByTag(i);
    }
}

//点击“提交”按钮的响应函数
void IfPopScene::submit_btn(Ref* pSender)
{
    //获取字符串
    std::string condition = condition_str;
    std::string operation = exec_str;
    std::string if_code = this->if_codes;

    for(int i=1;i<7;++i){
    this->removeChildByTag(i);
    }

    //当前场景
    auto curr_scene = (grammarScene2*)Director::getInstance()->getRunningScene();

    if(sceneName==6){
        delete curr_scene;
        auto curr_scene = (grammarScene4*)Director::getInstance()->getRunningScene();
    }
    if(sceneName==5){
        delete curr_scene;
        auto curr_scene = (grammarScene3*)Director::getInstance()->getRunningScene();
    }

    if(sceneName<4){return;}
    //更新代码输出框
    curr_scene->code_text = curr_scene->code_text+if_code+"\n";
    curr_scene->showCode();

    //小精灵运动
    if( (condition=="炸弹消失"&&operation=="等待") || (condition=="炸弹出现"&&operation=="forward()") ){
    //只有炸弹出现时，才调用前进函数；否则，无操作
        while(1){
            if(curr_scene->time%3!=0){
                curr_scene->forwardTurn();
            }
        }
    }else if( (condition=="炸弹消失"&&operation=="forward()") || (condition=="炸弹出现"&&operation=="等待") ){
    //只有炸弹消失时，才调用前进函数；否则，无操作
        while(1){
            if(curr_scene->time%3==0){
                curr_scene->forwardTurn();
            }
        }
    }else{
    //其他情况下，未不合法语句，小人不运动，代码框输出错误
    curr_scene->code_text = curr_scene->code_text+"语句不合法！\n";
    curr_scene->showCode();
    }

}


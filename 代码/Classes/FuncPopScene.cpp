# include "FuncPopScene.h"
#include "grammarScene4.h"

Scene* FuncPopScene::Scene()
{
    cocos2d::Scene* scene = NULL; 
    do
    {
        scene = Scene::create();
        FuncPopScene* layer = FuncPopScene::create();
        scene->addChild(layer);
    }while(0);

    return scene;
}

bool FuncPopScene::init()
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
                                                 CC_CALLBACK_1(FuncPopScene::left_btn, this));
    MenuItemImage* item_right = MenuItemImage::create("right_normal.png","right_selected.png",
                                                 CC_CALLBACK_1(FuncPopScene::right_btn, this));
    MenuItemImage* item_delete = MenuItemImage::create("delete_normal.png", "delete_selected.png", CC_CALLBACK_1(FuncPopScene::delete_btn, this));
    MenuItemImage* item_forward = MenuItemImage::create("up_normal.png", "up_selected.png", CC_CALLBACK_1(FuncPopScene::forward_btn, this));
    Menu* menu = Menu::create(item_left, item_right, item_delete, item_forward,  NULL);

   menu->setSwallowsTouches(true);
    
    // 设置位置
    //item_left->setAnchorPoint(Vec2(1, 0.5));
    item_left->setScale(0.4);
    item_left->setPosition(Vec2(visibleSize.width*3/4,  visibleSize.height));
    //item_right->setAnchorPoint(Vec2(0, 0.5));
    item_right->setScale(0.4);
    item_right->setPosition(Vec2(visibleSize.width*3/4,  visibleSize.height/9*7.5));
    //item_forward->setAnchorPoint(Vec2(1, 0.5));
    item_forward->setScale(0.4);
    item_forward->setPosition(Vec2(visibleSize.width*3/4,  visibleSize.height/9*6));
    //item_delete->setAnchorPoint(Vec2(0, 0.5));
    item_delete->setScale(0.4);
    item_delete->setPosition(Vec2(visibleSize.width*3/4+7,  visibleSize.height/9*4.5));


    menu->setPosition(Vec2(0,0));
    menu->setTag(2);

    this->addChild(menu,1);

    this->setTitle();
    this ->setContent();

    return true;
}

bool FuncPopScene::onTouchBegan(Touch * touch, Event * pevent)
{
    return true;
}

// 设置窗口标题
void FuncPopScene::setTitle()
{
    auto title = Label::createWithTTF("Function语句块", "fonts/STKAITI.TTF", 19);
    title->setPosition(Vec2( visibleSize.width/2 ,  visibleSize.height));
    title->setTag(3);
    this->addChild(title, 1);
}

//设置func语句块编辑框
void FuncPopScene::setContent()
{
    // 定义函数体编辑标签，函数体内最多允许添加5行命令
    auto content = Label::createWithTTF("函数体：","fonts/STKAITI.TTF",19);
    auto content1 = Label::createWithTTF("| ", "fonts/STKAITI.TTF", 15);
    auto content2 = Label::createWithTTF(" ", "fonts/STKAITI.TTF", 15);
    auto content3 = Label::createWithTTF(" ", "fonts/STKAITI.TTF", 15);
    auto content4 = Label::createWithTTF(" ", "fonts/STKAITI.TTF", 15);
    auto content5 = Label::createWithTTF(" ", "fonts/STKAITI.TTF", 15);
    //编辑位置
    content->setPosition(Vec2(visibleSize.width/4,  visibleSize.height));
    content1->setPosition(Vec2(visibleSize.width/3,  visibleSize.height/9*8));
    content2->setPosition(Vec2(visibleSize.width/3,  visibleSize.height/9*7));
    content3->setPosition(Vec2(visibleSize.width/3,  visibleSize.height/9*6));
    content4->setPosition(Vec2(visibleSize.width/3,  visibleSize.height/9*5));
    content5->setPosition(Vec2(visibleSize.width/3,  visibleSize.height/9*4));
    content->setTag(5);
    content1->setTag(6);
    content2->setTag(7);
    content3->setTag(8);
    content4->setTag(9);
    content5->setTag(10);


    //放入指针数组
    content_label[0] = content1;
    content_label[1] = content2;
    content_label[2] = content3;
    content_label[3] = content4;
    content_label[4] = content5;
    //定义按钮
    MenuItemImage* item_submit = MenuItemImage::create("submit_normal.png", "submit_selected.png", CC_CALLBACK_1(FuncPopScene::submit_btn, this));
    MenuItemImage* item_back = MenuItemImage::create("back_normal.png", "back_selected.png", CC_CALLBACK_1(FuncPopScene::back_btn, this));
    Menu* menu = Menu::create(item_submit, item_back, NULL);

    menu->setTag(4);

    menu->setSwallowsTouches(true);

    menu->setPosition(Vec2(0,0));

    item_submit->setScale(0.7);
    item_back->setScale(0.7);

    item_back->setPosition(Vec2(visibleSize.width/2-6, visibleSize.height/4));
    item_back->setAnchorPoint(Vec2(1, 0.5));
    item_submit->setPosition(Vec2(visibleSize.width/2+6, visibleSize.height/4));
    item_submit->setAnchorPoint(Vec2(0, 0.5));

    this->addChild(content, 1);
    for(int i=0; i<5; i++){
        this->addChild(content_label[i], 1);
    };
    this->addChild(menu, 1);
}

// 单击“left”按钮的响应函数
void FuncPopScene::left_btn(Ref* pSender)
{
    // 函数体编辑行满
    if(curr_content>=5){
        return;
    }
    // 更新当前编辑行内容以及内容数组
    content_label[curr_content]->setString("left()");
    content_str[curr_content] = "\tleft()\n";
    //更新当前编辑行号
    curr_content +=1; 
    if(curr_content<5){	//若数组未越界
        content_label[curr_content]->setString("| ");
    }
}

// 单击“right”按钮的响应函数
void FuncPopScene::right_btn(Ref* pSender)
{
    // 函数体编辑行满
    if(curr_content>=5){
        return;
    }
    // 更新当前编辑行内容以及内容数组
    content_label[curr_content]->setString("right()");
    content_str[curr_content] = "\tright()\n";
    //更新当前编辑行号
    curr_content += 1; 
    if(curr_content<5){	//若数组未越界
        content_label[curr_content]->setString("| ");
    }
}

// 单击“forward”按钮的响应函数
void FuncPopScene::forward_btn(Ref* pSender)
{
    // 函数体编辑行满
    if(curr_content>=5){
        return;
    }
    // 更新当前编辑行内容以及内容数组
    content_label[curr_content]->setString("forward()");
    content_str[curr_content] = "\tforward()\n";
    //更新当前编辑行号
    curr_content += 1; 
    if(curr_content<5){	//若数组未越界
        content_label[curr_content]->setString("| ");
    }
}

// 单击“delete”按钮的响应函数
void FuncPopScene::delete_btn(Ref* pSender)
{
    // 函数体已经清空
    if(curr_content<=0){
        return;
    }
    // 当前编辑行内容置为空
    content_label[curr_content]->setString("");
    //更新当前编辑行号，清空该行并更新内容数组
    curr_content -= 1; 
    content_label[curr_content]->setString("| ");
    content_str[curr_content] = "";
}

//点击“返回”按钮的响应函数
void FuncPopScene::back_btn(Ref* pSender)
{
    for(int i=1;i<11;++i){
        this->removeChildByTag(i);

    }

}

//点击“提交”按钮的响应函数
void FuncPopScene::submit_btn(Ref* pSender)
{
    //获取函数体语句，生成函数体字符串
    std::string operations[5];
    std::string func_codes = "def func(): \n";
    for(int i=0; i<5; i++){
        operations[i] = content_str[i];
        func_codes += operations[i];
    }

    for(int i=1;i<11;++i){
        this->removeChildByTag(i);

    }

    //当前场景
    grammarScene4* curr_scene = (grammarScene4*)Director::getInstance()->getRunningScene();
    //更新代码输出框
    curr_scene->code_text = curr_scene->code_text+func_codes+"\n";
    curr_scene->showCode();

    //精灵运动
    for(int i=0; i<5; i++){
        if(operations[i]=="") {
            return;
        }else if(operations[i]=="\tforward()\n") {
            curr_scene->forwardTurn();
        }else if(operations[i]=="\tleft()\n") {
            curr_scene->leftTurn();
        }else if(operations[i]=="\tright()\n") {
            curr_scene->rightTurn();
        }else{
            curr_scene->code_text += "语句不合法！\n";
            curr_scene->showCode();
            return;
        }
    }
}

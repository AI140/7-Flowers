//
// Created by ThinkPad on 2020/12/8.
//
#include "variableScene2.h"

USING_NS_CC;

Scene* variableScene2::createScene()
{
    return variableScene2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
// on "init" you need to initialize your instance
bool variableScene2::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto color_answer=Color3B(47,43,44);

    //添加故事区
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
    auto story_text = Label::createWithTTF("\t\t“这些金黄的小石头或许会有用……”\n\t\t赛文将它们装进口袋，\n\t\t继续往前走,发现这里停着一辆矿车\n\t\t",
            "fonts/songti.ttf", 15);
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

    auto story_chuan = Sprite::create("planet.png");
    story_chuan->setPosition(Vec2(visibleSize.width-20,visibleSize.height/5-4));
    story_chuan->setScale(0.5);
    story_chuan->setName("chuan");
    this->addChild(story_chuan,4);

    //设置开始LABEL
    auto begin = Label::createWithTTF("Begin", "fonts/Marker Felt.ttf", 24);
    begin->setPosition(Vec2(origin.x+visibleSize.width / 2,
                            origin.y+visibleSize.height - begin->getContentSize().height/2));
    begin->setName("Begin");
    this->addChild(begin, 1);
    begin->setVisible(true);

    //设置问题框层
    auto questionLayer = Layer::create();
    questionLayer->setPosition(0, 0);
    questionLayer->setName("questionLayer");
    questionLayer->setVisible(false);
    this->addChild(questionLayer, 2);

    //设置背景图片1
    auto levelBackGround = Sprite::create("background_vs2.png");
    auto width1=levelBackGround->getContentSize().width;
    auto height1=levelBackGround->getContentSize().height;
    levelBackGround->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height / 2));
    levelBackGround->setScale(visibleSize.width/width1+1, visibleSize.height/height1+1);
    this->addChild(levelBackGround, 0);

    //设置背景图片2
    auto levelBackGround2 = Sprite::create("road_vs2.png");
    levelBackGround2->setPosition(Vec2(origin.x+visibleSize.width / 2, origin.y+visibleSize.height / 766));
    levelBackGround2->setScale(visibleSize.width/levelBackGround2->getContentSize().width+1, 4);
    this->addChild(levelBackGround2, 0);
    levelBackGround2->setVisible(true);

    //设置卡车spirit
    auto lorry = Sprite::create("lorry.png");
    lorry->setPosition(Vec2(origin.x+visibleSize.width/7, origin.y+visibleSize.height*3/12));
    lorry->setName("lorry");
    lorry->setScale(0.5);
    this->addChild(lorry, 1);
    lorry->setVisible(true);

    //设置灯塔spirit
    auto tower = Sprite::create("tower.png");
    tower->setPosition(Vec2(origin.x+visibleSize.width*6/7, origin.y+visibleSize.height/2));
    tower->setName("tower");
    tower->setScale(1.5);
    this->addChild(tower, 1);
    tower->setVisible(true);

    //设置问题背景框
    auto question = Sprite::create("frame2.png");
    question->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2+30));
    question->setScale(1.25,1.0);
    question->setOpacity(200);
    question->setName("question");
    questionLayer->addChild(question, 0);

    //设置问题文本
    auto questionLabel =Label::createWithTTF("question", "fonts/songti.ttf", 24);
    questionLabel->setMaxLineWidth(250);
    questionLabel->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2+25);
    questionLabel->setName("questionLabel");
    questionLayer->addChild(questionLabel, 2);

    //设置答案A背景
    auto answerA = Sprite::create("planet.png");
    answerA->setPosition(origin.x+visibleSize.width/3,origin.y+visibleSize.height/3);
    answerA->setName("answerA");
    answerA->setOpacity(230);
    answerA->setScale(1.5);
    Answer.insert(0,answerA);
    questionLayer->addChild(answerA, 1);

    //设置答案A文本
    auto answerALabel = Label::createWithTTF("A", "fonts/XPZ.TTF", 24);
    answerALabel->setPosition(origin.x+visibleSize.width/3,origin.y+visibleSize.height/3);
    answerALabel->setName("answerALabel");
    answerALabel->setColor(color_answer);
    questionLayer->addChild(answerALabel, 2);

    //设置答案B背景
    auto answerB = Sprite::create("planet.png");
    answerB->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/3);
    answerB->setName("answerB");
    answerB->setOpacity(230);
    answerB->setScale(1.5);
    answerB->setOpacity(250);
    Answer.insert(1,answerB);
    questionLayer->addChild(answerB, 1);

    //设置答案B文本
    auto answerBLabel = Label::createWithTTF("B", "fonts/XPZ.TTF", 24);
    answerBLabel->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/3);
    answerBLabel->setName("answerBLabel");
    answerBLabel->setColor(color_answer);
    questionLayer->addChild(answerBLabel, 2);

    //设置答案C背景
    auto answerC = Sprite::create("planet.png");
    answerC->setPosition(origin.x+visibleSize.width*2/3,origin.y+visibleSize.height/3);
    answerC->setName("answerC");
    answerC->setOpacity(225);
    answerC->setOpacity(230);
    answerC->setScale(1.5);
    Answer.insert(2,answerC);
    questionLayer->addChild(answerC, 1);

    //设置答案C文本
    auto answerCLabel = Label::createWithTTF("C", "fonts/XPZ.TTF", 24);
    answerCLabel->setPosition(origin.x+visibleSize.width*2/3,origin.y+visibleSize.height/3);
    answerCLabel->setName("answerCLabel");
    answerCLabel->setColor(color_answer);
    questionLayer->addChild(answerCLabel, 2);

    //设置开始按钮的监听事件
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(variableScene2::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    //退出按钮
    auto backItem = MenuItemImage::create("back.png", "back.png",
                                            CC_CALLBACK_1(variableScene2::backToCallback, this));
    backItem->setScale(2.5);
    auto back = Menu::create(backItem, NULL);
    back->setPosition(Vec2(origin.x+visibleSize.width*0+25,origin.y+visibleSize.height-20)); //用不用vec2
    this->addChild(back, 6);


    //答对小星星
    auto Star = Sprite::create("star.png");
    Star->setName("Star");
    Star->setScale(1);
    Answer.insert(3,Star);
    this->addChild(Star,5);
    Star->setVisible(false);

    //答错叉号
    auto wrong = Sprite::create("wrong.png");
    wrong->setName("wrong");
    wrong->setScale(0.3);
    Answer.insert(4,wrong);
    this->addChild(wrong,5);
    Star->setVisible(false);
    //答错显示正确答案
    auto correct = Sprite::create("correct.png");
    correct->setName("correct");
    Answer.insert(5,correct);
    correct->setScale(0.4);
    this->addChild(correct,5);
    Star->setVisible(false);

    //分数显示框
    auto score = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
    score->setAnchorPoint(Vec2(0,1));
    score->setPosition(Vec2(origin.x+70,origin.y+visibleSize.height-5));
    score->setName("score");
    this->addChild(score,1);

    //倒计时显示框
    auto countDown = Label::createWithTTF("15", "fonts/Marker Felt.ttf", 24);
    countDown->setAnchorPoint(Vec2(1,1));
    countDown->setPosition(origin.x+visibleSize.width-countDown->getContentSize().width,origin.y+visibleSize.height-5);
    countDown->setName("countDown");
    this->addChild(countDown,1);

    return true;
}

bool variableScene2::onTouchBegan(Touch *touch, Event *event) {

    //按键音
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);
    //得到鼠标点击的地方
    auto target=(Label*)this->getChildByName("Begin");
    auto pos= Director::getInstance()->convertToGL(touch->getLocationInView());
    auto questionLayer=(Layer*)this->getChildByName("questionLayer");
    auto answerA = (Sprite*)questionLayer->getChildByName("answerA");
    auto answerALabel = questionLayer->getChildByName("answerALabel");
    auto answerB = (Sprite*)questionLayer->getChildByName("answerB");
    auto answerBLabel = questionLayer->getChildByName("answerBLabel");
    auto answerC =(Sprite*)questionLayer->getChildByName("answerC");
    auto answerCLabel = questionLayer->getChildByName("answerCLabel");
    auto star=this->getChildByName("Star");
    auto wrong=this->getChildByName("wrong");
    auto correct=this->getChildByName("correct");
    Label* countDown = (Label*)this->getChildByName("countDown");
    Sprite* story_chuan=(Sprite *)this->getChildByName("chuan");
    Sprite* story_background=(Sprite *)this->getChildByName("story_background");

    Label* story_text=(Label *)this->getChildByName("story_text");
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if(touchTime==1) {

        story_text->setVisible(false);
        story_background->setVisible(false);
        story_chuan->setVisible(false);

        ++touchTime;
        return true;
    }
    if(num==6){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/type.wav", false);
        star->setVisible(false);
        wrong->setVisible(false);
        correct->setVisible(false);
        questionLayer->setVisible(false);
        story_text->setString("\t\t赛文注意到，矿区的围墙上有一道大致允许一人通行的缝隙。\n\t\t“可能是矿区的出口。”\n\t\t事实上，小赛文没有别的选择，他只能向前走。\n\t\t");
        story_text->setVisible(true);
        story_background->setVisible(true);
        story_chuan->setVisible(true);
        num++;
        return true;
    }
    if(num==7){
        story_text->setString("\t\t于是，他又收集了一些附近的金色矿石，\n\t\t揣着满满的口袋向出口走去……\n\t\t（提示：请点击地图——语法丛林，解锁剧情）\n\t\t");
        //添加弹窗 弹出弹窗
        PopScene* popLayer = PopScene::create();
        popLayer->nextScene(0);
        popLayer->backScene(0);
        this->addChild(popLayer);
        return true;
    }
    /* 判断点击的坐标是否在范围内 是否开始游戏 */
    if (target->getBoundingBox().containsPoint(pos))
    {
        target->setVisible(false);
        star->setVisible(false);
        wrong->setVisible(false);
        correct->setVisible(false);
        click=false;
        start=true;
        //设置问题和选项
        random=SetText(questionLayer,num);
        questionLayer->setVisible(true);
        //downTime=15;
        countDown->setString("15");
        //倒计时更新
        this->schedule(schedule_selector(variableScene2::countUpdate), 1.0f, 15, 0);
    }else if(start&&!click&&(answerA->getBoundingBox().containsPoint(pos) ||
             answerALabel->getBoundingBox().containsPoint(pos)||answerB->getBoundingBox().containsPoint(pos) ||
             answerBLabel->getBoundingBox().containsPoint(pos)||answerC->getBoundingBox().containsPoint(pos) ||
             answerCLabel->getBoundingBox().containsPoint(pos))){
        if (answerA->getBoundingBox().containsPoint(pos) ||
            answerALabel->getBoundingBox().containsPoint(pos)) {
            timeOut = false;
            select = 0;
            click=true;
            Judge();
        }
        if (answerB->getBoundingBox().containsPoint(pos)||
            answerBLabel->getBoundingBox().containsPoint(pos)) {
            timeOut = false;
            select = 1;
            click=true;
            Judge();
        }
        if (answerC->getBoundingBox().containsPoint(pos)||
            answerCLabel->getBoundingBox().containsPoint(pos)) {
            timeOut = false;
            select = 2;
            click=true;
            Judge();
        }
        target->setString("next");
        target->setVisible(true);
        num++;
    }
    return true;
}

//题目设置 返回正确选项的编号
int variableScene2::SetText(Layer* layer, int num){

    auto question = (Label*)layer->getChildByName("questionLabel");
    question->setString(Question[num]);
    log("setString执行");
    auto answerA = (Label*)layer->getChildByName("answerALabel");
    auto answerB = (Label*)layer->getChildByName("answerBLabel");
    auto answerC = (Label*)layer->getChildByName("answerCLabel");
    srand((unsigned)time(NULL));
    int random = rand()%3;

    //设置选项的分布
    switch(random){
        case 0:
            answerA->setString(True[num]);
            answerB->setString(False1[num]);
            answerC->setString(False2[num]);
            break;
        case 1:
            answerB->setString(True[num]);
            answerA->setString(False1[num]);
            answerC->setString(False2[num]);
            break;
        case 2:
            answerC->setString(True[num]);
            answerB->setString(False1[num]);
            answerA->setString(False2[num]);
            break;
    }
    return random;
};

void variableScene2::Judge(){
    auto layer = (Layer*)this->getChildByName("questionLayer");
    auto score = (Label*)this->getChildByName("score");
    Sprite* right = Answer.at(random);
    auto correct=this->getChildByName("correct");
    auto wrong=this->getChildByName("wrong");
    MoveTo* moveTo = nullptr;
    DelayTime* delay = nullptr;

    if(random==select){
        //正确提示音
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/right.mp3", false);

        auto star=this->getChildByName("Star");
        star->setPosition(right->getPosition());
        star->setVisible(true);
        layer->addChild(star, 3);

        //小星星飞过去
        moveTo = MoveTo::create(1, score->getPosition());
        star->runAction(moveTo);
        Score++;
        score->setString(std::to_string(Score));

    }else if(timeOut){
        //错误提示音
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/wrong.wav", false);
        //将对号加到正确答案上
        correct->setPosition(right->getPosition());
        correct->setVisible(true);
        layer->addChild(correct,3);
        //经过几秒
        delay = DelayTime::create(2);
        correct->runAction(delay);

    }else{
        //错误提示音
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/wrong.wav", false);

        //将对号加到正确答案上
        correct->setPosition(right->getPosition());
        correct->setVisible(true);
        layer->addChild(correct,3);

        //将叉号加到错误答案上
        Sprite* choose = Answer.at(select);
        wrong->setPosition(choose->getPosition());
        wrong->setVisible(true);
        layer->addChild(wrong, 3);

        //经过几秒
        delay = DelayTime::create(2);
        correct->runAction(delay);
        wrong->runAction(delay);
    }

}
//倒计时栏
void variableScene2::countUpdate(float dt){
    Label* countDown = (Label*)this->getChildByName("countDown");
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> number = countDown->getString();
    downTime = std::stoi(number)-1;
    if(downTime<0){
        if(timeOut){
            Judge();
        }
        this->unscheduleUpdate();
    }else {
        countDown->setString(std::to_string(downTime));
    }
}


//返回按钮回调函数
void variableScene2::backToCallback(Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/pop.wav", false);
    auto HelloWorldScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(HelloWorldScene);
    //两个类互相调用 要把主页面里的B变成指针
}


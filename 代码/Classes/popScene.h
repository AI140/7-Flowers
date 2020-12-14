#ifndef PROJ_ANDROID_POPSCENE_H
#define PROJ_ANDROID_POPSCENE_H
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "variableScene.h"
#include "variableScene2.h"
#include "grammarScene.h"
#include "grammarScene2.h"
#include "grammarScene3.h"
#include "grammarScene4.h"
//#include "snowScene.h"
#include <iostream>
#include <string>

extern int sceneName;

using namespace cocos2d;

class PopScene : public Layer
{
public:
    static Scene* scene();
    bool init();
    void nextScene(int num);
    void backScene(int num);
    void setReword(Sprite* sprite);
    CREATE_FUNC(PopScene);
private:
    int backName = 0;    //回退到哪一关
    bool onTouchBegan(Touch * touch, Event * pevent);
    void nextButton(Ref *pSender);
    void backButton(Ref *pSender);
    void setTitle();	//设置对话框的title
    void setContent(); 	//设置对话框的文本内容
    Size scene_size;	//对话框背景的大小
    Size visibleSize;
    Sprite* scene_bgSprite;	//对话框的背景精灵
    Sprite* reword;
    Vec2 origin;
};

#endif //PROJ_ANDROID_POPSCENE_H
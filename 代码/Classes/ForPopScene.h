#ifndef PROJ_ANDROID_FORPOPSCENE_H
#define PROJ_ANDROID_FORPOPSCENE_H
#include "cocos2d.h"
#include <iostream>
#include <string>
#include "popScene.h"

using namespace cocos2d;

class ForPopScene: public Layer
{
public:
	static Scene* Scene();
	virtual bool init();
	CREATE_FUNC(ForPopScene);
private:
	bool onTouchBegan(Touch* touch, Event* pevent);
	// 点击响应函数
	void left_btn(Ref* pSender);
	void right_btn(Ref* pSender);
	void forward_btn(Ref* pSender);
	void add_btn(Ref* pSender);
	void minus_btn(Ref* pSender);
	void submit_btn(Ref* pSender);
	void back_btn(Ref* pSender);

	void setTitle();	// 设置title
	void setContent();	// 设置内容

	Size scene_size;
	Size visibleSize;
	Sprite* scene_bgSprite;
	Vec2 origin;

	int times = 0;
	Label* times_edit = Label::createWithTTF("0", "fonts/STKAITI.TTF",22);	//循环次数编辑框
	Label* action_edit = Label::createWithTTF("", "fonts/STKAITI.TTF",22);	//循环动作编辑框
};

#endif //PROJ_ANDROID_FORPOPSCENE_H
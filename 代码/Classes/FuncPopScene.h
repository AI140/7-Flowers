#ifndef PROJ_ANDROID_FUNCPOPSCENE_H
#define PROJ_ANDROID_FUNCPOPSCENE_H
#include "cocos2d.h"
#include <iostream>
#include <string>
#include "popScene.h"
using namespace cocos2d;

class FuncPopScene: public Layer
{
public:
	static Scene* Scene();
	virtual bool init();
	CREATE_FUNC(FuncPopScene);

	std::string content_str[5];		//函数体每行内容

	int change=0;

private:
	bool onTouchBegan(Touch* touch, Event* pevent);
	// 点击响应函数
	void left_btn(Ref* pSender);
	void right_btn(Ref* pSender);
	void forward_btn(Ref* pSender);
	void delete_btn(Ref* pSender);
	void submit_btn(Ref* pSender);
	void back_btn(Ref* pSender);

	void setTitle();	// 设置title
	void setContent();	// 设置内容
	
	Size scene_size;
	Size visibleSize;
	Sprite* scene_bgSprite;
	Vec2 origin;

	int curr_content = 0;		//函数体当前空白编辑行的行号，从0开始计数

	Label* content_label[5];	//函数体每行标签
};

#endif //PROJ_ANDROID_FUNCPOPSCENE_H
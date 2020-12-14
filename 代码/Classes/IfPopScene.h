#ifndef PROJ_ANDROID_IFPOPSCENE_H
#define PROJ_ANDROID_IFPOPSCENE_H
#include "cocos2d.h"
#include <iostream>
#include <string>
#include "popScene.h"

using namespace cocos2d;

class IfPopScene: public Layer
{
public:
	static Scene* Scene();
	virtual bool init();
	CREATE_FUNC(IfPopScene);
private:
	bool onTouchBegan(Touch* touch, Event* pevent);
	// 点击响应函数
	void with_bomb_btn(Ref* pSender);
	void no_bomb_btn(Ref* pSender);
	void still_btn(Ref* pSender);
	void forward_btn(Ref* pSender);
	void edit1_btn(Ref* pSender);
	void edit2_btn(Ref* pSender);
	void submit_btn(Ref* pSender);
	void back_btn(Ref* pSender);

	void setTitle();	// 设置title
	void setContent();	// 设置内容
	
	Size scene_size;
	Size visibleSize;
	Sprite* scene_bgSprite;
	Vec2 origin;

	MenuItemImage* edit_curr= nullptr;	// 当前的编辑框
	int edit_curr_index = 0;
	std::string condition_str = "";	//当前条件语句
	std::string exec_str = "";		// 当前执行语句
	std::string if_codes = "if "+condition_str+":\n"+"\t"+exec_str;	//条件语句块
};


#endif //PROJ_ANDROID_IFPOPSCENE_H
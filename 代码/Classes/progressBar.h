#ifndef _PROGRESSBAR_H_
#define _PROGRESSBAR_H_

# include "cocos2d.h"

using namespace cocos2d;

USING_NS_CC;

class progressBar : public cocos2d::Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    virtual void update(float dt);
    virtual  void updateBackground(float dt);

    CREATE_FUNC(progressBar);
    private:
    ProgressTimer* loadProgress;	//进度条
    Label* loadLabel;		       // 提示标签
    Label* percentLabel;		// 进度标签

private:

    int change=0;
};

#endif //PROJ_ANDROID_GRAMMARSCENE4_H
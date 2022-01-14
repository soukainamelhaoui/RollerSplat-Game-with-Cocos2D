#ifndef __Pause_Menu_H__
#define __Pause_Menu_H__

#include "cocos2d.h"

USING_NS_CC;


class PauseMenu : public cocos2d::Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(PauseMenu);

    // random sprite, allow it for now
    Sprite *mySprite;

    // Menu Functions
    void Resume(Ref* pSender);
    void Levels(Ref* pSender);
    void Exit(Ref* pSender);


};

#endif 

#ifndef __LEVEL_LIST_H__
#define __LEVEL_LIST_H__

#include "cocos2d.h"

USING_NS_CC;


class LevelList : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(LevelList);

    Sprite *mySprite;

    void StartLevel1(Ref* pSender);
    void StartLevel2(Ref* pSender);
    void StartLevel3(Ref* pSender);
};

#endif 
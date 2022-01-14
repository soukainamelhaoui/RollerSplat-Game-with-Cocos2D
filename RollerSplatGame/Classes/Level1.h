
#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__

#include "cocos2d.h"

USING_NS_CC;


class Level1 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Level1);

    Sprite *mySprite;

    void Pause(Ref* pSender);

private:
    PhysicsWorld* baseWorld;

    void setPhysicsWorld(PhysicsWorld* world){
        baseWorld = world;
    };
};

#endif 
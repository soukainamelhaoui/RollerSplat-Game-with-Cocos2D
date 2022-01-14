
#ifndef __LEVEL_2_H__
#define __LEVEL_2_H__

#include "cocos2d.h"

USING_NS_CC;


class Level2 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Level2);

    Sprite *mySprite;

    void Pause(Ref* pSender,float test);
    void goTop(Ref* pSender, Node* daBall, Level2* scene);
    void goRight(Ref* pSender, Node* daBall, Level2* scene);
    void goDown(Ref* pSender, Node* daBall, Level2* scene);
    void goLeft(Ref* pSender, Node* daBall, Level2* scene);

private:
    PhysicsWorld* baseWorld;

    void setPhysicsWorld(PhysicsWorld* world) {
        baseWorld = world;
    };
};

#endif 

#ifndef __LEVEL_3_H__
#define __LEVEL_3_H__

#include "cocos2d.h"

USING_NS_CC;


class Level3 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Level3);

    Sprite *mySprite;

    void Pause(Ref* pSender);
    void goTop(Ref* pSender, Node* daBall, Level3* scene);
    void goRight(Ref* pSender, Node* daBall, Level3* scene);
    void goDown(Ref* pSender, Node* daBall, Level3* scene);
    void goLeft(Ref* pSender, Node* daBall, Level3* scene);

private:
    PhysicsWorld* baseWorld;

    void setPhysicsWorld(PhysicsWorld* world) {
        baseWorld = world;
    };
};

#endif 
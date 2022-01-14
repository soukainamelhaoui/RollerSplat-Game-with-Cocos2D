#include "Level3.h"
#include "PauseMenuScene.h"

#include "Segment.h"


USING_NS_CC;


Scene* Level3::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));


    auto layer = Level3::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Level3::init(){
    if (!Layer::init())
    {
        return false;
    }

    auto dir = Director::getInstance();
    Size visibleSize = dir->getVisibleSize();
    Point origin = dir->getVisibleOrigin();



    auto label = Label::createWithSystemFont("Level 3","fonts/BreeSerif.ttf",30);
    label->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/6)*5 + origin.y));

    this->addChild(label,0);


    // Menu
    auto MenuItem1 = MenuItemFont::create("pause",CC_CALLBACK_1(Level3::Pause,this));
    MenuItem1->setPosition(Vec2(visibleSize.width - 45,visibleSize.height - 10));

    auto* menu = Menu::create(MenuItem1,NULL);
    menu->setPosition(cocos2d::Vec2(0,0));
    this->addChild(menu);

    //Physics
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);



    // creating sprite and its physics body
    float ballScale = 0.2;
    auto daBall = Sprite::create("res/RedBall.png");
    daBall->setScale(ballScale);
    daBall->setName("daBall");

    // get daBall size
    Size ballSize = daBall->getContentSize();
    float radius = ballSize.width;
    Segment empty = Segment();//creating empty segment to get positions
    daBall->setPosition(Vec2(empty.posx4, empty.posy1));
    auto daBallBody = PhysicsBody::createCircle(daBall->getContentSize().width / 2, PhysicsMaterial(0, 0, 0));
    daBall->setPhysicsBody(daBallBody);
    this->addChild(daBall, 1);


    // creating blocks
    auto block = Sprite::create("res/block.png");
    Size blockSize = block->getContentSize();
    block->setScale((radius * ballScale) / blockSize.width);

    // creating maze
    float posx = ((visibleSize.width / 2) - (3 * radius * ballScale)) + origin.x;
    float posy = ((visibleSize.height / 2) - (3 * radius * ballScale)) + origin.y;

    for (int i = 0; i < 20; i++) {
        auto block = Sprite::create("res/block.png");
        block->setPosition(Vec2(posx, posy));
        block->setScale((radius * ballScale) / blockSize.width);
        auto blockBody = PhysicsBody::createBox(block->getContentSize(), PhysicsMaterial(5.0f, 0.0f, 20.0f));
        blockBody->setDynamic(false);
        block->setPhysicsBody(blockBody);
        this->addChild(block);
        if (i < 5) {
            posy += radius * ballScale;
        }
        else if (5 <= i && i < 10) {
            posx += radius * ballScale;
        }
        else if (10 <= i && i < 15) {
            posy -= radius * ballScale;
        }
        else {
            posx -= radius * ballScale;
        }
    }

    //center of maze

   



    return true;
}

void Level3::Pause(cocos2d::Ref* pSender) {

    auto scene = PauseMenu::createScene();
    Director::getInstance()->pushScene(scene);
}
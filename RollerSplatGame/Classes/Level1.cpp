#include "Level1.h"
#include "PauseMenuScene.h"

USING_NS_CC;

Scene* Level1::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    

    auto layer = Level1::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Level1::init(){
    if (!Layer::init())
    {
        return false;
    }

    auto dir = Director::getInstance();
    Size visibleSize = dir->getVisibleSize();
    Point origin = dir->getVisibleOrigin();



    auto label = Label::createWithSystemFont("Level 1","fonts/BreeSerif.ttf",30);
    label->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/6)*5 + origin.y));

    this->addChild(label,0);


    // Menu/Header
    MenuItemFont::setFontName("BreeSerif.ttf");
    
    auto MenuItem1 = MenuItemFont::create("pause",CC_CALLBACK_1(Level1::Pause,this));
    MenuItem1->setPosition(Vec2(visibleSize.width - 45,visibleSize.height - 10));

    auto* menu = Menu::create(MenuItem1,NULL);
    menu->setPosition(cocos2d::Vec2(0,0));
    this->addChild(menu);

    //Trying Physics
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y));
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
    daBall->setPosition(Vec2(((visibleSize.width / 2) - (2 * radius * ballScale)) + origin.x, ((visibleSize.height / 2) - (2 * radius * ballScale)) + origin.y));
    auto daBallBody = PhysicsBody::createCircle(daBall->getContentSize().width/2,PhysicsMaterial(0,0,0));
    daBall->setPhysicsBody(daBallBody);
    this->addChild(daBall, 1);


    // creating blocks
    auto block = Sprite::create("res/block.png");
    Size blockSize = block->getContentSize();
    block->setScale((radius* ballScale) / blockSize.width);
    
    // creating maze
    float posx = ((visibleSize.width/2) - (3*radius*ballScale)) + origin.x;
    float posy = ((visibleSize.height/2) - (3 * radius * ballScale)) + origin.y;

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
        else if(5 <= i && i < 10) {
            posx += radius * ballScale;
        }
        else if(10 <= i && i < 15) {
            posy -= radius * ballScale;
        }
        else{
            posx -= radius * ballScale;
        }
    }

    
    //center of maze

    float posxCenter = posx + (2*radius*ballScale);
    float posyCenter = posy + (2*radius*ballScale);
    for (int i = 0; i < 2; i++) {
        auto block = Sprite::create("res/block.png");
        block->setPosition(Vec2(posxCenter, posyCenter));
        block->setScale((radius * 0.2) / blockSize.width);
        auto blockBody = PhysicsBody::createBox(block->getContentSize(), PhysicsMaterial(5.0f, 0.0f, 20.0f));
        blockBody->setDynamic(false);
        block->setPhysicsBody(blockBody);
        this->addChild(block);
        posxCenter += radius * ballScale;
    }

    float posxCenter2 = posx + (2 * radius * ballScale);
    float posyCenter2 = posy + (3 * radius * ballScale);
    for (int i = 0; i < 2; i++) {
        auto block = Sprite::create("res/block.png");
        block->setPosition(Vec2(posxCenter2, posyCenter2));
        block->setScale((radius * ballScale) / blockSize.width);
        auto blockBody = PhysicsBody::createBox(block->getContentSize(), PhysicsMaterial(5.0f, 0.0f, 20.0f));
        blockBody->setDynamic(false);
        block->setPhysicsBody(blockBody);
        this->addChild(block);
        posxCenter2 += radius * ballScale;
    }

    //test Keyboard
    auto eventListener = EventListenerKeyboard::create();
    auto eventListener2 = EventListenerKeyboard::create();
    auto eventListener3 = EventListenerKeyboard::create();


    /*eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        auto world = _director->getRunningScene()->getPhysicsWorld();
        auto scene = Director::getInstance()->getRunningScene();
        auto trace = DrawNode::create();
        Vec2 loc = event->getCurrentTarget()->getChildByName("daBall")->getPosition();
        Size ballSize = event->getCurrentTarget()->getChildByName("daBall")->getContentSize();
        float radius = ballSize.width;
        float ballScale = 0.2;

        switch (keyCode) {
            // Move Right
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
          
            log("old pos: %f %f", loc.x, loc.y);
            world->setGravity(Vec2(10000, 0));
            loc = event->getCurrentTarget()->getChildByName("daBall")->getPosition();
            log("new pos: %f %f",loc.x,loc.y);
            // drawing traces
            trace->drawSegment(Vec2(loc.x, loc.y), Vec2(loc.x + radius * ballScale * 3, loc.y), (radius * ballScale) / 2, Color4F(Color3B(0, 83, 119)));
            scene->addChild(trace, -99);
            break;
            //Move Left
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            world->setGravity(Vec2(-10000, 0));
            break;
            //Move Up
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            world->setGravity(Vec2(0, 10000));
            break;
            //Move Down
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            world->setGravity(Vec2(0, -10000));
            break;
        }


    };
    */

    eventListener2->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        auto world = _director->getRunningScene()->getPhysicsWorld();
        auto scene = Director::getInstance()->getRunningScene();
        auto trace = DrawNode::create();
        Vec2 loc = event->getCurrentTarget()->getPosition();
        log("z: %d", int(event->getCurrentTarget()->getLocalZOrder()));
        event->getCurrentTarget()->setLocalZOrder(-800);

        switch (keyCode) {
            // Move Right
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            log("old pos: %f %f", loc.x, loc.y);
            world->setGravity(Vec2(10000, 0));
            // drawing traces
            //trace->drawSegment(Vec2(loc.x, loc.y), Vec2(loc.x + radius * ballScale * 3, loc.y), (radius * ballScale) / 2, Color4F(Color3B(0, 83, 119)));
            //scene->addChild(trace, -99);
            break;
           
        }


    };

    eventListener3->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        auto world = _director->getRunningScene()->getPhysicsWorld();
        auto scene = _director->getRunningScene();
        auto trace = DrawNode::create();
        auto ballon = scene->getChildrenCount();
        Vec2 loc = event->getCurrentTarget()->getPosition();
        log("z: %d", int(event->getCurrentTarget()->getLocalZOrder()));
       
        //log("position: %d", ballon);
      


        switch (keyCode) {
            // Move Right
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            log("new pos: %f %f", loc.x, loc.y);

            // drawing traces
            //trace->drawSegment(Vec2(loc.x, loc.y), Vec2(loc.x + radius * ballScale * 3, loc.y), (radius * ballScale) / 2, Color4F(Color3B(0, 83, 119)));
            //scene->addChild(trace, -99);
            break;
        
        }


    };

    //this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this); // daBall is the event recived by eventDispatcher
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener2, daBall);// daBall is the event recived by eventDispatcher
    //log("z: %d", int(daBall->getLocalZOrder()));
   
    //log("z: %d",  int(daBall->getLocalZOrder()));
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener3, daBall); // daBall is the event recived by eventDispatcher




    

    return true;
}

void Level1::Pause(cocos2d::Ref* pSender){
    cocos2d::log("Pause");
    auto scene = PauseMenu::createScene();
    Director::getInstance()->pushScene(scene);
}


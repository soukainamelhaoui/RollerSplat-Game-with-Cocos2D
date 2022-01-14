#include "Level2.h"
#include "PauseMenuScene.h"
#include "Segment.h"


USING_NS_CC;



Scene* Level2::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));


    auto layer = Level2::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

bool Level2::init(){
    if (!Layer::init())
    {
        return false;
    }

    auto dir = Director::getInstance();
    Size visibleSize = dir->getVisibleSize();
    Point origin = dir->getVisibleOrigin();



    auto label = Label::createWithSystemFont("Level 2","fonts/BreeSerif.ttf",30);
    label->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/6)*5 + origin.y));

    this->addChild(label,0);


    // Menu
    MenuItemFont::setFontName("fonts/BreeSerif.ttf");
    
    auto MenuItem1 = MenuItemFont::create("pause",CC_CALLBACK_1(Level2::Pause,this,7.98));
    MenuItem1->setPosition(Vec2(visibleSize.width - 45,visibleSize.height - 10));

    auto* menu = Menu::create(MenuItem1,NULL);
    menu->setPosition(cocos2d::Vec2(0,0));
    this->addChild(menu);

    //Trying Physics
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
    daBall->setPosition(Vec2(empty.posx4,empty.posy1));
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

    float posxCenter = posx + (4 * radius * ballScale);
    float posyCenter = posy + (2 * radius * ballScale);
    for (int i = 0; i < 3; i++) {
        auto block = Sprite::create("res/block.png");
        block->setPosition(Vec2(posxCenter, posyCenter));
        block->setScale((radius * 0.2) / blockSize.width);
        auto blockBody = PhysicsBody::createBox(block->getContentSize(), PhysicsMaterial(5.0f, 0.0f, 20.0f));
        blockBody->setDynamic(false);
        block->setPhysicsBody(blockBody);
        this->addChild(block);
        posxCenter -= radius * ballScale;
    }

    float posxCenter2 = posx + (2 * radius * ballScale);
    float posyCenter2 = posy + (3 * radius * ballScale);
    for (int i = 0; i < 1; i++) {
        auto block = Sprite::create("res/block.png");
        block->setPosition(Vec2(posxCenter2, posyCenter2));
        block->setScale((radius * ballScale) / blockSize.width);
        auto blockBody = PhysicsBody::createBox(block->getContentSize(), PhysicsMaterial(5.0f, 0.0f, 20.0f));
        blockBody->setDynamic(false);
        block->setPhysicsBody(blockBody);
        this->addChild(block);
        posxCenter2 += radius * ballScale;
    }
    
    // Controls
    float flotii = 5.5;
    auto top = MenuItemFont::create("Top", CC_CALLBACK_1(Level2::goTop, this, daBall,this));
    auto right = MenuItemFont::create("Right", CC_CALLBACK_1(Level2::goRight, this, daBall, this));
    auto down = MenuItemFont::create("Down", CC_CALLBACK_1(Level2::goDown, this, daBall, this));
    auto left = MenuItemFont::create("Left", CC_CALLBACK_1(Level2::goLeft, this, daBall, this));
    top->setPosition(Vec2(100, 150));
    right->setPosition(Vec2(150, 100));
    down->setPosition(Vec2(100, 50));
    left->setPosition(Vec2(50, 100));

    auto* controls = Menu::create(top, right, down, left, NULL);
    controls->setPosition(cocos2d::Vec2(0, 0));
    this->addChild(controls);




    return true;
}

void Level2::Pause(cocos2d::Ref* pSender,float test){
    cocos2d::log("Pause: %f",test);
    auto scene = PauseMenu::createScene();
    Director::getInstance()->pushScene(scene);
}

void moveAndApply(float posax,float posay,float posbx,float posby, Node* daBall, Level2* scene) {
    // moving the ball
    auto movement = MoveTo::create(0.2, Vec2(posbx, posby));
    daBall->runAction(movement);
    // drawing the trace
    Size ballSize = daBall->getContentSize();
    float radius = ballSize.width;
    float ballScale = 0.2;
    auto trace = DrawNode::create();
    trace->drawSegment(Vec2(posax, posay), Vec2(posbx, posby), (radius * ballScale) / 2, Color4F(Color3B(0, 83, 119)));
    scene->addChild(trace, -99);
    // create segment icstance
    Segment newSegment = Segment(Vec2(posax, posay), Vec2(posbx, posby));
    // check if segment is alraedy there or reversed
    bool alreadyThere = false;
    for (Segment::segmentIterator = Segment::segmentsList.begin(); Segment::segmentIterator != Segment::segmentsList.end(); Segment::segmentIterator++)
    {
        if (
            int(Segment::segmentIterator->start.x) == int(newSegment.start.x) &&
            int(Segment::segmentIterator->start.y) == int(newSegment.start.y) &&
            int(Segment::segmentIterator->stop.x) == int(newSegment.stop.x) &&
            int(Segment::segmentIterator->stop.y) == int(newSegment.stop.y)
            )
        {
            alreadyThere = true;
            log("already there");
            
        }
        else if (
            int(Segment::segmentIterator->start.x) == int(newSegment.stop.x) &&
            int(Segment::segmentIterator->start.y) == int(newSegment.stop.y) &&
            int(Segment::segmentIterator->stop.x) == int(newSegment.start.x) &&
            int(Segment::segmentIterator->stop.y) == int(newSegment.start.y)
            ) {
            alreadyThere = true;
            log("already ther in reverse");
        }

    }
    // check how many intersections with other segments
    int intersectionCounter = 0;
    for (Segment::segmentIterator = Segment::segmentsList.begin(); Segment::segmentIterator != Segment::segmentsList.end(); Segment::segmentIterator++)
    {

        if (Vec2::isLineIntersect(Segment::segmentIterator->start, Segment::segmentIterator->stop, newSegment.start, newSegment.stop))
        {
            intersectionCounter++;

        }
    }
    // add segment to list but not to coverd distance,
              //at the end number of segments in the vector willl be the number of moves the player made
    Segment::segmentsList.push_back(newSegment);
    // update coverd distance
    if (!alreadyThere)
    {
        Segment::coverdDistance += newSegment.size;
    }
    // check if coverdDistance equal or bigger than target distance, if so the player wins
    log("coverdDistance: %f", Segment::coverdDistance);
    if (int(Segment::coverdDistance) >= 670) {
        Segment::coverdDistance = 0;
        Segment::segmentsList.clear();
        auto scene = PauseMenu::createScene();
        Director::getInstance()->pushScene(scene);
    }
}

void Level2::goTop(Ref* pSender, Node* daBall, Level2* scene) {

    Vec2 loc = daBall->getPosition();
    Segment empty = Segment();
    //posx1,ppsy1
    if (int(loc.x) == int(empty.posx1) && int(loc.y) == int(empty.posy1))
    {
        moveAndApply(loc.x, loc.y, empty.posx1, empty.posy4, daBall, scene);
    }
    //(4,3)->(4,4)
    if (int(loc.y) == int(empty.posy3) && int(loc.x) == int(empty.posx4)) {
        moveAndApply(loc.x, loc.y, empty.posx4, empty.posy4, daBall, scene);
    }
}

void Level2::goRight(cocos2d::Ref* pSender, Node* daBall, Level2* scene) {

    Vec2 loc = daBall->getPosition();
    Segment empty = Segment();

    //1,1
    if (int(loc.x) == int(empty.posx1) && int(loc.y) == int(empty.posy1))
    {
        moveAndApply(loc.x, loc.y, empty.posx4, empty.posy1, daBall, scene);

    }
    //(1,4)
    if (int(loc.x) == int(empty.posx1) && int(loc.y) == int(empty.posy4)) {

        moveAndApply(loc.x, loc.y, empty.posx4, empty.posy4, daBall, scene);

    }


}
void Level2::goDown(cocos2d::Ref* pSender, Node* daBall, Level2* scene) {

    Vec2 loc = daBall->getPosition();
    Segment empty = Segment();

    //(4,4)

    if (int(loc.x) == int(empty.posx4) && int(loc.y) == int(empty.posy4))
    {
        moveAndApply(loc.x, loc.y, empty.posx4, empty.posy3, daBall, scene);

    }
    //(1,4)
    if (int(loc.x) == int(empty.posx1) && int(loc.y) == int(empty.posy4)) {
        moveAndApply(loc.x, loc.y, empty.posx1, empty.posy1, daBall, scene);

    }


}
void Level2::goLeft(cocos2d::Ref* pSender, Node* daBall, Level2* scene) {
    Vec2 loc = daBall->getPosition();
    Segment empty = Segment();

    //(4,4)
    if (int(loc.x) == int(empty.posx4) && int(loc.y) == int(empty.posy4))
    {
        moveAndApply(loc.x, loc.y, empty.posx1, empty.posy4, daBall, scene);

    }
    //(4,1)
    if (int(loc.x) == int(empty.posx4) && int(loc.y) == int(empty.posy1))
    {
        moveAndApply(loc.x, loc.y, empty.posx1, empty.posy1, daBall, scene);

    }
    //(4,3)
    if (int(loc.x) == int(empty.posx4) && int(loc.y) == int(empty.posy3))
    {
        moveAndApply(loc.x, loc.y, empty.posx3, empty.posy3, daBall, scene);

    }

}
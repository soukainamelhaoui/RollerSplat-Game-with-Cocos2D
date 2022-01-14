#include "HelloWorldScene.h"
#include "LevelList.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init(){
    if (!Layer::init())
    {
        return false;
    }

    auto dir = Director::getInstance();
    Size visibleSize = dir->getVisibleSize();
    Point origin = dir->getVisibleOrigin();



    auto label = Label::createWithSystemFont("Ramo's RS","fonts/BreeSerif.ttf",30);
    label->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/6)*5 + origin.y));

    this->addChild(label,0);


    // Menu
    MenuItemFont::setFontName("fonts/BreeSerif.ttf");

    auto MenuItem1 = MenuItemFont::create("Play",CC_CALLBACK_1(HelloWorld::Play,this));
    auto MenuItem2 = MenuItemFont::create("Exit",CC_CALLBACK_1(HelloWorld::Exit,this));
    MenuItem1->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/3)*2 + origin.y));
    MenuItem2->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/3)*1 + origin.y));

    auto* menu = Menu::create(MenuItem1,MenuItem2,NULL);
    menu->setPosition(cocos2d::Vec2(0,0));
    this->addChild(menu);


    // sprite 
    mySprite = Sprite::create("res/Fall (32x32).png");
    mySprite->setPosition(Vec2(100,100));
    mySprite->setScale(3);
    this->addChild(mySprite,1);

    return true;
}

void HelloWorld::Play(cocos2d::Ref* pSender){
    cocos2d::log("Play");
    auto scene = LevelList::createScene();

    Director::getInstance()->pushScene(TransitionSlideInR::create(.3,scene));
}

void HelloWorld::Exit(cocos2d::Ref* pSender){
    cocos2d::log("Exit");
    Director::getInstance()->end();
}


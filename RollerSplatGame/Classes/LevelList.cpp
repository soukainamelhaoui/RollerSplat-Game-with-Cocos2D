#include "LevelList.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

USING_NS_CC;

Scene* LevelList::createScene()
{
    auto scene = Scene::create();
    auto layer = LevelList::create();

    scene->addChild(layer);

    return scene;
}

bool LevelList::init(){
    if (!Layer::init())
    {
        return false;
    }

    auto dir = Director::getInstance();
    Size visibleSize = dir->getVisibleSize();
    Point origin = dir->getVisibleOrigin();



    auto label = Label::createWithSystemFont("Select a Level","fonts/BreeSerif.ttf",30);
    label->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/6)*5 + origin.y));

    this->addChild(label,0);


    // Menu
    MenuItemFont::setFontName("fonts/BreeSerif.ttf");
    
    auto MenuItem1 = MenuItemFont::create("1",CC_CALLBACK_1(LevelList::StartLevel1,this));
    auto MenuItem2 = MenuItemFont::create("2", CC_CALLBACK_1(LevelList::StartLevel2, this));
    auto MenuItem3 = MenuItemFont::create("3",CC_CALLBACK_1(LevelList::StartLevel3,this));
    MenuItem1->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/10)*7 + origin.y));
    MenuItem2->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 10) * 6 + origin.y));
    MenuItem3->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/10)*5 + origin.y));

    auto* menu = Menu::create(MenuItem1,MenuItem2, MenuItem3,NULL);
    menu->setPosition(cocos2d::Vec2(0,0));
    this->addChild(menu);


    return true;
}

void LevelList::StartLevel1(cocos2d::Ref* pSender){
    cocos2d::log("StartLevel1");
    auto scene = Level1::createScene();
    Director::getInstance()->pushScene(scene);
}

void LevelList::StartLevel2(cocos2d::Ref* pSender){
    cocos2d::log("StartLevel2");
    auto scene = Level2::createScene();
    Director::getInstance()->pushScene(TransitionSlideInR::create(.3,scene));
}

void LevelList::StartLevel3(cocos2d::Ref* pSender) {
    cocos2d::log("StartLevel3");
    auto scene = Level3::createScene();
    Director::getInstance()->pushScene(TransitionSlideInR::create(.3, scene));
}


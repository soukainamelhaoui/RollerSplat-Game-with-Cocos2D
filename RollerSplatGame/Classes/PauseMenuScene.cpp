#include "PauseMenuScene.h"
#include "LevelList.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = PauseMenu::create();

    scene->addChild(layer);

    return scene;
}

bool PauseMenu::init(){
    if (!Layer::init())
    {
        return false;
    }

    auto dir = Director::getInstance();
    Size visibleSize = dir->getVisibleSize();
    Point origin = dir->getVisibleOrigin();



    // sprite 
    mySprite = Sprite::create("res/Fall (32x32).png");
    mySprite->setPosition(Vec2(100,100));
    mySprite->setScale(3);
    this->addChild(mySprite,1);
 
    // Menu
    MenuItemFont::setFontName("fonts/BreeSerif.ttf");

    auto MenuItem1 = MenuItemFont::create("Resume",CC_CALLBACK_1(PauseMenu::Resume,this));
    auto MenuItem2 = MenuItemFont::create("Back to Levels", CC_CALLBACK_1(PauseMenu::Levels, this));
    auto MenuItem3 = MenuItemFont::create("Exit",CC_CALLBACK_1(PauseMenu::Exit,this));

    MenuItem1->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 5) * 4 + origin.y));
    MenuItem2->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/5)*3 + origin.y));
    MenuItem3->setPosition(Vec2(visibleSize.width/2 + origin.x,(visibleSize.height/5)*2 + origin.y));

    auto* menu = Menu::create(MenuItem1,MenuItem2,MenuItem3,NULL);
    menu->setPosition(cocos2d::Vec2(0,0));
    this->addChild(menu);

    return true;
}

void PauseMenu::Resume(Ref* pSender){
    cocos2d::log("Resume");
    Director::getInstance()->popScene();
}

void PauseMenu::Levels(Ref* pSender) {
    cocos2d::log("Levels");
    auto scene = LevelList::createScene();

    Director::getInstance()->replaceScene(TransitionSlideInR::create(.3, scene));
}

void PauseMenu::Exit(Ref* pSender){
    cocos2d::log("Exit");
    Director::getInstance()->end();
}
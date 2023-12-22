#ifndef __WARMAP_H__
#define __WARMAP_H__

#include "cocos2d.h"
#include "ShopScene.h"
#define MAX_HERO 18
USING_NS_CC;

class WarMap : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createWarMap();
    
    virtual bool init();

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    Sprite* createHero(int gits);
    void UpGrade();

    void gotoshop(cocos2d::Ref* pSender);

    ShopScene* shopScene;

    CREATE_FUNC(WarMap);

private:

    int fightHerosMap[6][3] = { 0 };
    int fightHerosMap_X;
    int fightHerosMap_y;
    int preFightHerosMap[6] = { 0 };
    int preFightHerosMap_X;
    int touchchose;
    int fightHeronums;
    int allHerosNums[45] = { 0 };
    Sprite* preHero;

    Vector<Sprite*> preHerosMap;
    Vector<Sprite*> fightHeros;
};

#endif // __HELLOWORLD_SCENE_H__#pragma oncence


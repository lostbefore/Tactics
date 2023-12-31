#ifndef __WARMAP_H__
#define __WARMAP_H__

#include "cocos2d.h"
#include "ShopScene.h"
USING_NS_CC;

class WarMap : public cocos2d::Scene
{
public:
    //创建场景
    static cocos2d::Scene* createWarMap();
    //初始化
    virtual bool init();
    //我方生命值
    int myHealth = 100;
    //敌方生命值
    int enemyHealth = 100;
    //点击开始，点击移动，点击结束
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    //依据编号创建对应的英雄
    Sprite* createHero(int gits);
    //英雄升星
    void UpGrade();
    //前往商店
    void gotoshop(cocos2d::Ref* pSender);
    //改变点击状态
    void changLabel(Ref* pSender);
    //进入战斗
    void IntoBattle(float dt);
    //商店界面
    ShopScene* shopScene;

    CREATE_FUNC(WarMap);

private:
    //回合倒计时
    Label* countdownLabel;
    int countdownSeconds;
    void WarMap::updateCountdown(float dt);
    //轮次数
    Label* roundLabel;
    int round = 1;
    //点击状态
    int changAction=1;
    //战斗地图上英雄的x，y坐标
    int fightHerosMap_X;
    int fightHerosMap_y;
    //预战斗区域英雄编号储存
    int preFightHerosMap[6] = { 0 };
    //预战斗区域英雄的x坐标
    int preFightHerosMap_X;
    //点击区域
    int touchchose;
    //战斗区域英雄数量
    int fightHeronums;
    //己方场上所有英雄各个的数量
    int allHerosNums[45] = { 0 };
    //指向预战斗区域英雄指针
    Sprite* preHero;
    //小小英雄
    Sprite* smallHero;
    //储存预战斗区域英雄容器
    Vector<Sprite*> preHerosMap;
    //储存战斗区域英雄容器
    Vector<Sprite*> fightHeros;
};

#endif // __HELLOWORLD_SCENE_H__#pragma oncence


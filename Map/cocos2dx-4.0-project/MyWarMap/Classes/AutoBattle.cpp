#include<iostream>
#include<random>
#include"cocos2d.h"
#include "AutoBattle.h"
#include "ShopScene.h"
#include"Champions.h"
USING_NS_CC;
#define HERO_MAX 10
#define ATTACK_DIS 1.414*64
#define FARATTACK_DIS 1.414*3*64
#define MAX_DISTANCE 1e9
#define SPEED 3.0f
extern int fightHerosMap[6][3];//己方数据
extern int enemyHerosMap[6][3];//敌方数据
int win = -1;//0为己方失败，1为己方胜利
bool myFirst = 0;
//调用方法：
//Scene* BattleScene = AutoBattle::createAutoBattle();
//cocos2d::Director::getInstance()->pushScene(TransitionFade::create(0.5, BattleScene, Color3B(0, 255, 255)));
//战斗结束会自动回退到上一个场景，不需要修改
Scene* AutoBattle::createAutoBattle()
{
    return AutoBattle::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool FindPos(int& x, int& y, bool flag) {
    if (x < 0 || x >= 6 || y < 0 || y >= 3)
        return 0;
    if (flag) {
        x = 5 - x;
        y = 5 - y;
    }
    x = (5 + x) * 64 + 32;
    y = (3 + y) * 64 + 32;
    return 1;
}
bool AutoBattle::init()
{

    if (!Scene::init())
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    Sprite* AutoBattleSprite = Sprite::create("myWarMap.png");
    AutoBattleSprite->setPosition(Vec2(512, 384));
    this->addChild(AutoBattleSprite, 0);
    //初始化地图

    int x, y;
    myList.clear();
    enemyList.clear();
    win = -1;

    //---------------------------------测试
    /*
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            fightHerosMap[i][j] = enemyHerosMap[i][j] = 0;
    AIenemy(3, fightHerosMap);
    AIenemy(3, enemyHerosMap);*/
    //---------------------------------

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (fightHerosMap[i][j] != 0) {
                x = i, y = j;
                if (!FindPos(x, y, 0)) {
                    std::cerr << "position error!\n";
                    return false;
                }
                auto sp = switchCreate(fightHerosMap[i][j], this, x, y);
                myList.push_back(sp);
                sp->setPosition(Vec2(x, y));
                this->addChild(sp, 1);
            }
            if (enemyHerosMap[i][j] != 0) {
                x = i, y = j;
                if (!FindPos(x, y, 1)) {
                    std::cerr << "position error!\n";
                    return false;
                }
                auto sp = switchCreate(enemyHerosMap[i][j], this, x, y);
                enemyList.push_back(sp);
                sp->setPosition(Vec2(x, y));
                this->addChild(enemyList.back(), 1);
            }
        }

    }

    scheduleOnce([=](float dt) {
        this->scheduleUpdate();
        }, 2.0f, "exit_key");

    return true;
}

void AIenemy(int level, int enemyHerosMap[6][3]) {//随机生成敌人
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            enemyHerosMap[i][j] = 0;
    int l = 0, r = 0, t = 0;
    int NumOfHero[46] = { 0 };
    for (int i = 0; i < level * 3 && i < HERO_MAX; i++) {
        int j;
        do
            j = rand() % (level * 3) + 1;
        while (NumOfHero[j] == 2);
        NumOfHero[j]++;
        if (r == 3 && l == 3) {
            if (t == 2)
                return;
            l = r = 0;
            t++;
        }
        if (l < r) {
            enemyHerosMap[2 - l][t] = j;
            l++;
        }
        else {
            enemyHerosMap[3 + r][t] = j;
            r++;
        }
    }
}
float DistanceCalc(Vec2 a, Vec2 b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void AutoBattle::update(float dt) {
    if (win != -1) {
        unscheduleUpdate();
        //本场战斗结束，胜利/失败
        scheduleOnce([=](float dt) {
            Director::getInstance()->popScene();
            }, 2.0f, "exit_key");
        return;
    }
    if (myFirst == 1) {
        Attack(myList, enemyList);
        if (enemyList.empty()) {
            win = 1;
            return;
        }
    }

    Attack(enemyList, myList);
    if (myList.empty()) {
        win = 0;
        return;
    }
    if (myFirst == 0) {
        Attack(myList, enemyList);
        if (enemyList.empty()) {
            win = 1;
            return;
        }
    }

}
void AutoBattle::Attack(list<Champion*>& myList, list<Champion*>& enemyList) {


    for (auto myIt = myList.begin(); myIt != myList.end(); myIt++) {
        if (enemyList.empty())
            return;
        Champion* myHero = *myIt;
        auto aimIt = enemyList.end();
        float minDis = MAX_DISTANCE, nowDis = MAX_DISTANCE;
        Vec2 myPos;
        Vec2 enemyPos;
        myPos = myHero->getPosition();
        for (auto enemyIt = enemyList.begin(); enemyIt != enemyList.end(); enemyIt++) {
            enemyPos = (*enemyIt)->getPosition();
            nowDis = DistanceCalc(myPos, enemyPos);
            if (nowDis < minDis) {
                minDis = nowDis;
                aimIt = enemyIt;
            }
        }
        const Vec2 aimPos = (*aimIt)->getPosition();

        if (nowDis <= ATTACK_DIS || myHero->AttackDistance == 0 && nowDis <= FARATTACK_DIS) {
            if (myHero->canAttack()) {
                (*aimIt)->GetDamage(myHero->AttackDamage());
                myHero->playMeleeAttackAnimation();
                if ((*aimIt)->Death()) {
                    (*aimIt)->removeChild(this);
                    enemyList.erase(aimIt);
                }
            }/**/
        }
        else {
            Vec2 next = (enemyPos - myPos) / 2;
            next.normalize();
            auto t = next * SPEED + myPos;
            if (!(t.x >= 5 * 64 + 32 && t.x <= 10 * 64 + 32 && t.y >= 3 * 64 + 32 && t.y <= 8 * 64 + 32))
                exit(-1);
            myHero->setPosition(t);
            myPos = myHero->getPosition();
        }
    }
}